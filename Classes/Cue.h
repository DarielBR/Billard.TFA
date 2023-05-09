#pragma once
#include "cocos2d.h"
//just a visual feature
class Cue
{
public:
	cocos2d::Sprite* faceSprite;
	cocos2d::Sprite* aimSprite;
	cocos2d::Sprite* player1Sprite;
	cocos2d::Sprite* player2Sprite;
	Cue(cocos2d::Scene* scene, int zOrder, cocos2d::Vec2 position);
	void moveAround();
};

