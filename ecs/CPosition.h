#ifndef CPOSITION_H_INCLUDED
#define CPOSITION_H_INCLUDED
#include "Component.h"

struct CPosition : public Component
{
	//Constructor/Destructor
	CPosition(const Vector2f& rPosition = { 0.0f, 0.0f });
	~CPosition() = default;

	//Functions
	float x() const noexcept;
	float y() const noexcept;

	//Members
	Vector2f m_position;
};
#endif	/* end CPOSITION_H_INCLUDED */