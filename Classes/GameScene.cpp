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
#include "UnitFactory.h"
#include "Unit.h"

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

    addChild(UnitFactory::sharedInstance().getSpriteBatchNode());
    
    CCSize win_size = CCDirector::sharedDirector()->getWinSize();
    
    Unit *pirate = UnitFactory::sharedInstance().createUnit("Pirate");
    pirate->setPosition(ccp(win_size.width / 2.0, win_size.height / 2.0));
    CCAnimate *animate = CCAnimate::create(pirate->getMovingAnimation());
    pirate->runAction(CCRepeat::create(animate, -1));
    
    
    Unit *soldierAttack = UnitFactory::sharedInstance().createUnit("USSoldier");
    soldierAttack->setPosition(ccp(win_size.width / 3.0, win_size.height / 3.0));
    CCAnimate *animateSoldier = CCAnimate::create(soldierAttack->getAttackAnimation());
    soldierAttack->runAction(CCRepeat::create(animateSoldier, -1));
    
    Unit *soldierWalk = UnitFactory::sharedInstance().createUnit("USSoldier");
    soldierWalk->setPosition(ccp(win_size.width / 1.5, win_size.height / 3.0));
    CCAnimate *animateSoldierWalk = CCAnimate::create(soldierWalk->getMovingAnimation());
    soldierWalk->runAction(CCRepeat::create(animateSoldierWalk, -1));
    
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

