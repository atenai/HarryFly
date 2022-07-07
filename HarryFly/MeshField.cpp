//=============================================================================
//
// ���b�V���t�B�[���h [MeshField.cpp]
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
// �}�N����`
//*****************************************************************************
#define MESH_H	(1000)	//�c�̒���
#define MESH_W	(20)	//���̒���

#define VERTEX_COUNT ((MESH_W+1)*(MESH_H+1))						//���_��
#define INDEX_COUNT ((((MESH_H+1) * 2)*MESH_H + (MESH_W * 2) -1))	//�C���f�b�N�X��
#define PRIM_COUNT (MESH_H*MESH_W*2)								//�v���~�e�B�u��

#define OBJECT_COUNT (1)//�\������I�u�W�F�N�g��
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE|D3DFVF_TEX1|D3DFVF_NORMAL) //�ݒ�
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE|D3DFVF_TEX1) //�ݒ�

typedef struct
{
	D3DXMATRIX mtx_meshNull;	//���ꕨ
	D3DXMATRIX mtx_meshWorld;	//���[���h
	D3DXMATRIX mtx_meshTrans;	//�ړ�
	D3DXMATRIX mtx_meshRot;		//��]����
	D3DXMATRIX mtx_meshRotX;	//��]X
	D3DXMATRIX mtx_meshRotY;	//��]Y
	D3DXMATRIX mtx_meshRotZ;	//��]Z
	D3DXMATRIX mtx_meshScale;	//�g�k

	float fTransX = 0;//�ړ�X
	float fTransY = 0;//�ړ�Y
	float fTransZ = 0;//�ړ�Z

	float fRotX = 0;//��]X
	float fRotY = 0;//��]Y
	float fRotZ = 0;//��]Z

	float fScaleX = 1;//�g��X(���{)
	float fScaleY = 1;//�g��Y(���{)
	float fScaleZ = 1;//�g��Z(���{)

}OBJECT;

static OBJECT object[OBJECT_COUNT];
static D3DXMATRIX g_mtx_meshWorld;

static float g_fTexCoorX = 0;//�e�N�X�`�����WX
static float g_fTexCoorY = 0;//�e�N�X�`�����WY

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 Normal;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX_3D;


//*****************************************************************************
// �O���[�o���ϐ�
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
//  �������֐�
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

	//�e�N�X�`���̓ǂݍ���
	for (nCntTexture = 0; nCntTexture < MESH_MAXIMUM; nCntTexture++)
	{
		if (FAILED(D3DXCreateTextureFromFile(pDevice,//�f�o�C�X
			cTextuerMesh[nCntTexture].FileName,//�t�@�C����
			&g_pTexture[nCntTexture]//�A�h���X�̃A�h���X	
		)))
		{
			MessageBox(NULL, "MESH_TEX_ERROR", "���s", MB_OK);
		}
	};

	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,	//�؂肽���ʁ@���_��*4 �o�C�g
		D3DUSAGE_WRITEONLY,		//�g�p�p�r D3DUSAGE_WRITEONLY = �������݂������Ȃ�
		FVF_VERTEX_3D,			//FVF
		D3DPOOL_MANAGED,		//���_�̊Ǘ����@
		&g_pVertexBuffer,		//�Ǘ��҂̋��ꏊ�̃���
		NULL					//�s��
	))) {
		MessageBox(NULL, "���_�o�b�t�@�̍쐬�Ɏ��s���܂���", "���s", MB_OK);
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_COUNT, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX_COUNT, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);

	//�x�N�g���ǂݎ��
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);//�������ɏ������ݎn��
	memcpy(pV, V, sizeof(VERTEX_3D) * VERTEX_COUNT);//CPU�Ƀ�����������(�R�s�[����)
	g_pVertexBuffer->Unlock();//�������ɏ������ݏI���

							  //�C���f�b�N�X�ǂݎ��
	g_pIndexBuffer->Lock(0, 0, (void**)&LPindex, D3DLOCK_DISCARD);//�������ɏ������ݎn��
	memcpy(LPindex, index, sizeof(WORD) * INDEX_COUNT);//CPU�Ƀ�����������(�R�s�[����)
	g_pIndexBuffer->Unlock();//�������ɏ������ݏI���
}

