#pragma once
//=======================================================================================
//						‚ ‚½‚è”»’è•`‰æ
//						2017.06.05
//=======================================================================================

#ifndef _ATARIHANTEI_H_
#define _ATARIHANTEI_H_

bool atari(float zibunx, float zibuny, float zibunz, float zibunhankei, float ITEMx, float ITEMy, float ITEMz, float ITEMhankei);
void Initatari(void);//‚ ‚½‚è”»’è‚Ì‰Šú‰»ˆ—
void Updateatari(void);//‚ ‚½‚è”»’è‚ÌXVˆ—
void atariidou(float x, float y, float z);//Xmodel‚Ìˆ—‚ğatarihantei.cpp‚Ö”š‚ğ‘—‚é
void ataricube1(float cx, float cy, float cz);//Polygon3D‚Ìˆ—‚ğatarihantei.cpp‚Ö”š‚ğ‘—‚é
void ataricube2(float cx, float cy, float cz);//Polygon3D‚Ìˆ—‚ğatarihantei.cpp‚Ö”š‚ğ‘—‚é
void ataricube3(float cx, float cy, float cz);//Polygon3D‚Ìˆ—‚ğatarihantei.cpp‚Ö”š‚ğ‘—‚é
void ataricube4(float cx, float cy, float cz);//Polygon3D‚Ìˆ—‚ğatarihantei.cpp‚Ö”š‚ğ‘—‚é
void ataricube5(float cx, float cy, float cz);//Polygon3D‚Ìˆ—‚ğatarihantei.cpp‚Ö”š‚ğ‘—‚é
void ataricube6(float cx, float cy, float cz);//Polygon3D‚Ìˆ—‚ğatarihantei.cpp‚Ö”š‚ğ‘—‚é
void ataribonbe(int bonbesu, float ix, float iy, float iz);//Item.cpp‚Ìˆ—‚ğatarihantei.cpp‚Ö”š‚ğ‘—‚é
void ataricoin(int coinsu, float ix, float iy, float iz);//Item.cpp‚Ìˆ—‚ğatarihantei.cpp‚Ö”š‚ğ‘—‚é
#endif //_ATARIHANTEI_H_

