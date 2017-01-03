//
//  PhysicsSprite.cpp
//  PuzzleGame
//
//  Created by 何遵祖 on 13-6-20.
//
//

#include "PhysicsSprite.h"

const char* contactBegin = "begin";
const char* contactEnd = "end";
const char* preSolve = "Pre";
const char* postSolve = "post";

#define PTM_RATIO 32

using namespace cocos2d;
using namespace cocos2d::extension;

void ContactListener::BeginContact(b2Contact* contact){
    if (contact) {
        //观察者模式用
        POST_MSG(contactBegin);
        contact_list.push_back(mc);
    }
    B2_NOT_USED(contact);
}

void ContactListener::EndContact(b2Contact* contact){
    if (contact) {
        POST_MSG(contactEnd);
        contact_list.clear();
    }
    B2_NOT_USED(contact);
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManfold){
    POST_MSG(preSolve);
}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse){
    POST_MSG(postSolve);
}

SpriteBody::SpriteBody()
: m_pBody(NULL)
{}


bool SpriteBody::isDirty(void)
{
    return true;
}

//viren+
#if 0
CCAffineTransform SpriteBody::nodeToParentTransform(void)
{
    b2Vec2 pos  = m_pBody->GetPosition();
    
    float x = pos.x * PTM_RATIO;
    float y = pos.y * PTM_RATIO;
    
    if ( isIgnoreAnchorPointForPosition() ) {
        x += m_tAnchorPointInPoints.x;
        y += m_tAnchorPointInPoints.y;
    }
    
    // Make matrix
    float radians = m_pBody->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);
    
    if( ! CCPoint::CCPointEqualToPoint(m_tAnchorPointInPoints, CCPointZero) ){
        x += c*-m_tAnchorPointInPoints.x + -s*-m_tAnchorPointInPoints.y;
        y += s*-m_tAnchorPointInPoints.x + c*-m_tAnchorPointInPoints.y;
    }
    
    // Rot, Translate Matrix
    m_tTransform = CCAffineTransformMake( c,  s,
                                         -s,  c,
                                         x,  y );
    
    return m_tTransform;
}
#endif

CCAffineTransform SpriteBody::nodeToParentTransform(void) {
  
  CCAffineTransform  m2;
  b2Vec2 pos  = m_pBody->GetPosition();
  CCPoint p = this->getAnchorPointInPoints();
  float x = pos.x * PTM_RATIO;
  float y = pos.y * PTM_RATIO;
  if ( isIgnoreAnchorPointForPosition() ) {
    x += p.x;
    y += p.y;
  }
    // Make matrix
  float radians = m_pBody->GetAngle();
  float c = cosf(radians);
  float s = sinf(radians);
  if( ! p.equals(CCPointZero) ){
    x += c*-p.x + -s*-p.y;
    y += s*-p.x + c*-p.y;
  }
  m2 = CCAffineTransformMake( c,  s,
                             -s,    c,
                             x,    y );
  return m2;
}
//viren-

void SpriteBody::applyFroce(b2Vec2 force, b2Vec2 point){
    m_pBody->ApplyForce(force, point);
}

void SpriteBody::applyLinearImpulse(b2Vec2 speed, b2Vec2 point){
    m_pBody->ApplyLinearImpulse(speed, point);
}

b2Vec2 SpriteBody::getLinearImpulse(){
    return m_pBody->GetLinearVelocity();
}

void SpriteBody::setTransform(b2Vec2 pos, float32 angle){
    m_pBody->SetTransform(pos, angle);
}

void SpriteBody::setLinearDamping(float damping){
    m_pBody->SetLinearDamping(damping);
}

void SpriteBody::setIsAwake(bool flag){
    m_pBody->SetAwake(flag);
}

void SpriteBody::setFixedRotation(bool flag){
    m_pBody->SetFixedRotation(flag);
}

void SpriteBody::awakeBody(){
    m_pBody->SetAwake(true);
}

void SpriteBody::setAngle(float angle){
    m_pBody->SetAngularVelocity((angle/180.0)*M_PI*30);
}