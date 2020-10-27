#ifndef CBOX_H_INCLUDED
#define CBOX_H_INCLUDED
#include "Component.h"
#include "CPosition.h"

struct CBox : public Component
{
	//Constructor/Destructor
	CBox(const Vector2f& rSize);
	~CBox() = default;

	//Functions
	void init() override;
	void update(const float& deltaTime) override;

	/*TMP for debaging box
	void render(SDL_Renderer& rRender) override;
	*/

	float x() const noexcept;
	float y() const noexcept;
	float w() const noexcept;
	float h() const noexcept;
	float xCenter() const noexcept;
	float yCenter() const noexcept;
	float left() const noexcept;
	float right() const noexcept;
	float top() const noexcept;
	float bottom() const noexcept;
	bool pointInRect(const SDL_Point& rPoint, const SDL_Rect& rRect) const noexcept;
	bool pointInRect(const Vector2f& rPoint, const SDL_FRect& rRect) const noexcept;
	bool hasIntersection(const SDL_Rect& rRectA, const SDL_Rect& rRectB) const noexcept;
	bool hasIntersection(const SDL_FRect& rFRectA, const SDL_FRect& rFRectB) const noexcept;

	// Members
	CPosition* m_pPosComp{ nullptr };
	SDL_FRect m_fRect{ 0.0f };
};

#endif	/* end CBOX_H_INCLUDED */