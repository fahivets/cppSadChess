#ifndef STARTSTATE_H_INCLUDED
#define STARTSTATE_H_INCLUDED
#include "State.h"

// ECS includes
#include "ecs/Entity.h"
#include "managers/EntityManager.h"

class StartState : public State
{
public:
	//Enum for groups to keep track entities
	enum StartStateGroup : std::size_t
	{
		GBackground,
		GButton
	};

	//Constructors/Destructors
	StartState(MainGame& rGame);
	virtual ~StartState();

	//Functions
	void endState() override;
	void handleInput(const InputManager& input) override;
	void update(const float& deltaTime) override;
	void render(SDL_Renderer& rRender) override;

private:
	//Private functions
	void initStateResources();
	void createStateEntitys();
	void createStateButtons();
	void playMusic();

	ButtonTextureArray setButtonTextureArray(const std::string& buttonName, const std::string& fontName, int fontSize);

	//Entity factory
	Entity& createButton(const Vector2f& rPosition, const Vector2f& rSize, const ButtonTextureArray& buttonTextures, std::function<void(void)> function = nullptr);
	Entity& createBackground(const Vector2f& rPosition, const Vector2f& rSize, const std::string& textureName);
	
private:
	EntityManager m_entityManager;
};

#endif	/* end STARTSTATE_H_INCLUDED */