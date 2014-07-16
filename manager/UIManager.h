//
//  UIManager.h
//  ESGame
//
//  Created by wangbin on 13-1-14.
//
//

#ifndef __UIManager__
#define __UIManager__

#include <iostream>
#include "CommonDef.h"

class CCCutTouchLayer;


class UIManager
{
public:
    UIManager();
    virtual ~UIManager();
    static UIManager*   shareInstance();
    void                RegisterAllUILayer();
    void                showUI(eUILayerId eLayerId);
    void                removeUI(eUILayerId eLayerId);

    CCCutTouchLayer*    getUILayer(eUILayerId eLayerId);
    void                removeAllUI();
private:
    std::map<eUILayerId,CCCutTouchLayer*>   m_mapLayer;
};

#endif /* defined(__UIManager__) */
