#include "stdafx.h"
#include "CPosition.h"

CPosition::CPosition(const Vector2f& rPosition)
	: m_position(rPosition)
{}

float CPosition::x() const noexcept
{
	return (m_position.x);
}

float CPosition::y() const noexcept
{
	return (m_position.y);
}