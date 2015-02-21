//
//  SelectCharacterScene.h
//  WitchRace
//
//  Created by yasutomo on 2015/01/20.
//
//

#ifndef __WitchRace__SelectCharacterScene__
#define __WitchRace__SelectCharacterScene__

#include "cocos2d.h"

using namespace cocos2d;

class SelectCharacterScene : public cocos2d::Layer
{
public:

    
    virtual bool init();
    static cocos2d::Scene *createScene();
    void setBackBt();
    void backBtCallBack(cocos2d::Ref *pSender);
    
    
    //配列(透明度の一括管理のため)
    Vector<Sprite*> *characters = new Vector<Sprite*>;
    Label *charaExLabel;
    
    //キキ
    std::string kikiExText;
    //おまけキキ
    std::string petitKikiExText;
    //ハリーポッター
    std::string haryyPotterExText;
    //ポニョ
    std::string ponyoExText;
    //空飛ぶ車
    std::string fordAngliaExText;
    //ポルコ・ロッソ
    std::string porcoRossoExText;

    CREATE_FUNC(SelectCharacterScene);

};

#endif /* defined(__WitchRace__SelectCharacterScene__) */
