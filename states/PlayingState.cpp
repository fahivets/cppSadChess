#include "stdafx.h"
#include "PlayingState.h"
#include "../MainGame.h"

PlayingState::PlayingState(MainGame& rGame) : State(rGame)
{
	initStateResources();
	createStateEntitys();
	playMusic();
}

PlayingState::~PlayingState()
{}

void PlayingState::endState()
{

}

void PlayingState::handleInput(const InputManager& input)
{
	if (input.keyDown(SDL_SCANCODE_ESCAPE))
	{
		ResourceHolder::get().audio.stopMusic();
		ResourceHolder::get().audio.playMusic("start.mp3");
		needPop(true);
	}
	if (input.mouseButtonPressed(LEFT))
	{
		auto& boards(m_entityManager.getEntitiesByGroup(GBoard));
		for (auto& board : boards)
		{
			auto& boardBox(board->getComponent<CBox>());
			if (boardBox.pointInRect(input.mousePos(), boardBox.m_fRect))
			{
				handleMouseIventOnBoard(input);
			}
		}	
	}
	if (input.mouseButtonPressed(RIGHT))
	{
		m_currFigureID = -1;
		for (auto& id : m_validMove)
		{
			m_board[id.first].legalMove = false;
		}
	}

	m_entityManager.handleInput(input);
}

void PlayingState::update(const float& deltaTime)
{
	m_entityManager.refresh();
	m_entityManager.update(deltaTime);

	//Update board
	for (auto& cell : m_board)
	{
		//Update cells color
		auto& rect(cell.entity->getComponent<CRect>());
		if (cell.legalMove)
			rect.m_color = cell.validMoveColor;
		else
			rect.m_color = cell.basicColor;
		//Update figures and figuresOnBoard status
		if (cell.figure)
		{
			auto& type(cell.figure->getComponent<CFigureType>());
			m_figuresOnBoard[cell.id] = type.getType();

			//Update map ofr validation
			if (cell.figure->hasGroup(GWFigures))
			{
				m_mapForValidation[cell.id] = 1;
			}
			else if (cell.figure->hasGroup(GBFigures))
			{
				m_mapForValidation[cell.id] = 0;
			}
			//Update figures position
			auto& figurePos(cell.figure->getComponent<CPosition>());
			auto& cellPos(cell.entity->getComponent<CPosition>());
			figurePos.m_position = cellPos.m_position;
		}
		else
		{
			m_figuresOnBoard[cell.id] = FigureType::NONE;
			m_mapForValidation[cell.id] = -1;
		}
	}
}

void PlayingState::render(SDL_Renderer& rRender)
{
	m_entityManager.render(rRender);
}

void PlayingState::handleMouseIventOnBoard(const InputManager& input)
{
	for (auto& cell : m_board)
	{
		auto& box(cell.entity->getComponent<CBox>());
		if (box.pointInRect(input.mousePos(), box.m_fRect))
		{
			if (cell.figure && m_currFigureID == -1)
			{
				if (m_whiteMove && cell.figure->hasGroup(GWFigures) || !m_whiteMove && cell.figure->hasGroup(GBFigures))
				{
					m_currFigureID = cell.id;
					
					auto& testMove(cell.figure->getComponent<CMove>());
					m_validMove = testMove.getLegalMove(cell.id, m_mapForValidation, m_figuresOnBoard);
					
					for (auto& id : m_validMove)
					{
						m_board[id.first].legalMove = true;
					}
				}
				else
					ResourceHolder::get().audio.playSound("meow.ogg", 0, 0, 42);
			}
			else if (cell.figure && m_currFigureID == cell.id)
			{
				m_currFigureID = -1;
				for (auto& id : m_validMove)
				{
					m_board[id.first].legalMove = false;
				}
			}
			else if (m_currFigureID != -1)
			{
				if (cell.legalMove)
				{
					if (cell.figure)
					{
						cell.figure->destroy();
						cell.figure = nullptr;
					}
					cell.figure = m_board[m_currFigureID].figure;
					m_board[m_currFigureID].figure = nullptr;
					m_currFigureID = -1;
					for (auto& id : m_validMove)
					{
						m_board[id.first].legalMove = false;
					}
					m_whiteMove = (m_whiteMove == true) ? (false) : (true);
				}
				else
				{
					for (auto& id : m_validMove)
					{
						m_board[id.first].legalMove = false;
					}
					m_currFigureID = -1;
					ResourceHolder::get().audio.playSound("404_sound.wav", 0, 1);
				}
				m_currFigureID = -1;
			}
		}
	}
}

