#include "Gluttony.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Gluttony::createScene()
{
    return Gluttony::create();
}

bool Gluttony::init()
{
    
    if ( !Scene::init() )
    {
        return false;
    }
    
    addChild(drawNode);
    configKeyboard();
    
    auto screenSize = Director::getInstance()->getVisibleSize();
    borders = screenSize / (charactersSize * 2);
    
    loadGame();

    return true;
}

void Gluttony::loadGame()
{
    speed = 1.0f;
    this->schedule(schedule_selector(Gluttony::update), speed);
    
    playerDirection = RIGHT;
    auto screenSize = Director::getInstance()->getVisibleSize();
    playerPosition = screenSize / (charactersSize * 4);
    drawCharacter(PLAYER, playerPosition);
    
    createPoint();
}

void Gluttony::configKeyboard()
{
    auto eventListener = EventListenerKeyboard::create();
    
    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch(keyCode)
        {
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
                playerDirection = UP;
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                playerDirection = DOWN;
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                playerDirection = RIGHT;
                break;
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                playerDirection = LEFT;
                break;
            default:
                break;
        }
    };
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}

void Gluttony::update(float deltaTime)
{
    movePlayer();
    
    drawNode->clear();
    
    drawCharacter(PLAYER, playerPosition);
    drawCharacter(POINT, pointPosition);
}

void Gluttony::drawCharacter(CharacterType type, Vec2 gridPosition)
{
    Color4F color;
    switch (type) {
        case PLAYER:
            color = Color4F::WHITE;
            break;
        case POINT:
            color = Color4F::GREEN;
            break;
        case ENEMY:
            color = Color4F::RED;
            break;
    }
    drawNode->drawDot(gridPosition * (charactersSize * 2) + Vec2(charactersSize, charactersSize), charactersSize, color);
}

void Gluttony::movePlayer()
{
    switch (playerDirection) {
        case UP:
            playerPosition.y++;
            break;
        case DOWN:
            playerPosition.y--;
            break;
        case RIGHT:
            playerPosition.x++;
            break;
        case LEFT:
            playerPosition.x--;
            break;
    }
}

void Gluttony::createPoint() {
    pointPosition = Vec2(cocos2d::random() % (int) borders.x, cocos2d::random() % (int) borders.y);
    drawCharacter(POINT, pointPosition);
}
