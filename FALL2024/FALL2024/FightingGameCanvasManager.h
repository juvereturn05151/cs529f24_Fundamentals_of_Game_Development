#pragma once
#include "Canvas.h"
#include "HeartUI.h"

class FightingGameCanvasManager : public Canvas
{
private:
	HeartUI* player1HeartUI[3];
	HeartUI* player2HeartUI[3];
	Node* postGameBg;
	Node* player1Win;
	Node* player2Win;
	Node* ready;
	Node* fight;
	const float countDownToPostGameUI = 2.0f;
	float currentCountDownToPostGameUI;
	bool startCountDownToPostGame;

public:
	FightingGameCanvasManager(Renderer& rend);
	~FightingGameCanvasManager();

	void update(float deltaTime) override;
	void decreasePlayerHealth(int playerSide, int health);
	void triggerReadyUI();
	void triggerFightUI();
	void disableReadyAndFightUI();
	void triggerResultUI();
};

