/*
 *  BWransformSprite.h
 *  FlyFlyRookie
 *
 *  Created by dscky on 11-10-8.
 *  Copyright 2011 locojoy. All rights reserved.
 *
 */

#ifndef __BWransformSprite_H__
#define __BWransformSprite_H__

#include "cocos2d.h"

USING_NS_CC;

class BWransformSprite : public cocos2d::Sprite
{
public:
	BWransformSprite();
	virtual		~BWransformSprite();
	static              BWransformSprite* create(const char *pszFileName);
	static              BWransformSprite* create(const char *pszFileName ,Rect pRect);
	void			    setTransformSpeed(float speedX,float speedY);
	virtual void	    tick(float dt);
protected:
	void			updateTextureCoords(float dt);
    
private:
	float		m_SpeedX;
	float		m_SpeedY;
    
    float       m_clipWidth;
    float       m_clipHeight;
    float       m_u;
    float       m_v;
};

#endif // __BWransformSprite_H__	


/*
 CCSize size = getContentSize();
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
 
 m_sQuad.bl.texCoords.u = rateX2;
 m_sQuad.bl.texCoords.v = rateY2;
 
 m_sQuad.br.texCoords.u = rateX;
 m_sQuad.br.texCoords.v = rateY2;
 
 m_sQuad.tl.texCoords.u = rateX2;
 m_sQuad.tl.texCoords.v = rateY;
 
 m_sQuad.tr.texCoords.u = rateX;
 m_sQuad.tr.texCoords.v = rateY;
 
*/