#ifndef PLAYINGSTATE_H_INCLUDED
#define PLAYINGSTATE_H_INCLUDED
#include "State.h"

//ECS include
#include "ecs/Entity.h"
#include "managers/EntityManager.h"

class PlayingState : public State
{
public:
	//Enum for groups to keep track entities
	enum PlayingStateGroup : std::size_t
	{
		GBackground,
		GBoard,
		GCells,
		GFigures,
		GWFigures,
		GBFigures
	};
	
	struct Cell
	{
		size_t id{ 0 };
		Entity* entity{ nullptr };
		Entity* figure{ nullptr };
		SDL_Color basicColor{ 0 };
		SDL_Color validMoveColor{ 0 };
		bool legalMove{ false };
	};

	//Constructors/Destructors
	PlayingState(MainGame& rGame);
	virtual ~PlayingState();

	//Functions
	void endState() override;
	void handleInput(const InputManager& input) override;
	void update(const float& deltaTime) override;
	void render(SDL_Renderer& rRender) override;
	void handleMouseIventOnBoard(const InputManager& input);

private:
	//Private functions
	void initStateResources();
	void createStateEntitys();
	void createBoard();
	void createCells();
	void createFigures();
	void createWhiteFigures();
	void createBlackFigures();
	void playMusic();

	//Entity factory
	Entity& createBackgroundEntity(const Vector2f& rPosition, const Vector2f& rSize, const std::string& textureName);
	Entity& createBoardEntity(const Vector2f& rPosition, const Vector2f& rSize);
	Entity& createCellEntity(const Vector2f& rPosition, const Vector2f& rSize, const SDL_Color& color);
	Entity& createFigureEntity(const Vector2f& rPosition, const Vector2f& rSize, const std::string& textureName,
			PlayingStateGroup group, FigureType figureType);
	

private:
	EntityManager m_entityManager;
	std::array<Cell, 64> m_board;
	std::map<int, FigureType> m_figuresOnBoard;
	std::map<int, int> m_mapForValidation;
	std::map<int, bool> m_validMove;
	int m_currFigureID{ -1 };
	bool m_whiteMove{ true };
};

#endif /* end PLAYINGSTATE_H_INCLUDED */