#pragma once
#include "AI.h"
ref class AIMedium :
public AI
{
public:
	AIMedium(Piece::Color color, BoardForm^ boardForm);
	virtual void play() override;
	virtual ~AIMedium();
};

