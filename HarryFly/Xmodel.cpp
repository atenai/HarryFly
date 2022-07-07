//=============================================================================
//
// Xモデル [Xmodel.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Polygon.h"
#include "Main.h"
#include "Xmodel.h"
#include"input.h"
#include "Atarihantei.h"
#include "Cube.h"

//Xモデル表示用変数
LPD3DXMESH g_pMesh;
DWORD g_nMaterialNum;
LPD3DXBUFFER g_pMaterial = NULL;
static LPD3DXBUFFER   g_pMaterialBuffer = NULL;
static LPD3DXMATERIAL pMaterial;
//*****************************************************************************
// グローバル変数
//*****************************************************************************
//xモデル 05
static D3DXMATRIX g_mtxWorld05;

//スケール
static D3DXMATRIX g_mtxWorld05kakudai;//拡大用変数
static float x05 = 1.0f;//x軸拡大
static float y05 = 1.0f;//y軸拡大
static float z05 = 1.0f;//z軸拡大

						//ローテーション
static D3DXMATRIX g_mtxWorld05Zrot;//XモデルのZ回転用変数
static float Zkaitenspeed = 0.0f;//Z回転スピード用数値
static float Zkaitenidou = 0.0f;//Z回転移動用数値

static D3DXMATRIX g_mtxWorld05Xrot;//XモデルのX回転用変数
static float Xkaitenspeed = 0.0f;//X回転スピード用数値
static float Xkaitenidou = 0.0f;//X回転移動用数値

								//トランスレーション
static D3DXMATRIX g_mtxWorld05move;//移動用変数
static float okuidou = 0.0f;//奥移動用数値//XモデルのZ座標
static float zmovespeed = 0.0f;//Xモデルのzスピード

static float yokoidou = 0.0f;//横移動用数値//XモデルのX座標
static float xmovespeed = 0.0f;//Xモデルのxスピード

static float tateidou = 0.5f;//縦移動用数値//XモデルのY座標
static float ymovespeed = 0.0f;//Xモデルのyスピード






							   //==============
							   //  初期化関数
							   //==============
void InitXmodel(void)
{

	//初期化
	LPD3DXBUFFER  pAdjacencyBuffer;

	HRESULT hr;

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();//main.h//pDeviceを使う場合これが必要

	hr = D3DXLoadMeshFromX("./recource/UAV8.x",		//Xモデルのアドレス
		D3DXMESH_SYSTEMMEM, pDevice,
		&pAdjacencyBuffer, &g_pMaterialBuffer, NULL,
		&g_nMaterialNum, &g_pMesh);


	if (FAILED(hr))
	{
		MessageBox(NULL, "Xmodelファイルの読み込みに失敗しました", "エラー", MB_OK);
	}

	//マテリアルの取得
	pMaterial = (LPD3DXMATERIAL)g_pMaterialBuffer->GetBufferPointer();

	hr = g_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)pAdjacencyBuffer->GetBufferPointer(),
		NULL, NULL, NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "メッシュの最適化に失敗しました", "エラー", MB_OK);
	}


}

//==============
//  終了関数
//==============
void UninitXmodel(void)
{
	g_pMaterialBuffer->Release();

	
	g_pMesh = NULL;//LPD3DXMESHはNULLでメモリ開放
	g_nMaterialNum = 0;//DWORDは0でメモリ開放
	g_pMaterialBuffer = NULL;//LPD3DXBUFFERはNULLでメモリ開放
	g_pMaterial = NULL;//LPD3DXBUFFERはNULLでメモリ開放
	Zkaitenspeed = 0.0f;//floatは0.0fでメモリ開放
	Zkaitenidou = 0.0f;//floatは0.0fでメモリ開放
	Xkaitenspeed = 0.0f;//floatは0.0fでメモリ開放
	Xkaitenidou = 0.0f;//floatは0.0fでメモリ開放
	okuidou = 0.0f;//floatは0.0fでメモリ開放
	zmovespeed = 0;//floatは0.0fでメモリ開放
	yokoidou = 0.0f;//floatは0.0fでメモリ開放
	xmovespeed = 0.0f;//floatは0.0fでメモリ開放
	tateidou = 0.0f;//floatは0.0fでメモリ開放
	ymovespeed = 0;//floatは0.0fでメモリ開放
				   //boolはfalseでメモリ開放
	
}

