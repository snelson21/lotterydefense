//
//  GameScene.h
//  LotteryDefense
//
//  Created by Steele Nelson on 2/20/14.
//
//

#ifndef __LotteryDefense__GameScene__
#define __LotteryDefense__GameScene__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public CCLayerColor
{
public:
    /**
     @brief  GameScene constructor
     */
    GameScene();
    
    /**
     @brief  GameScene destructor
     */
    ~GameScene();
    
    /**
     @brief  GameScene default initializer
     */
    virtual bool init();
    
    /**
     @brief  Autorelease instance creation macro for GameScene
     */
    CREATE_FUNC(GameScene);
    
    /**
     @brief  Scene creation function.  An autoreleased GameScene will be a child of a generic CCScene.  
             The generic CCScene is returned.
     @return a generic autoreleased CCScene with an autoreleased GameScene set as it's child
     */
    static CCScene *scene();
    
    /**
     @brief  Main scene update loop callback
     @param  the amount of time passed since the last update was called
     */
    void update(float timeElapsed);
    
    /**
     @brief  Function where work is done within the fixed timestep of the game loop
     */
    void doWork();

protected:
    float _timeAccumulator;
};

#endif /* defined(__LotteryDefense__GameScene__) */
