#ifndef CMOVE_H_INCLUDED
#define CMOVE_H_INCLUDED
#include "Component.h"
#include "CFigureType.h"

struct CMove : public Component
{
	//Constructor/Destructor
	CMove();
	~CMove() = default;
	
	//Functions
	void init() override;
	
	std::map<int, bool> getLegalMove(const int currCell, const std::map<int, int>& board, const std::map<int, FigureType>& figureOnBoard);
	std::map<int, bool> findValidPawnMoves(const int currCell, const std::map<int, int>& board);
	std::map<int, bool> findValidKnightMoves(const int currCell, const std::map<int, int>& board);
	std::map<int, bool> findValidBishopRookQueenKingMoves(const int currCell, const std::map<int, int>& board, const std::map<int, FigureType>& figureOnBoard);
	
	bool isValid(int x, int y) const noexcept;
	bool isOccupied(int x, int y, const std::map<int, int>& board) const noexcept;
	
	//Members
	CFigureType* m_pFTypeComp{ nullptr };
};

#endif /* end CMOVE_H_INCLUDED */