#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    Vec4 color(0.5f, 0.5f, 0.5f, 1.0f);
    m_ctime = 0.01f;  // メンバ変数
    GLfloat gtime = 1.0f;
    GLfloat radius = 5.0f;
    
    auto fileUtiles = FileUtils::getInstance();
    auto fragmentFullPath = fileUtiles->fullPathForFilename("glow.fsh");
    auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
    
    auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
    auto glProgramState = GLProgramState::getOrCreateWithGLProgram(glprogram);
    
    glProgramState->setUniformVec4("u_outlineColor", color);
    glProgramState->setUniformFloat("u_ctime", m_ctime);
    glProgramState->setUniformFloat("u_threshold", gtime);
    glProgramState->setUniformFloat("u_radius", radius);
    
    sprite->setGLProgramState(glProgramState);
    
    glProgramState->setUniformCallback("u_ctime", CC_CALLBACK_2(HelloWorld::callbackColor, this));

    // add the sprite as a child to this layer
    this->addChild(sprite, 1);
    
    return true;
}
void HelloWorld::callbackCTime(GLProgram* glProgram, Uniform* uniform)
{
    m_ctime += 0.05f;
    glProgram->setUniformLocationWith1f(uniform->location, (sin(m_ctime) + 1)/2);
}
void HelloWorld::callbackColor(GLProgram* glProgram, Uniform* uniform)
{
    float r = CCRANDOM_0_1();
    float g = CCRANDOM_0_1();
    float b = CCRANDOM_0_1();
    float a = 1.0f;
    
    glProgram->setUniformLocationWith4f(uniform->location, r, g, b, a);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
