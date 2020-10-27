#ifndef CRECT_H_INCLUDED
#define CRECT_H_INCLUDED
#include "Component.h"
#include "CBox.h"

struct CRect : public Component
{
	//Constructor/Destructor
	CRect(const SDL_Color& color = {0, 0, 0, 255});
	~CRect() = default;

	//Functions
	void init() override;
	void render(SDL_Renderer& rRender) override;
	void update(const float& deltaTime) override;

	//Members
	CBox* m_pBoxComp{ nullptr };
	SDL_Color m_color{ 0 };
};

#endif /* end CRECT_H_INCLUDED */