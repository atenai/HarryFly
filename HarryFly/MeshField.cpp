//=============================================================================
//
// メッシュフィールド [MeshField.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Polygon.h"
#include "MeshField.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESH_H	(1000)	//縦の長さ
#define MESH_W	(20)	//横の長さ

#define VERTEX_COUNT ((MESH_W+1)*(MESH_H+1))						//頂点数
#define INDEX_COUNT ((((MESH_H+1) * 2)*MESH_H + (MESH_W * 2) -1))	//インデックス数
#define PRIM_COUNT (MESH_H*MESH_W*2)								//プリミティブ数

#define OBJECT_COUNT (1)//表示するオブジェクト数
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE|D3DFVF_TEX1|D3DFVF_NORMAL) //設定
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE|D3DFVF_TEX1) //設定

typedef struct
{
	D3DXMATRIX mtx_meshNull;	//入れ物
	D3DXMATRIX mtx_meshWorld;	//ワールド
	D3DXMATRIX mtx_meshTrans;	//移動
	D3DXMATRIX mtx_meshRot;		//回転総合
	D3DXMATRIX mtx_meshRotX;	//回転X
	D3DXMATRIX mtx_meshRotY;	//回転Y
	D3DXMATRIX mtx_meshRotZ;	//回転Z
	D3DXMATRIX mtx_meshScale;	//拡縮

	float fTransX = 0;//移動X
	float fTransY = 0;//移動Y
	float fTransZ = 0;//移動Z

	float fRotX = 0;//回転X
	float fRotY = 0;//回転Y
	float fRotZ = 0;//回転Z

	float fScaleX = 1;//拡大X(等倍)
	float fScaleY = 1;//拡大Y(等倍)
	float fScaleZ = 1;//拡大Z(等倍)

}OBJECT;

static OBJECT object[OBJECT_COUNT];
static D3DXMATRIX g_mtx_meshWorld;

static float g_fTexCoorX = 0;//テクスチャ座標X
static float g_fTexCoorY = 0;//テクスチャ座標Y

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 Normal;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX_3D;


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static float u0[MESH_H*MESH_W];
static float v0[MESH_H*MESH_W];
static float u1[MESH_H*MESH_W];
static float v1[MESH_H*MESH_W];

static VERTEX_3D V[VERTEX_COUNT];

static WORD index[INDEX_COUNT];

static int g_animCnt;
static	LPDIRECT3DVERTEXBUFFER9	g_pVertexBuffer = NULL;
static 	LPDIRECT3DINDEXBUFFER9	g_pIndexBuffer = NULL;
static	LPDIRECT3DTEXTURE9		g_pTexture[MESH_MAXIMUM] = { NULL, };

//==============
//  初期化関数
//==============
void InitMesh(void)
{
	VERTEX_3D* pV;
	LPWORD LPindex;
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	static int nCntTexture;

	float defX = -(float)MESH_W / 2;
	float defZ = (float)MESH_H / 2;
	float defY = 0;


	for (int nCnt = 0; nCnt < MESH_H*MESH_W; nCnt++)
	{
		u0[nCnt] = 0;
		v0[nCnt] = 0;
		u1[nCnt] = 1;
		v1[nCnt] = 1;
	}

	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);

	int ver = 0;

	for (int nCntH = 0; nCntH < MESH_H + 1; nCntH++)
	{
		for (int nCntW = 0; nCntW < MESH_W + 1; nCntW++)
		{
			V[ver].pos = D3DXVECTOR3(defX + nCntW, 0.0f, defZ - nCntH);
			V[ver].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			V[ver].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			V[ver].texcoord = D3DXVECTOR2(g_fTexCoorX, g_fTexCoorY);

			g_fTexCoorX += 1.0f;

			ver++;
		}
		g_fTexCoorX = 0.0f;
		g_fTexCoorY += 1.0f;
	}

	V[0].texcoord = D3DXVECTOR2(0, 0);
	V[1].texcoord = D3DXVECTOR2(1, 0);
	V[MESH_W + 1].texcoord = D3DXVECTOR2(0, 1);
	V[MESH_W + 2].texcoord = D3DXVECTOR2(1, 1);





	int idx = 0;

	for (int y = 0; y < MESH_H + 1; y++)
	{
		if (!y == 0)
		{
			index[idx] = (MESH_W + 1)*(y + 1);
			idx++;
		}

		for (int x = 0; x < MESH_W + 1; x++)
		{
			index[idx] = (MESH_W + 1 + x) + ((MESH_W + 1)*y);
			idx++;
			index[idx] = x + ((MESH_W + 1)*y);
			idx++;
		}
		index[idx] = MESH_W + ((MESH_W + 1)*y);
		idx++;
	}

	//テクスチャの読み込み
	for (nCntTexture = 0; nCntTexture < MESH_MAXIMUM; nCntTexture++)
	{
		if (FAILED(D3DXCreateTextureFromFile(pDevice,//デバイス
			cTextuerMesh[nCntTexture].FileName,//ファイル名
			&g_pTexture[nCntTexture]//アドレスのアドレス	
		)))
		{
			MessageBox(NULL, "MESH_TEX_ERROR", "失敗", MB_OK);
		}
	};

	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,	//借りたい量　頂点数*4 バイト
		D3DUSAGE_WRITEONLY,		//使用用途 D3DUSAGE_WRITEONLY = 書き込みしかしない
		FVF_VERTEX_3D,			//FVF
		D3DPOOL_MANAGED,		//頂点の管理方法
		&g_pVertexBuffer,		//管理者の居場所のメモ
		NULL					//不明
	))) {
		MessageBox(NULL, "頂点バッファの作成に失敗しました", "失敗", MB_OK);
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_COUNT, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX_COUNT, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);

	//ベクトル読み取り
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);//メモリに書き込み始め
	memcpy(pV, V, sizeof(VERTEX_3D) * VERTEX_COUNT);//CPUにメモリを入れる(コピーする)
	g_pVertexBuffer->Unlock();//メモリに書き込み終わり

							  //インデックス読み取り
	g_pIndexBuffer->Lock(0, 0, (void**)&LPindex, D3DLOCK_DISCARD);//メモリに書き込み始め
	memcpy(LPindex, index, sizeof(WORD) * INDEX_COUNT);//CPUにメモリを入れる(コピーする)
	g_pIndexBuffer->Unlock();//メモリに書き込み終わり
}

