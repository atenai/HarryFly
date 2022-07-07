#include "Bonbe.h"
#include "Main.h"
#include "Atarihantei.h"

//�݌v�}�����
typedef struct {
	D3DXVECTOR3 pos;//���W
	D3DXMATRIX mtxworld;//
	D3DXMATRIX mtxworldS;//�g�k�p�ϐ�
	D3DXMATRIX mtxworldR;//�g�k�p�ϐ�
	D3DXMATRIX mtxworldT;//�ړ��p�֐�
	bool hihixyouzibonbe;//�{���x�̕\����\��
}BONBE_DATA;

static BONBE_DATA Bonbe[6];//�\���̂ŃA�C�e����������邩��錾

//�\���̂��񂷁i���[�v�j�����邽�߂̕ϐ�
static int Ui = 0;//�\���̂����[�v�����邽�߂̕ϐ�


//X���f���\���悤�֐��̏�����
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

	for (Ui = 0; Ui < 6; Ui++)//�\���̂̐������� 
	{
		Bonbe[Ui].hihixyouzibonbe = true;//�{���x�̕\��
	}

		//������
		LPD3DXBUFFER  pItemAdjacencyBuffer;

		LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

		//X���f���̃A�h���X
		HRESULT hr;

		hr = D3DXLoadMeshFromX("./recource/bonbe5.x", D3DXMESH_SYSTEMMEM,
			pDevice, &pItemAdjacencyBuffer, &g_pBonbeMaterialBuffer, NULL, &g_nBonbeMaterialNum, &g_pBonbeMesh);

		if (FAILED(hr))
		{
			MessageBox(NULL, "Xmodel�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK);
		}

		//�}�e���A���̎擾
		pBonbeMaterial = (LPD3DXMATERIAL)g_pBonbeMaterialBuffer->GetBufferPointer();

		hr = g_pBonbeMesh->OptimizeInplace(D3DXMESHOPT_COMPACT |
			D3DXMESHOPT_ATTRSORT |
			D3DXMESHOPT_VERTEXCACHE,
			(DWORD*)pItemAdjacencyBuffer->GetBufferPointer(),
			NULL, NULL, NULL);

		if (FAILED(hr))
		{
			MessageBox(NULL, "���b�V���̍œK���Ɂu���s���܂���", "�G���[", MB_OK);
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



	for (Ui = 0; Ui < 6; Ui++)//�\���̂̐������� 
	{

		ataribonbe(Ui, Bonbe[Ui].pos.x, Bonbe[Ui].pos.y, Bonbe[Ui].pos.z);//�X�V�����{���x�̐��ƍ��W�������蔻��ɑ���

		D3DXMatrixIdentity(&Bonbe[Ui].mtxworld);

		D3DXMatrixRotationZ(&Bonbe[Ui].mtxworldR, -0.4f);//X���f����Z��]�֐�
		D3DXMatrixMultiply(&Bonbe[Ui].mtxworld, &Bonbe[Ui].mtxworld, &Bonbe[Ui].mtxworldR);//����

		D3DXMatrixTranslation(&Bonbe[Ui].mtxworldT, Bonbe[Ui].pos.x, Bonbe[Ui].pos.y, Bonbe[Ui].pos.z);//���s�ړ��֐�
		D3DXMatrixMultiply(&Bonbe[Ui].mtxworld, &Bonbe[Ui].mtxworld, &Bonbe[Ui].mtxworldT);//����
	}
}

void Drawbonbe(void) 
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	for (Ui = 0; Ui < 6; Ui++)//�\���̂̐������� 
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

				pDevice->SetTexture(0, NULL);		//�e�N�X�`�����g���ꍇ��NULL��g_pTextures[i]�ɕύX

				HRESULT hrResult = g_pBonbeMesh->DrawSubset(i);

				
				if (FAILED(hrResult))//�G���[�`�F�b�N
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

	g_pBonbeMesh = NULL;//LPD3DXMESH��NULL�Ń������J��
	g_nBonbeMaterialNum = 0;//DWORD��0�Ń������J��
	g_pBonbeMaterialBuffer = NULL;//LPD3DXBUFFER��NULL�Ń������J��
	pBonbeMaterial = NULL;//LPD3DXBUFFER��NULL�Ń������J��
	pBonbeTemMesh = NULL;//LPD3DXMESH��NULL�Ń������J��
	Ui = 0;//int��0�Ń������J��
	//bool��false�Ń������J��
}

//�{���x�̂����蔻��ɐ��l�𑗂�
void hihixyouzibonbe(int bonbesu, bool drawbonbe)
{
	Bonbe[bonbesu].hihixyouzibonbe = drawbonbe;//false�̒l��ataribonbex�ɓ����

}
//�{���x�̏������̓��e�𑗂�
void sixyyokikadrawbonbe(int bonbesu, bool drawbonbe)
{
	Bonbe[bonbesu].hihixyouzibonbe = drawbonbe;//true�̒l��ataribonbex�ɓ����
}