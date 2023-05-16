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
#include "P1Wins.h"
#include "P2Wins.h"
#include "Ball.h"
#include "Table.h"
#include "Cue.h"
#include "audio/include/AudioEngine.h"


USING_NS_CC;

#define RADIUS 50
#define MAGNITUDE 1000//10000*7

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

    /////////////////////////////
    // 3. Physics World configuration
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    getPhysicsWorld()->setGravity(Vec2(0, 0));
    //getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    ////////////////////////////
    // 3. Flags and Registers initialization
    gameIsOn = false;//DEPRECATED
    openTable = true;//good
    onPlay = false;//DEPRECATED
    playHasStart = false;//good
    firstContact = 0;//good
    counterPocketed = 0;//good
    moveCueBAll = true;//good
    illegalPlay = false;//good
    playerInTurn = 1;//good
    player1Solid = true;//good
    rackScoreP1[8] = { false };//good
    rackScoreP2[8] = { false };//good


    ////////////////////////////
    // 4. Scene Objects

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
    Cue cue = Cue(this, 2, ballCue.faceSprite->getPosition());


    ////////////////////////////////////
    // 5. Collitioin handling
    auto collitionListener = cocos2d::EventListenerPhysicsContact::create();
    collitionListener->onContactBegin = [=](PhysicsContact& contact) {
        
        auto nodeA = contact.getShapeA()->getBody()->getNode();
        auto nodeB = contact.getShapeB()->getBody()->getNode();

        //check for collition with:
        if (nodeA && nodeB) {
            if (contact.getShapeA()->getBody()->getTag() == 16 || contact.getShapeB()->getBody()->getTag() == 16) {
                int fxBallToBall = AudioEngine::play2d("audio/ball_rail.mp3", false, 0.1f, nullptr);; //the border
            }
            else if (contact.getShapeA()->getBody()->getTag() > 16 || contact.getShapeB()->getBody()->getTag() > 16) {
                    int fxBallToBall = AudioEngine::play2d("audio/ball_pocket.mp3", false, 1.0f, nullptr); //the pockets
                    counterPocketed++;
                    if (contact.getShapeA()->getBody()->getTag() < 16) {
                        playerChoice(nodeA->getTag());
                        ballFallsIntoPocket(nodeA, _table, contact.getShapeB()->getBody()->getTag(), contact.getShapeA()->getBody()->getTag());
                    }
                    if (contact.getShapeB()->getBody()->getTag() < 16) {
                        playerChoice(nodeB->getTag());
                        ballFallsIntoPocket(nodeB, _table, contact.getShapeA()->getBody()->getTag(), contact.getShapeB()->getBody()->getTag());
                    }
            }
            else if(contact.getShapeA()->getBody()->getTag() < 16 && contact.getShapeB()->getBody()->getTag() < 16){//a ball-ball contact has been detected
                int fxBallToBall = AudioEngine::play2d("audio/ball_ball.mp3", false, 0.5f, nullptr); //ball hit
                if (firstContact == 0) {//we only care for the first contact between the cue ball and other ball
                    if ((contact.getShapeA()->getBody()->getTag() > 0 && contact.getShapeA()->getBody()->getTag() < 16)//shapeA is a ball OR
                        || (contact.getShapeB()->getBody()->getTag() > 0 && contact.getShapeB()->getBody()->getTag() < 16)) {//shapeB is a ball
                        if (contact.getShapeA()->getBody()->getTag() == 0) {//is shapeA the cue-ball?
                            firstContact = contact.getShapeB()->getBody()->getTag();//then the first contact is shapeB
                        }
                        else if (contact.getShapeB()->getBody()->getTag() == 0) {//is shapeB the cue-ball
                            firstContact = contact.getShapeA()->getBody()->getTag();//then the first contact is shapeA
                        }
                    }
                }
            } 
        }
        return true;
    };

    /* 
    //debug block
    auto labelOnPlay = Label::createWithTTF("", "fonts/arial.ttf", 18);
    labelOnPlay->setPosition(Vec2(100, 260));
    this->addChild(labelOnPlay, 5);
    auto labelOpenTable = Label::createWithTTF("", "fonts/arial.ttf", 18);
    labelOpenTable->setPosition(Vec2(100, 240));
    this->addChild(labelOpenTable, 5);
    auto labelHits = Label::createWithTTF("", "fonts/arial.ttf", 18);
    labelHits->setPosition(Vec2(100, 220));
    this->addChild(labelHits, 5);
    auto labelChoice = Label::createWithTTF("", "fonts/arial.ttf", 18);
    labelChoice->setPosition(Vec2(100, 200));
    this->addChild(labelChoice, 5);
    auto labelTurn = Label::createWithTTF("", "fonts/arial.ttf", 18);
    labelTurn->setPosition(Vec2(100, 180));
    this->addChild(labelTurn, 5);
    auto labelFirstContact = Label::createWithTTF("", "fonts/arial.ttf", 18);
    labelFirstContact->setPosition(Vec2(100, 160));
    this->addChild(labelFirstContact, 5);

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
        labelTurn->setString("player in turn " + std::to_string(playerInTurn));
        labelFirstContact->setString("first contact " + std::to_string(firstContact));
        labelOpenTable->setString("is table open: " + std::to_string(openTable));
        labelOnPlay->setString("is on a play: " + std::to_string(onPlay));
        labelChoice->setString("player 1 has solids: " + std::to_string(player1Solid));
        labelHits->setString("number of pocketed: " + std::to_string(counterPocketed));
    };
    //debug block end 
    */
    
    //////////////////////////////////
    // 6. Touch events hangling
    playerListener = EventListenerTouchOneByOne::create();
    playerListener->setSwallowTouches(true);
    playerListener->setEnabled(false);

    playerListener->onTouchBegan = [=](Touch* touch, Event* event) {
     
        if (ballCue.faceSprite->getBoundingBox().containsPoint(touch->getLocation())) {
            return true;
        } 
        else return false;
    };

    playerListener->onTouchMoved = [=](Touch* touch, Event* event) {
        if (moveCueBAll) {//set the cue ball position
            Vec2 position = touch->getLocation();
            if (illegalPlay) {
                //freezing ball objects
                auto phBodies = this->getPhysicsWorld()->getAllBodies();
                for (auto phBody : phBodies) {
                    if (phBody->getTag() < 16 && phBody->getTag() > 0) {
                        phBody->setDynamic(false);
                    }
                }
                //colocate the cue ball at any position on the table with every other ball set to non dynamic
                if (touch->getLocation().x > 1195)
                    position.x = 1190 - ballCue.faceSprite->getBoundingBox().size.width / 2;
                if (touch->getLocation().x < 305 + ballCue.faceSprite->getBoundingBox().size.width / 2)
                    position.x = 310 + ballCue.faceSprite->getBoundingBox().size.width / 2;
                if (touch->getLocation().y > 775)
                    position.y = 770 - ballCue.faceSprite->getBoundingBox().size.height / 2;
                if (touch->getLocation().y < 330)
                    position.y = 335 + ballCue.faceSprite->getBoundingBox().size.height / 2;
                ballCue.faceSprite->setPosition(position);
            }
            else {//movement allowed withing head third
                if (touch->getLocation().x > _table.getHeadStringX()) position.x = _table.getHeadStringX();
                if (touch->getLocation().x < 305 + ballCue.faceSprite->getBoundingBox().size.width / 2)
                    position.x = 310 + ballCue.faceSprite->getBoundingBox().size.width / 2;
                if (touch->getLocation().y > 775)
                    position.y = 770 - ballCue.faceSprite->getBoundingBox().size.height / 2;
                if (touch->getLocation().y < 330)
                    position.y = 335 + ballCue.faceSprite->getBoundingBox().size.height / 2;
                ballCue.faceSprite->setPosition(position);
            }
        }
        else{//aim for a play
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
        if (illegalPlay) {
            illegalPlay = false;
            //wait until cue ball is settled
             while (ballCue.phBody->getVelocity() > Vec2(0.0f, 0.0f)) {//REVISAR ESTE BUCLE PROPUESTO A ELIMINAR
                auto a = 'a';
             }
        }
        if (moveCueBAll) moveCueBAll = false;
        else{
            //restoring movibility to balls objects
            auto phBodies = this->getPhysicsWorld()->getAllBodies();
            for (auto phBody : phBodies) {
                if (phBody->getTag() < 16 && phBody->getTag() > 0)
                    phBody->setDynamic(true);
            }
            ballCue.phBody->applyImpulse(forceCue* forceCue.length()* MAGNITUDE);
            //ballCue.phBody->applyForce(forceCue * forceCue.length() * MAGNITUDE);
            forceCue = cocos2d::Vec2(cocos2d::Vec2::ZERO);
            firstContact = 0;//reset
            counterPocketed = 0;//reset
            playHasStart = true;
        }
    };
    
    //Registering event handlers
    _eventDispatcher->addEventListenerWithSceneGraphPriority(collitionListener, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);//debug only
    _eventDispatcher->addEventListenerWithSceneGraphPriority(playerListener, this);//debug only
    
    this->scheduleUpdate();
    
    return true;
}
/**
* Switches the players turn flag
*/
void HelloWorld::switchPlayer() {
    auto scene = Director::getInstance()->getRunningScene();
    if (playerInTurn == 1) {
        playerInTurn = 2;
    } 
    else if (playerInTurn == 2) {
        playerInTurn = 1;
    } 
}
/**
* Returns true if there is any ball in movement.
*/
bool HelloWorld::playIsOn() {
    auto scene = Director::getInstance()->getRunningScene();
    auto phBodies = scene->getPhysicsWorld()->getAllBodies();
    for (auto phBody : phBodies) {
        if (phBody->getTag() < 16) {//balls only
            if (phBody->getVelocity().x > 0.001f || phBody->getVelocity().y > 0.001f || phBody->getAngularVelocity() > 0.001f) {
                return true;
                break;
            }
        }
    }
    return false;
}
/**
* Returns true if a ball form wrong group has been hitted first.
*/
bool HelloWorld::otherBallGroupHittedFirst() {
    if (playerInTurn == 1) {
        if ((!player1Solid && firstContact > 0 && firstContact < 8)//player1 has Stripes and first cantact is solid OR 
            || (player1Solid && firstContact > 8 && firstContact < 16)) {//player1 has SOLIDS and first contact is STRIPES
            return true;
        }
    }
    else if (playerInTurn == 2) {
        if ((player1Solid && firstContact > 0 && firstContact < 8)//player2 has STRIPES and 1st contact is SOLID OR
            || (!player1Solid && firstContact > 8 && firstContact < 16)) {//player2 has SOLIDS and 1st contact is STRIPES
            return true;
        }
    }
    else return false;
}
/**
* Evaluates the contanct with the 8-ball. If illegal returns true, if not, returns false.
*/
bool HelloWorld::isContactWith8Bad() {//this code must be improved to achieve proper behavior.
    if (firstContact == 8) {
        if (playerInTurn == 1) {
            int emptySpace = 0;
            for (auto score : rackScoreP1) {//check for empty spaces in the score
                if (score == false) emptySpace++;
            }
            if (emptySpace > 1) {//mora than one found, thus contact is illegal
                return true;//it may be necesary to comment remove this line;
            } 
            else return false;
        }
        if (playerInTurn == 2) {
            int emptySpace = 0;
            for (auto score : rackScoreP2) {
                if (score == false) emptySpace++;
            }
            if (emptySpace > 1) {
                return true;//it may be necesary to comment remove this line;
            } 
            else return false;
        }
    }
    return false;
}
/**
* Evaluates the pocketing of the 8-ball. If illegal finishes the game, if not, returns false.
*/
void HelloWorld::checkPocketing8Ball() {//this code must be improved to achieve proper behavior.
    if (playerInTurn == 1) {
        int emptySpace = 0;
        for (auto score : rackScoreP1) {//check for empty spaces in the score
            if (score == false) emptySpace++;
        }
        if (emptySpace > 1) {//mora than one found, thus contact is illegal
            auto director = Director::getInstance();
            auto scene4 = P2WinsScene::createScene();
            auto scene2 = HelloWorld::createScene();
            director->replaceScene(scene2);
            director->pushScene(scene4);
        }
    }else if (playerInTurn == 2) {
        int emptySpace = 0;
        for (auto score : rackScoreP2) {
            if (score == false) emptySpace++;
        }
        if (emptySpace > 1) {
            auto director = Director::getInstance();
            auto scene3 = P1WinsScene::createScene();
            auto scene2 = HelloWorld::createScene();
            director->replaceScene(scene2);
            director->pushScene(scene3);               
        }
    }
}
/**
* Evaluates the result of the current play. 
*/
void HelloWorld::playResult() {
        if (openTable) {
            switchPlayer();
        }
        else {
            if ( (isContactWith8Bad()) || (otherBallGroupHittedFirst()) || (firstContact == 0) || (counterPocketed == 0)) {
                switchPlayer();
            }
        }
        playHasStart = false;//reset

}
/**
* Evaluates if all physics bodies have stopped
*/
bool HelloWorld::allBodiesStopped() {
    bool stopped = true;
    auto scene = Director::getInstance()->getRunningScene();
    auto physicsWorld = scene->getPhysicsWorld();
    auto bodies = physicsWorld->getAllBodies();
    
    for (auto body : bodies) {
        if (body->getTag() < 16) {
            if ((body->getVelocity().x > 0.001f || body->getVelocity().y > 0.001f) || (body->getAngularVelocity() > 0.1f)) {
                stopped =  false;
                break;
            }
        }
    }
    return stopped;
}
/**
* Performs necesary visuals when a ball has collides with a pocket.
*/
void HelloWorld::ballFallsIntoPocket(cocos2d::Node* node, Table table, int pocketTag, int ballTag) {
    if (ballTag == 8) checkPocketing8Ball();
    int value = ballTag;//int value is there for scoring purpouses
    cocos2d::MoveTo* roll;
    switch (pocketTag) {
    case 17:
        roll = cocos2d::MoveTo::create(0.5f, Vec2(295, 786));
        break;
    case 18:
        roll = cocos2d::MoveTo::create(0.5f, Vec2(750, 803));
        break;
    case 19:
        roll = cocos2d::MoveTo::create(0.5f, Vec2(1208, 786));
        break;
    case 20:
        roll = cocos2d::MoveTo::create(0.5f, Vec2(1208, 317));
        break;
    case 21:
        roll = cocos2d::MoveTo::create(0.5f, Vec2(750, 302));
        break;
    case 22:
        roll = cocos2d::MoveTo::create(0.5f, Vec2(295, 317));
        break;
    default:
        break;
    }
    //actions and sequences
    auto delay1 = cocos2d::DelayTime::create(0.2f);
    auto shrink = cocos2d::ScaleBy::create(0.5f, 0.7f);
    auto inflate = cocos2d::ScaleBy::create(0.5f, 1.4f);
    auto fadeOut = cocos2d::FadeOut::create(0.5f);
    auto intoPocket = cocos2d::Spawn::create(roll, delay1, shrink, fadeOut, nullptr);
    auto moveToScore = cocos2d::MoveTo::create(1.0f, getRackPosition(ballTag));
    auto moveToTable = cocos2d::MoveTo::create(1.0f, table.getHeadSpot());
    auto delay2 = cocos2d::DelayTime::create(0.5f);
    auto fadeIn = cocos2d::FadeIn::create(0.5f);
    auto intoTable = cocos2d::Sequence::create(CallFunc::create([node]() {  node->setVisible(false);
                                                                            node->getPhysicsBody()->setVelocity(Vec2(0.0f, 0.0f));
                                                                            node->getPhysicsBody()->setAngularVelocity(0.0f); }),
                                                moveToTable, delay2,
                                                CallFunc::create([node]() {node->setVisible(true); }),
                                                nullptr);
    auto intoScore = cocos2d::Sequence::create(moveToScore, delay2, fadeIn, nullptr);
    auto cueIntoPocket = cocos2d::Sequence::create(intoPocket, nullptr);
    auto ballIntoPocket = cocos2d::Sequence::create(intoPocket, intoScore, nullptr);
    if (ballTag == 0) {
        node->runAction(intoTable);
        moveCueBAll = true;
        illegalPlay = true;
        playHasStart = false;//reset
        switchPlayer();
    } 
    else {
        node->removeAllComponents();
        node->runAction(ballIntoPocket);
    } 
}
/**
* When the table is open, it will set player's ball-group choice for the game.
*/
void HelloWorld::playerChoice(int ballTag) {//quitar el prametro player: no se usa
    if (openTable) {//this register starts on true state
        if (ballTag > 0 && ballTag < 8) {
            if (playerInTurn == 1) {
                player1Solid = true;
                firstContact = ballTag;
            }
            else {
                player1Solid = false;
                firstContact = ballTag;
            } 
        }
        else if (ballTag > 8 && ballTag < 16){
            if (playerInTurn == 1) {
                player1Solid = false;
                firstContact = ballTag;
            }
            else {
                player1Solid = true;
                firstContact = ballTag;
            }
        }
        
    }
    openTable = false;//after the first call to this function it will turn into false state: table is not open any more.
}
/**
* Gets a free score position and returnr it position coordinates.
*/
cocos2d::Vec2 HelloWorld::getRackPosition(int ballTag) {
    //TODO recorrer el arreglo de posiciones segun el jugador dado y devolver el primer espacio vacio.
    if (ballTag == 0 || ballTag == 8) return Vec2(Vec2::ZERO);
    if (player1Solid) {
        if (ballTag > 0 && ballTag < 8) {
            for (int i = 0; i < 10; i++) {
                if (rackScoreP1[i] == false) {
                    rackScoreP1[i] = true;
                    switch (i) {
                    case 0:
                        return Vec2(LEFT1);
                        break;
                    case 1:
                        return Vec2(LEFT2);
                        break;
                    case 2:
                        return Vec2(LEFT3);
                        break;
                    case 3:
                        return Vec2(LEFT4);
                        break;
                    case 4:
                        return Vec2(LEFT5);
                        break;
                    case 5:
                        return Vec2(LEFT6);
                        break;
                    case 6:
                        return Vec2(LEFT7);
                        break;
                    case 7:
                        return Vec2(LEFT8);
                        break;
                    default:
                        break;
                    }
                    break;
                }
            }
        }
        else if(ballTag > 8 && ballTag < 16){
            for (int i = 0; i < 10; i++) {
                if (rackScoreP2[i] == false) {
                    rackScoreP2[i] = true;
                    switch (i) {
                    case 0:
                        return Vec2(RIGHT1);
                        break;
                    case 1:
                        return Vec2(RIGHT2);
                        break;
                    case 2:
                        return Vec2(RIGHT3);
                        break;
                    case 3:
                        return Vec2(RIGHT4);
                        break;
                    case 4:
                        return Vec2(RIGHT5);
                        break;
                    case 5:
                        return Vec2(RIGHT6);
                        break;
                    case 6:
                        return Vec2(RIGHT7);
                        break;
                    case 7:
                        return Vec2(RIGHT8);
                        break;
                    default:
                        break;
                    }
                    break;
                }
            }
        }
    }
    else if(!player1Solid) {
        if (ballTag > 8 && ballTag < 16) {
            for (int i = 0; i < 10; i++) {
                if (rackScoreP1[i] == false) {
                    rackScoreP1[i] = true;
                    switch (i) {
                    case 0:
                        return Vec2(LEFT1);
                        break;
                    case 1:
                        return Vec2(LEFT2);
                        break;
                    case 2:
                        return Vec2(LEFT3);
                        break;
                    case 3:
                        return Vec2(LEFT4);
                        break;
                    case 4:
                        return Vec2(LEFT5);
                        break;
                    case 5:
                        return Vec2(LEFT6);
                        break;
                    case 6:
                        return Vec2(LEFT7);
                        break;
                    case 7:
                        return Vec2(LEFT8);
                        break;
                    default:
                        break;
                    }
                    break;
                }
            }
        }
        else if(ballTag > 0 && ballTag < 8){
            for (int i = 0; i < 10; i++) {
                if (rackScoreP2[i] == false) {
                    rackScoreP2[i] = true;
                    switch (i) {
                    case 0:
                        return Vec2(RIGHT1);
                        break;
                    case 1:
                        return Vec2(RIGHT2);
                        break;
                    case 2:
                        return Vec2(RIGHT3);
                        break;
                    case 3:
                        return Vec2(RIGHT4);
                        break;
                    case 4:
                        return Vec2(RIGHT5);
                        break;
                    case 5:
                        return Vec2(RIGHT6);
                        break;
                    case 6:
                        return Vec2(RIGHT7);
                        break;
                    case 7:
                        return Vec2(RIGHT8);
                        break;
                    default:
                        break;
                    }
                    break;
                }
            }
        }
    }
    //return Vec2(500,160);
}
/**
* DEPRECATED
*/
void HelloWorld::playGame() {
    //playerChoice(nodeBall->getTag());
    if (gameIsOn) {
        if (playerInTurn == 1) {
            if ((!player1Solid && firstContact > 0 && firstContact < 8)//player1 has Stripes and first cantact is solid OR 
                || (player1Solid && firstContact > 8 && firstContact < 16)) {//player1 has SOLIDS and first contact is STRIPES
                //illegalPlay = true;
                //moveCueBAll = true;
                switchPlayer();//player1 lost its turn
                return;
            }
        }
        else if (playerInTurn == 2) {
            if ((player1Solid && firstContact > 0 && firstContact < 8)//player2 has STRIPES and 1st contact is SOLID OR
                || (!player1Solid && firstContact > 8 && firstContact < 16)) {//player2 has SOLIDS and 1st contact is STRIPES
                // illegalPlay = true;
                 //moveCueBAll = true;
                switchPlayer();//player2 lost its turn
                return;
            }
        }
        else if (!onPlay && counterPocketed < 1 && gameIsOn) {
            switchPlayer();//no ball has been pocketed
            return;
        }
        else if (!onPlay && firstContact == 0 && gameIsOn) {
            switchPlayer();//no ball has been hit
            return;
        }
    }
}

