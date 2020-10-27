#ifndef CFIGURETYPE_H_INCLUDED
#define CFIGURETYPE_H_INCLUDED
#include "Component.h"
#include "CPosition.h"

enum FigureType
{
	NONE = 0,
	Pawn,
	Rook,
	Knight,
	Bishop,
	Queen,
	King
};

struct CFigureType : public Component
{
	//Constructor/Destructor
	CFigureType(bool isWhite, FigureType type = FigureType::NONE);
	~CFigureType() = default;

	//Functions
	void init() override;
	void update(const float& deltaTime) override;
	void setType(FigureType type);
	FigureType getType() const;
	bool isWhite() const;
	bool isMoved() const;

	//Members
	bool m_isWhite{ false };
	FigureType m_type{ FigureType::NONE };
	bool m_isMoved{ false };
	CPosition* m_pPosComp{ nullptr };
	Vector2f m_startPos{ 0 };
};

#endif /* end CFIGURETYPE_H_INCLUDED */