//
//  StorySelect.h
//  WitchRace
//
//  Created by 新井脩司 on 2014/12/16.
//
//

#ifndef __WitchRace__StorySelect__
#define __WitchRace__StorySelect__

#include <stdio.h>
#include "cocos2d.h"
//#include "TutorialScene.h"
//#include "GameCenterBridge.h"

class StorySelect : public cocos2d::Layer
{
    
protected:
    
    
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void selectStoryCallBack(cocos2d::Ref* pSender);
    void backBtCallBack(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(StorySelect);
    
    //ストーリー選択ボタン設定
    void setSelectButton();
    
    
    //戻るボタン
    void setBackBt();
    
    
    //タップイベントの宣言
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    
    bool nextScene;
    
    //配列を使う場合
    //cocos2d::Vector<cocos2d::Sprite*>dropVector = cocos2d::Vector<cocos2d::Sprite*>();
    
    //AppCCloudの広告用
    //void setAppCCloud();
    //void removeAppCCloud();
    
};

#endif /* defined(__WitchRace__StorySelect__) */