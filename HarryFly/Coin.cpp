#include "Coin.h"
#include "Main.h"
#include "Atarihantei.h"

typedef struct {
	D3DXVECTOR3 pos;//���W
	D3DXMATRIX mtxworld;//
	D3DXMATRIX mtxworldS;//�g�k�p�ϐ�
	D3DXMATRIX mtxworldR;//�g�k�p�ϐ�
	D3DXMATRIX mtxworldT;//�ړ��p�֐�
	bool hihixyouzicoin;//�{���x�̕\����\��
}COIN_DATA;

static COIN_DATA Coin[10];//�\���̂ŃA�C�e����������邩��錾

 //�\���̂��񂷁i���[�v�j�����邽�߂̕ϐ�
static int Ui = 0;//�\���̂����[�v�����邽�߂̕ϐ�

static float coinkaiten = 0.0f;

				  //X���f���\���悤�֐��̏�����
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


	for (Ui = 0; Ui < 10; Ui++)//�\���̂̐������� 
	{
		Coin[Ui].hihixyouzicoin = true;//�{���x�̕\��
	}

	//������
	LPD3DXBUFFER  pCoinAdjacencyBuffer;

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//X���f���̃A�h���X
	HRESULT hr;

	hr = D3DXLoadMeshFromX("./recource/coin2.x", D3DXMESH_SYSTEMMEM,
		pDevice, &pCoinAdjacencyBuffer, &g_pCoinMaterialBuffer, NULL, &g_nCoinMaterialNum, &g_pCoinMesh);

	if (FAILED(hr))
	{
		MessageBox(NULL, "Xmodel�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK);
	}

	//�}�e���A���̎擾
	pCoinMaterial = (LPD3DXMATERIAL)g_pCoinMaterialBuffer->GetBufferPointer();

	hr = g_pCoinMesh->OptimizeInplace(D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)pCoinAdjacencyBuffer->GetBufferPointer(),
		NULL, NULL, NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "���b�V���̍œK���Ɂu���s���܂���", "�G���[", MB_OK);
	}

	if (pCoinAdjacencyBuffer != NULL)
	{
		pCoinAdjacencyBuffer->Release();
	}

	D3DVERTEXELEMENT9 Elements[32];

	g_pCoinMesh->GetDeclaration(Elements);

	hr = g_pCoinMesh->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, Elements, pDevice, &pCoinTemMesh);

	if (FAILED(hr))//�G���[�`�F�b�N 
	{
		char b = 'b';
	}

	g_pCoinMesh->Release();

	g_pCoinMesh = pCoinTemMesh;

}

void Updatecoin(void)
{



	for (Ui = 0; Ui < 10; Ui++)//�\���̂̐������� 
	{

		ataricoin(Ui, Coin[Ui].pos.x, Coin[Ui].pos.y, Coin[Ui].pos.z);//�X�V�����{���x�̐��ƍ��W�������蔻��ɑ���

		D3DXMatrixIdentity(&Coin[Ui].mtxworld);

		coinkaiten = coinkaiten + 0.01f;//�R�C����]�̃X�s�[�h

		D3DXMatrixRotationY(&Coin[Ui].mtxworldR, coinkaiten);//X���f����Z��]�֐�
		D3DXMatrixMultiply(&Coin[Ui].mtxworld, &Coin[Ui].mtxworld, &Coin[Ui].mtxworldR);//����

		D3DXMatrixTranslation(&Coin[Ui].mtxworldT, Coin[Ui].pos.x, Coin[Ui].pos.y, Coin[Ui].pos.z);//���s�ړ��֐�
		D3DXMatrixMultiply(&Coin[Ui].mtxworld, &Coin[Ui].mtxworld, &Coin[Ui].mtxworldT);//����
	}
}

void Drawcoin(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	for (Ui = 0; Ui < 10; Ui++)//�\���̂̐������� 
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

				pDevice->SetTexture(0, NULL);		//�e�N�X�`�����g���ꍇ��NULL��g_pTextures[i]�ɕύX

				HRESULT hrResult = g_pCoinMesh->DrawSubset(i);


				if (FAILED(hrResult))//�G���[�`�F�b�N
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


	g_pCoinMesh = NULL;//LPD3DXMESH��NULL�Ń������J��
	g_nCoinMaterialNum = 0;//DWORD��0�Ń������J��
	g_pCoinMaterialBuffer = NULL;//LPD3DXBUFFER��NULL�Ń������J��
	pCoinMaterial = NULL;//LPD3DXBUFFER��NULL�Ń������J��
	pCoinTemMesh = NULL;//LPD3DXMESH��NULL�Ń������J��
	coinkaiten = 0.0f;//float��0.0f�Ń������J��
	Ui = 0;//int��0�Ń������J��
	//bool��false�Ń������J��
}

//�{���x�̂����蔻��ɐ��l�𑗂�
void hihixyouzicoin(int coinsu, bool drawcoin)
{
	Coin[coinsu].hihixyouzicoin = drawcoin;//false�̒l��ataricoin�ɓ����

}
//�{���x�̏������̓��e�𑗂�
void sixyyokikadrawcoin(int coinsu, bool drawcoin)
{
	Coin[coinsu].hihixyouzicoin = drawcoin;//true�̒l��sixyokikacoin�ɓ����
}