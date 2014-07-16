
/*
 *
 *  Created by wangbin
 *
 */


#include "CCLabelStroke.h"

//=============================================================
//=============================================================
CCLabelStroke::CCLabelStroke():
m_renderTexture(NULL),
m_lineWidth(0),
m_pLabelStroke(NULL)
{
}
//=============================================================
//=============================================================
CCLabelStroke::~CCLabelStroke()
{
    if (m_pLabelStroke)
    {
         m_pLabelStroke->autorelease();
    }
}
//=============================================================
//=============================================================
void CCLabelStroke::setString(const char *label)
{
    CCLabelTTF::setString(label);
    if (m_pLabelStroke)
    {
        m_pLabelStroke->setString(label);
    }
    
    if(m_renderTexture)
    {
        m_renderTexture->removeFromParentAndCleanup(true);
        m_renderTexture = NULL;
        setStroke(m_lineWidth, m_lineColor,m_strokeType);
    }
   
}
//=============================================================
//=============================================================
CCLabelStroke * CCLabelStroke::labelWithString(const char *label, Size dimensions, TextHAlignment alignment, const char *fontName, float fontSize,float lineWidth,Color3B lineColor,StrokeTypeEnum strokeType)
{
    CCLabelStroke* strokeLabel = labelWithString(label,dimensions,alignment,fontName,fontSize);
      if(lineWidth!=0)
    {
        strokeLabel->setStroke(lineWidth, lineColor,strokeType);
    }
    return strokeLabel;
}
//=============================================================
//=============================================================
CCLabelStroke * CCLabelStroke::labelWithString(const char *label, const char *fontName, float fontSize,float lineWidth, Color3B lineColor,StrokeTypeEnum strokeType)
{
    if(strlen(label) == 0)
    {
        label = " ";
    }
    CCLabelStroke* strokeLabel = labelWithString(label,fontName,fontSize);
    if(lineWidth!=0)
    {
      
        strokeLabel->m_pLabelStroke=CCLabelTTF::create(label, fontName, fontSize);
        strokeLabel->m_pLabelStroke->retain();
        strokeLabel->m_pLabelStroke->setColor(lineColor);
      
        strokeLabel->setStroke(lineWidth, lineColor,strokeType);
    }
   
    return strokeLabel;
}
//=============================================================
//=============================================================
CCLabelStroke * CCLabelStroke::labelWithString(const char *label, Size dimensions, TextHAlignment alignment, const char *fontName,float fontSize)
{
    CCLabelStroke* strokeLabel = new CCLabelStroke();
    strokeLabel->initWithString(label, fontName, fontSize, dimensions, alignment, TextVAlignment::CENTER);
    strokeLabel->autorelease();
    return strokeLabel;
}
//=============================================================
//=============================================================
CCLabelStroke * CCLabelStroke::labelWithString(const char *label, const char *fontName, float fontSize)
{
    CCLabelStroke* strokeLabel = new CCLabelStroke();
    strokeLabel->initWithString(label,fontName, fontSize);
    strokeLabel->autorelease();
    return strokeLabel;
}
//=============================================================
//=============================================================
CCLabelStroke *  CCLabelStroke::labelWithData(unsigned char* pMultiData, unsigned int nLen, Size dimensions)
{
    CCLabelStroke* strokeLabel = new CCLabelStroke();
    strokeLabel->initWithData(pMultiData,nLen,dimensions.width,dimensions.height);
    strokeLabel->autorelease();
    return strokeLabel;
}
//=============================================================
//=============================================================
CCLabelStroke * CCLabelStroke::labelWithData(unsigned char* pMultiData,unsigned int unlen, Size dimensions,TextHAlignment alignment, const char *fontName, float fontSize,float lineWidth, Color3B lineColor,StrokeTypeEnum strokeType)
{    
    CCLabelStroke* strokeLabel = new CCLabelStroke();
    strokeLabel->initWithData(pMultiData,unlen,dimensions.width,dimensions.height);
    strokeLabel->autorelease();
    if(lineWidth!=0)
    {
        strokeLabel->setStroke(lineWidth, lineColor,strokeType);
    }
    return strokeLabel;
}
//=============================================================
//=============================================================
bool CCLabelStroke::initWithData(unsigned char* pMultiData, unsigned int unlen, unsigned int texWidth, unsigned int texHeight)
{
    //bool initWithData(const void *data, long dataLen, Texture2D::PixelFormat pixelFormat, long pixelsWide, long pixelsHigh, const Size& contentSize);

    
//    CCTexture2D*  texture = new CCTexture2D();
//    texture->autorelease();
//    texture->initWithData(pMultiData,unlen, Texture2D::PixelFormat::RGBA8888, texWidth, texHeight, CCSize(texWidth,texHeight));
//    initWithTexture(texture);
    
	return true;
}
//=============================================================
//=============================================================
void CCLabelStroke::setStroke(float size,Color3B color,StrokeTypeEnum strokeType)
{
//    m_lineWidth = size;
//    m_lineColor = color;
//    m_strokeType = strokeType;
//    
//    Size labelSize = getTexture()->getContentSize();
//    Point labelAnchorPoint = getAnchorPoint();
//    Point originalPos = getPosition();
//    Color3B originalColor = getColor();
//    BlendFunc originalBlend = getBlendFunc();
//    float originalScale = getScale();
//    bool bOldVisible = isVisible();
//    
//    float scaleStroke = 2.0f; 
//    float w = labelSize.width + m_lineWidth*2;
//    float h = labelSize.height + m_lineWidth*2;
//    w *= scaleStroke;
//    h *= scaleStroke;
//    RenderTexture* renderRexture = CCRenderTexture::create(w,h, Texture2D::PixelFormat::RGBA8888);
//
//    setColor(color);
//    setBlendFunc((BlendFunc) { GL_SRC_ALPHA, GL_ONE });
//    
//    float moveX = labelSize.width * (labelAnchorPoint.x - 0.5) * scaleStroke;
//    float moveY = labelSize.height * (labelAnchorPoint.y - 0.5) * scaleStroke;
//
//    Point position = Point(w/2 + moveX, h/2 + moveY);
//    renderRexture->begin();
//    
//    setVisible(true);
//    
//    float degreeX = 0;
//    float degreeY = 0;
//    
//    if(strokeType != STE_ALL)
//    {
//        switch (strokeType)
//        {
//            case STE_UP:
//            {
//                degreeX = 0; //0
//                degreeY = 0; //1
//            }
//                break;
//                
//            case STE_DOWN:
//            {
//                degreeX = 0;    //0
//                degreeY = 180;  //-1
//            }
//                break;
//            case STE_LEFT:
//            {
//                degreeX = -90; //-1
//                degreeY = 90;  //0
//            }
//                break;
//            case STE_RIGHT:
//            {
//                degreeX = 90;  //1
//                degreeY = 90;  //0
//                
//            }
//                break;
//            case STE_LEFT_UP:
//            {
//                degreeX = -90;  //-1
//                degreeY = 0;   // 1
//            }
//                break;
//            case STE_RIGHT_UP:
//            {
//                degreeX = 90;  //1
//                degreeY = 0; //1
//            }
//                break;
//            case STE_LEFT_DOWN:
//            {
//                degreeX = -90; //-1
//                degreeY = 180;  //-1
//            }
//                break;
//                
//            case STE_RIGHT_DOWN:
//            {
//                degreeX = 90;  //1
//                degreeY = 180;  //-1
//            }
//                break;
//            default:
//                break;
//        }
//        setScale(scaleStroke);
//        setPosition(Point(position.x + sin(CC_DEGREES_TO_RADIANS(degreeX)) * m_lineWidth * scaleStroke,
//                        position.y + cos(CC_DEGREES_TO_RADIANS(degreeY)) * m_lineWidth * scaleStroke));
//        visit();
//
//    }
//    else
//    {
//        for (int i=0; i<=360; i+=15)
//        {
//            
//            LabelTTF* pLabel=this;
//            if (m_pLabelStroke)
//            {
//                pLabel=m_pLabelStroke;
//                pLabel->setHorizontalAlignment(getHorizontalAlignment());
//                pLabel->setVerticalAlignment(getVerticalAlignment());
//                pLabel->setDimensions(getDimensions());
//            }
//            pLabel->setAnchorPoint(getAnchorPoint());
//            pLabel->setScale(scaleStroke);
//            pLabel->setPosition(Point(position.x + sin(CC_DEGREES_TO_RADIANS(i)) * m_lineWidth * scaleStroke,
//                           position.y + cos(CC_DEGREES_TO_RADIANS(i)) * m_lineWidth * scaleStroke));
//            pLabel->visit();
//          
//        }
//    }
//    renderRexture->end();
//    setAnchorPoint(labelAnchorPoint);
//    setPosition(originalPos);
//    setColor(originalColor);
//    setBlendFunc(originalBlend);
//    setScale(originalScale);
//    setVisible(bOldVisible);
//    Point strokePosition = Point(labelSize.width/2, labelSize.height/2);
//    renderRexture->setPosition(strokePosition);
//    renderRexture->setScale(1/scaleStroke);
//    addChild(renderRexture,-1);
//    m_renderTexture = renderRexture;
}
//=============================================================
//=============================================================