void HelloWorld::update(float dt) {//Visuals for the cue and aim
    auto scene = Director::getInstance()->getRunningScene();
    if (allBodiesStopped()) {
        playerListener->setEnabled(true);
        auto ballCuePosition = scene->getChildByTag(0)->getPosition();
        scene->getChildByTag(23)->setPosition(ballCuePosition);
        scene->getChildByTag(23)->setVisible(true);
        scene->getChildByTag(24)->setPosition(ballCuePosition);
        scene->getChildByTag(24)->setVisible(true);
        //player sprites
        scene->getChildByTag(25)->setPosition(ballCuePosition);
        scene->getChildByTag(26)->setPosition(ballCuePosition);
        if (playerInTurn == 1) {
            scene->getChildByTag(25)->setVisible(true);
            scene->getChildByTag(26)->setVisible(false);
        }
        else if (playerInTurn == 2) {
            scene->getChildByTag(26)->setVisible(true);
            scene->getChildByTag(25)->setVisible(false);
        }
    } 
    else {//balls still moving, nathing must be done
        playerListener->setEnabled(false);
        scene->getChildByTag(23)->setVisible(false);
        scene->getChildByTag(24)->setVisible(false);
        scene->getChildByTag(25)->setVisible(false);
        scene->getChildByTag(26)->setVisible(false);
    }

    //evaluating the result of the play
    auto debugPlay = playIsOn();
    if (playHasStart && !debugPlay) {
        playResult();
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
