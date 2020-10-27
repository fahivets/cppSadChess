#include "stdafx.h"
#include "CUIButton.h"
#include "Entity.h"

CUIButton::CUIButton(SDL_Renderer& rRenderer, const TextureNameArray& rTextureNameArray)
{
	ResourceHolder::get().textures.set(rRenderer, rTextureNameArray[ButtonState::NORMAL]);
	ResourceHolder::get().textures.set(rRenderer, rTextureNameArray[ButtonState::HOVER]);
	ResourceHolder::get().textures.set(rRenderer, rTextureNameArray[ButtonState::PRESSED]);

	m_buttonTextureArray[ButtonState::NORMAL] = ResourceHolder::get().textures.get(rTextureNameArray[ButtonState::NORMAL]);
	m_buttonTextureArray[ButtonState::HOVER] = ResourceHolder::get().textures.get(rTextureNameArray[ButtonState::HOVER]);
	m_buttonTextureArray[ButtonState::PRESSED] = ResourceHolder::get().textures.get(rTextureNameArray[ButtonState::PRESSED]);
}

CUIButton::CUIButton(const ButtonTextureArray& buttonTextureArray)
{
	m_buttonTextureArray = buttonTextureArray;
}

void CUIButton::init()
{
	m_pBoxComp = &m_entity->getComponent<CBox>();
	m_buttonsSize[ButtonState::NORMAL] =
		ResourceHolder::get().textures.queryTexture(m_buttonTextureArray[ButtonState::NORMAL]);
	m_buttonsSize[ButtonState::HOVER] =
		ResourceHolder::get().textures.queryTexture(m_buttonTextureArray[ButtonState::HOVER]);
	m_buttonsSize[ButtonState::PRESSED] =
		ResourceHolder::get().textures.queryTexture(m_buttonTextureArray[ButtonState::PRESSED]);
	setTrueButtonBoxSize();
}

void CUIButton::render(SDL_Renderer& rRender)
{
	SDL_RenderCopyF(&rRender, m_buttonTextureArray[m_currentState], 0, &m_pBoxComp->m_fRect);
}

void CUIButton::update(const float& deltaTime)
{
	setTrueButtonBoxSize();
}

void CUIButton::handleInput(const InputManager& input)
{
	Vector2f mousePos = input.mousePos();
	SDL_Point point = { static_cast<int>(mousePos.x), static_cast<int>(mousePos.y) };
	SDL_Rect rect = {
		static_cast<int>(m_pBoxComp->m_fRect.x),
		static_cast<int>(m_pBoxComp->m_fRect.y),
		static_cast<int>(m_pBoxComp->m_fRect.w),
		static_cast<int>(m_pBoxComp->m_fRect.h)
	};

	if (m_pBoxComp->pointInRect(point, rect))
	{
		if (input.mouseButtonPressed(LEFT) && !input.mouseButtonReleased(LEFT))
		{
			m_currentState = ButtonState::PRESSED;
		}
		else if (input.mouseButtonReleased(LEFT))
		{
			m_currentState = ButtonState::PRESSED;
			m_function();
		}
		else if (!input.mouseButtonDown(LEFT))
		{
			m_currentState = ButtonState::HOVER;
		}
	}
	else
	{
		m_currentState = ButtonState::NORMAL;
	}
}

void CUIButton::setFunction(std::function<void(void)> function)
{
	m_function = function;
}

void CUIButton::setTrueButtonBoxSize()
{
	if (m_pBoxComp != nullptr)
	{
		m_pBoxComp->m_fRect.w = m_buttonsSize[m_currentState].x;
		m_pBoxComp->m_fRect.h = m_buttonsSize[m_currentState].y;
	}
}

const ButtonState& CUIButton::getButtonState() const
{
	return (m_currentState);
}