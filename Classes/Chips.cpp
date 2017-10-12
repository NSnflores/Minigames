#include "Chips.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Chips::createScene()
{
    return Chips::create();
}

bool Chips::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    initComponents();
    initClickListener();
    
    return true;
}

void Chips::initComponents()
{
    auto screenSize = Director::getInstance()->getVisibleSize();
    
    schedule([=](float dt){
        
        Sprite* chip = Sprite::create("circle.png");
        float xPosition = random(chip->getContentSize().width / 2, screenSize.width - chip->getContentSize().width / 2);
        float yPosition = random(chip->getContentSize().height / 2, screenSize.height - chip->getContentSize().height / 2);
        
        chip->setPosition(Vec2(xPosition, yPosition));
        
        int chipNumber = random(1,8);
        chip->setTag(chipNumber);
        chip->setName("chip");
     
        chips.push_back(chip);
        context->addChild(chip);
        
    }, 1.5f, 10, 0, "spawnerCallBack");
    
}

void Chips::initClickListener()
{
    auto mouseListener = EventListenerTouchOneByOne::create();
    
    mouseListener->onTouchBegan = [=](Touch* touch, Event* event){
        for(int i = 0; i < chips.size(); i++)
        {
            if(isTouchingChip(chips.at(i), touch->getLocation())){
                chips.at(i)->runAction(RemoveSelf::create(true));
            }
        }
        return true;
    };
    mouseListener->onTouchMoved = [=](Touch* touch, Event* event){};
    
    mouseListener->onTouchEnded = [=](Touch* touch, Event* event){};
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

bool Chips::isTouchingChip(Sprite* chip, Vec2 touchPosition)
{
    float xSquared = chip->getPosition().x - touchPosition.x;
    xSquared *= xSquared;
    
    float ySquared = chip->getPosition().y - touchPosition.y;
    ySquared *= ySquared;

    float radiusSquared = (chip->getContentSize().width/ 2) * (chip->getContentSize().width / 2);
    return xSquared + ySquared < radiusSquared;
}
