#ifndef __Chips_SCENE_H__
#define __Chips_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>

USING_NS_CC;
using namespace ui;

class Chips : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    std::vector<Sprite*> chips;
    
    void initComponents();
    void initClickListener();
    
    bool isTouchingChip(Sprite* chip, Vec2 touchPosition);
    
    Chips* context = this;
    
    CREATE_FUNC(Chips);
};

#endif // Chips
