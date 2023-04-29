#include "Table.h"

USING_NS_CC;

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
	tableBorder->addComponent(phBody);
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