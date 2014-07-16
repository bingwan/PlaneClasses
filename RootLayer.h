//
//  RootLayer.h
//
//  Created by wangbin on 13-1-14.
//
//

#ifndef __ESGame__RootLayer__
#define __ESGame__RootLayer__

#include <iostream>
#include "CCCutTouchLayer.h"
#include "CommonDef.h"
//#include "Button.h"

class RootLayer : public CCCutTouchLayer
{
public:
    RootLayer();
    ~RootLayer();
    static RootLayer*     shareRootLayer();
    
    static RootLayer*     create(const Color4B& color, GLfloat width, GLfloat height);
    virtual bool            initWithColor(const Color4B& color, GLfloat w, GLfloat h);
    virtual void            onEnter();
    virtual void            onExit();
    
//    virtual bool            onTouchBegan(Touch *pTouch, Event *pEvent);
//    virtual void            onTouchMoved(Touch *pTouch, Event *pEvent);
//    virtual void            onTouchEnded(Touch *pTouch, Event *pEvent);
//    virtual void            onTouchCancelled(Touch *pTouch, Event *pEvent);
    void                    showConnectNetTips();
    void                    hideConnectNetTips();
    void                    waitEnd(float dt);
    
    void                    showMessageDefault(const char* pszMsg);
    void                    showAlertLayer(const char* pszMsg, const char* pszOk ,const char* pszCancel ,eGAME_CMD_ID cmdOk,eGAME_CMD_ID cmdCancel);
    void showTipsMessage(const char *pMess);

protected:
    void                    clickSelectGroupLevel(Object* p);
   // void                    clickOkButton( Button* pButton);
   // void                    clickButtonCancel( Button* pButton);
      
    
private:
    void tipsMessageDisappear(Node *sender);
    CCCutTouchLayer*        m_pNetPreventLay;
    bool                    m_bShowLoading;
    CCCutTouchLayer*        m_pAlertLayer;
    
    
};

#endif /* defined(__ESGame__RootLayer__) */