//Private functions
void PlayingState::initStateResources()
{
	//Load textures
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "bg_game.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "whitePawn.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "whiteRook.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "whiteKnight.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "whiteBishop.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "whiteQueen.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "whiteKing.png");

	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "blackPawn.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "blackRook.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "blackKnight.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "blackBishop.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "blackQueen.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "blackKing.png");

	//Load audio
	ResourceHolder::get().audio.setMusic("game_1.mp3");
	ResourceHolder::get().audio.setMusic("game_2.mp3");
	ResourceHolder::get().audio.setSound("404_sound.wav");
	ResourceHolder::get().audio.setSound("meow.ogg");
}

void PlayingState::createStateEntitys()
{
	Vector2f windowSize{ static_cast<float>(m_pGame->getWinWidth()), static_cast<float>(m_pGame->getWinHeigth()) };
	std::string textureName{ "bg_game.png" };
	
	createBackgroundEntity({ windowSize.x / 2.0f, windowSize.y / 2.0f },
		windowSize,
		textureName);

	createBoard();
}

void PlayingState::createBoard()
{
	Vector2f boardPos{
		static_cast<float>(m_pGame->getWinWidth()) / 2.0f,
		static_cast<float>(m_pGame->getWinHeigth()) / 2.0f
	};
	createBoardEntity(boardPos, { BOARD_DEFAULT::WIDTH, BOARD_DEFAULT::HEIGTH });
	createCells();
	createFigures();
}

void PlayingState::createCells()
{
	auto& boards(m_entityManager.getEntitiesByGroup(GBoard));
	for (auto& board : boards)
	{
		auto& boardBox(board->getComponent<CBox>());
		//Cells values
		Vector2f cellSize{ CELL_SIZE_DEFAULT::WIDTH, CELL_SIZE_DEFAULT::HEIGTH };
		SDL_Color cellBlackColor{ 0, 153, 76, 255 };
		SDL_Color cellWhiteColor{ 192, 192, 192, 255 };
		SDL_Color cellValidBlackColor{ 255, 51, 51, 255 };
		SDL_Color cellValidWhiteColor{ 255, 102, 102, 255 };
		Vector2f startPos{
			boardBox.x() - (cellSize.x / 2.0f),
			(boardBox.y() + boardBox.h()) + (cellSize.y / 2.0f)
		};

		int row = 1;
		for (int i = 0; i < 64; ++i)
		{
			m_board[i].id = i;

			//Set cell position
			if (i % 8 == 0)
			{
				startPos.y -= cellSize.y;
				startPos.x = boardBox.x() + cellSize.x / 2.0f;
				row++;
				std::swap(cellBlackColor, cellWhiteColor);
				std::swap(cellValidBlackColor, cellValidWhiteColor);
			}
			else
			{
				startPos.x += cellSize.x;
			}

			//Set cell color
			if (i % 2 == 0)
			{
				m_board[i].basicColor = cellWhiteColor;
				m_board[i].validMoveColor = cellValidWhiteColor;
			}
			else
			{
				m_board[i].basicColor = cellBlackColor;
				m_board[i].validMoveColor = cellValidBlackColor;
			}

			//Create cell entity
			m_board[i].entity = &createCellEntity(startPos, cellSize, m_board[i].basicColor);
			m_mapForValidation[i] = 0;
		}
	}
}

void PlayingState::createFigures()
{
	createWhiteFigures();
	createBlackFigures();
}

