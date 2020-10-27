#include"stdafx.h"
#include "CTexture.h"
#include "Entity.h"

CTexture::CTexture(SDL_Renderer& rRenderer, const char* textureName)
{
	m_textureName = textureName;
	ResourceHolder::get().textures.set(rRenderer, m_textureName);
	m_texture = ResourceHolder::get().textures.get(m_textureName);

	Vector2f textureSize = ResourceHolder::get().textures.queryTexture(m_texture);
	m_srcRect = {
		0,
		0,
		static_cast<int>(textureSize.x),
		static_cast<int>(textureSize.y)
	};
}

void CTexture::init()
{
	m_pBoxComp = &m_entity->getComponent<CBox>();
	m_dstFRect = m_pBoxComp->m_fRect;
}

void CTexture::render(SDL_Renderer& rRender)
{
	SDL_RenderCopyF(&rRender, m_texture, &m_srcRect, &m_dstFRect);
}

void CTexture::update(const float& deltaTime)
{
	m_dstFRect = m_pBoxComp->m_fRect;
}