/*
 *  BWransformSprite.cpp
 *  FlyFlyRookie
 *
 *  Created by dscky on 11-10-8.
 *  Copyright 2011 locojoy. All rights reserved.
 *
 */

#include "BWransformSprite.h"
#include "ccUtils.h"

USING_NS_CC;

BWransformSprite::BWransformSprite():
m_SpeedX(0),
m_SpeedY(0)
{
}

BWransformSprite::~BWransformSprite()
{
}

void BWransformSprite::tick(float dt)
{
	updateTextureCoords(dt);
}

BWransformSprite* BWransformSprite::create(const char *pszFileName)
{
	BWransformSprite *pobSprite = new BWransformSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        Texture2D* pTexture = pobSprite->getTexture();
		if (pTexture)
		{
			cocos2d::Texture2D::TexParams texParams = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
			pTexture->setTexParameters(texParams);
		}
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

BWransformSprite* BWransformSprite::create(const char *pszFileName ,Rect pRect)
{
	BWransformSprite *pobSprite = new BWransformSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName,pRect))
    {
        pobSprite->autorelease();
        Texture2D* pTexture = pobSprite->getTexture();
		if (pTexture)
		{
			cocos2d::Texture2D::TexParams texParams = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
			pTexture->setTexParameters(texParams);
		}
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void BWransformSprite::setTransformSpeed(float speedX,float speedY)
{
	m_SpeedX = speedX;
	m_SpeedY = speedY;
}

void BWransformSprite::updateTextureCoords(float dt)
{
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
//     
//	float rateX = m_SpeedX * dt / size.width;
//	float rateY = m_SpeedY * dt / size.height;
//    
//	rateX -= (int)rateX;
//	rateY -= (int)rateY;
//
//	m_sQuad.bl.texCoords.u += rateX;
//	m_sQuad.bl.texCoords.v += rateY;
//    
//	m_sQuad.br.texCoords.u += rateX;
//
//	m_sQuad.br.texCoords.v += rateY;
//    
//	m_sQuad.tl.texCoords.u += rateX;
//	m_sQuad.tl.texCoords.v += rateY;
//    
//	m_sQuad.tr.texCoords.u += rateX;
//	m_sQuad.tr.texCoords.v += rateY;
    
    Size size = getContentSize();
    m_clipWidth = size.width;
    m_clipHeight = size.height;
    
    unsigned long width_pot = ccNextPOT((unsigned long) (size.width));
    unsigned long height_pot = ccNextPOT((unsigned long) (size.height));
    m_u -= m_SpeedX * dt;
    m_v -= m_SpeedY * dt;
    if(m_u < 0)
        m_u = m_clipWidth + m_u;
    if(m_v < 0)
        m_v = m_clipHeight + m_v;
    float rateX = m_u / width_pot;
    float rateY = m_v / height_pot;
    float rateX2 = (m_u + m_clipWidth) / width_pot;
    float rateY2 = (m_v + m_clipHeight) / height_pot;
    
    
    
    _quad.bl.texCoords.u = rateX2;
    _quad.bl.texCoords.v = rateY2;
    
    _quad.br.texCoords.u = rateX;
    _quad.br.texCoords.v = rateY2;
    
    _quad.tl.texCoords.u = rateX2;
    _quad.tl.texCoords.v = rateY;
    
    _quad.tr.texCoords.u = rateX;
    _quad.tr.texCoords.v = rateY;

}