//==============
// 　更新関数
//==============
void UpdateXmodel(void)
{
	//////////////////////////////奥自動移動///////////////////////////////////
	//ここをいじる場合はカメラもいじらないといけない！
	zmovespeed += 0.5f;//Xモデルの奥に進むスピード

	if (GetKeyboardPress(DIK_SPACE)) {//スペースキーを押している間奥移動がスピードアップ！
		zmovespeed = zmovespeed + 0.5f;
	}

	if (okuidou >= 330) {//奥移動の範囲制限
		zmovespeed = 0;
		getnum(2);//ゲームクリアーに移動//main.hに数字が行き、その後main.cppに行く
	}

	

	okuidou = okuidou + zmovespeed;//奥移動計算
	zmovespeed = 0;//奥移動のスピードを初期化
				   //////////////////////////////奥自動移動///////////////////////////////////

				   ///////////////////////////////左右移動&左右回転///////////////////////
				   //ここをいじる場合はカメラもいじらないといけない！
	if (GetKeyboardPress(DIK_A))//もしAキーが入力されたら
	{
		xmovespeed = xmovespeed - 0.4f;//横移動スピード
		Zkaitenspeed = Zkaitenspeed + 0.016f;

	}
	else if (GetKeyboardPress(DIK_D))//もしDキーが入力されたら
	{
		xmovespeed = xmovespeed + 0.4f;//横移動スピード
		Zkaitenspeed = Zkaitenspeed - 0.016f;

	}
	else
	{
		//Xmodelの回転をもとに戻す処理//比率は 移動0.1 : 回転0.004 がベスト！
		if (Zkaitenidou >= 0.016) {
			Zkaitenidou = Zkaitenidou - 0.016f;
		}
		else if (Zkaitenidou <= -0.016) {
			Zkaitenidou = Zkaitenidou + 0.016f;
		}
	}

	//移動できる範囲の固定//ここをいじる場合はカメラもいじらないといけない！
	if (yokoidou <= -16)//もし横移動できる範囲の数値が-16になったら
	{
		yokoidou = -16;//横に移動できる範囲の固定
		Zkaitenspeed = 0;//横に回転できる範囲の固定
	}
	if (yokoidou >= 16)//もし横移動できる範囲の数値が1になったら
	{
		yokoidou = 16;//横に移動できる範囲の固定
		Zkaitenspeed = 0;//横に回転できる範囲の固定
	}


	Zkaitenidou = Zkaitenidou + Zkaitenspeed;//回転計算
	Zkaitenspeed = 0;//横回転スピード数値の初期化

	yokoidou = yokoidou + xmovespeed;//横移動計算
	xmovespeed = 0;//横移動スピード数値の初期化


				   ///////////////////////////////左右移動&左右回転///////////////////////

				   /////////////////////////////////上下移動////////////////////////////////////
				   //ここをいじる場合はカメラもいじらないといけない！
	if (GetKeyboardPress(DIK_W))//もしWキーが入力されたら
	{
		ymovespeed = ymovespeed + 0.4f;//縦移動スピード
		Xkaitenspeed = Xkaitenspeed - 0.016f;
	}
	else if (GetKeyboardPress(DIK_S))//もしSキーが入力されたら
	{
		ymovespeed = ymovespeed - 0.4f;//縦移動スピード
		Xkaitenspeed = Xkaitenspeed + 0.016f;
	}
	else
	{
		//Xmodelの回転をもとに戻す処理//比率は 移動0.1 : 回転0.004 がベスト！
		if (Xkaitenidou >= 0.016) {
			Xkaitenidou = Xkaitenidou - 0.016f;
		}
		else if (Xkaitenidou <= -0.016) {
			Xkaitenidou = Xkaitenidou + 0.016f;
		}
	}

	//移動できる範囲の固定//ここをいじる場合はカメラもいじらないといけない！
	if (tateidou <= 0)//もし縦移動できる範囲の数値が-1になったら
	{
		tateidou = 0;//縦に移動できる範囲の固定
		Xkaitenspeed = 0;
	}
	if (tateidou >= 16)//もし縦移動できる範囲の数値が20になったら
	{
		tateidou = 16;//縦に移動できる範囲の固定
		Xkaitenspeed = 0;
	}

	Xkaitenidou = Xkaitenidou + Xkaitenspeed;//回転計算
	Xkaitenspeed = 0;//縦回転スピード数値の初期化

	tateidou = tateidou + ymovespeed;//縦移動計算
	ymovespeed = 0;//縦移動スピード数値の初期化



				   /////////////////////////////////上下移動////////////////////////////////////

	atariidou(yokoidou, tateidou, okuidou);//atarihantei.hへ数字を送る/更新したプレイヤーの座標をあたり判定に送る

										   //SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
	D3DXMatrixIdentity(&g_mtxWorld05);//数字を入れるための初期化

									  //xモデル 05
	D3DXMatrixScaling(&g_mtxWorld05kakudai, x05, y05, z05);//Xモデルの拡大関数
	D3DXMatrixMultiply(&g_mtxWorld05, &g_mtxWorld05kakudai, &g_mtxWorld05);//合成

	D3DXMatrixRotationZ(&g_mtxWorld05Zrot, Zkaitenidou);//XモデルのZ回転関数
	D3DXMatrixMultiply(&g_mtxWorld05, &g_mtxWorld05kakudai, &g_mtxWorld05Zrot);//合成

	D3DXMatrixRotationX(&g_mtxWorld05Xrot, Xkaitenidou);//XモデルのX回転関数
	D3DXMatrixMultiply(&g_mtxWorld05, &g_mtxWorld05, &g_mtxWorld05Xrot);//合成

	D3DXMatrixTranslation(&g_mtxWorld05move, yokoidou, tateidou, okuidou);//Xモデルの平行移動関数
	D3DXMatrixMultiply(&g_mtxWorld05, &g_mtxWorld05, &g_mtxWorld05move);//合成

}

//==============
// 　描画関数
//==============
void DrawXmodel(void)
{

	g_nMaterialNum;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main.h//pDeviceを使う場合これが必要

											//xモデル 05
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld05);

	for (unsigned int i = 0; i < g_nMaterialNum; i++)
	{
		pMaterial[i].MatD3D.Ambient.r = 0.3f;
		pMaterial[i].MatD3D.Ambient.g = 0.3f;
		pMaterial[i].MatD3D.Ambient.b = 0.3f;
		pMaterial[i].MatD3D.Ambient.a = 1.0f;
	
		pDevice->SetMaterial(&pMaterial[i].MatD3D);

		pDevice->SetTexture(0, NULL);		//テクスチャを使う場合にNULLをg_pTextures[i]に変更

		g_pMesh->DrawSubset(i);
	}

}

//Xモデルの移動の初期化
void getiou(float yokoidounum, float tateidounum, float okuidounum) {
	yokoidou = yokoidounum;
	tateidou = tateidounum;
	okuidou = okuidounum;
	
}