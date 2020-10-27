#include "stdafx.h"
#include "State.h"
#include "../MainGame.h"

State::State(MainGame& game)
	: m_pGame(&game), m_needPop(false)
{}

State::~State()
{
	m_pGame = nullptr;
}