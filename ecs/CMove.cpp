#include "stdafx.h"
#include "CMove.h"
#include "Entity.h"

CMove::CMove()
{}

void CMove::init()
{
	m_pFTypeComp = &m_entity->getComponent<CFigureType>();
}

std::map<int, bool> CMove::getLegalMove(const int currCell, const std::map<int, int>& board, const std::map<int, FigureType>& figureOnBoard)
{
	std::map<int, bool> validMove;
	FigureType type = m_pFTypeComp->getType();

	switch (type)
	{
		case Pawn:
			validMove = findValidPawnMoves(currCell, board);
			break;

		case Knight:
			validMove = findValidKnightMoves(currCell, board);
			break;

		case Rook:
		case Bishop:
		case Queen:
		case King:
			validMove = findValidBishopRookQueenKingMoves(currCell, board, figureOnBoard);
			break;

		case NONE:
			break;
		default:
			break;
	}
	
	return (validMove);
}

std::map<int, bool> CMove::findValidPawnMoves(const int currCell, const std::map<int, int>& board)
{
	std::map<int, bool> validMove;
	const int step = (m_pFTypeComp->isWhite() == true) ? (1) : (-1);
	const int x = currCell % 8;
	const int y = currCell / 8;
	int newX = x;
	int newY = y + step;
	
	if (isValid(newX, newY) && !isOccupied(newX, newY, board))
	{
		validMove[(newX)+ 8 * (newY)] = true;

		//Try make first move
		newY = y + 2 * step;
		if (!m_pFTypeComp->isMoved() && !isOccupied(newX, newY, board))
			validMove[(newX)+8 * (newY)] = true;
	}
	//Try to capture
	const int delta[2][2] = { {1, step}, {-1, step} };
	for (int i = 0; i < 2; ++i)
	{
		newX = x + delta[i][0];
		newY = y + delta[i][1];
		if (isValid(newX, newY))
		{
			if (isOccupied(newX, newY, board) && board.at((newX)+8 * (newY)) != board.at(currCell))
			{
				validMove[(newX)+8 * (newY)] = true;
			}
		}
	}

	return (validMove);
}

std::map<int, bool> CMove::findValidKnightMoves(const int currCell, const std::map<int, int>& board)
{
	std::map<int, bool> validMove;
	const int x = currCell % 8;
	const int y = currCell / 8;
	const int delta[8][2] = { {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2} };

	for (int i = 0; i < 8; ++i)
	{
		const int newX = x + delta[i][0];
		const int newY = y + delta[i][1];
		if (isValid(newX, newY))
		{
			if (!isOccupied(newX, newY, board) || board.at((newX)+8 * (newY)) != board.at(currCell))
			{
				validMove[(newX)+8 * (newY)] = true;
			}
		}
	}

	return (validMove);
}

std::map<int, bool> CMove::findValidBishopRookQueenKingMoves(const int currCell, const std::map<int, int>& board, const std::map<int, FigureType>& figureOnBoard)
{
	std::map<int, bool> validMove;
	const int x = currCell % 8;
	const int y = currCell / 8;

	const int delta[8][2] = { {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1} };
	bool dirValid[8] = { true, true, true, true, true, true, true, true };
	const int distMax = (m_pFTypeComp->getType() == King) ? 1 : 7;

	if (m_pFTypeComp->getType() == Bishop)
	{
		dirValid[0] = dirValid[2] = dirValid[4] = dirValid[6] = false;
	}
	else if (m_pFTypeComp->getType() == Rook)
	{
		dirValid[1] = dirValid[3] = dirValid[5] = dirValid[7] = false;
	}

	for (int dir = 0; dir < 8; ++dir)
	{
		if (dirValid[dir])
		{
			for (int dist = 1; dist <= distMax; ++dist)
			{
				const int newX = x + dist * delta[dir][0];
				const int newY = y + dist * delta[dir][1];


				if (!isValid(newX, newY))
					break;

				if (!isOccupied(newX, newY, board) || board.at((newX)+8 * (newY)) != board.at(currCell))
				{
					validMove[(newX)+8 * (newY)] = true;
				}
				if (isOccupied(newX, newY, board))
					break;
			}
		}
	}
	//TODO: BAG -> Stack overflow => need to change architecture and data transfer method.
	/*
	if (m_pFTypeComp->getType() == King)
	{
		std::map<int, bool> castlingMove = tryCastlings(currCell, board, figureOnBoard);
		for(auto& cMove : castlingMove)
		{
			if (cMove.second)
				validMove[cMove.first] = true;
		}
	}
	*/
	return (validMove);
}

bool CMove::isValid(int x, int y) const noexcept
{
	if (x < 0 || y < 0 || x >= 8 || y >= 8)
		return (false);
	return (true);
}

bool CMove::isOccupied(int x, int y, const std::map<int, int>& board) const noexcept
{
	if (isValid(x, y))
	{
		if (board.at(x + y * 8) != -1)
		{
			return (true);
		}
	}
	return (false);
}