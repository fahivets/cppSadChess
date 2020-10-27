#include "stdafx.h"
#include "CFigureType.h"
#include "Entity.h"

CFigureType::CFigureType(bool isWhite, FigureType type)
	: m_isWhite(isWhite), m_type(type)
{
}

void CFigureType::init()
{
	m_pPosComp = m_pPosComp = &m_entity->getComponent<CPosition>();
	m_startPos.x = m_pPosComp->m_position.x;
	m_startPos.y = m_pPosComp->m_position.y;
}

void CFigureType::update(const float& deltaTime)
{
	if (m_isMoved == false)
	{
		if (m_startPos.x != m_pPosComp->m_position.x || m_startPos.y != m_pPosComp->m_position.y)
		{
			m_isMoved = true;
		}
	}
}

void CFigureType::setType(FigureType type)
{
	m_type = type;
}

FigureType CFigureType::getType() const
{
	return (m_type);
}

bool CFigureType::isWhite() const
{
	return (m_isWhite);
}

bool CFigureType::isMoved() const
{
	return (m_isMoved);
}
