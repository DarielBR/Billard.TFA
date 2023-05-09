#ifndef __P12WINS_SCENE_H__
#define __P12WINS_SCENE_H__

#include "cocos2d.h"

class P2WinsScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(P2WinsScene);
};

#endif // __P12WINS_SCENE_H__
