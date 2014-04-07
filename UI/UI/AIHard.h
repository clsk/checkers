#pragma once
#include "AI.h"
ref class AIHard :
public AI
{
public:
	AIHard(Piece::Color color, BoardForm^ boardForm, uint8_t depth);
	virtual void play() override;
	virtual ~AIHard();
private:
	uint8_t m_depth;
};

