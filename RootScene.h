
/*
 *
 *  Created by wangbin
 *
 */

#ifndef __ESHOMESCENE_SCENE_H__
#define __ESHOMESCENE_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;


class RootScene : public Scene
{
public:
    RootScene();
    ~RootScene();
    bool                        init();
    static RootScene*         create();
    void                        showMemoryLabel();
protected:
    void updateLabel(float dt);
private:
    LabelTTF*             m_pMemoryLabel;
};

#endif // __ESHOMESCENE_SCENE_H__
