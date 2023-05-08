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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Ball.h"
#include "Table.h"
#include "Cue.h"

#define LEFT1 625,160
#define LEFT2 589,160
#define LEFT3 554,160
#define LEFT4 518,160
#define LEFT5 482,160
#define LEFT6 446,160
#define LEFT7 409,160
#define LEFT8 374,160
#define RIGHT1 875,160
#define RIGHT2 910,160
#define RIGHT3 947,160
#define RIGHT4 982,160
#define RIGHT5 1018,160
#define RIGHT6 1053,160
#define RIGHT7 1089,160
#define RIGHT8 1123,160

class HelloWorld : public cocos2d::Scene
{
private:
    cocos2d::Vec2 forceCue = cocos2d::Vec2(cocos2d::Vec2::ZERO);
    //bool gameStart = false;
    bool gameIsOn;//it will indicate that the game has started, starts flase and turns on with the first cue hit only.
    bool openTable;
    bool playHasStart;
    bool onPlay;
    int firstContact;
    int counterPocketed;
    bool moveCueBAll;
    bool illegalPlay;
    int playerInTurn;
    bool player1Solid;
    bool rackScoreP1[8];
    bool rackScoreP2[8];


    cocos2d::EventListenerTouchOneByOne* playerListener;
    //Table _table = -1;
public:
    static cocos2d::Scene* createScene();
    //cocos2d
    virtual bool init();
    void update(float dt);
    void menuCloseCallback(cocos2d::Ref* pSender);
    //game play
    bool isContactWith8Bad();
    bool otherBallGroupHittedFirst();
    void playResult();
    bool playIsOn();
    void playGame();
    void switchPlayer();
    bool allBodiesStopped();
    void ballFallsIntoPocket(cocos2d::Node* node, Table table, int pocketTag, int ballTag);
    cocos2d::Vec2 getRackPosition(int ballTag);
    void playerChoice(int ballTag);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
