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
	scene->addChild(aimSprite, zOrder);
	scene->addChild(faceSprite, zOrder);
}
void Cue::moveAround() {}