//==============
//  終了関数
//==============
void UninitMesh(void)
{
	for (int nCntTexture = 0; nCntTexture < MESH_MAXIMUM; nCntTexture++)
	{
		if (g_pTexture[nCntTexture] != NULL)
		{
			g_pTexture[nCntTexture]->Release();//借りたメモリを返す
			g_pTexture[nCntTexture] = NULL;
		}//g_pTextureがNULLじゃなかったらNULLにする
	}

	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer->Release();//借りたメモリを返す
		g_pVertexBuffer = NULL;
	}//g_pVertexBufferがNULLじゃなかったらNULLにする


	if (g_pIndexBuffer != NULL)
	{
		g_pIndexBuffer->Release();//借りたメモリを返す
		g_pIndexBuffer = NULL;
	}//g_pIndexBufferがNULLじゃなかったらNULLにする
}

//==============
// 　更新関数
//==============
void UpdateMesh(void)
{
	//ワールド変換行列
	for (int nCnt = 0; nCnt < OBJECT_COUNT; nCnt++)
	{
		D3DXMatrixIdentity(&object[nCnt].mtx_meshWorld);

		/*回転*/
		D3DXMatrixRotationX(&object[nCnt].mtx_meshRotX, object[nCnt].fRotX);
		D3DXMatrixRotationY(&object[nCnt].mtx_meshRotY, object[nCnt].fRotY);
		D3DXMatrixRotationZ(&object[nCnt].mtx_meshRotZ, object[nCnt].fRotZ);
		D3DXMatrixMultiply(&object[nCnt].mtx_meshRot, &object[nCnt].mtx_meshRotX, &object[nCnt].mtx_meshRotY);
		D3DXMatrixMultiply(&object[nCnt].mtx_meshRot, &object[nCnt].mtx_meshRot, &object[nCnt].mtx_meshRotZ);

		/*拡大*/
		D3DXMatrixScaling(&object[nCnt].mtx_meshScale, object[nCnt].fScaleX, object[nCnt].fScaleY, object[nCnt].fScaleZ);

		/*移動*/
		D3DXMatrixTranslation(&object[nCnt].mtx_meshTrans, object[nCnt].fTransX, object[nCnt].fTransY, object[nCnt].fTransZ);

		/*拡縮x回転*/
		D3DXMatrixMultiply(&object[nCnt].mtx_meshNull, &object[nCnt].mtx_meshScale, &object[nCnt].mtx_meshRot);

		/*(拡縮x回転)x移動*/
		D3DXMatrixMultiply(&object[nCnt].mtx_meshWorld, &object[nCnt].mtx_meshNull, &object[nCnt].mtx_meshTrans);

	}//END OF for (int nCnt = 0; nCnt < OBJECT_COUNT; nCnt++)

}//END OF void meshUpdate(void)

 //==============
 // 　描画関数
 //==============
void DrawMesh(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	for (int nCnt = 0; nCnt < OBJECT_COUNT; nCnt++)
	{
		pDevice->SetFVF(FVF_VERTEX_3D);
		pDevice->SetRenderState(D3DRS_LIGHTING, false);//ライティングオフ

													   //各種行列の設定
		pDevice->SetTransform(D3DTS_WORLD, &object[nCnt].mtx_meshWorld);		//セットしたい行列の先頭アドレス
		pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_3D));
		pDevice->SetIndices(g_pIndexBuffer);

		//マテリアルの設定

		pDevice->SetTexture(0, g_pTexture[1]);//何番目のテクスチャを使うかをここでセットする
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VERTEX_COUNT, 0, PRIM_COUNT + INDEX_COUNT - VERTEX_COUNT);

	}//END OF for (int nCnt = 0; nCnt < OBJECT_COUNT; nCnt++)

}//END OF void meshDraw(void)
