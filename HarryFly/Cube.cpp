#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Polygon.h"
#include "Main.h"
#include "Cube.h"
#include "Atarihantei.h"

//3D用頂点データ

//構造体の宣言
typedef struct {
	//座標
	D3DXVECTOR3 pos;
	//法線
	D3DXVECTOR3 normal;
	//カラー
	D3DCOLOR color;
	//テクスチャ
	D3DXVECTOR2 texcoord;
}VERTEX3D;

//FVFの宣言(定数)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL )//設定



//グローバル変数に行列を用意
//D3DXMATRIX(4×4)(16ビット消費)
static float CUBE_HABA = 5.0f;//キューブの半径
							  //キューブ01
static D3DXMATRIX g_mtxWorld01;
static D3DXMATRIX g_mtxWorld01kakudai;
static D3DXMATRIX g_mtxWorld01move;
//キューブ1
static float CUBE_1_X = 1.0f;//キューブのX座標
static float CUBE_1_Y = 10.0f;//キューブのY座標
static float CUBE_1_Z = 40.0f;//キューブのZ座標
							  //キューブ02
static D3DXMATRIX g_mtxWorld02;
static D3DXMATRIX g_mtxWorld02kakudai;
static D3DXMATRIX g_mtxWorld02move;
//キューブ2
static float CUBE_2_X = 8.0f;//キューブのX座標
static float CUBE_2_Y = 2.0f;//キューブのY座標
static float CUBE_2_Z = 80.0f;//キューブのZ座標
							  //キューブ03
static D3DXMATRIX g_mtxWorld03;
static D3DXMATRIX g_mtxWorld03move;
static D3DXMATRIX g_mtxWorld03kakudai;
//キューブ3
static float CUBE_3_X = -2.0f;//キューブのX座標
static float CUBE_3_Y = 6.0f;//キューブのY座標
static float CUBE_3_Z = 120.0f;//キューブのZ座標
							   //キューブ04
static D3DXMATRIX g_mtxWorld04;
static D3DXMATRIX g_mtxWorld04move;
static D3DXMATRIX g_mtxWorld04kakudai;
//キューブ4
static float CUBE_4_X = 10.0f;//キューブのX座標
static float CUBE_4_Y = 15.0f;//キューブのY座標
static float CUBE_4_Z = 160.0f;//キューブのZ座標
							   //キューブ05
static D3DXMATRIX g_mtxWorld05;
static D3DXMATRIX g_mtxWorld05move;
static D3DXMATRIX g_mtxWorld05kakudai;
//キューブ5
static float CUBE_5_X = -10.0f;//キューブのX座標
static float CUBE_5_Y = 0.0f;//キューブのY座標
static float CUBE_5_Z = 200.0f;//キューブのZ座標
							   //キューブ06
static D3DXMATRIX g_mtxWorld06;
static D3DXMATRIX g_mtxWorld06move;
static D3DXMATRIX g_mtxWorld06kakudai;
//キューブ6
static float CUBE_6_X = -2.0f;//キューブのX座標
static float CUBE_6_Y = 6.0f;//キューブのY座標
static float CUBE_6_Z = 240.0f;//キューブのZ座標

							   //テクスチャ1
static const char* g_aTextureFileName[] = { "recource/texture/zimen.jpg", };
#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])
static const int TEXTURE_FILE_COUNT = ARRAYCOUNT(g_aTextureFileName);
static LPDIRECT3DTEXTURE9 g_pTexture[TEXTURE_FILE_COUNT];//ファイルのカウント数


														 //ポリゴン3Dの初期化処理
