#pragma once
//=============================================================================
//  
// ボンベの描画
//
//　      
//=============================================================================

#ifndef _BONBE_H_
#define _BONBE_H_

void Initbonbe(void);//初期化処理
void Updatebonbe(void);//更新処理
void Drawbonbe(void);//画像を表示
void Uninitbonbe(void);//終了処理

void hihixyouzibonbe(int bonbesu, bool drawbonbe);//Atarihantei.cppの内容をItem.cppに送る

#endif // _BONBE_H_