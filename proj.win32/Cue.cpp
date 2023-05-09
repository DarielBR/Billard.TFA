#include "Cue.h"
#include "cocos2d.h"

Cue::Cue(cocos2d::Scene* scene, int zOrder, cocos2d::Vec2 position) {
	faceSprite = cocos2d::Sprite::create("img/cueE.png");
	faceSprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.95f));
	faceSprite->setPosition(position);//modificarlo para que salga tamgente a la bola
	faceSprite->setTag(23);
	aimSprite = cocos2d::Sprite::create("img/aim.png");
	aimSprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.4f));
	aimSprite->setPosition(position);//modificarlo para que salga tamgente a la bola
	aimSprite->setTag(24);
	player1Sprite = cocos2d::Sprite::create("img/p1.png");
	player1Sprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	player1Sprite->setPosition(position);
	player1Sprite->setTag(25);
	player2Sprite = cocos2d::Sprite::create("img/p2.png");
	player2Sprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	player2Sprite->setPosition(position);
	player2Sprite->setTag(26);
	player2Sprite->setVisible(false);
	//adding to scene
	scene->addChild(player1Sprite);
	scene->addChild(player2Sprite);
	scene->addChild(aimSprite, zOrder);
	scene->addChild(faceSprite, zOrder);
}
void Cue::moveAround() {}