void InitPolygon3D(void) {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main.h

											//テクスチャ2
											//エラーチェック
	HRESULT hr;
	for (int i = 0; i<2; i++)
	{
		hr = D3DXCreateTextureFromFile(pDevice, "recource/texture/zimen.jpg", &g_pTexture[i]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "テクスチャが見つからない", "エラー", MB_OK);
		}
	}


}
//ポリゴン3Dの終了処理
void UninitPolygon3D(void) {
	//テクスチャ3
	for (int i = 0; i<TEXTURE_FILE_COUNT; i++)
	{
		if (g_pTexture[i] != NULL)
		{
			g_pTexture[i]->Release();
			g_pTexture[i] = NULL;
		}
	}

	CUBE_HABA = 0.0f;//キューブの半径

	CUBE_1_X = 0.0f;//キューブのX座標
	CUBE_1_Y = 0.0f;//キューブのY座標
	CUBE_1_Z = 0.0f;//キューブのZ座標

	CUBE_2_X = 0.0f;//キューブのX座標
	CUBE_2_Y = 0.0f;//キューブのY座標
	CUBE_2_Z = 0.0f;//キューブのZ座標

	CUBE_3_X = 0.0f;//キューブのX座標
	CUBE_3_Y = 0.0f;//キューブのY座標
	CUBE_3_Z = 0.0f;//キューブのZ座標

	CUBE_4_X = 0.0f;//キューブのX座標
	CUBE_4_Y = 0.0f;//キューブのY座標
	CUBE_4_Z = 0.0f;//キューブのZ座標

	CUBE_5_X = 0.0f;//キューブのX座標
	CUBE_5_Y = 0.0f;//キューブのY座標
	CUBE_5_Z = 0.0f;//キューブのZ座標
	
	CUBE_6_X = 0.0f;//キューブのX座標
	CUBE_6_Y = 0.0f;//キューブのY座標
	CUBE_6_Z = 0.0f;//キューブのZ座標

}
//ポリゴン3Dの更新処理
void UpdatePolygon3D(void) {

	//ワールド変換行列//SRT	スケール→ローテーション→トランスレーション

	//キューブ01
	//画像が一定の左まで行ったら次は一定の右に移動しまた左に移動するやつ(2)
	static float hidarigezi1 = 0.0f;
	static float migigezi1 = 0.0f;
	static float idouspeed1 = 0.5;

	if (hidarigezi1 <= 600 && hidarigezi1 >= 100)//hidariの数値が600～100の間なら移動 
	{
		hidarigezi1 = hidarigezi1 - 5;//hidariの数値(ゲージ)を減らす
		CUBE_1_X = CUBE_1_X + idouspeed1;//移動
	}
	else if (hidarigezi1 = 100 && migigezi1 <= 600 && migigezi1 >= 100)//migiの数値が600～100かつhidariの数値が100なら移動
	{
		migigezi1 = migigezi1 - 5;//migiの数値(ゲージ)を減らす
		CUBE_1_X = CUBE_1_X - idouspeed1;//移動
	}
	else if (hidarigezi1 <= 100 && migigezi1 <= 100)//hidariの数値が100かつmigiの数値が100ならhidari,migiの数値の初期化 
	{
		hidarigezi1 = 600;//hidariの数値を元通りにする
		migigezi1 = 600;//migiの数値をもと通りにする
	}

	ataricube1(CUBE_1_X, CUBE_1_Y, CUBE_1_Z);//更新したキューブの座標をあたり判定に送る

	D3DXMatrixIdentity(&g_mtxWorld01);//数字を入れるための初期化
	D3DXMatrixScaling(&g_mtxWorld01kakudai, CUBE_HABA, CUBE_HABA, CUBE_HABA);//モデルの拡大関数
	D3DXMatrixMultiply(&g_mtxWorld01, &g_mtxWorld01, &g_mtxWorld01kakudai);//合成
	D3DXMatrixTranslation(&g_mtxWorld01move, CUBE_1_X, CUBE_1_Y, CUBE_1_Z);//キューブの平行移動関数
	D3DXMatrixMultiply(&g_mtxWorld01, &g_mtxWorld01, &g_mtxWorld01move);//合成

																		//キューブ02
																		//画像が一定の左まで行ったら次は一定の右に移動しまた左に移動するやつ(2)
	static float hidarigezi2 = 0.0f;
	static float migigezi2 = 0.0f;
	static float idouspeed2 = 0.5;

	if (hidarigezi2 <= 600 && hidarigezi2 >= 100)//hidariの数値が600～100の間なら画像が移動 
	{
		hidarigezi2 = hidarigezi2 - 5;//hidariの数値(ゲージ)を減らす
		CUBE_2_Y = CUBE_2_Y + idouspeed2;//移動
	}
	else if (hidarigezi2 = 100 && migigezi2 <= 600 && migigezi2 >= 100)//migiの数値が600～100かつhidariの数値が100なら移動
	{
		migigezi2 = migigezi2 - 5;//migiの数値(ゲージ)を減らす
		CUBE_2_Y = CUBE_2_Y - idouspeed2;//移動
	}
	else if (hidarigezi2 <= 100 && migigezi2 <= 100)//hidariの数値が100かつmigiの数値が100ならhidari,migiの数値の初期化 
	{
		hidarigezi2 = 600;//hidariの数値を元通りにする
		migigezi2 = 600;//migiの数値をもと通りにする
	}

	ataricube2(CUBE_2_X, CUBE_2_Y, CUBE_2_Z);//更新したキューブの座標をあたり判定に送る

	D3DXMatrixIdentity(&g_mtxWorld02);//数字を入れるための初期化
	D3DXMatrixScaling(&g_mtxWorld02kakudai, CUBE_HABA, CUBE_HABA, CUBE_HABA);//モデルの拡大関数
	D3DXMatrixMultiply(&g_mtxWorld02, &g_mtxWorld02, &g_mtxWorld02kakudai);//合成
	D3DXMatrixTranslation(&g_mtxWorld02move, CUBE_2_X, CUBE_2_Y, CUBE_2_Z);//キューブの平行移動関数
	D3DXMatrixMultiply(&g_mtxWorld02, &g_mtxWorld02, &g_mtxWorld02move);//合成

																		//キューブ03
																		//画像が一定の左まで行ったら次は一定の右に移動しまた左に移動するやつ(2)
	static float hidarigezi3 = 0.0f;
	static float migigezi3 = 0.0f;
	static float idouspeed3 = 0.5;

	if (hidarigezi3 <= 600 && hidarigezi3 >= 100)//hidariの数値が600～100の間なら移動 
	{
		hidarigezi3 = hidarigezi3 - 5;//hidariの数値(ゲージ)を減らす
		CUBE_3_Z = CUBE_3_Z + idouspeed3;//移動
	}
	else if (hidarigezi3 = 100 && migigezi3 <= 600 && migigezi3 >= 100)//migiの数値が600～100かつhidariの数値が100なら移動
	{
		migigezi3 = migigezi3 - 5;//migiの数値(ゲージ)を減らす
		CUBE_3_Z = CUBE_3_Z - idouspeed3;//移動
	}
	else if (hidarigezi3 <= 100 && migigezi3 <= 100)//hidariの数値が100かつmigiの数値が100ならhidari,migiの数値の初期化 
	{
		hidarigezi3 = 600;//hidariの数値を元通りにする
		migigezi3 = 600;//migiの数値をもと通りにする
	}

	ataricube3(CUBE_3_X, CUBE_3_Y, CUBE_3_Z);//更新したキューブの座標をあたり判定に送る

	D3DXMatrixIdentity(&g_mtxWorld03);//数字を入れるための初期化
	D3DXMatrixScaling(&g_mtxWorld03kakudai, CUBE_HABA, CUBE_HABA, CUBE_HABA);//モデルの拡大関数
	D3DXMatrixMultiply(&g_mtxWorld03, &g_mtxWorld03, &g_mtxWorld03kakudai);//合成
	D3DXMatrixTranslation(&g_mtxWorld03move, CUBE_3_X, CUBE_3_Y, CUBE_3_Z);//キューブの平行移動
	D3DXMatrixMultiply(&g_mtxWorld03, &g_mtxWorld03, &g_mtxWorld03move);//合成

																		//キューブ04
																		//画像が一定の左まで行ったら次は一定の右に移動しまた左に移動するやつ(2)
	static float hidarigezi4 = 0.0f;
	static float migigezi4 = 0.0f;
	static float idouspeed4 = 0.5;

	if (hidarigezi4 <= 600 && hidarigezi4 >= 100)//hidariの数値が600～100の間なら画像が移動 
	{
		hidarigezi4 = hidarigezi4 - 5;//hidariの数値(ゲージ)を減らす
		CUBE_4_X = CUBE_4_X - idouspeed4;//移動
		CUBE_4_Y = CUBE_4_Y - idouspeed4;//移動
	}
	else if (hidarigezi4 = 100 && migigezi4 <= 600 && migigezi4 >= 100)//migiの数値が600～100かつhidariの数値が100なら移動
	{
		migigezi4 = migigezi4 - 5;//migiの数値(ゲージ)を減らす
		CUBE_4_X = CUBE_4_X + idouspeed4;//移動
		CUBE_4_Y = CUBE_4_Y + idouspeed4;//移動
	}
	else if (hidarigezi4 <= 100 && migigezi4 <= 100)//hidariの数値が100かつmigiの数値が100ならhidari,migiの数値の初期化 
	{
		hidarigezi4 = 600;//hidariの数値を元通りにする
		migigezi4 = 600;//migiの数値をもと通りにする
	}

	ataricube4(CUBE_4_X, CUBE_4_Y, CUBE_4_Z);//更新したキューブの座標をあたり判定に送る

	D3DXMatrixIdentity(&g_mtxWorld04);//数字を入れるための初期化
	D3DXMatrixScaling(&g_mtxWorld04kakudai, CUBE_HABA, CUBE_HABA, CUBE_HABA);//モデルの拡大関数
	D3DXMatrixMultiply(&g_mtxWorld04, &g_mtxWorld04, &g_mtxWorld04kakudai);//合成
	D3DXMatrixTranslation(&g_mtxWorld04move, CUBE_4_X, CUBE_4_Y, CUBE_4_Z);//キューブの平行移動
	D3DXMatrixMultiply(&g_mtxWorld04, &g_mtxWorld04, &g_mtxWorld04move);//合成

																		//キューブ05
																		//画像が一定の左まで行ったら次は一定の右に移動しまた左に移動するやつ(2)
	static float hidarigezi5 = 0.0f;
	static float migigezi5 = 0.0f;
	static float idouspeed5 = 0.5;

	if (hidarigezi5 <= 600 && hidarigezi5 >= 100)//hidariの数値が600～100の間なら画像が移動 
	{
		hidarigezi5 = hidarigezi5 - 5;//hidariの数値(ゲージ)を減らす
		CUBE_5_X = CUBE_5_X + idouspeed5;//移動
		CUBE_5_Y = CUBE_5_Y + idouspeed5;//移動
	}
	else if (hidarigezi5 = 100 && migigezi5 <= 600 && migigezi5 >= 100)//migiの数値が600～100かつhidariの数値が100なら移動
	{
		migigezi5 = migigezi5 - 5;//migiの数値(ゲージ)を減らす
		CUBE_5_X = CUBE_5_X - idouspeed5;//移動
		CUBE_5_Y = CUBE_5_Y - idouspeed5;//移動
	}
	else if (hidarigezi5 <= 100 && migigezi5 <= 100)//hidariの数値が100かつmigiの数値が100ならhidari,migiの数値の初期化 
	{
		hidarigezi5 = 600;//hidariの数値を元通りにする
		migigezi5 = 600;//migiの数値をもと通りにする
	}

	ataricube5(CUBE_5_X, CUBE_5_Y, CUBE_5_Z);//更新したキューブの座標をあたり判定に送る

	D3DXMatrixIdentity(&g_mtxWorld05);//数字を入れるための初期化
	D3DXMatrixScaling(&g_mtxWorld05kakudai, CUBE_HABA, CUBE_HABA, CUBE_HABA);//モデルの拡大関数
	D3DXMatrixMultiply(&g_mtxWorld05, &g_mtxWorld05, &g_mtxWorld05kakudai);//合成
	D3DXMatrixTranslation(&g_mtxWorld05move, CUBE_5_X, CUBE_5_Y, CUBE_5_Z);//キューブの平行移動
	D3DXMatrixMultiply(&g_mtxWorld05, &g_mtxWorld05, &g_mtxWorld05move);//合成

																		//キューブ06
																		//画像が一定の左まで行ったら次は一定の右に移動しまた左に移動するやつ(2)
	static float hidarigezi6 = 0.0f;
	static float migigezi6 = 0.0f;
	static float idouspeed6 = 0.5;

	if (hidarigezi6 <= 600 && hidarigezi6 >= 100)//hidariの数値が600～100の間なら移動 
	{
		hidarigezi6 = hidarigezi6 - 5;//hidariの数値(ゲージ)を減らす
		CUBE_6_X = CUBE_6_X + idouspeed6;//移動
	}
	else if (hidarigezi6 = 100 && migigezi6 <= 600 && migigezi6 >= 100)//migiの数値が600～100かつhidariの数値が100なら移動
	{
		migigezi6 = migigezi6 - 5;//migiの数値(ゲージ)を減らす
		CUBE_6_X = CUBE_6_X - idouspeed6;//移動
	}
	else if (hidarigezi6 <= 100 && migigezi6 <= 100)//hidariの数値が100かつmigiの数値が100ならhidari,migiの数値の初期化 
	{
		hidarigezi6 = 600;//hidariの数値を元通りにする
		migigezi6 = 600;//migiの数値をもと通りにする
	}

	ataricube6(CUBE_6_X, CUBE_6_Y, CUBE_6_Z);//更新したキューブの座標をあたり判定に送る

	D3DXMatrixIdentity(&g_mtxWorld06);//数字を入れるための初期化
	D3DXMatrixScaling(&g_mtxWorld06kakudai, CUBE_HABA, CUBE_HABA, CUBE_HABA);//モデルの拡大関数
	D3DXMatrixMultiply(&g_mtxWorld06, &g_mtxWorld06, &g_mtxWorld06kakudai);//合成
	D3DXMatrixTranslation(&g_mtxWorld06move, CUBE_6_X, CUBE_6_Y, CUBE_6_Z);//キューブの平行移動関数
	D3DXMatrixMultiply(&g_mtxWorld06, &g_mtxWorld06, &g_mtxWorld06move);//合成



}
//3D画像を表示
void DrawPolygon3D(void) {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main.h//pDeviceを使う場合これが必要

											//テクスチャ4
	pDevice->SetTexture(0, g_pTexture[0]);

	//頂点の作成
	VERTEX3D v[] = {
		//手前
		//座標								//法線						//カラー							//テクスチャ
		{ D3DXVECTOR3(-0.5f,  0.5f, -0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f), D3DCOLOR_RGBA(255,   255, 255, 255),D3DXVECTOR2(0 , 0) },//左上[0]
		{ D3DXVECTOR3(0.5f,  0.5f, -0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f), D3DCOLOR_RGBA(255,   255, 255, 255),D3DXVECTOR2(0.25 , 0) },//右上[1]
		{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f), D3DCOLOR_RGBA(255,   255, 255, 255),D3DXVECTOR2(0 , 0.25) },//左下[2]

		{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f), D3DCOLOR_RGBA(255,   255, 255, 255),D3DXVECTOR2(0 , 0.25) },//左下[2]
		{ D3DXVECTOR3(0.5f,  0.5f, -0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f), D3DCOLOR_RGBA(255,   255, 255, 255),D3DXVECTOR2(0.25 , 0) },//右上[1]
		{ D3DXVECTOR3(0.5f, -0.5f, -0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f), D3DCOLOR_RGBA(255,   255, 255, 255),D3DXVECTOR2(0.25 , 0.25) },//右下[3]



																																	   //奥
		{ D3DXVECTOR3(0.5f,  0.5f, 0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25 , 0) },//左上[4]
		{ D3DXVECTOR3(-0.5f,  0.5f, 0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5 , 0) },//右上[5]
		{ D3DXVECTOR3(0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25 , 0.25) },//左下[6]

		{ D3DXVECTOR3(0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25 , 0.25) },//左下[6]
		{ D3DXVECTOR3(-0.5f,  0.5f, 0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5 , 0) },//右上[5]
		{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5 , 0.25) },//右下[7]

																																	 //右
		{ D3DXVECTOR3(0.5f,  0.5f, -0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5,0) },//右上前[1]
		{ D3DXVECTOR3(0.5f,  0.5f,  0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.75,0) },//右上後[4]
		{ D3DXVECTOR3(0.5f, -0.5f, -0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5,0.25) },//右下前[3]

		{ D3DXVECTOR3(0.5f, -0.5f, -0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5,0.25) },//右下前[3]
		{ D3DXVECTOR3(0.5f,  0.5f,  0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.75,0) },//右上後[4]
		{ D3DXVECTOR3(0.5f, -0.5f,  0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.75,0.25) },//右下後[6]

																																	//左
		{ D3DXVECTOR3(-0.5f,  0.5f,  0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.75,0) },//左上後[5]
		{ D3DXVECTOR3(-0.5f,  0.5f, -0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(1,0) },//[0]
		{ D3DXVECTOR3(-0.5f, -0.5f,  0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.75,0.25) },//[7]

		{ D3DXVECTOR3(-0.5f, -0.5f,  0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.75,0.25) },//[7]
		{ D3DXVECTOR3(-0.5f,  0.5f, -0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(1,0) },//[0]
		{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(1,0.25) },//[2]

																																   //上
		{ D3DXVECTOR3(-0.5f,  0.5f,  0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0,0.25) },//[5]
		{ D3DXVECTOR3(0.5f,  0.5f,  0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25,0.25) },//[4]
		{ D3DXVECTOR3(-0.5f,  0.5f, -0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0,0.5) },//[0]

		{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0,0.5) },//[0]
		{ D3DXVECTOR3(0.5f,  0.5f, 0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25,0.25) },//[4]
		{ D3DXVECTOR3(0.5f, 0.5f, -0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25,0.5) },//[1]

																																   //下
		{ D3DXVECTOR3(-0.5f,  -0.5f, -0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25,0.25) },//[2]
		{ D3DXVECTOR3(0.5f,  -0.5f, -0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5,0.25) },//[3]
		{ D3DXVECTOR3(-0.5f,  -0.5f,  0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25,0.5) },//[7]

		{ D3DXVECTOR3(-0.5f, -0.5f,  0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25,0.5) },//[7]
		{ D3DXVECTOR3(0.5f, -0.5f, -0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5,0.25) },//[3]
		{ D3DXVECTOR3(0.5f, -0.5f,  0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5,0.5) },//[6]
	};

	WORD index[] = {
		0,1,2,
		2,1,3,
		4,5,6,
		6,5,7,
		1,4,3,
		3,4,6,
		5,0,7,
		7,0,2,
		5,4,0,
		0,4,1,
		2,3,7,
		7,3,6
	};

	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);



	//描画(ファン形式で、面１つ、頂点配列へのアドレス、サイズは頂点構造体)
	//キューブ01
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld01);
	//描画(ファン形式で,面１つ,頂点配列へのアドレス,サイズは頂点構造体)
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &v[0], sizeof(VERTEX3D));

	//キューブ02
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld02);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &v[0], sizeof(VERTEX3D));

	//キューブ03
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld03);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &v[0], sizeof(VERTEX3D));

	//キューブ04
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld04);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &v[0], sizeof(VERTEX3D));

	//キューブ05
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld05);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &v[0], sizeof(VERTEX3D));

	//キューブ06
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld06);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &v[0], sizeof(VERTEX3D));
}