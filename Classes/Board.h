#ifndef __Board_SCENE_H__
#define __Board_SCENE_H__

#include "cocos2d.h"

#include "JumpingHippo.h"
#include "Chips.h"
#include "Drow.h"
#include "Gluttony.h"

#include "ui/CocosGUI.h"
#include <vector>


USING_NS_CC;
using namespace ui;
using namespace std;

typedef Scene* (*SceneConstructors) ();

class Board : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void initTiles();
    void initPlayer();
    void initClickListener();
    
    Sprite* playerSprite;
    
    vector<SceneConstructors> sceneConstructors = {
        JumpingHippo::createScene,
        Chips::createScene,
        Drow::createScene,
        Gluttony::createScene,
    };
    
    void throwDiceAndMove();
    
    Vec2 firstTilePosition;
    Size firstTileSize;
    
    CREATE_FUNC(Board);
};

#endif // Chips
