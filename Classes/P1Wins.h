#ifndef __P1WINS_SCENE_H__
#define __P1WINS_SCENE_H__

#include "cocos2d.h"

class P1WinsScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(P1WinsScene);
};

#endif // __P1WINS_SCENE_H__