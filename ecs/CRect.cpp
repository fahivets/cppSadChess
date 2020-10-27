#include "stdafx.h"
#include "CRect.h"
#include "Entity.h"

//Constructor/Destructor
CRect::CRect(const SDL_Color& color)
	: m_color(color)
{
}

//Functions
void CRect::init()
{
	m_pBoxComp = &m_entity->getComponent<CBox>();
}

void CRect::render(SDL_Renderer& rRender)
{
	SDL_SetRenderDrawColor(&rRender, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRectF(&rRender, &m_pBoxComp->m_fRect);
	SDL_SetRenderDrawColor(&rRender, 0, 0, 0, 255);
}

void CRect::update(const float& deltaTime)
{

}