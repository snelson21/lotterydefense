//
//  GameScene.cpp
//  LotteryDefense
//
//  Created by Steele Nelson on 2/20/14.
//
//

#include "GameScene.h"
#include "cocos2d.h"
#include "AppMacros.h"

USING_NS_CC;
using namespace std;

GameScene::GameScene()
{
    
}

GameScene::~GameScene()
{
    
}

bool GameScene::init()
{
    //super (CCLayerColor) init
    if( ! CCLayerColor::initWithColor(BACKGROUND_COLOR))
    {
        return false;
    }
    
    //schedule the update
    this->schedule(schedule_selector(GameScene::update), FIXED_TIMESTEP);
    
    this->setTouchEnabled(true);
    
    return true;
}

CCScene *GameScene::scene()
{
    CCScene *scene = CCScene::create();
    
    GameScene *layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}


void GameScene::update(float timeElapsed)
{
    float timeToRun = timeElapsed + _timeAccumulator;
    while(timeToRun >= FIXED_TIMESTEP)
    {
        timeToRun = timeToRun - FIXED_TIMESTEP;
        doWork();
    }
    _timeAccumulator = timeToRun;
}

void GameScene::doWork()
{
    
}

