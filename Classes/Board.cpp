#include "Board.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Board::createScene()
{
    return Board::create();
}

bool Board::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    initTiles();
    initPlayer();
    initClickListener();
    startDice();
    
    return true;
}

void Board::initTiles()
{
    Size screenSize = Director::getInstance()->getVisibleSize();
    
    float yPosition = screenSize.height/3;
    
    //First tile
    auto stoneTile = Sprite::create("stone.png");
    stoneTile->setScale(0.85, 0.5);
    
    stoneTile->setPosition(Vec2(stoneTile->getContentSize().width / 2, yPosition));
    
    addChild(stoneTile);
    
    
    firstTileSize = stoneTile->getContentSize();
    firstTilePosition = stoneTile->getPosition();
    
    //6 tiles
    for(int i = 1; i < 7; i++)
    {
        Sprite* tile = Sprite::create("grass.png");
        
        tile->setScale(0.85, 0.5);
        
        float xPosition = screenSize.width / 7 * i + tile->getContentSize().width / 2;
        
        tile->setPosition(Vec2(xPosition, yPosition));
        
        addChild(tile);
        
        //SceneLabel
        auto label = Label::create();
        label->setScale(1.f/0.85, 2.f);
        label->setPosition(Vec2(tile->getContentSize().width/2, 0));
        
        tile->addChild(label);
        label->setString(sceneNames[i-1]);
    }
}

void Board::initPlayer()
{
    playerSprite = Sprite::create("p_stand.png");
    playerSprite->setScale(0.5);
    
    float xPosition = firstTilePosition.x;
    float yPosition = firstTilePosition.y + playerSprite->getContentSize().height/2 - 6;
    
    playerSprite->setPosition(Vec2(xPosition, yPosition));
    
    addChild(playerSprite);
}

void Board::initClickListener()
{
    auto mouseListener = EventListenerTouchOneByOne::create();
    
    mouseListener->onTouchBegan = [=](Touch* touch, Event* event){
        stopDiceAndMove();
        return true;
    };
    mouseListener->onTouchMoved = [=](Touch* touch, Event* event){};
    
    mouseListener->onTouchEnded = [=](Touch* touch, Event* event){};
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void Board::stopDiceAndMove()
{
    stopDice();
    
    Size screenSize = Director::getInstance()->getVisibleSize();
    
    Vec2 finalPosition = Vec2(screenSize.width / 7 * actualNumber + firstTileSize.width / 2, playerSprite->getPosition().y);
    
    auto jumps = JumpTo::create(actualNumber * 0.6, finalPosition, 60, actualNumber);
    
    playerSprite->runAction(jumps);
    
    schedule([=](float dt){
        Director::getInstance()->pushScene(sceneConstructors[actualNumber-1]());
    }, actualNumber, 1, 0, "changeScene");
}

void Board::startDice()
{
    Size screenSize = Director::getInstance()->getVisibleSize();
    auto diceLabel = Label::create();
    
    diceLabel->setPosition(Vec2(screenSize/3.f * 2.f));
    diceLabel->setSystemFontSize(40);
    
    addChild(diceLabel);
    
    schedule([=](float dt){

        actualNumber %= sceneConstructors.size();
        actualNumber++;
        
        string text = "";
        text.push_back(actualNumber+'0');
        diceLabel->setString(text);
        
    }, 0.1f, -1, 0, "changeDiceNumber");
    
}

void Board::stopDice()
{
    unschedule("changeDiceNumber");
}

