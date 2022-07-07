#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Polygon.h"
#include "Main.h"
#include "Cube.h"
#include "Grit.h"

//3D用頂点データ

//構造体の宣言
typedef struct {
	D3DXVECTOR3 pos;
	D3DCOLOR color;
}VERTEX3D;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//FVFの宣言(定数)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE)//設定

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//グローバル変数に行列を用意
//D3DXMATRIX(4×4)(16ビット消費)
static D3DXMATRIX g_mtxWorld;



//==============
// 　更新関数
//==============
void UpdateGrit(void) {

	//ワールド変換行列
	//何もしない行列（単位行列）
	D3DXMatrixIdentity(&g_mtxWorld);

}

//==============
// 　描画関数
//==============
void DrawGrit(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main.h

											//頂点の作成
	VERTEX3D v[44];


	v[0].pos = D3DXVECTOR3(-10.0f, 5.0f, 320.0f);
	v[0].color = D3DCOLOR_RGBA(187, 0, 75, 255);

	v[1].pos = D3DXVECTOR3(10.0f, 5.0f, 320.0f);
	v[1].color = D3DCOLOR_RGBA(187, 0, 75, 255);

	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//各種行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);


	//描画(ファン形式で、面１つ、頂点配列へのアドレス、サイズは頂点構造体)
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &v[0], sizeof(VERTEX3D));


}