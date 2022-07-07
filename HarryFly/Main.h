#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#include<d3d9.h>//これ消すな!!
#include<d3dx9.h>//これ消すな!!

#define SCREEN_WIDTH (1366)//スクリーンの横の長さ
#define SCREEN_HEIGHT (768)//スクリーンの縦の長さ

LPDIRECT3DDEVICE9 GetD3DDevice(void);
LPDIRECT3DDEVICE9 GetDevice(void);



void getnum(int num);//ゲームオーバーに移動させるための数字移動用関数


#endif // _MAIN_H_

