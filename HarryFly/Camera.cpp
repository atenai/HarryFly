//=============================================================================
//
// カメラ [Camera.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include"Camera.h"
#include"Main.h"
#include"input.h"
#include "Sixyokika.h"
//*****************************************************************************
// グローバル変数
//*****************************************************************************

//カメラ座標
static float eyeX = 0.0f;
static float eyeY = 7.0f;
static float eyeZ = -35.0f;
//視点座標
static float atX = 0.0f;
static float atY = 0.0f;
static float atZ = 0.0f;

//カメラ
static D3DXMATRIX g_mtxView;
static D3DXMATRIX g_mtxPro;
static D3DXVECTOR3 g_UP_Vector(0.f, 1.f, 0.f);//上ベクトル
static D3DXVECTOR3 g_mae_Vector(0.f, 0.f, 1.f);//前ベクトル
static D3DXVECTOR3 g_RIGHT_Vector(1.f, 0.f, 0.f);//右ベクトル
static D3DXVECTOR3 g_eye_pos(eyeX, eyeY, eyeZ);//カメラ座標//eye
static D3DXVECTOR3 g_at_pos(atX, atY, atZ);//視点座標//at

static float g_Move_Speed = 0.4f;//左右上下のカメラ移動スピードの数値
static float g_okuMove_Speed = 0.4f;//スペースキーによるカメラが奥へ移動するスピードアップの数値
static float sabun = 0.0f;//カメラと物体の差分を計算する数値
static float g_sabunMove_Speed = 0.1f;//カメラの差分ぶん移動スピードがアップする数値
static float g_zidouMove_Speed = 0.5f;//カメラが奥へ自動移動するスピードの数値






void UpdateCamera(void)
{
	

	//カメラ
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	g_mae_Vector = g_at_pos - g_eye_pos;//前ベクトル＝視点座標ーカメラ座標

	D3DXVec3Cross(&g_RIGHT_Vector, &g_mae_Vector, &g_UP_Vector);//D3DXVec3Cross(&右ベクトル,&前ベクトル,&上ベクトル);
	D3DXVec3Normalize(&g_RIGHT_Vector, &g_RIGHT_Vector);//右ベクトルをノーマライズする単位化

														//////////////////////////////奥自動移動///////////////////////////////////

														//カメラ
														//前方へのカメラの自動移動
	D3DXVECTOR3 vec = g_mae_Vector;
	vec.y = 0;
	D3DXVec3Normalize(&vec, &vec);
	g_eye_pos += vec * g_zidouMove_Speed;
	g_at_pos += vec * g_zidouMove_Speed;

	if (GetKeyboardPress(DIK_SPACE)) {//スペースキーを押している間奥移動がスピードアップ！

									  //カメラ
		vec = g_mae_Vector;//D3DXVECTOR3 vec = 前ベクトル
		vec.y = 0;//vec.y=0;
		D3DXVec3Normalize(&vec, &vec);//D3DXVec3Normalize(&vec,&vec);
		g_eye_pos += vec * g_okuMove_Speed;//カメラ座標(eye) += vec * 速度//backに進むときは-=
		g_at_pos += vec * g_okuMove_Speed;//視点座標(at) += vec * 速度///backに進むときは-=

		sabun = sabun + 1;//差分を足していく
	}
	else
	{
		if (sabun >= 0 && !GetKeyboardPress(DIK_SPACE)) {//差分の数値がある時かつスペースキーが押されていない場合下の内容実行！
			vec = g_mae_Vector;
			vec.y = 0;
			D3DXVec3Normalize(&vec, &vec);
			g_eye_pos += vec * g_sabunMove_Speed;
			g_at_pos += vec * g_sabunMove_Speed;

			sabun = sabun - 1;//差分を引いていく
		}
	}

	if (g_eye_pos.z >= 280 && g_at_pos.z >= 350) {//カメラの奥移動の範囲制限
		g_zidouMove_Speed = 0;
		g_okuMove_Speed = 0;
		g_sabunMove_Speed = 0;
	}

	//////////////////////////////奥自動移動///////////////////////////////////

	///////////////////////////////左右移動&左右回転///////////////////////
	if (GetKeyboardPress(DIK_A))//もしAキーが入力されたら
	{

		//カメラ
		D3DXVECTOR3 vec = g_RIGHT_Vector;
		vec.y = 0;
		D3DXVec3Normalize(&vec, &vec);
		g_eye_pos += vec * g_Move_Speed;//back場合は-=
		g_at_pos += vec * g_Move_Speed;

	}
	else if (GetKeyboardPress(DIK_D))//もしDキーが入力されたら
	{

		//カメラ
		D3DXVECTOR3 vec = g_RIGHT_Vector;
		vec.y = 0;
		D3DXVec3Normalize(&vec, &vec);
		g_eye_pos -= vec * g_Move_Speed;//back場合は-=
		g_at_pos -= vec * g_Move_Speed;

	}


	//カメラの移動範囲の固定
	if (g_eye_pos.x <= -16 && g_at_pos.x <= -16)//カメラの左移動範囲の固定
	{
		g_eye_pos.x = -16;
		g_at_pos.x = -16;
	}

	if (g_eye_pos.x >= 16 && g_at_pos.x >= 16)//カメラの右移動範囲の固定
	{
		g_eye_pos.x = 16;
		g_at_pos.x = 16;
	}

	///////////////////////////////左右移動&左右回転///////////////////////

	/////////////////////////////////上下移動////////////////////////////////////
	if (GetKeyboardPress(DIK_W))//もしWキーが入力されたら
	{

		//カメラ
		vec = g_UP_Vector;
		vec.x = 0;
		vec.z = 0;
		D3DXVec3Normalize(&vec, &vec);
		g_eye_pos += vec * g_Move_Speed;//back場合は-=
		g_at_pos += vec * g_Move_Speed;
	}
	else if (GetKeyboardPress(DIK_S))//もしSキーが入力されたら
	{

		//カメラ
		vec = g_UP_Vector;
		vec.x = 0;
		vec.z = 0;
		D3DXVec3Normalize(&vec, &vec);
		g_eye_pos -= vec * g_Move_Speed;//back場合は-=
		g_at_pos -= vec * g_Move_Speed;

	}


	//カメラの移動範囲の固定
	if (g_eye_pos.y <= 7 && g_at_pos.y <= 0)//カメラの下移動範囲の固定
	{
		g_eye_pos.y = 7;
		g_at_pos.y = 0;
	}

	if (g_eye_pos.y >= 23 && g_at_pos.y >= 16)//カメラの上移動範囲の固定
	{
		g_eye_pos.y = 23;
		g_at_pos.y = 16;
	}

	/////////////////////////////////上下移動////////////////////////////////////


	//カメラ
	//ビュー行列
	D3DXMatrixLookAtLH(&g_mtxView, &g_eye_pos, &g_at_pos, &g_UP_Vector);
	//プロジェクション行列
	D3DXMatrixPerspectiveFovLH(&g_mtxPro, D3DX_PI / 3, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);


	//SetTransform二つ
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxPro);
}

//カメラ初期化用関数
void getcamera(void) {
	g_eye_pos = D3DXVECTOR3(eyeX, eyeY, eyeZ);//カメラ座標//eye
	g_at_pos = D3DXVECTOR3(atX, atY, atZ);//視点座標//at
	sabun = 0.0f;//スピードアップした際のカメラ差分の初期化
}