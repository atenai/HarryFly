#pragma once
//=======================================================================================
//						あたり判定描画
//						2017.06.05
//=======================================================================================

#ifndef _ATARIHANTEI_H_
#define _ATARIHANTEI_H_

bool atari(float zibunx, float zibuny, float zibunz, float zibunhankei, float ITEMx, float ITEMy, float ITEMz, float ITEMhankei);
void Initatari(void);//あたり判定の初期化処理
void Updateatari(void);//あたり判定の更新処理
void atariidou(float x, float y, float z);//Xmodelの処理をatarihantei.cppへ数字を送る
void ataricube1(float cx, float cy, float cz);//Polygon3Dの処理をatarihantei.cppへ数字を送る
void ataricube2(float cx, float cy, float cz);//Polygon3Dの処理をatarihantei.cppへ数字を送る
void ataricube3(float cx, float cy, float cz);//Polygon3Dの処理をatarihantei.cppへ数字を送る
void ataricube4(float cx, float cy, float cz);//Polygon3Dの処理をatarihantei.cppへ数字を送る
void ataricube5(float cx, float cy, float cz);//Polygon3Dの処理をatarihantei.cppへ数字を送る
void ataricube6(float cx, float cy, float cz);//Polygon3Dの処理をatarihantei.cppへ数字を送る
void ataribonbe(int bonbesu, float ix, float iy, float iz);//Item.cppの処理をatarihantei.cppへ数字を送る
void ataricoin(int coinsu, float ix, float iy, float iz);//Item.cppの処理をatarihantei.cppへ数字を送る
#endif //_ATARIHANTEI_H_

