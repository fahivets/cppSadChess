#ifndef CUIBUTTON_H_INCLUDED
#define CUIBUTTON_H_INCLUDED
#include "Component.h"
#include "CBox.h"

using TextureNameArray = std::array<const char*, 3>;
using ButtonTextureArray = std::array<SDL_Texture*, 3>;
using TextureBoxSizeArray = std::array<Vector2f, 3>;

enum ButtonState
{
	NORMAL = 0,
	HOVER = 1,
	PRESSED = 2
};

struct CUIButton : public Component
{
	//Constructor/Destructor
	CUIButton(SDL_Renderer& rRenderer, const TextureNameArray& buttonTextureArray);
	CUIButton(const ButtonTextureArray& buttonTextureArray);
	~CUIButton() = default;

	//Functions
	void init() override;
	void render(SDL_Renderer& rRender) override;
	void update(const float& deltaTime) override;
	void handleInput(const InputManager& input) override;
	void setFunction(std::function<void(void)> function);
	void setTrueButtonBoxSize();
	const ButtonState& getButtonState() const;

	//Members
	CBox* m_pBoxComp{ nullptr };
	ButtonTextureArray m_buttonTextureArray;
	ButtonState m_currentState{ ButtonState::NORMAL };
	TextureBoxSizeArray m_buttonsSize;
	std::function<void(void)> m_function = []() {};
};

#endif	/* end CUIBUTTON_H_INCLUDED */