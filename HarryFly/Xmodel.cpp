//=============================================================================
//
// X���f�� [Xmodel.cpp]
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

//X���f���\���p�ϐ�
LPD3DXMESH g_pMesh;
DWORD g_nMaterialNum;
LPD3DXBUFFER g_pMaterial = NULL;
static LPD3DXBUFFER   g_pMaterialBuffer = NULL;
static LPD3DXMATERIAL pMaterial;
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//x���f�� 05
static D3DXMATRIX g_mtxWorld05;

//�X�P�[��
static D3DXMATRIX g_mtxWorld05kakudai;//�g��p�ϐ�
static float x05 = 1.0f;//x���g��
static float y05 = 1.0f;//y���g��
static float z05 = 1.0f;//z���g��

						//���[�e�[�V����
static D3DXMATRIX g_mtxWorld05Zrot;//X���f����Z��]�p�ϐ�
static float Zkaitenspeed = 0.0f;//Z��]�X�s�[�h�p���l
static float Zkaitenidou = 0.0f;//Z��]�ړ��p���l

static D3DXMATRIX g_mtxWorld05Xrot;//X���f����X��]�p�ϐ�
static float Xkaitenspeed = 0.0f;//X��]�X�s�[�h�p���l
static float Xkaitenidou = 0.0f;//X��]�ړ��p���l

								//�g�����X���[�V����
static D3DXMATRIX g_mtxWorld05move;//�ړ��p�ϐ�
static float okuidou = 0.0f;//���ړ��p���l//X���f����Z���W
static float zmovespeed = 0.0f;//X���f����z�X�s�[�h

static float yokoidou = 0.0f;//���ړ��p���l//X���f����X���W
static float xmovespeed = 0.0f;//X���f����x�X�s�[�h

static float tateidou = 0.5f;//�c�ړ��p���l//X���f����Y���W
static float ymovespeed = 0.0f;//X���f����y�X�s�[�h






							   //==============
							   //  �������֐�
							   //==============
void InitXmodel(void)
{

	//������
	LPD3DXBUFFER  pAdjacencyBuffer;

	HRESULT hr;

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	hr = D3DXLoadMeshFromX("./recource/UAV8.x",		//X���f���̃A�h���X
		D3DXMESH_SYSTEMMEM, pDevice,
		&pAdjacencyBuffer, &g_pMaterialBuffer, NULL,
		&g_nMaterialNum, &g_pMesh);


	if (FAILED(hr))
	{
		MessageBox(NULL, "Xmodel�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK);
	}

	//�}�e���A���̎擾
	pMaterial = (LPD3DXMATERIAL)g_pMaterialBuffer->GetBufferPointer();

	hr = g_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)pAdjacencyBuffer->GetBufferPointer(),
		NULL, NULL, NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "���b�V���̍œK���Ɏ��s���܂���", "�G���[", MB_OK);
	}


}

//==============
//  �I���֐�
//==============
void UninitXmodel(void)
{
	g_pMaterialBuffer->Release();

	
	g_pMesh = NULL;//LPD3DXMESH��NULL�Ń������J��
	g_nMaterialNum = 0;//DWORD��0�Ń������J��
	g_pMaterialBuffer = NULL;//LPD3DXBUFFER��NULL�Ń������J��
	g_pMaterial = NULL;//LPD3DXBUFFER��NULL�Ń������J��
	Zkaitenspeed = 0.0f;//float��0.0f�Ń������J��
	Zkaitenidou = 0.0f;//float��0.0f�Ń������J��
	Xkaitenspeed = 0.0f;//float��0.0f�Ń������J��
	Xkaitenidou = 0.0f;//float��0.0f�Ń������J��
	okuidou = 0.0f;//float��0.0f�Ń������J��
	zmovespeed = 0;//float��0.0f�Ń������J��
	yokoidou = 0.0f;//float��0.0f�Ń������J��
	xmovespeed = 0.0f;//float��0.0f�Ń������J��
	tateidou = 0.0f;//float��0.0f�Ń������J��
	ymovespeed = 0;//float��0.0f�Ń������J��
				   //bool��false�Ń������J��
	
}

