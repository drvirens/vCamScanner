//
//  BasicPhysics.cpp
//  PuzzleGame
//
//  Created by 何遵祖 on 13-6-19.
//
//

#include "BasicPhysics.h"

using namespace cocos2d;

static BasicPhysics* gamePhysics;

BasicPhysics* BasicPhysics::sharedPhysics(){
    if (!gamePhysics) {
        gamePhysics=new BasicPhysics();
        gamePhysics->initWithPhysics();
    }
    return gamePhysics;
}

void BasicPhysics::end(){
    CC_SAFE_RELEASE(gamePhysics);
    gamePhysics=NULL;
    
    //删除世界
    CC_SAFE_DELETE(world_);
    world_=NULL;
    
    CC_SAFE_DELETE(contactListener);
    CC_SAFE_DELETE(m_debugDraw);
}

void BasicPhysics::initWithPhysics(){
    PlistLoader *loader=PlistLoader::initWithPlistFile("PhysicsWorldPlist.plist");
    CCString *pointStr=(CCString*)loader->getObjectFromFileKey("Gravity");
    CCPoint gravityPoint=CCPointFromString(pointStr->getCString());
    
    CCString *ratioString=(CCString*)loader->getObjectFromFileKey("PTM_RATIO");
    PTM_RATIO=ratioString->intValue();
    
    b2Vec2 gravity;
    gravity.Set(gravityPoint.x, gravityPoint.y);
    
    world_=new b2World(gravity);
    
    CCString* allowSleepingStr=dynamic_cast<CCString*>(loader->getObjectFromFileKey("AllowSleeping"));
    bool allowSleeping=allowSleepingStr->boolValue();
    world_->SetAllowSleeping(allowSleeping);
    
    CCString* contiunousPhysicsStr=dynamic_cast<CCString*>(loader->getObjectFromFileKey("ContinuousPhysics"));
    bool contiunousPhysics=contiunousPhysicsStr->boolValue();
    world_->SetContinuousPhysics(contiunousPhysics);
    
    //是否为调试模式
    CCString* isDebugingStr=dynamic_cast<CCString*>(loader->getObjectFromFileKey("Debug"));
    bool isDebuging=isDebugingStr->boolValue();
    if (isDebuging) {
        m_debugDraw = new GLESDebugDraw(PTM_RATIO);
        world_->SetDebugDraw(m_debugDraw);
        
        uint32 flags=0;
        flags += b2Draw::e_shapeBit;
        flags += b2Draw::e_jointBit;
        flags += b2Draw::e_aabbBit;
        flags += b2Draw::e_pairBit;
        flags += b2Draw::e_centerOfMassBit;
        m_debugDraw->SetFlags(flags);
    }
    
    //碰撞事件
    contactListener = new ContactListener();
    world_->SetContactListener(contactListener);
    
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    groundBody=world_->CreateBody(&groundBodyDef);
    b2EdgeShape groundBox;
    
    //产生边缘
    this->crateEdgeShape(groundBody, groundBox);
}

void BasicPhysics::update(float dt){
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    
    int velocityIterations = 8;
    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world_->Step(dt, velocityIterations, positionIterations);
    
    //Iterate over the bodies in the physics world
    for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            //Synchronize the AtlasSprites position and rotation with the corresponding body
            CCSprite* myActor = (CCSprite*)b->GetUserData();
            myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }
    }
}

void BasicPhysics::crateEdgeShape(b2Body *groundBody, b2EdgeShape groundBox){
    CCSize s=CCDirector::sharedDirector()->getWinSize();
    PlistLoader *loader=PlistLoader::initWithPlistFile("PhysicsWorldPlist.plist");
    CCString *edgeWidthStr=dynamic_cast<CCString*>(loader->getObjectFromFileKey("EdgeWidth"));
    int edgeWidth=edgeWidthStr->intValue();
    CCString *edgeHeightStr=dynamic_cast<CCString*>(loader->getObjectFromFileKey("EdgeHeight"));
    int edgeHeight=edgeHeightStr->intValue();
    
    //产生四边的碰撞墙壁
    //底部
    groundBox.Set(b2Vec2(-edgeWidth/PTM_RATIO,(s.height-edgeHeight)/PTM_RATIO),
                  b2Vec2(edgeWidth*2/PTM_RATIO,(s.height-edgeHeight)/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    //顶部
    groundBox.Set(b2Vec2(-edgeHeight/PTM_RATIO,s.height/PTM_RATIO),
                  b2Vec2(edgeWidth*2/PTM_RATIO,s.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    //左边
    groundBox.Set(b2Vec2(-edgeWidth/PTM_RATIO,s.height/PTM_RATIO),
                  b2Vec2(-edgeWidth/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);
    //右边
    groundBox.Set(b2Vec2(edgeWidth*2/PTM_RATIO,s.height/PTM_RATIO), b2Vec2(edgeWidth*2/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);
}

void BasicPhysics::createBody(SpriteBody *sprite,
                              CCPoint position,
                              b2BodyType type,
                              float density,
                              float friction,
                              float restitution,
                              CCSize sprContentSize){
    b2BodyDef bodyDef;
    bodyDef.type=type;
    bodyDef.position.Set(position.x/PTM_RATIO, position.y/PTM_RATIO);
    bodyDef.userData=sprite;
    
    //在物理世界中产生body
    b2Body *body=world_->CreateBody(&bodyDef);
    
    //产生一个squareBox
    //产生一个square box
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(sprContentSize.width/2/PTM_RATIO,sprContentSize.height/2/PTM_RATIO);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape=&dynamicBox;
    fixtureDef.density=density;//密度
    fixtureDef.friction=friction;//设置摩擦
    fixtureDef.restitution=restitution;//恢复
    
    body->CreateFixture(&fixtureDef);
    
    sprite->setPhysicsBody(body);
}

void BasicPhysics::createBodyInCircle(SpriteBody *sprite,
                                      CCPoint position,
                                      b2BodyType type,
                                      float density,
                                      float friction,
                                      float restitution,
                                      float radius){
    b2BodyDef bodyDef;
    bodyDef.type=type;
    bodyDef.position.Set(position.x/PTM_RATIO, position.y/PTM_RATIO);
    bodyDef.userData=sprite;
    
    //在物理世界中产生body
    b2Body *body=world_->CreateBody(&bodyDef);
    
    //产生一个circleBody
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius=radius;
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape=&dynamicCircle;
    fixtureDef.density=density;//密度
    fixtureDef.friction=friction;//设置摩擦
    fixtureDef.restitution=restitution;//恢复
    
    body->CreateFixture(&fixtureDef);
    
    sprite->setPhysicsBody(body);
}
void BasicPhysics::destroyBody(SpriteBody *sprite){
    b2Body *spriteBody=sprite->getPhysicsBody();
    world_->DestroyBody(spriteBody);
}

void BasicPhysics::draw(){
    PlistLoader *loader=PlistLoader::initWithPlistFile("PhysicsWorldPlist.plist");
    CCString* isDebugingStr=dynamic_cast<CCString*>(loader->getObjectFromFileKey("Debug"));
    bool isDebuging=isDebugingStr->boolValue();
    
    if (!isDebuging) {
        return;
    }
    
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
    kmGLPushMatrix();
    world_->DrawDebugData();
    kmGLPopMatrix();
}