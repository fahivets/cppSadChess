#ifndef CLABLE_H_INCLUDED
#define CLABLE_H_INCLUDED
#include "Component.h"
#include "CBox.h"

struct CLable : public Component
{
	//Constructor/Destructor
	CLable(SDL_Renderer& rRenderer,
		const std::string& text,
		const std::string& fontName, const int& size,
		const SDL_Color& color = { 255, 255, 255 });
	~CLable() = default;

	//Functions
	void init() override;
	void render(SDL_Renderer& rRender) override;
	void setTrueLableBoxSize();

	//Members
	CBox* m_pBoxComp{ nullptr };
	SDL_Texture* m_textTexture{ nullptr };
	std::string m_text;
	std::string m_fontName;
	int m_size;
	SDL_Color m_lableColor;
	Vector2f m_lableSize;
};

#endif	/* end CLABLE_H_INCLUDED */