//==============
//  �I���֐�
//==============
void UninitMesh(void)
{
	for (int nCntTexture = 0; nCntTexture < MESH_MAXIMUM; nCntTexture++)
	{
		if (g_pTexture[nCntTexture] != NULL)
		{
			g_pTexture[nCntTexture]->Release();//�؂肽��������Ԃ�
			g_pTexture[nCntTexture] = NULL;
		}//g_pTexture��NULL����Ȃ�������NULL�ɂ���
	}

	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer->Release();//�؂肽��������Ԃ�
		g_pVertexBuffer = NULL;
	}//g_pVertexBuffer��NULL����Ȃ�������NULL�ɂ���


	if (g_pIndexBuffer != NULL)
	{
		g_pIndexBuffer->Release();//�؂肽��������Ԃ�
		g_pIndexBuffer = NULL;
	}//g_pIndexBuffer��NULL����Ȃ�������NULL�ɂ���
}

//==============
// �@�X�V�֐�
//==============
void UpdateMesh(void)
{
	//���[���h�ϊ��s��
	for (int nCnt = 0; nCnt < OBJECT_COUNT; nCnt++)
	{
		D3DXMatrixIdentity(&object[nCnt].mtx_meshWorld);

		/*��]*/
		D3DXMatrixRotationX(&object[nCnt].mtx_meshRotX, object[nCnt].fRotX);
		D3DXMatrixRotationY(&object[nCnt].mtx_meshRotY, object[nCnt].fRotY);
		D3DXMatrixRotationZ(&object[nCnt].mtx_meshRotZ, object[nCnt].fRotZ);
		D3DXMatrixMultiply(&object[nCnt].mtx_meshRot, &object[nCnt].mtx_meshRotX, &object[nCnt].mtx_meshRotY);
		D3DXMatrixMultiply(&object[nCnt].mtx_meshRot, &object[nCnt].mtx_meshRot, &object[nCnt].mtx_meshRotZ);

		/*�g��*/
		D3DXMatrixScaling(&object[nCnt].mtx_meshScale, object[nCnt].fScaleX, object[nCnt].fScaleY, object[nCnt].fScaleZ);

		/*�ړ�*/
		D3DXMatrixTranslation(&object[nCnt].mtx_meshTrans, object[nCnt].fTransX, object[nCnt].fTransY, object[nCnt].fTransZ);

		/*�g�kx��]*/
		D3DXMatrixMultiply(&object[nCnt].mtx_meshNull, &object[nCnt].mtx_meshScale, &object[nCnt].mtx_meshRot);

		/*(�g�kx��])x�ړ�*/
		D3DXMatrixMultiply(&object[nCnt].mtx_meshWorld, &object[nCnt].mtx_meshNull, &object[nCnt].mtx_meshTrans);

	}//END OF for (int nCnt = 0; nCnt < OBJECT_COUNT; nCnt++)

}//END OF void meshUpdate(void)

 //==============
 // �@�`��֐�
 //==============
void DrawMesh(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	for (int nCnt = 0; nCnt < OBJECT_COUNT; nCnt++)
	{
		pDevice->SetFVF(FVF_VERTEX_3D);
		pDevice->SetRenderState(D3DRS_LIGHTING, false);//���C�e�B���O�I�t

													   //�e��s��̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &object[nCnt].mtx_meshWorld);		//�Z�b�g�������s��̐擪�A�h���X
		pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_3D));
		pDevice->SetIndices(g_pIndexBuffer);

		//�}�e���A���̐ݒ�

		pDevice->SetTexture(0, g_pTexture[1]);//���Ԗڂ̃e�N�X�`�����g�����������ŃZ�b�g����
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VERTEX_COUNT, 0, PRIM_COUNT + INDEX_COUNT - VERTEX_COUNT);

	}//END OF for (int nCnt = 0; nCnt < OBJECT_COUNT; nCnt++)

}//END OF void meshDraw(void)
