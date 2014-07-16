
/*
 *
 *  Created by wangbin
 *
 */

#ifndef CCLabelStroke_CCLabelStroke_h
#define CCLabelStroke_CCLabelStroke_h

#include "cocos2d.h"
USING_NS_CC;

class CCLabelStroke : public LabelTTF
{
public:
    enum StrokeTypeEnum
    {
        STE_UNKNOWN         = 0,
        STE_UP              = 1,
        STE_DOWN            = 2,
        STE_LEFT            = 3,
        STE_RIGHT           = 4,
        STE_LEFT_UP         = 5,
        STE_RIGHT_UP        = 6,
        STE_LEFT_DOWN       = 7,
        STE_RIGHT_DOWN      = 8,
        STE_ALL             = 9,
    };
    
    
    CCLabelStroke();
    virtual  ~CCLabelStroke();
    virtual void            setString(const char *label);
     static CCLabelStroke *  labelWithData(unsigned char* pMultiData,unsigned int unlen,  Size dimensions);
    static CCLabelStroke *  labelWithData(unsigned char* pMultiData, unsigned int unlen, Size dimensions,TextHAlignment alignment, const char *fontName, float fontSize,float lineWidth, Color3B lineColor,StrokeTypeEnum strokeType);
    
    
    static CCLabelStroke * labelWithString(const char *label, Size dimensions, TextHAlignment alignment, const char *fontName, float fontSize,float lineWidth, Color3B lineColor,StrokeTypeEnum strokeType);
    static CCLabelStroke * labelWithString(const char *label, const char *fontName, float fontSize,float lineWidth, Color3B lineColor,StrokeTypeEnum strokeType);
    
    
    static CCLabelStroke * labelWithString(const char *label, Size dimensions, TextHAlignment alignment, const char *fontName, float fontSize);
    static CCLabelStroke * labelWithString(const char *label, const char *fontName, float fontSize);
    
    //void                    setDimensions(Size size){_dimensions = size;}
    void                    setStrokeType(StrokeTypeEnum type){m_strokeType = type;}
    

protected:
    bool   initWithData(unsigned char* pMultiData,unsigned int unlen, unsigned int texWidth, unsigned int texHeight);
    void                    setStroke(float size,Color3B color,StrokeTypeEnum strokeType);

    
private:
    RenderTexture*    m_renderTexture;
    float               m_lineWidth;
    Color3B           m_lineColor;
    StrokeTypeEnum      m_strokeType;
    LabelTTF*         m_pLabelStroke;
};



#endif
