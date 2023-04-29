/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "Ball.h"
#include "Table.h"

USING_NS_CC;

#define RADIUS 50
#define MAGNITUDE 10000*5

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}



// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    getPhysicsWorld()->setGravity(Vec2(0, 0));
    //getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    Table testTable = Table(this, -1, Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));

    Ball ball8 = Ball(8, this, 0, testTable.getOffsetFromFootSpot(1, table_half::CENTER));
    Ball ball9 = Ball(9, this, 0, testTable.getFootSpot());
    Ball ballCue = Ball(0, this, 0, testTable.getHeadSpot());


    /*debug block*/
    auto labelX = Label::createWithTTF("", "fonts/arial.ttf", 18);
    if (labelX == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        labelX->setPosition(Vec2(origin.x + 150, origin.y + 120));
        //label->setColor(Color3B::RED);
        // add the label as a child to this layer
        this->addChild(labelX, 5);
    }
    auto labelY = Label::createWithTTF("", "fonts/arial.ttf", 18);
    if (labelY == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        labelY->setPosition(Vec2(origin.x + 150, origin.y + 100));
        //label->setColor(Color3B::RED);
        // add the label as a child to this layer
        this->addChild(labelY, 5);
    }
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = [=](Event* event) {
        EventMouse* e = (EventMouse*)event;
        labelX->setString(std::to_string(e->getCursorX()));
        //labelX->updateContent();
        labelY->setString(std::to_string(e->getCursorY()));
        //labelY->updateContent();
    };
    //aim aid for player experience
    cocos2d::DrawNode* aimLine = DrawNode::create();
    aimLine->setLineWidth(5.0f);
    addChild(aimLine);

    auto playerListener = EventListenerTouchOneByOne::create();
    playerListener->setSwallowTouches(true);

    playerListener->onTouchBegan = [=](Touch* touch, Event* event) {
        if (ballCue.faceSprite->getBoundingBox().containsPoint(touch->getLocation())) {
            //playerFBody->setGravityEnable(false);
            return true;
        }
        else {
            return false;
        }

    };

    playerListener->onTouchMoved = [=](Touch* touch, Event* event) {
        forceCue = ballCue.faceSprite->getPosition() - touch->getLocation();
        //move the player along the touch within a radius of 50
        //normalize the movement
        if (forceCue.length() > RADIUS) {
            forceCue.normalize();
            forceCue *= RADIUS;
        }
        aimLine->clear();
        aimLine->drawLine(cocos2d::Vec2(ballCue.faceSprite->getPosition().x, ballCue.faceSprite->getPosition().y), touch->getLocation(), Color4F::RED);
    };

    playerListener->onTouchEnded = [=](Touch* touch, Event* event) {

        //n_FBody->setGravityEnable(true);
        ballCue.phBody->applyForce(forceCue * forceCue.length() * MAGNITUDE);
        forceCue = cocos2d::Vec2(cocos2d::Vec2::ZERO);
        aimLine->clear();
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);//debug only
    _eventDispatcher->addEventListenerWithSceneGraphPriority(playerListener, this);//debug only
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
