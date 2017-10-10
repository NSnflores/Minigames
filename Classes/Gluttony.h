#ifndef __GLUTTONY_SCENE_H__
#define __GLUTTONY_SCENE_H__

#include "cocos2d.h"

class Gluttony : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    enum CharacterType {PLAYER, POINT, ENEMY};
    
    enum Direction {UP, DOWN, LEFT, RIGHT};
    
    cocos2d::DrawNode* drawNode = cocos2d::DrawNode::create();
    
    cocos2d::Vec2 borders;
    float charactersSize = 10.0f;
    float speed;
    
    virtual bool init();
    
    void update(float deltaTime);
    
    void drawCharacter(CharacterType type, cocos2d::Vec2 gridPosition);
    
    void loadGame();
    
    void configKeyboard();
    
    // Player
    cocos2d::Vec2 playerPosition;
    Direction playerDirection;
    
    void movePlayer();
    
    // Point
    cocos2d::Vec2 pointPosition;
    
    void createPoint();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Gluttony);
};

#endif // __GLUTTONY_SCENE_H__
