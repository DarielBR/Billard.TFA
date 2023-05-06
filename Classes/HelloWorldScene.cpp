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
#include "Cue.h"
#include "audio/include/AudioEngine.h"


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
    /////////////////////////////
    // 2. Starting audio engine and reproducing intro background music
    AudioEngine::setEnabled(true);
    //int fxBallToBall = AudioEngine::play2d("audio/ball_ball.mp3", false, 1.0f, nullptr);
    //int fxBallToRail = AudioEngine::play2d("audio/ball_rail.mp3", false, 1.0f, nullptr);
    //int fxBallToPocket = AudioEngine::play2d("audio/ball_pocket.mp3", false, 1.0f, nullptr);
    //AudioEngine::resume(fxBallToBall);

    /////////////////////////////
    // 3. Physics World configuration
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    getPhysicsWorld()->setGravity(Vec2(0, 0));
    //getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    ////////////////////////////
    // 4. Game rules init
    
    
    
    ////////////////////////////
    // 5. Scene Objects

    Table _table = Table(this, -1, Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
    auto rack = _table.magicRack();

    Ball ball1 = Ball(1, this, 0, _table.getRackPosition(rack[0]));
    Ball ball2 = Ball(2, this, 0, _table.getRackPosition(rack[1]));
    Ball ball3 = Ball(3, this, 0, _table.getRackPosition(rack[2]));
    Ball ball4 = Ball(4, this, 0, _table.getRackPosition(rack[3]));
    Ball ball5 = Ball(5, this, 0, _table.getRackPosition(rack[4]));
    Ball ball6 = Ball(6, this, 0, _table.getRackPosition(rack[5]));
    Ball ball7 = Ball(7, this, 0, _table.getRackPosition(rack[6]));
    Ball ball8 = Ball(8, this, 0, _table.getRackPosition(15));
    Ball ball9 = Ball(9, this, 0, _table.getRackPosition(rack[7]));
    Ball ball10 = Ball(10, this, 0, _table.getRackPosition(rack[8]));
    Ball ball11 = Ball(11, this, 0, _table.getRackPosition(rack[9]));
    Ball ball12 = Ball(12, this, 0, _table.getRackPosition(rack[10]));
    Ball ball13 = Ball(13, this, 0, _table.getRackPosition(rack[11]));
    Ball ball14 = Ball(14, this, 0, _table.getRackPosition(rack[12]));
    Ball ball15 = Ball(15, this, 0, _table.getRackPosition(rack[13]));
    
    Ball ballCue = Ball(0, this, 0, _table.getHeadSpot());
    //cocos2d::Vec2 forceCue = cocos2d::Vec2(0,0);//force to apply on cue ball
    Cue cue = Cue(this, 2, ballCue.faceSprite->getPosition());
    
    auto collitionListener = cocos2d::EventListenerPhysicsContact::create();
    collitionListener->onContactBegin = [=](PhysicsContact& contact) {
        
        auto nodeA = contact.getShapeA()->getBody()->getNode();
        auto nodeB = contact.getShapeB()->getBody()->getNode();

        //check for collition with:
        if (nodeA && nodeB) {
            if (contact.getShapeA()->getBody()->getTag() == 16
                || contact.getShapeB()->getBody()->getTag() == 16) {
                int fxBallToBall = AudioEngine::play2d("audio/ball_rail.mp3", false, 0.1f, nullptr);; //the border
            }
            else if (contact.getShapeA()->getBody()->getTag() > 16
                || contact.getShapeB()->getBody()->getTag() > 16) {
                    int fxBallToBall = AudioEngine::play2d("audio/ball_pocket.mp3", false, 1.0f, nullptr); //the pockets
                    if (contact.getShapeA()->getBody()->getTag() < 16) {
                        _table.ballFallsIntoPocket(nodeA, contact.getShapeB()->getBody()->getTag(), contact.getShapeA()->getBody()->getTag());
                    }
                    if (contact.getShapeB()->getBody()->getTag() < 16) {
                        _table.ballFallsIntoPocket(nodeB, contact.getShapeA()->getBody()->getTag(), contact.getShapeB()->getBody()->getTag());
                    }
            }
            else {
                int fxBallToBall = AudioEngine::play2d("audio/ball_ball.mp3", false, 0.5f, nullptr); //the balls
            } 
        }
        return true;
    };

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

    playerListener = EventListenerTouchOneByOne::create();
    playerListener->setSwallowTouches(true);
    playerListener->setEnabled(false);

    playerListener->onTouchBegan = [=](Touch* touch, Event* event) {
        if (ballCue.faceSprite->getBoundingBox().containsPoint(touch->getLocation())) {
           if (moveCueBAll) return true;
            else {  
                //playerFBody->setGravityEnable(false);
                //Cue cue = Cue(this, 2, ballCue.faceSprite->getPosition());
                return true;
            }
        }
        else return false;
    };

    playerListener->onTouchMoved = [=](Touch* touch, Event* event) {
        if (moveCueBAll) {//set the cue ball position
            Vec2 position = touch->getLocation();
            if (touch->getLocation().x > _table.getHeadStringX()) position.x = _table.getHeadStringX();
            if (touch->getLocation().x < 305 + ballCue.faceSprite->getBoundingBox().size.width / 2)
                position.x = 310 + ballCue.faceSprite->getBoundingBox().size.width / 2;
            ballCue.faceSprite->setPosition(position);
        }
        else{
            forceCue = ballCue.faceSprite->getPosition() - touch->getLocation();
            //move the player along the touch within a radius of 50
            //normalize the movement
            if (forceCue.length() > RADIUS) {
                forceCue.normalize();
                forceCue *= RADIUS;
            }
            //movement of the cue
            auto angle = forceCue.getAngle();
            this->getChildByTag(23)->setAnchorPoint(Vec2(0.5f, 0.95f + forceCue.length() * 0.005f));
            this->getChildByTag(23)->setPosition(ballCue.faceSprite->getPosition());
            this->getChildByTag(23)->setRotation((CC_RADIANS_TO_DEGREES(angle) * -1) + 90);
            //movement of the aim
            this->getChildByTag(24)->setPosition(ballCue.faceSprite->getPosition());
            this->getChildByTag(24)->setRotation((CC_RADIANS_TO_DEGREES(angle) * -1) + 90);
        }
    };

    playerListener->onTouchEnded = [=](Touch* touch, Event* event) {
        if (moveCueBAll) moveCueBAll = false;
        else{
            //n_FBody->setGravityEnable(true);
            ballCue.phBody->applyForce(forceCue * forceCue.length() * MAGNITUDE);
            forceCue = cocos2d::Vec2(cocos2d::Vec2::ZERO);
            //this->removeChildByTag(23, true);
            //this->removeChildByTag(24, true);
        }
    };
    
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(collitionListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);//debug only
    _eventDispatcher->addEventListenerWithSceneGraphPriority(playerListener, this);//debug only
    
    this->scheduleUpdate();
    
    return true;
}

bool HelloWorld::allBodiesStopped() {
    bool stopped = true;
    auto scene = Director::getInstance()->getRunningScene();
    auto physicsWorld = scene->getPhysicsWorld();
    auto bodies = physicsWorld->getAllBodies();

    for (auto body : bodies) {
        if ((body->getVelocity().x > 0.1f || body->getVelocity().y > 0.1f) || (body->getAngularVelocity() > 0.1f)) {
            stopped = false;
            break;
        }
    }
    return stopped;
}

void HelloWorld::update(float dt) {
    auto scene = Director::getInstance()->getRunningScene();
    if (allBodiesStopped()) {
        playerListener->setEnabled(true);
        auto ballCuePosition = scene->getChildByTag(0)->getPosition();
        scene->getChildByTag(23)->setPosition(ballCuePosition);
        scene->getChildByTag(23)->setVisible(true);
        scene->getChildByTag(24)->setPosition(ballCuePosition);
        scene->getChildByTag(24)->setVisible(true);
    } 
    else {
        playerListener->setEnabled(false);
        scene->getChildByTag(23)->setVisible(false);
        scene->getChildByTag(24)->setVisible(false);
    } 
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
