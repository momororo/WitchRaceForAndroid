//
//  PetitKiki.cpp
//  WitchRace
//
//  Created by yasutomo on 2014/12/03.
//
//

#include "PetitKiki.h"
#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()

//おまじない
USING_NS_CC;


//初期値NULL
PetitKiki* PetitKiki::petitKikiInstance = NULL;

//シングルトン
PetitKiki* PetitKiki::getInstance(){
    
    if(!petitKikiInstance){
        petitKikiInstance = new PetitKiki();
    }
    
    
    return petitKikiInstance;
    
}
//デストラクタ
void PetitKiki::destroyInstance() {
    if (petitKikiInstance != NULL){
        delete petitKikiInstance;
        
        petitKikiInstance = NULL;
    }
}


//キキちゃんのスプライトをGET
Sprite* PetitKiki::getCharacter(){
    return petitKiki;
}


//キキちゃんの動作開始
void PetitKiki::startCharacter(){
    
    petitKiki->getPhysicsBody()->setEnable(true);
    broom -> getPhysicsBody()-> setEnable(true);
    
}

//キキちゃんの動作停止
void PetitKiki::stopCharacter(){
    
    petitKiki->getPhysicsBody()->setEnable(false);
    broom -> getPhysicsBody()-> setEnable(false);
    
}


//キキちゃんの初期設定
PetitKiki::PetitKiki(){
 
    //キャラクタースプライトの生成(UP時)
    petitKiki = Sprite::create("kiki_up.png");
    //影
    petitKikiShadow = Sprite::create("kiki_up_shadow.png");
    
    //キャラクタースプライトの大きさ
    petitKiki -> setScale(0.5);
    
    //影を実体に入れちゃう
    petitKiki->addChild(petitKikiShadow);
    //影のポジション調整
    petitKikiShadow->setPosition(petitKiki->getContentSize().width/2,petitKiki->getContentSize().height/2);
    //影の透明度を設定
    petitKikiShadow->setOpacity(180);
    petitKikiShadow->setGlobalZOrder(zOrderOfKikiShadow);
    
    //影の大きさ(実体のスケールをgetしてます)※特にスケールせずにぴったり入りました(謎)
    //kikiShadow -> setScale(kiki->getScale());

    
    //ポジションの設定
    petitKiki->setPosition(Vec2(selfFrame.width/4, selfFrame.height/2));
    
    //zポジションの設定
    petitKiki->setGlobalZOrder(zOrderOfKiki);
    
    
    //タグつけ
    petitKiki->setName("kiki");
    
    //タグで上昇か下降か判断してみる(1は上昇、0は下降)
    petitKiki->setTag(1);
    
    //物理体の生成
    auto petitKikiMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    
    auto petitKikiBody = PhysicsBody::createCircle(5,petitKikiMaterial);
    
    
    //重力による影響の可否
    petitKikiBody->setGravityEnable(false);
    //まじない
    petitKikiBody->setDynamic(true);
    petitKikiBody->setEnable(false);

    //ビットマスクはてきとう
    petitKikiBody->setCategoryBitmask(0x01);
    petitKikiBody->setCollisionBitmask(0);
    petitKikiBody->setContactTestBitmask(0x02);
    
    petitKiki->setPhysicsBody(petitKikiBody);
    
    
    //箒の設定
    broom = Sprite::create();
    broom -> setTextureRect(Rect(0, 0, 10, 10));
    broom -> setPosition(Vec2(0,0));
    broom -> setVisible(false);
    
    
    auto broomBody = PhysicsBody::create();
    broomBody -> setGravityEnable(false);
    broomBody -> setDynamic(true);
    broomBody -> setEnable(false);
    
    broomBody ->setCategoryBitmask(0x01);
    broomBody ->setCollisionBitmask(0);
    broomBody ->setContactTestBitmask(0x02);
    
    broom -> setPhysicsBody(broomBody);
    
    petitKiki -> addChild(broom);
    
    endParticle = ParticleSystemQuad::create("particleFlower.plist");
    //retainしないと勝手に解放されて後々エラーへ
    endParticle->retain();
    
    petitKikiParticle = ParticleSystemQuad::create("kikiparticle.plist");
    petitKikiParticle->setAnchorPoint(Vec2(0.5f,0.5f));
    petitKikiParticle->setPosition(Vec2(3,petitKiki->getContentSize().height/3-6));
    petitKikiParticle->setName("kikiParticle");
    petitKikiParticle->setGlobalZOrder(zOrderOfKikiShadow);
    petitKiki->addChild(petitKikiParticle);
    
}

void PetitKiki::makeGameOver(){
    
    //パーティクルの設定
    endParticle->setAutoRemoveOnFinish(true);
    endParticle->setPosition(petitKiki->getPosition());
    //キキから親ノード(scene)取ってaddchild
    petitKiki->getParent()->addChild(endParticle);
    //キキをremove
    petitKiki->removeFromParent();

}

void PetitKiki::makeGameClear(){
        //パーティクルを飛ばす
    auto action = MoveTo::create(1, Vec2(selfFrame.width * 1.5, petitKiki->getPositionY()));
        
    auto remove = RemoveSelf::create(true);
        
    //フェードアウト->削除のアニメーション開始
    petitKiki->runAction(Sequence::create(action, remove, NULL));
    
}




//キキちゃんの1フレーム毎の処理
void PetitKiki::characterUpdate(bool tappedFlag){
    
    CCLOG("重力:%d",pGravity);

    
    
    //タップされている場合は上昇！
        if (tappedFlag == true) {
            
            
            
            petitKikiParticle->cocos2d::ParticleSystem::setSpeed(500);
            
            
            
            //透明度を変更
            if(petitKikiShadow->getOpacity() != 255){
            
                petitKikiShadow->setOpacity(255);
            
            }

            //画像の交換(下降画像の場合のみ)
            if(petitKiki->getTag() == 0){

                petitKiki->setTexture("kiki_up.png");
                petitKikiShadow->setTexture("kiki_up_shadow.png");
                //タグを上昇状態へ変更
                petitKiki->setTag(1);
            
            }
            
            if (pGravity>700) {
                
                pGravity = 700;
                
            }else{
                
                //下降時はより強く
                if(pGravity < -200){

                    pGravity+= 15;
                    
                }else{

                    pGravity+= 11;
                

                }
                
                
            }
            
            
            petitKiki->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            broom->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            
        }else{
            
            
            //タップされていない場合は下降！
        
            //kikiParticle->cocos2d::ParticleSystem::setSpeed(300);


            
            
            //透明度を変更
            if(petitKikiShadow->getOpacity() != 180){
                petitKikiShadow->setOpacity(180);
            }


            
            //画像の交換(上昇画像の場合のみ)
            if(petitKiki->getTag() == 1){
                
                petitKiki->setTexture("kiki_down.png");
                petitKikiShadow->setTexture("kiki_down_shadow.png");
                //タグを下降状態へ変更
                petitKiki->setTag(0);
            }

            
            if (pGravity<-700) {
                
                pGravity = -700;
                
            }else{
                
                //上昇時はより強く
                if(pGravity > 200){

                    pGravity -= 15;
                    
                }else{

                    pGravity -= 10;

                }
                
                
            }
            
            petitKiki->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            broom->getPhysicsBody()->setVelocity(Vec2(0,pGravity));

            
            
        }
        
}
