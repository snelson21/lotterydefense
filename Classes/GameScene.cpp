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
#include "Map.h"
#include "GameTile.h"

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
    
    this->setTouchEnabled(true);
    
    Map *map = new Map();
    map->init();
    
    CCDrawNode *drawNode = CCDrawNode::create();
    
    for( int i = 0; i < map->getTotalTiles(); i++ )
    {
        GameTile *tile = map->getTiles()[i];
        drawNode->drawDot(tile->getPosition(), 10.0f, ccc4f(1.0f, 0.0f, 0.0f, 1.0f));
        if(tile->up)
        {
            drawNode->drawSegment(tile->getPosition(), tile->up->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
        if(tile->down)
        {
            drawNode->drawSegment(tile->getPosition(), tile->down->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
        if(tile->left)
        {
            drawNode->drawSegment(tile->getPosition(), tile->left->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
        if(tile->right)
        {
            drawNode->drawSegment(tile->getPosition(), tile->right->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
        if(tile->upLeft)
        {
            drawNode->drawSegment(tile->getPosition(), tile->upLeft->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
        if(tile->downLeft)
        {
            drawNode->drawSegment(tile->getPosition(), tile->downLeft->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
        if(tile->upRight)
        {
            drawNode->drawSegment(tile->getPosition(), tile->upRight->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
        if(tile->downRight)
        {
            drawNode->drawSegment(tile->getPosition(), tile->downRight->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
    }
    
    addChild(drawNode);

    addChild(UnitFactory::sharedInstance().getSpriteBatchNode());
    
    CCSize win_size = CCDirector::sharedDirector()->getWinSize();
    
    CCLog("Winsize width: %f height: %f", win_size.width, win_size.height);
    
    Unit *pirate = UnitFactory::sharedInstance().createUnit("Pirate");
    pirate->setAlliance(Neutral);
    pirate->setPosition(ccp(win_size.width / 2.0, win_size.height / 2.0));
    
    CCRect PirateTextureRect = pirate->getTextureRect();
    CCLog("Pirate Width: %f Height: %f", PirateTextureRect.size.width, PirateTextureRect.size.height);
    
    Unit *soldierAttack = UnitFactory::sharedInstance().createUnit("USSoldier");
    soldierAttack->setAlliance(Friendly);
    soldierAttack->setPosition(ccp(win_size.width / 3.0, win_size.height / 3.0));
    
    Unit *soldierWalk = UnitFactory::sharedInstance().createUnit("USSoldier");
    soldierWalk->setAlliance(Enemy);
    soldierWalk->setPosition(ccp(win_size.width / 1.5, win_size.height / 3.0));
    
    CCRect textureRect = soldierWalk->getTextureRect();
    CCLog("Soldier Width: %f Height: %f", textureRect.size.width, textureRect.size.height);
    
    //schedule the update
    this->schedule(schedule_selector(GameScene::update), FIXED_TIMESTEP);
    
    
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


