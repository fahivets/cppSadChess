#include "stdafx.h"
#include "StartState.h"
#include "../MainGame.h"
#include "PlayingState.h"

//Constructors/Destructors
StartState::StartState(MainGame& rGame)
	: State(rGame)
{
	initStateResources();
	createStateEntitys();
	playMusic();
}

StartState::~StartState()
{
}

//Functions
void StartState::endState()
{
	ResourceHolder::get().audio.stopMusic();
}

void StartState::handleInput(const InputManager& input)
{
	if (input.keyDown(SDL_SCANCODE_Q))
	{
		needPop(true);
	}
	if (input.keyDown(SDL_SCANCODE_RETURN))
	{
		ResourceHolder::get().audio.stopMusic();
		m_pGame->pushState<PlayingState>(*m_pGame);
	}

	m_entityManager.handleInput(input);
}

void StartState::update(const float& deltaTime)
{
	m_entityManager.refresh();
	m_entityManager.update(deltaTime);
}

void StartState::render(SDL_Renderer& rRender)
{
	m_entityManager.render(rRender);
}

//Private functions
void StartState::initStateResources()
{
	//Load textures
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "sad_cat.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "bg_menu.png");

	//Load audio
	ResourceHolder::get().audio.setMusic("start.mp3");
	ResourceHolder::get().audio.setSound("meow.ogg");
}

void StartState::createStateEntitys()
{
	Vector2f windowSize{ static_cast<float>(m_pGame->getWinWidth()), static_cast<float>(m_pGame->getWinHeigth()) };
	std::string textureName{ "bg_menu.png" };
	createBackground({windowSize.x / 2.0f, windowSize.y / 2.0f},
		windowSize,
		textureName);

	createStateButtons();
}

void StartState::createStateButtons()
{
	Vector2f windowSize{ static_cast<float>(m_pGame->getWinWidth()), static_cast<float>(m_pGame->getWinHeigth()) };
	std::string fontName{ "basic.ttf" };
	int fontSize{ 42 };
	
	//Play Button Param
	ButtonTextureArray startButtonTextures{ setButtonTextureArray("Play", fontName, fontSize) };
	Vector2f startButtonPos = { windowSize.x / 2, windowSize.y * 0.7f };
	Vector2f startButtonSize = ResourceHolder::get().textures.queryTexture(startButtonTextures[0]);
	std::function<void(void)> startButtonFunc = [&]() -> void
	{
		ResourceHolder::get().audio.stopMusic();
		m_pGame->pushState<PlayingState>(*m_pGame);
	};

	//Options Button Param
	ButtonTextureArray optionsButtonTextures{ setButtonTextureArray("Settings", fontName, fontSize) };
	Vector2f optionsButtonPos = { windowSize.x / 2, windowSize.y * 0.8f };
	Vector2f optionsButtonSize = ResourceHolder::get().textures.queryTexture(optionsButtonTextures[0]);
	std::function<void(void)> optionsButtonFunc = [&]() -> void
	{
		//ResourceHolder::get().audio.playSound("404_sound.wav", 0, 0, 42);
		ResourceHolder::get().audio.playSound("meow.ogg", 0, 0, 42);
		std::cout << "Settings in progress ^_^" << "\n";
	};

	//Quit Button Param
	ButtonTextureArray exitButtonTextures{ setButtonTextureArray("Quit", fontName, fontSize) };
	Vector2f exitButtonPos = { windowSize.x / 2, windowSize.y * 0.9f };
	Vector2f exitButtonSize = ResourceHolder::get().textures.queryTexture(exitButtonTextures[0]);
	std::function<void(void)> exitButtonFunc = [&]() -> void
	{
		ResourceHolder::get().audio.stopMusic();
		needPop(true);
	};

	createButton(startButtonPos, startButtonSize, startButtonTextures, startButtonFunc);
	createButton(optionsButtonPos, optionsButtonSize, optionsButtonTextures, optionsButtonFunc);
	createButton(exitButtonPos, exitButtonSize, exitButtonTextures, exitButtonFunc);
}

void StartState::playMusic()
{
	if (!Mix_PlayingMusic())
		ResourceHolder::get().audio.playMusic("start.mp3");
}

ButtonTextureArray StartState::setButtonTextureArray(const std::string& buttonName, const std::string& fontName, int fontSize)
{
	return {
		ResourceHolder::get().fonts.getText(m_pGame->getRenderer(), buttonName, fontName, fontSize, {0, 0, 0}),
		ResourceHolder::get().fonts.getText(m_pGame->getRenderer(), buttonName, fontName, fontSize - 1, {200, 100, 0}),
		ResourceHolder::get().fonts.getText(m_pGame->getRenderer(), buttonName, fontName, fontSize + 1, {200, 0, 0})
	};
}

Entity& StartState::createButton(const Vector2f& rPosition, const Vector2f& rSize, const ButtonTextureArray& buttonTextures, std::function<void(void)> function)
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<CPosition>(rPosition);
	entity.addComponent<CBox>(rSize);
	entity.addComponent<CUIButton>(buttonTextures);
	auto& button(entity.getComponent<CUIButton>());
	button.setFunction(function);

	entity.addGroup(StartStateGroup::GButton);
	return (entity);
}

Entity& StartState::createBackground(const Vector2f& rPosition, const Vector2f& rSize, const std::string& textureName)
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<CPosition>(rPosition);
	entity.addComponent<CBox>(Vector2f{ rSize.x, rSize.y });
	entity.addComponent<CTexture>(m_pGame->getRenderer(), textureName.c_str());
	entity.addGroup(StartStateGroup::GBackground);

	return (entity);
}
