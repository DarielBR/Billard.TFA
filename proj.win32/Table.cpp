#include "Table.h"

USING_NS_CC;

#define POCKET_RADIUS 15

Table::Table(cocos2d::Scene* scene, int zOrder, cocos2d::Vec2 position) {
	tableSprite = cocos2d::Sprite::create("res/table.png");
	tableSprite->setPosition(position);

	tableBorder = cocos2d::Node::create();

    Vec2 railBorder[] = {
					Vec2(285,345),
					Vec2(305,367),
					Vec2(305,735),
					Vec2(288,766),
					Vec2(320,795),
					Vec2(345,777),
					Vec2(703,777),
					Vec2(725,795),
					Vec2(770,795),
					Vec2(796,777),
					Vec2(1159,777),
					Vec2(1186,795),
					Vec2(1216,760),
					Vec2(1196,737),
					Vec2(1196,367),
					Vec2(1216,340),
					Vec2(1181,310),
					Vec2(1159,330),
					Vec2(795,330),
					Vec2(770,310),
					Vec2(725,310),
					Vec2(703,330),
					Vec2(345,330),
					Vec2(320,310),
					Vec2(285,345)};

	phBody = PhysicsBody::createEdgePolygon(railBorder, 25, PHYSICSBODY_MATERIAL_DEFAULT);
	phBody->setDynamic(false);
	phBody->setCategoryBitmask(0x02); //0010
	phBody->setCollisionBitmask(0x01); //0001
	phBody->setContactTestBitmask(0x01);
	phBody->setTag(17);
	tableBorder->addComponent(phBody);
	//Pockes	
	pocketUpLeft = cocos2d::Node::create();
	pocketUpLeft->setPosition(Vec2(295, 786));
	auto phBodyUL = cocos2d::PhysicsBody::createCircle(POCKET_RADIUS, PHYSICSBODY_MATERIAL_DEFAULT);
	phBodyUL->setDynamic(false);
	phBodyUL->setCategoryBitmask(0x02); //0010
	phBodyUL->setCollisionBitmask(0x01); //0001
	phBodyUL->setContactTestBitmask(0x02);
	phBodyUL->setTag(16);
	pocketUpLeft->addComponent(phBodyUL);
	scene->addChild(pocketUpLeft);
	
	pocketUpCenter = cocos2d::Node::create();
	pocketUpCenter->setPosition(Vec2(750, 803));
	auto phBodyUC = cocos2d::PhysicsBody::createCircle(POCKET_RADIUS, PHYSICSBODY_MATERIAL_DEFAULT);
	phBodyUC->setDynamic(false);
	phBodyUC->setCategoryBitmask(0x02); //0010
	phBodyUC->setCollisionBitmask(0x01); //0001
	phBodyUC->setContactTestBitmask(0x02);
	phBodyUC->setTag(16);
	pocketUpCenter->addComponent(phBodyUC);
	scene->addChild(pocketUpCenter);
	
	pocketUpRight = cocos2d::Node::create();
	pocketUpRight->setPosition(Vec2(1208, 786));
	auto phBodyUR = cocos2d::PhysicsBody::createCircle(POCKET_RADIUS, PHYSICSBODY_MATERIAL_DEFAULT);
	phBodyUR->setDynamic(false);
	phBodyUR->setCategoryBitmask(0x02); //0010
	phBodyUR->setCollisionBitmask(0x01); //0001
	phBodyUR->setContactTestBitmask(0x02);
	phBodyUR->setTag(16);
	pocketUpRight->addComponent(phBodyUR);
	scene->addChild(pocketUpRight);
	
	pocketDownRight = cocos2d::Node::create();
	pocketDownRight->setPosition(Vec2(1208, 317));
	auto phBodyDR = cocos2d::PhysicsBody::createCircle(POCKET_RADIUS, PHYSICSBODY_MATERIAL_DEFAULT);
	phBodyDR->setDynamic(false);
	phBodyDR->setCategoryBitmask(0x02); //0010
	phBodyDR->setCollisionBitmask(0x01); //0001
	phBodyDR->setContactTestBitmask(0x02);
	phBodyDR->setTag(16);
	pocketDownRight->addComponent(phBodyDR);
	scene->addChild(pocketDownRight);
	
	pocketDownCenter = cocos2d::Node::create();
	pocketDownCenter->setPosition(Vec2(750, 302));
	auto phBodyDC = cocos2d::PhysicsBody::createCircle(POCKET_RADIUS, PHYSICSBODY_MATERIAL_DEFAULT);
	phBodyDC->setDynamic(false);
	phBodyDC->setCategoryBitmask(0x02); //0010
	phBodyDC->setCollisionBitmask(0x01); //0001
	phBodyDC->setContactTestBitmask(0x02);
	phBodyDC->setTag(16);
	pocketDownCenter->addComponent(phBodyDC);
	scene->addChild(pocketDownCenter);
				
	pocketDownLeft = cocos2d::Node::create();
	pocketDownLeft->setPosition(Vec2(295, 317));
	auto phBodyDL = cocos2d::PhysicsBody::createCircle(POCKET_RADIUS, PHYSICSBODY_MATERIAL_DEFAULT);
	phBodyDL->setDynamic(false);
	phBodyDL->setCategoryBitmask(0x02); //0010
	phBodyDL->setCollisionBitmask(0x01); //0001
	phBodyDL->setContactTestBitmask(0x02);
	phBodyDL->setTag(16);
	pocketDownLeft->addComponent(phBodyDL);
	scene->addChild(pocketDownLeft);
	//Adding table and border to the scene
	scene->addChild(tableSprite, zOrder);
	scene->addChild(tableBorder, zOrder);

	tableSprite->setScale(.3f);
}

void Table::setScale(float scale) {
	//shineSprite->setScale(scale);
	tableSprite->setScale(scale);
}

Vec2 Table::getOffsetFromFootSpot(int ballPositions, table_half side) {
	int ballWide = 37;
	int offsetX = Table::getFootSpot().x + ballPositions * ballWide;
	int offsetY = NULL;
	switch (side) {
		case table_half::RIGHT:
			offsetY = Table::getFootSpot().y - ballPositions * ballWide;
			break;
		case table_half::LEFT:
			offsetY = Table::getFootSpot().y + ballPositions * ballWide;
			break;
		case table_half::CENTER:
			offsetY = Table::getFootSpot().y;
			break;
		default:
			offsetY = Table::getFootSpot().y;
	}
	
	return Vec2(offsetX, offsetY);
}