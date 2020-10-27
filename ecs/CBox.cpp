#include "stdafx.h"
#include "CBox.h"
#include "Entity.h"

CBox::CBox(const Vector2f& rSize)
{
	m_fRect.w = rSize.x;
	m_fRect.h = rSize.y;
}

void CBox::init()
{
	m_pPosComp = &m_entity->getComponent<CPosition>();
	m_fRect.x = m_pPosComp->x() - m_fRect.w / 2;
	m_fRect.y = m_pPosComp->y() - m_fRect.h / 2;
}

void CBox::update(const float& deltaTime)
{
	m_fRect.x = m_pPosComp->x() - m_fRect.w / 2;
	m_fRect.y = m_pPosComp->y() - m_fRect.h / 2;
}

/*TMP for debaging box
void CBox::render(SDL_Renderer& rRender)
{
	SDL_SetRenderDrawColor(&rRender, 255, 0, 0, 255);
	SDL_RenderDrawRectF(&rRender, &m_fRect);
	SDL_SetRenderDrawColor(&rRender, 0, 0, 0, 255);
}
*/
float CBox::x() const noexcept
{
	return (m_fRect.x);
}

float CBox::y() const noexcept
{
	return (m_fRect.y);
}

float CBox::w() const noexcept
{
	return (m_fRect.w);
}

float CBox::h() const noexcept
{
	return (m_fRect.h);
}

float CBox::xCenter() const noexcept
{
	return (m_pPosComp->x());
}

float CBox::yCenter() const noexcept
{
	return (m_pPosComp->y());
}

float CBox::left() const noexcept
{
	return (xCenter() - (w() / 2.0f));
}

float CBox::right() const noexcept
{
	return (xCenter() + (w() / 2.0f));
}

float CBox::top() const noexcept
{
	return (yCenter() - (h() / 2.0f));
}

float CBox::bottom() const noexcept
{
	return (yCenter() + (h() / 2.0f));
}

bool CBox::pointInRect(const SDL_Point& rPoint, const SDL_Rect& rRect) const noexcept
{
	return (SDL_PointInRect(&rPoint, &rRect));
}

bool CBox::pointInRect(const Vector2f& rPoint, const SDL_FRect& rRect) const noexcept
{
	SDL_Point point{static_cast<int>(rPoint.x), static_cast<int>(rPoint.y)};
	SDL_Rect rect{
		static_cast<int>(rRect.x),
		static_cast<int>(rRect.y),
		static_cast<int>(rRect.w),
		static_cast<int>(rRect.h)
	};
	return (SDL_PointInRect(&point, &rect));
}

bool CBox::hasIntersection(const SDL_Rect& rRectA, const SDL_Rect& rRectB) const noexcept
{
	return (SDL_HasIntersection(&rRectA, &rRectB));
}

bool CBox::hasIntersection(const SDL_FRect& rFRectA, const SDL_FRect& rFRectB) const noexcept
{
	SDL_Rect rectA{
		static_cast<int>(rFRectA.x),
		static_cast<int>(rFRectA.y),
		static_cast<int>(rFRectA.w),
		static_cast<int>(rFRectA.h)
	};
	SDL_Rect rectB{
	static_cast<int>(rFRectB.x),
	static_cast<int>(rFRectB.y),
	static_cast<int>(rFRectB.w),
	static_cast<int>(rFRectB.h)
	};
	return (SDL_HasIntersection(&rectA, &rectB));
}
