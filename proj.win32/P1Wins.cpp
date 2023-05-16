#include "P1Wins.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "audio/include/AudioEngine.h"
USING_NS_CC;

Scene* P1WinsScene::createScene()
{
    return P1WinsScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool P1WinsScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto center = Vec2(visibleSize.width / 2 + 25, visibleSize.height / 2);

    /////////////////////////////
    // 2. Starting audio engine and reproducing intro background music
    AudioEngine::setEnabled(true);
    int intro = AudioEngine::play2d("audio/BilliardsAmbience.mp3", true, 0.5f, nullptr);
    AudioEngine::resume(intro);

    //////////////////////////////
    //3. Crreating a sprite for Game Title
    auto label = Sprite::create("img/P1Wins.png");
    label->setScale(1.10f);
    label->setPosition(Vec2(center.x, center.y + 200));
    this->addChild(label, 0);

    /////////////////////////////
    // 4. add a menu with an array of MenuItem type and lambda fucntions

    Vector<MenuItem*> menuItems;

    auto exitItem = MenuItemImage::create("img/exit.png", "img/exit.png",
        [=](Ref* sender) {
            //handling music and sounds
            AudioEngine::pause(intro);
            Director::getInstance()->end();
        });
    exitItem->setPosition(Vec2(exitItem->getPosition().x, exitItem->getPosition().y - 250));
    menuItems.pushBack(exitItem);

    auto playItem = MenuItemImage::create("img/reset.png", "img/reset.png",
        [=](Ref* sender) {
            //handling music and sounds
            AudioEngine::pause(intro);
            auto director = Director::getInstance();
            director->popToRootScene();
        });
    playItem->setPosition(Vec2(playItem->getPosition().x, playItem->getPosition().y - 100));
    menuItems.pushBack(playItem);

    auto menu = Menu::createWithArray(menuItems);
    menu->setPosition(center);
    menu->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->addChild(menu, 10);

    return true;
}