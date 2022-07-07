#include "Coin.h"
#include "Main.h"
#include "Atarihantei.h"

typedef struct {
	D3DXVECTOR3 pos;//座標
	D3DXMATRIX mtxworld;//
	D3DXMATRIX mtxworldS;//拡縮用変数
	D3DXMATRIX mtxworldR;//拡縮用変数
	D3DXMATRIX mtxworldT;//移動用関数
	bool hihixyouzicoin;//ボンベの表示非表示
}COIN_DATA;

static COIN_DATA Coin[10];//構造体でアイテムをいくつ作るかを宣言

 //構造体を回す（ループ）させるための変数
static int Ui = 0;//構造体をループさせるための変数

static float coinkaiten = 0.0f;

				  //Xモデル表示よう関数の初期化
static LPD3DXBUFFER   g_pCoinMaterialBuffer = NULL;
static DWORD          g_nCoinMaterialNum = 0;
static LPD3DXMESH     g_pCoinMesh = NULL;
static LPD3DXMATERIAL pCoinMaterial;
static LPD3DXMESH     pCoinTemMesh;

void Initcoin(void)
{
	Coin[0].pos.x = -2;
	Coin[0].pos.y = 3;
	Coin[0].pos.z = 40;

	Coin[1].pos.x = -5;
	Coin[1].pos.y = 5;
	Coin[1].pos.z = 80;

	Coin[2].pos.x = -3;
	Coin[2].pos.y = 3;
	Coin[2].pos.z = 120;

	Coin[3].pos.x = 4;
	Coin[3].pos.y = 3;
	Coin[3].pos.z = 160;

	Coin[4].pos.x = 5;
	Coin[4].pos.y = 0;
	Coin[4].pos.z = 200;

	Coin[5].pos.x = -3;
	Coin[5].pos.y = 3;
	Coin[5].pos.z = 240;

	Coin[6].pos.x = -5;
	Coin[6].pos.y = 5;
	Coin[6].pos.z = 260;

	Coin[7].pos.x = -3;
	Coin[7].pos.y = 3;
	Coin[7].pos.z = 220;

	Coin[8].pos.x = 4;
	Coin[8].pos.y = 3;
	Coin[8].pos.z = 180;

	Coin[9].pos.x = 5;
	Coin[9].pos.y = 7;
	Coin[9].pos.z = 140;


	for (Ui = 0; Ui < 10; Ui++)//構造体の数だけ回す 
	{
		Coin[Ui].hihixyouzicoin = true;//ボンベの表示
	}

	//初期化
	LPD3DXBUFFER  pCoinAdjacencyBuffer;

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//Xモデルのアドレス
	HRESULT hr;

	hr = D3DXLoadMeshFromX("./recource/coin2.x", D3DXMESH_SYSTEMMEM,
		pDevice, &pCoinAdjacencyBuffer, &g_pCoinMaterialBuffer, NULL, &g_nCoinMaterialNum, &g_pCoinMesh);

	if (FAILED(hr))
	{
		MessageBox(NULL, "Xmodelファイルの読み込みに失敗しました", "エラー", MB_OK);
	}

	//マテリアルの取得
	pCoinMaterial = (LPD3DXMATERIAL)g_pCoinMaterialBuffer->GetBufferPointer();

	hr = g_pCoinMesh->OptimizeInplace(D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)pCoinAdjacencyBuffer->GetBufferPointer(),
		NULL, NULL, NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "メッシュの最適化に「失敗しました", "エラー", MB_OK);
	}

	if (pCoinAdjacencyBuffer != NULL)
	{
		pCoinAdjacencyBuffer->Release();
	}

	D3DVERTEXELEMENT9 Elements[32];

	g_pCoinMesh->GetDeclaration(Elements);

	hr = g_pCoinMesh->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, Elements, pDevice, &pCoinTemMesh);

	if (FAILED(hr))//エラーチェック 
	{
		char b = 'b';
	}

	g_pCoinMesh->Release();

	g_pCoinMesh = pCoinTemMesh;

}

void Updatecoin(void)
{



	for (Ui = 0; Ui < 10; Ui++)//構造体の数だけ回す 
	{

		ataricoin(Ui, Coin[Ui].pos.x, Coin[Ui].pos.y, Coin[Ui].pos.z);//更新したボンベの数と座標をあたり判定に送る

		D3DXMatrixIdentity(&Coin[Ui].mtxworld);

		coinkaiten = coinkaiten + 0.01f;//コイン回転のスピード

		D3DXMatrixRotationY(&Coin[Ui].mtxworldR, coinkaiten);//XモデルのZ回転関数
		D3DXMatrixMultiply(&Coin[Ui].mtxworld, &Coin[Ui].mtxworld, &Coin[Ui].mtxworldR);//合成

		D3DXMatrixTranslation(&Coin[Ui].mtxworldT, Coin[Ui].pos.x, Coin[Ui].pos.y, Coin[Ui].pos.z);//平行移動関数
		D3DXMatrixMultiply(&Coin[Ui].mtxworld, &Coin[Ui].mtxworld, &Coin[Ui].mtxworldT);//合成
	}
}

void Drawcoin(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	for (Ui = 0; Ui < 10; Ui++)//構造体の数だけ回す 
	{
		if (Coin[Ui].hihixyouzicoin == true) {

			pDevice->SetTransform(D3DTS_WORLD, &Coin[Ui].mtxworld);


			for (unsigned int i = 0; i < g_nCoinMaterialNum; i++)
			{
				pCoinMaterial[i].MatD3D.Ambient.r = 0.3f;
				pCoinMaterial[i].MatD3D.Ambient.g = 0.3f;
				pCoinMaterial[i].MatD3D.Ambient.b = 0.3f;
				pCoinMaterial[i].MatD3D.Ambient.a = 1.0f;

				pDevice->SetMaterial(&pCoinMaterial[i].MatD3D);

				pDevice->SetTexture(0, NULL);		//テクスチャを使う場合にNULLをg_pTextures[i]に変更

				HRESULT hrResult = g_pCoinMesh->DrawSubset(i);


				if (FAILED(hrResult))//エラーチェック
				{
					char b = 'b';
				}
			}
		}
	}
}

void Uninitcoin(void)
{
	g_pCoinMaterialBuffer->Release();


	g_pCoinMesh = NULL;//LPD3DXMESHはNULLでメモリ開放
	g_nCoinMaterialNum = 0;//DWORDは0でメモリ開放
	g_pCoinMaterialBuffer = NULL;//LPD3DXBUFFERはNULLでメモリ開放
	pCoinMaterial = NULL;//LPD3DXBUFFERはNULLでメモリ開放
	pCoinTemMesh = NULL;//LPD3DXMESHはNULLでメモリ開放
	coinkaiten = 0.0f;//floatは0.0fでメモリ開放
	Ui = 0;//intは0でメモリ開放
	//boolはfalseでメモリ開放
}

//ボンベのあたり判定に数値を送る
void hihixyouzicoin(int coinsu, bool drawcoin)
{
	Coin[coinsu].hihixyouzicoin = drawcoin;//falseの値をataricoinに入れる

}
//ボンベの初期化の内容を送る
void sixyyokikadrawcoin(int coinsu, bool drawcoin)
{
	Coin[coinsu].hihixyouzicoin = drawcoin;//trueの値をsixyokikacoinに入れる
}