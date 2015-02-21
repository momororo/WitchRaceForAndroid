//
//  Zorder.h
//  WitchRace
//
//  Created by yasutomo on 2014/12/04.
//
//

/**
 *  zOrderを一括管理します。
 *  スプライトにzPositionを設定する際は、ここでdefine後、当ファイルをincludeして使ってください。。
 */
#ifndef WitchRace_Zorder_h
#define WitchRace_Zorder_h

/**
 *  zPosition一覧
 */

//staticBackGround
#define zOrderOfStaticBackGround -3
//背景
#define zOrderOfBackGround -2
//背景部品
#define zOrderOfBackGroundParts -2

//キキ
#define zOrderOfKiki 10
//キキ(影)
#define zOrderOfKikiShadow 5

//こうもり
#define zOrderOfEnemy 0

#define zOrderOfGauge 0

#define zOrderOfPause 200

#define zOrderOfPauseLabel 300

#endif
