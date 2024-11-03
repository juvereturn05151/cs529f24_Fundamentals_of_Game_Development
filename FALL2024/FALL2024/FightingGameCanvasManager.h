#pragma once
#include "Canvas.h"
#include "HeartUI.h"
class FightingGameCanvasManager : public Canvas
{
private:
	HeartUI* player1HeartUI[3];
	HeartUI* player2HeartUI[3];
public:
	FightingGameCanvasManager(Renderer& rend);
	~FightingGameCanvasManager();

	void decreasePlayer1Health();
	void decreasePlayer2Health();
};

