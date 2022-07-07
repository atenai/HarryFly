#pragma once
//=============================================================================
//  
// 初期化
//
//　      
//=============================================================================

#ifndef _SIXYOKIKA_H_
#define _SIXYOKIKA_H_

void Updatesixyokika(void);//更新処理

void getiou(float yokoidounum, float tateidounum, float okuidounum);//Xモデルの移動の初期化
void getcoin(int coinnum);//coinの数字を移動する関数
void sixyokikacoin(int coinnum);//coinの数字を移動する関数
void getzikan(int zikannum);//zikanの数字を移動する関数
void sixyokikazikan(int zikannum);//zikanの数字を移動する関数
void getcamera(void);//カメラの初期化処理

void sixyyokikadrawbonbe(int bonbesu, bool drawbonbe);//ボンベの初期化
void sixyyokikaataribonbe(int bonbesu, bool ataribonbe);//ボンベの初期化
void sixyyokikadrawcoin(int coinsu, bool drawcoin);//コインの初期化
void sixyyokikaataricoin(int coinsu, bool ataricoin);//コインの初期化
#endif // _SIXYOKIKA_H_
