//=============================================================================
//  
// コインの描画
//
//　      
//=============================================================================

#ifndef _COIN_H_
#define _COIN_H_

void Initcoin(void);//初期化処理
void Updatecoin(void);//更新処理
void Drawcoin(void);//画像を表示
void Uninitcoin(void);//終了処理

void hihixyouzicoin(int coinsu, bool drawcoin);//Atarihantei.cppの内容をCoin.cppに送る

#endif // _ITEM_H_