#include "Bonbe.h"
#include "Main.h"
#include "Atarihantei.h"

//設計図を作る
typedef struct {
	D3DXVECTOR3 pos;//座標
	D3DXMATRIX mtxworld;//
	D3DXMATRIX mtxworldS;//拡縮用変数
	D3DXMATRIX mtxworldR;//拡縮用変数
	D3DXMATRIX mtxworldT;//移動用関数
	bool hihixyouzibonbe;//ボンベの表示非表示
}BONBE_DATA;

static BONBE_DATA Bonbe[6];//構造体でアイテムをいくつ作るかを宣言

//構造体を回す（ループ）させるための変数
static int Ui = 0;//構造体をループさせるための変数


//Xモデル表示よう関数の初期化
static LPD3DXBUFFER   g_pBonbeMaterialBuffer = NULL;
static DWORD          g_nBonbeMaterialNum = 0;
static LPD3DXMESH     g_pBonbeMesh = NULL;
static LPD3DXMATERIAL pBonbeMaterial;
static LPD3DXMESH     pBonbeTemMesh;

void Initbonbe(void) 
{
	Bonbe[0].pos.x = 2;
	Bonbe[0].pos.y = 3;
	Bonbe[0].pos.z = 40;

	Bonbe[1].pos.x = 5;
	Bonbe[1].pos.y = 5;
	Bonbe[1].pos.z = 80;

	Bonbe[2].pos.x = 3;
	Bonbe[2].pos.y = 3;
	Bonbe[2].pos.z = 120;

	Bonbe[3].pos.x = -4;
	Bonbe[3].pos.y = 3;
	Bonbe[3].pos.z = 160;

	Bonbe[4].pos.x = -8;
	Bonbe[4].pos.y = 3;
	Bonbe[4].pos.z = 200;

	Bonbe[5].pos.x = 3;
	Bonbe[5].pos.y = 3;
	Bonbe[5].pos.z = 240;

	for (Ui = 0; Ui < 6; Ui++)//構造体の数だけ回す 
	{
		Bonbe[Ui].hihixyouzibonbe = true;//ボンベの表示
	}

		//初期化
		LPD3DXBUFFER  pItemAdjacencyBuffer;

		LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

		//Xモデルのアドレス
		HRESULT hr;

		hr = D3DXLoadMeshFromX("./recource/bonbe5.x", D3DXMESH_SYSTEMMEM,
			pDevice, &pItemAdjacencyBuffer, &g_pBonbeMaterialBuffer, NULL, &g_nBonbeMaterialNum, &g_pBonbeMesh);

		if (FAILED(hr))
		{
			MessageBox(NULL, "Xmodelファイルの読み込みに失敗しました", "エラー", MB_OK);
		}

		//マテリアルの取得
		pBonbeMaterial = (LPD3DXMATERIAL)g_pBonbeMaterialBuffer->GetBufferPointer();

		hr = g_pBonbeMesh->OptimizeInplace(D3DXMESHOPT_COMPACT |
			D3DXMESHOPT_ATTRSORT |
			D3DXMESHOPT_VERTEXCACHE,
			(DWORD*)pItemAdjacencyBuffer->GetBufferPointer(),
			NULL, NULL, NULL);

		if (FAILED(hr))
		{
			MessageBox(NULL, "メッシュの最適化に「失敗しました", "エラー", MB_OK);
		}

		if (pItemAdjacencyBuffer != NULL)
		{
			pItemAdjacencyBuffer->Release();
		}

		D3DVERTEXELEMENT9 Elements[32];

		g_pBonbeMesh->GetDeclaration(Elements);

		hr = g_pBonbeMesh->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, Elements, pDevice, &pBonbeTemMesh);

		if (FAILED(hr)) {
			char b = 'b';
		}

		g_pBonbeMesh->Release();

		g_pBonbeMesh = pBonbeTemMesh;

}

void Updatebonbe(void) 
{



	for (Ui = 0; Ui < 6; Ui++)//構造体の数だけ回す 
	{

		ataribonbe(Ui, Bonbe[Ui].pos.x, Bonbe[Ui].pos.y, Bonbe[Ui].pos.z);//更新したボンベの数と座標をあたり判定に送る

		D3DXMatrixIdentity(&Bonbe[Ui].mtxworld);

		D3DXMatrixRotationZ(&Bonbe[Ui].mtxworldR, -0.4f);//XモデルのZ回転関数
		D3DXMatrixMultiply(&Bonbe[Ui].mtxworld, &Bonbe[Ui].mtxworld, &Bonbe[Ui].mtxworldR);//合成

		D3DXMatrixTranslation(&Bonbe[Ui].mtxworldT, Bonbe[Ui].pos.x, Bonbe[Ui].pos.y, Bonbe[Ui].pos.z);//平行移動関数
		D3DXMatrixMultiply(&Bonbe[Ui].mtxworld, &Bonbe[Ui].mtxworld, &Bonbe[Ui].mtxworldT);//合成
	}
}

void Drawbonbe(void) 
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	for (Ui = 0; Ui < 6; Ui++)//構造体の数だけ回す 
	{
		if (Bonbe[Ui].hihixyouzibonbe == true) {

			pDevice->SetTransform(D3DTS_WORLD, &Bonbe[Ui].mtxworld);


			for (unsigned int i = 0; i < g_nBonbeMaterialNum; i++)
			{
				pBonbeMaterial[i].MatD3D.Ambient.r = 0.3f;
				pBonbeMaterial[i].MatD3D.Ambient.g = 0.3f;
				pBonbeMaterial[i].MatD3D.Ambient.b = 0.3f;
				pBonbeMaterial[i].MatD3D.Ambient.a = 1.0f;

				pDevice->SetMaterial(&pBonbeMaterial[i].MatD3D);

				pDevice->SetTexture(0, NULL);		//テクスチャを使う場合にNULLをg_pTextures[i]に変更

				HRESULT hrResult = g_pBonbeMesh->DrawSubset(i);

				
				if (FAILED(hrResult))//エラーチェック
				{
					char b = 'b';
				}
			}
		}
	}
}

void Uninitbonbe(void) 
{
	g_pBonbeMaterialBuffer->Release();

	g_pBonbeMesh = NULL;//LPD3DXMESHはNULLでメモリ開放
	g_nBonbeMaterialNum = 0;//DWORDは0でメモリ開放
	g_pBonbeMaterialBuffer = NULL;//LPD3DXBUFFERはNULLでメモリ開放
	pBonbeMaterial = NULL;//LPD3DXBUFFERはNULLでメモリ開放
	pBonbeTemMesh = NULL;//LPD3DXMESHはNULLでメモリ開放
	Ui = 0;//intは0でメモリ開放
	//boolはfalseでメモリ開放
}

//ボンベのあたり判定に数値を送る
void hihixyouzibonbe(int bonbesu, bool drawbonbe)
{
	Bonbe[bonbesu].hihixyouzibonbe = drawbonbe;//falseの値をataribonbexに入れる

}
//ボンベの初期化の内容を送る
void sixyyokikadrawbonbe(int bonbesu, bool drawbonbe)
{
	Bonbe[bonbesu].hihixyouzibonbe = drawbonbe;//trueの値をataribonbexに入れる
}