void PlayingState::createWhiteFigures()
{
	FigureType figureType{ FigureType::NONE };
	for (size_t i = 0; i <= 15 ; ++i)
	{
		auto& box(m_board[i].entity->getComponent<CBox>());
		std::string textureName{"white"};

		if (i >= 8 && i <= 15)
		{
			figureType = FigureType::Pawn;
			textureName += "Pawn.png";
		}
		else if (i == 0 || i == 7)
		{
			figureType = FigureType::Rook;
			textureName += "Rook.png";
		}
		else if (i == 1 || i == 6)
		{
			figureType = FigureType::Knight;
			textureName += "Knight.png";
		}
		else if (i == 2 || i == 5)
		{
			figureType = FigureType::Bishop;
			textureName += "Bishop.png";
		}
		else if (i == 3)
		{
			figureType = FigureType::Queen;
			textureName += "Queen.png";
		}
		else
		{
			figureType = FigureType::King;
			textureName += "King.png";
		}

		m_board[i].figure = &createFigureEntity(
			Vector2f{ box.xCenter(), box.yCenter() },
			Vector2f{ box.w(), box.h() },
			textureName,
			PlayingStateGroup::GWFigures, 
			figureType);
	}
}

void PlayingState::createBlackFigures()
{
	FigureType figureType{ FigureType::NONE };
	for (size_t i = 48; i <= 63; ++i)
	{
		auto& box(m_board[i].entity->getComponent<CBox>());
		std::string textureName{ "black" };

		if (i >= 48 && i <= 55)
		{
			figureType = FigureType::Pawn;
			textureName += "Pawn.png";
		}
		else if (i == 56 || i == 63)
		{
			figureType = FigureType::Rook;
			textureName += "Rook.png";
		}
		else if (i == 57 || i == 62)
		{
			figureType = FigureType::Knight;
			textureName += "Knight.png";
		}
		else if (i == 58 || i == 61)
		{
			figureType = FigureType::Bishop;
			textureName += "Bishop.png";
		}
		else if (i == 59)
		{
			figureType = FigureType::Queen;
			textureName += "Queen.png";
		}
		else
		{
			figureType = FigureType::King;
			textureName += "King.png";
		}

		m_board[i].figure = &createFigureEntity(
			Vector2f{ box.xCenter(), box.yCenter() },
			Vector2f{ box.w(), box.h() },
			textureName,
			PlayingStateGroup::GBFigures,
			figureType);
	}
}

void PlayingState::playMusic()
{
	if (!Mix_PlayingMusic())
		ResourceHolder::get().audio.playMusic("game_1.mp3");
}

//Entity factory
Entity& PlayingState::createBackgroundEntity(const Vector2f& rPosition, const Vector2f& rSize, const std::string& textureName)
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<CPosition>(rPosition);
	entity.addComponent<CBox>(Vector2f{ rSize.x, rSize.y });
	entity.addComponent<CTexture>(m_pGame->getRenderer(), textureName.c_str());
	entity.addGroup(PlayingStateGroup::GBackground);

	return (entity);
}

Entity& PlayingState::createBoardEntity(const Vector2f& rPosition, const Vector2f& rSize)
{
	auto& entity(m_entityManager.addEntity());
	entity.addComponent<CPosition>(rPosition);
	entity.addComponent<CBox>(Vector2f{ rSize.x, rSize.y });
	entity.addGroup(PlayingStateGroup::GBoard);

	return (entity);
}

Entity& PlayingState::createCellEntity(const Vector2f& rPosition, const Vector2f& rSize, const SDL_Color& color)
{
	auto& entity(m_entityManager.addEntity());
	entity.addComponent<CPosition>(rPosition);
	entity.addComponent<CBox>(Vector2f{ rSize.x, rSize.y });
	entity.addComponent<CRect>(color);
	entity.addGroup(PlayingStateGroup::GCells);

	return (entity);
}

Entity& PlayingState::createFigureEntity(const Vector2f& rPosition, const Vector2f& rSize,
		const std::string& textureName, PlayingStateGroup group, FigureType figureType)
{
	bool isWhite = (group == PlayingStateGroup::GWFigures) ? (true) : (false);
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<CPosition>(rPosition);
	entity.addComponent<CBox>(Vector2f{ rSize.x, rSize.y });
	entity.addComponent<CFigureType>(isWhite, figureType);
	entity.addComponent<CMove>();
	entity.addComponent<CTexture>(m_pGame->getRenderer(), textureName.c_str());
	entity.addGroup(PlayingStateGroup::GFigures);
	entity.addGroup(group);

	return (entity);
}
