#ifndef CTEXTURE_H_INCLUDED
#define CTEXTURE_H_INCLUDED
#include "Component.h"
#include "CBox.h"

struct CTexture : public Component
{
	//Constructor/Destructor
	CTexture(SDL_Renderer& rRenderer, const char* textureName);
	~CTexture() = default;

	//Functions
	void init() override;
	void render(SDL_Renderer& rRender) override;
	void update(const float& deltaTime) override;

	//Members
	CBox* m_pBoxComp{ nullptr };

	std::string	m_textureName;
	SDL_Texture* m_texture{ nullptr };
	SDL_Rect m_srcRect{ 0 };
	SDL_FRect	m_dstFRect{ 0 };
};

#endif	/* end CTEXTURE_H_INCLUDED */