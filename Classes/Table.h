#pragma once
#ifndef __TABLE_H__
#define __TABLE_H__

#include <string.h>
#include "cocos2d.h"
#include <array>
#include <random>
#include "Ball.h"

enum table_half { LEFT, RIGHT, CENTER};

struct ScoreNest {
	bool filled;
	cocos2d::Vec2 position;
};

class Table {
private:
	int headStringX = 545;
	cocos2d::Vec2 headSpot = cocos2d::Vec2(545, 550);
	cocos2d::Vec2 centerSpot = cocos2d::Vec2(750, 550);
	cocos2d::Vec2 footSpot = cocos2d::Vec2(965,550);
	//cocos2d::Vec2 railBorder[2] = {cocos2d::Vec2::ZERO, cocos2d::Vec2::ZERO};
	ScoreNest scoreP1[8];
	ScoreNest scoreP2[8];
	//game rules
	bool moveCueBAll = true;
	int playerInTurn;
	ball_group player1Choice;
	bool gameStart;
public:
	cocos2d::Sprite* tableSprite;
	cocos2d::Sprite* scoreSpriteP1;
	cocos2d::Sprite* scoreSpriteP2;
	cocos2d::Node* tableBorder;
	cocos2d::PhysicsBody* phBody;
	cocos2d::Node* pocketUpLeft;
	cocos2d::Node* pocketUpCenter;
	cocos2d::Node* pocketUpRight;
	cocos2d::Node* pocketDownLeft;
	cocos2d::Node* pocketDownCenter;
	cocos2d::Node* pocketDownRight;

	//constructor
	Table(cocos2d::Scene* scene, int zOrder, cocos2d::Vec2 position);
	//behavior
	int getHeadStringX() const { return headStringX; };
	cocos2d::Vec2 getHeadSpot() { return headSpot; };
	cocos2d::Vec2 getFootSpot() { return footSpot; };
	cocos2d::Vec2 getRackPosition(int position);
	//game rules
	void gameIsOn() { gameStart = false; };
	bool isGameStart() { return gameStart; };
	void blockCueBAll() { moveCueBAll = false; };
	bool isCueBallMovementAllowed() const { return moveCueBAll; };
	void setPlayerInTurn(int player) { if (player == 1 || player == 2) playerInTurn = player; };
	int getPlayerInTurn() { return playerInTurn; };
	void setPlayer1Choice(ball_group choice) { if (player1Choice == CUE) player1Choice = choice; };
	ball_group getPlayer1Choice() { return player1Choice; };
	std::array<int, 14> magicRack();
	//visuals
	void setScale(float scale);
	void ballFallsIntoPocket(cocos2d::Node* node, int pocketTag, int ballTag) const;
};

#endif // __TABLE_H__
