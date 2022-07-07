#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Polygon.h"
#include "Main.h"
#include "Cube.h"
#include "Grit.h"

//3D�p���_�f�[�^

//�\���̂̐錾
typedef struct {
	D3DXVECTOR3 pos;
	D3DCOLOR color;
}VERTEX3D;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//FVF�̐錾(�萔)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE)//�ݒ�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//�O���[�o���ϐ��ɍs���p��
//D3DXMATRIX(4�~4)(16�r�b�g����)
static D3DXMATRIX g_mtxWorld;



//==============
// �@�X�V�֐�
//==============
void UpdateGrit(void) {

	//���[���h�ϊ��s��
	//�������Ȃ��s��i�P�ʍs��j
	D3DXMatrixIdentity(&g_mtxWorld);

}

//==============
// �@�`��֐�
//==============
void DrawGrit(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main.h

											//���_�̍쐬
	VERTEX3D v[44];


	v[0].pos = D3DXVECTOR3(-10.0f, 5.0f, 320.0f);
	v[0].color = D3DCOLOR_RGBA(187, 0, 75, 255);

	v[1].pos = D3DXVECTOR3(10.0f, 5.0f, 320.0f);
	v[1].color = D3DCOLOR_RGBA(187, 0, 75, 255);

	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//�e��s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);


	//�`��(�t�@���`���ŁA�ʂP�A���_�z��ւ̃A�h���X�A�T�C�Y�͒��_�\����)
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &v[0], sizeof(VERTEX3D));


}