//==============
// �@�X�V�֐�
//==============
void UpdateXmodel(void)
{
	//////////////////////////////�������ړ�///////////////////////////////////
	//������������ꍇ�̓J������������Ȃ��Ƃ����Ȃ��I
	zmovespeed += 0.5f;//X���f���̉��ɐi�ރX�s�[�h

	if (GetKeyboardPress(DIK_SPACE)) {//�X�y�[�X�L�[�������Ă���ԉ��ړ����X�s�[�h�A�b�v�I
		zmovespeed = zmovespeed + 0.5f;
	}

	if (okuidou >= 330) {//���ړ��͈̔͐���
		zmovespeed = 0;
		getnum(2);//�Q�[���N���A�[�Ɉړ�//main.h�ɐ������s���A���̌�main.cpp�ɍs��
	}

	

	okuidou = okuidou + zmovespeed;//���ړ��v�Z
	zmovespeed = 0;//���ړ��̃X�s�[�h��������
				   //////////////////////////////�������ړ�///////////////////////////////////

				   ///////////////////////////////���E�ړ�&���E��]///////////////////////
				   //������������ꍇ�̓J������������Ȃ��Ƃ����Ȃ��I
	if (GetKeyboardPress(DIK_A))//����A�L�[�����͂��ꂽ��
	{
		xmovespeed = xmovespeed - 0.4f;//���ړ��X�s�[�h
		Zkaitenspeed = Zkaitenspeed + 0.016f;

	}
	else if (GetKeyboardPress(DIK_D))//����D�L�[�����͂��ꂽ��
	{
		xmovespeed = xmovespeed + 0.4f;//���ړ��X�s�[�h
		Zkaitenspeed = Zkaitenspeed - 0.016f;

	}
	else
	{
		//Xmodel�̉�]�����Ƃɖ߂�����//�䗦�� �ړ�0.1 : ��]0.004 ���x�X�g�I
		if (Zkaitenidou >= 0.016) {
			Zkaitenidou = Zkaitenidou - 0.016f;
		}
		else if (Zkaitenidou <= -0.016) {
			Zkaitenidou = Zkaitenidou + 0.016f;
		}
	}

	//�ړ��ł���͈͂̌Œ�//������������ꍇ�̓J������������Ȃ��Ƃ����Ȃ��I
	if (yokoidou <= -16)//�������ړ��ł���͈͂̐��l��-16�ɂȂ�����
	{
		yokoidou = -16;//���Ɉړ��ł���͈͂̌Œ�
		Zkaitenspeed = 0;//���ɉ�]�ł���͈͂̌Œ�
	}
	if (yokoidou >= 16)//�������ړ��ł���͈͂̐��l��1�ɂȂ�����
	{
		yokoidou = 16;//���Ɉړ��ł���͈͂̌Œ�
		Zkaitenspeed = 0;//���ɉ�]�ł���͈͂̌Œ�
	}


	Zkaitenidou = Zkaitenidou + Zkaitenspeed;//��]�v�Z
	Zkaitenspeed = 0;//����]�X�s�[�h���l�̏�����

	yokoidou = yokoidou + xmovespeed;//���ړ��v�Z
	xmovespeed = 0;//���ړ��X�s�[�h���l�̏�����


				   ///////////////////////////////���E�ړ�&���E��]///////////////////////

				   /////////////////////////////////�㉺�ړ�////////////////////////////////////
				   //������������ꍇ�̓J������������Ȃ��Ƃ����Ȃ��I
	if (GetKeyboardPress(DIK_W))//����W�L�[�����͂��ꂽ��
	{
		ymovespeed = ymovespeed + 0.4f;//�c�ړ��X�s�[�h
		Xkaitenspeed = Xkaitenspeed - 0.016f;
	}
	else if (GetKeyboardPress(DIK_S))//����S�L�[�����͂��ꂽ��
	{
		ymovespeed = ymovespeed - 0.4f;//�c�ړ��X�s�[�h
		Xkaitenspeed = Xkaitenspeed + 0.016f;
	}
	else
	{
		//Xmodel�̉�]�����Ƃɖ߂�����//�䗦�� �ړ�0.1 : ��]0.004 ���x�X�g�I
		if (Xkaitenidou >= 0.016) {
			Xkaitenidou = Xkaitenidou - 0.016f;
		}
		else if (Xkaitenidou <= -0.016) {
			Xkaitenidou = Xkaitenidou + 0.016f;
		}
	}

	//�ړ��ł���͈͂̌Œ�//������������ꍇ�̓J������������Ȃ��Ƃ����Ȃ��I
	if (tateidou <= 0)//�����c�ړ��ł���͈͂̐��l��-1�ɂȂ�����
	{
		tateidou = 0;//�c�Ɉړ��ł���͈͂̌Œ�
		Xkaitenspeed = 0;
	}
	if (tateidou >= 16)//�����c�ړ��ł���͈͂̐��l��20�ɂȂ�����
	{
		tateidou = 16;//�c�Ɉړ��ł���͈͂̌Œ�
		Xkaitenspeed = 0;
	}

	Xkaitenidou = Xkaitenidou + Xkaitenspeed;//��]�v�Z
	Xkaitenspeed = 0;//�c��]�X�s�[�h���l�̏�����

	tateidou = tateidou + ymovespeed;//�c�ړ��v�Z
	ymovespeed = 0;//�c�ړ��X�s�[�h���l�̏�����



				   /////////////////////////////////�㉺�ړ�////////////////////////////////////

	atariidou(yokoidou, tateidou, okuidou);//atarihantei.h�֐����𑗂�/�X�V�����v���C���[�̍��W�������蔻��ɑ���

										   //SRT(�X�P�[�������[�e�[�V�������g�����X���[�V����)�̏��Ԃō������Ȃ��Ƃ����Ȃ�
	D3DXMatrixIdentity(&g_mtxWorld05);//���������邽�߂̏�����

									  //x���f�� 05
	D3DXMatrixScaling(&g_mtxWorld05kakudai, x05, y05, z05);//X���f���̊g��֐�
	D3DXMatrixMultiply(&g_mtxWorld05, &g_mtxWorld05kakudai, &g_mtxWorld05);//����

	D3DXMatrixRotationZ(&g_mtxWorld05Zrot, Zkaitenidou);//X���f����Z��]�֐�
	D3DXMatrixMultiply(&g_mtxWorld05, &g_mtxWorld05kakudai, &g_mtxWorld05Zrot);//����

	D3DXMatrixRotationX(&g_mtxWorld05Xrot, Xkaitenidou);//X���f����X��]�֐�
	D3DXMatrixMultiply(&g_mtxWorld05, &g_mtxWorld05, &g_mtxWorld05Xrot);//����

	D3DXMatrixTranslation(&g_mtxWorld05move, yokoidou, tateidou, okuidou);//X���f���̕��s�ړ��֐�
	D3DXMatrixMultiply(&g_mtxWorld05, &g_mtxWorld05, &g_mtxWorld05move);//����

}

//==============
// �@�`��֐�
//==============
void DrawXmodel(void)
{

	g_nMaterialNum;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

											//x���f�� 05
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld05);

	for (unsigned int i = 0; i < g_nMaterialNum; i++)
	{
		pMaterial[i].MatD3D.Ambient.r = 0.3f;
		pMaterial[i].MatD3D.Ambient.g = 0.3f;
		pMaterial[i].MatD3D.Ambient.b = 0.3f;
		pMaterial[i].MatD3D.Ambient.a = 1.0f;
	
		pDevice->SetMaterial(&pMaterial[i].MatD3D);

		pDevice->SetTexture(0, NULL);		//�e�N�X�`�����g���ꍇ��NULL��g_pTextures[i]�ɕύX

		g_pMesh->DrawSubset(i);
	}

}

//X���f���̈ړ��̏�����
void getiou(float yokoidounum, float tateidounum, float okuidounum) {
	yokoidou = yokoidounum;
	tateidou = tateidounum;
	okuidou = okuidounum;
	
}