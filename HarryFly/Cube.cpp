#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Polygon.h"
#include "Main.h"
#include "Cube.h"
#include "Atarihantei.h"

//3D�p���_�f�[�^

//�\���̂̐錾
typedef struct {
	//���W
	D3DXVECTOR3 pos;
	//�@��
	D3DXVECTOR3 normal;
	//�J���[
	D3DCOLOR color;
	//�e�N�X�`��
	D3DXVECTOR2 texcoord;
}VERTEX3D;

//FVF�̐錾(�萔)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL )//�ݒ�



//�O���[�o���ϐ��ɍs���p��
//D3DXMATRIX(4�~4)(16�r�b�g����)
static float CUBE_HABA = 5.0f;//�L���[�u�̔��a
							  //�L���[�u01
static D3DXMATRIX g_mtxWorld01;
static D3DXMATRIX g_mtxWorld01kakudai;
static D3DXMATRIX g_mtxWorld01move;
//�L���[�u1
static float CUBE_1_X = 1.0f;//�L���[�u��X���W
static float CUBE_1_Y = 10.0f;//�L���[�u��Y���W
static float CUBE_1_Z = 40.0f;//�L���[�u��Z���W
							  //�L���[�u02
static D3DXMATRIX g_mtxWorld02;
static D3DXMATRIX g_mtxWorld02kakudai;
static D3DXMATRIX g_mtxWorld02move;
//�L���[�u2
static float CUBE_2_X = 8.0f;//�L���[�u��X���W
static float CUBE_2_Y = 2.0f;//�L���[�u��Y���W
static float CUBE_2_Z = 80.0f;//�L���[�u��Z���W
							  //�L���[�u03
static D3DXMATRIX g_mtxWorld03;
static D3DXMATRIX g_mtxWorld03move;
static D3DXMATRIX g_mtxWorld03kakudai;
//�L���[�u3
static float CUBE_3_X = -2.0f;//�L���[�u��X���W
static float CUBE_3_Y = 6.0f;//�L���[�u��Y���W
static float CUBE_3_Z = 120.0f;//�L���[�u��Z���W
							   //�L���[�u04
static D3DXMATRIX g_mtxWorld04;
static D3DXMATRIX g_mtxWorld04move;
static D3DXMATRIX g_mtxWorld04kakudai;
//�L���[�u4
static float CUBE_4_X = 10.0f;//�L���[�u��X���W
static float CUBE_4_Y = 15.0f;//�L���[�u��Y���W
static float CUBE_4_Z = 160.0f;//�L���[�u��Z���W
							   //�L���[�u05
static D3DXMATRIX g_mtxWorld05;
static D3DXMATRIX g_mtxWorld05move;
static D3DXMATRIX g_mtxWorld05kakudai;
//�L���[�u5
static float CUBE_5_X = -10.0f;//�L���[�u��X���W
static float CUBE_5_Y = 0.0f;//�L���[�u��Y���W
static float CUBE_5_Z = 200.0f;//�L���[�u��Z���W
							   //�L���[�u06
static D3DXMATRIX g_mtxWorld06;
static D3DXMATRIX g_mtxWorld06move;
static D3DXMATRIX g_mtxWorld06kakudai;
//�L���[�u6
static float CUBE_6_X = -2.0f;//�L���[�u��X���W
static float CUBE_6_Y = 6.0f;//�L���[�u��Y���W
static float CUBE_6_Z = 240.0f;//�L���[�u��Z���W

							   //�e�N�X�`��1
static const char* g_aTextureFileName[] = { "recource/texture/zimen.jpg", };
#define ARRAYCOUNT(x) sizeof(x) / sizeof(x[0])
static const int TEXTURE_FILE_COUNT = ARRAYCOUNT(g_aTextureFileName);
static LPDIRECT3DTEXTURE9 g_pTexture[TEXTURE_FILE_COUNT];//�t�@�C���̃J�E���g��


														 //�|���S��3D�̏���������
void InitPolygon3D(void) {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main.h

											//�e�N�X�`��2
											//�G���[�`�F�b�N
	HRESULT hr;
	for (int i = 0; i<2; i++)
	{
		hr = D3DXCreateTextureFromFile(pDevice, "recource/texture/zimen.jpg", &g_pTexture[i]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "�e�N�X�`����������Ȃ�", "�G���[", MB_OK);
		}
	}


}
//�|���S��3D�̏I������
void UninitPolygon3D(void) {
	//�e�N�X�`��3
	for (int i = 0; i<TEXTURE_FILE_COUNT; i++)
	{
		if (g_pTexture[i] != NULL)
		{
			g_pTexture[i]->Release();
			g_pTexture[i] = NULL;
		}
	}

	CUBE_HABA = 0.0f;//�L���[�u�̔��a

	CUBE_1_X = 0.0f;//�L���[�u��X���W
	CUBE_1_Y = 0.0f;//�L���[�u��Y���W
	CUBE_1_Z = 0.0f;//�L���[�u��Z���W

	CUBE_2_X = 0.0f;//�L���[�u��X���W
	CUBE_2_Y = 0.0f;//�L���[�u��Y���W
	CUBE_2_Z = 0.0f;//�L���[�u��Z���W

	CUBE_3_X = 0.0f;//�L���[�u��X���W
	CUBE_3_Y = 0.0f;//�L���[�u��Y���W
	CUBE_3_Z = 0.0f;//�L���[�u��Z���W

	CUBE_4_X = 0.0f;//�L���[�u��X���W
	CUBE_4_Y = 0.0f;//�L���[�u��Y���W
	CUBE_4_Z = 0.0f;//�L���[�u��Z���W

	CUBE_5_X = 0.0f;//�L���[�u��X���W
	CUBE_5_Y = 0.0f;//�L���[�u��Y���W
	CUBE_5_Z = 0.0f;//�L���[�u��Z���W
	
	CUBE_6_X = 0.0f;//�L���[�u��X���W
	CUBE_6_Y = 0.0f;//�L���[�u��Y���W
	CUBE_6_Z = 0.0f;//�L���[�u��Z���W

}
//�|���S��3D�̍X�V����
void UpdatePolygon3D(void) {

	//���[���h�ϊ��s��//SRT	�X�P�[�������[�e�[�V�������g�����X���[�V����

	//�L���[�u01
	//�摜�����̍��܂ōs�����玟�͈��̉E�Ɉړ����܂����Ɉړ�������(2)
	static float hidarigezi1 = 0.0f;
	static float migigezi1 = 0.0f;
	static float idouspeed1 = 0.5;

	if (hidarigezi1 <= 600 && hidarigezi1 >= 100)//hidari�̐��l��600�`100�̊ԂȂ�ړ� 
	{
		hidarigezi1 = hidarigezi1 - 5;//hidari�̐��l(�Q�[�W)�����炷
		CUBE_1_X = CUBE_1_X + idouspeed1;//�ړ�
	}
	else if (hidarigezi1 = 100 && migigezi1 <= 600 && migigezi1 >= 100)//migi�̐��l��600�`100����hidari�̐��l��100�Ȃ�ړ�
	{
		migigezi1 = migigezi1 - 5;//migi�̐��l(�Q�[�W)�����炷
		CUBE_1_X = CUBE_1_X - idouspeed1;//�ړ�
	}
	else if (hidarigezi1 <= 100 && migigezi1 <= 100)//hidari�̐��l��100����migi�̐��l��100�Ȃ�hidari,migi�̐��l�̏����� 
	{
		hidarigezi1 = 600;//hidari�̐��l�����ʂ�ɂ���
		migigezi1 = 600;//migi�̐��l�����ƒʂ�ɂ���
	}

	ataricube1(CUBE_1_X, CUBE_1_Y, CUBE_1_Z);//�X�V�����L���[�u�̍��W�������蔻��ɑ���

	D3DXMatrixIdentity(&g_mtxWorld01);//���������邽�߂̏�����
	D3DXMatrixScaling(&g_mtxWorld01kakudai, CUBE_HABA, CUBE_HABA, CUBE_HABA);//���f���̊g��֐�
	D3DXMatrixMultiply(&g_mtxWorld01, &g_mtxWorld01, &g_mtxWorld01kakudai);//����
	D3DXMatrixTranslation(&g_mtxWorld01move, CUBE_1_X, CUBE_1_Y, CUBE_1_Z);//�L���[�u�̕��s�ړ��֐�
	D3DXMatrixMultiply(&g_mtxWorld01, &g_mtxWorld01, &g_mtxWorld01move);//����

																		//�L���[�u02
																		//�摜�����̍��܂ōs�����玟�͈��̉E�Ɉړ����܂����Ɉړ�������(2)
	static float hidarigezi2 = 0.0f;
	static float migigezi2 = 0.0f;
	static float idouspeed2 = 0.5;

	if (hidarigezi2 <= 600 && hidarigezi2 >= 100)//hidari�̐��l��600�`100�̊ԂȂ�摜���ړ� 
	{
		hidarigezi2 = hidarigezi2 - 5;//hidari�̐��l(�Q�[�W)�����炷
		CUBE_2_Y = CUBE_2_Y + idouspeed2;//�ړ�
	}
	else if (hidarigezi2 = 100 && migigezi2 <= 600 && migigezi2 >= 100)//migi�̐��l��600�`100����hidari�̐��l��100�Ȃ�ړ�
	{
		migigezi2 = migigezi2 - 5;//migi�̐��l(�Q�[�W)�����炷
		CUBE_2_Y = CUBE_2_Y - idouspeed2;//�ړ�
	}
	else if (hidarigezi2 <= 100 && migigezi2 <= 100)//hidari�̐��l��100����migi�̐��l��100�Ȃ�hidari,migi�̐��l�̏����� 
	{
		hidarigezi2 = 600;//hidari�̐��l�����ʂ�ɂ���
		migigezi2 = 600;//migi�̐��l�����ƒʂ�ɂ���
	}

	ataricube2(CUBE_2_X, CUBE_2_Y, CUBE_2_Z);//�X�V�����L���[�u�̍��W�������蔻��ɑ���

	D3DXMatrixIdentity(&g_mtxWorld02);//���������邽�߂̏�����
	D3DXMatrixScaling(&g_mtxWorld02kakudai, CUBE_HABA, CUBE_HABA, CUBE_HABA);//���f���̊g��֐�
	D3DXMatrixMultiply(&g_mtxWorld02, &g_mtxWorld02, &g_mtxWorld02kakudai);//����
	D3DXMatrixTranslation(&g_mtxWorld02move, CUBE_2_X, CUBE_2_Y, CUBE_2_Z);//�L���[�u�̕��s�ړ��֐�
	D3DXMatrixMultiply(&g_mtxWorld02, &g_mtxWorld02, &g_mtxWorld02move);//����

																		//�L���[�u03
																		//�摜�����̍��܂ōs�����玟�͈��̉E�Ɉړ����܂����Ɉړ�������(2)
	static float hidarigezi3 = 0.0f;
	static float migigezi3 = 0.0f;
	static float idouspeed3 = 0.5;

	if (hidarigezi3 <= 600 && hidarigezi3 >= 100)//hidari�̐��l��600�`100�̊ԂȂ�ړ� 
	{
		hidarigezi3 = hidarigezi3 - 5;//hidari�̐��l(�Q�[�W)�����炷
		CUBE_3_Z = CUBE_3_Z + idouspeed3;//�ړ�
	}
	else if (hidarigezi3 = 100 && migigezi3 <= 600 && migigezi3 >= 100)//migi�̐��l��600�`100����hidari�̐��l��100�Ȃ�ړ�
	{
		migigezi3 = migigezi3 - 5;//migi�̐��l(�Q�[�W)�����炷
		CUBE_3_Z = CUBE_3_Z - idouspeed3;//�ړ�
	}
	else if (hidarigezi3 <= 100 && migigezi3 <= 100)//hidari�̐��l��100����migi�̐��l��100�Ȃ�hidari,migi�̐��l�̏����� 
	{
		hidarigezi3 = 600;//hidari�̐��l�����ʂ�ɂ���
		migigezi3 = 600;//migi�̐��l�����ƒʂ�ɂ���
	}

	ataricube3(CUBE_3_X, CUBE_3_Y, CUBE_3_Z);//�X�V�����L���[�u�̍��W�������蔻��ɑ���

	D3DXMatrixIdentity(&g_mtxWorld03);//���������邽�߂̏�����
	D3DXMatrixScaling(&g_mtxWorld03kakudai, CUBE_HABA, CUBE_HABA, CUBE_HABA);//���f���̊g��֐�
	D3DXMatrixMultiply(&g_mtxWorld03, &g_mtxWorld03, &g_mtxWorld03kakudai);//����
	D3DXMatrixTranslation(&g_mtxWorld03move, CUBE_3_X, CUBE_3_Y, CUBE_3_Z);//�L���[�u�̕��s�ړ�
	D3DXMatrixMultiply(&g_mtxWorld03, &g_mtxWorld03, &g_mtxWorld03move);//����

																		//�L���[�u04
																		//�摜�����̍��܂ōs�����玟�͈��̉E�Ɉړ����܂����Ɉړ�������(2)
	static float hidarigezi4 = 0.0f;
	static float migigezi4 = 0.0f;
	static float idouspeed4 = 0.5;

	if (hidarigezi4 <= 600 && hidarigezi4 >= 100)//hidari�̐��l��600�`100�̊ԂȂ�摜���ړ� 
	{
		hidarigezi4 = hidarigezi4 - 5;//hidari�̐��l(�Q�[�W)�����炷
		CUBE_4_X = CUBE_4_X - idouspeed4;//�ړ�
		CUBE_4_Y = CUBE_4_Y - idouspeed4;//�ړ�
	}
	else if (hidarigezi4 = 100 && migigezi4 <= 600 && migigezi4 >= 100)//migi�̐��l��600�`100����hidari�̐��l��100�Ȃ�ړ�
	{
		migigezi4 = migigezi4 - 5;//migi�̐��l(�Q�[�W)�����炷
		CUBE_4_X = CUBE_4_X + idouspeed4;//�ړ�
		CUBE_4_Y = CUBE_4_Y + idouspeed4;//�ړ�
	}
	else if (hidarigezi4 <= 100 && migigezi4 <= 100)//hidari�̐��l��100����migi�̐��l��100�Ȃ�hidari,migi�̐��l�̏����� 
	{
		hidarigezi4 = 600;//hidari�̐��l�����ʂ�ɂ���
		migigezi4 = 600;//migi�̐��l�����ƒʂ�ɂ���
	}

	ataricube4(CUBE_4_X, CUBE_4_Y, CUBE_4_Z);//�X�V�����L���[�u�̍��W�������蔻��ɑ���

	D3DXMatrixIdentity(&g_mtxWorld04);//���������邽�߂̏�����
	D3DXMatrixScaling(&g_mtxWorld04kakudai, CUBE_HABA, CUBE_HABA, CUBE_HABA);//���f���̊g��֐�
	D3DXMatrixMultiply(&g_mtxWorld04, &g_mtxWorld04, &g_mtxWorld04kakudai);//����
	D3DXMatrixTranslation(&g_mtxWorld04move, CUBE_4_X, CUBE_4_Y, CUBE_4_Z);//�L���[�u�̕��s�ړ�
	D3DXMatrixMultiply(&g_mtxWorld04, &g_mtxWorld04, &g_mtxWorld04move);//����

																		//�L���[�u05
																		//�摜�����̍��܂ōs�����玟�͈��̉E�Ɉړ����܂����Ɉړ�������(2)
	static float hidarigezi5 = 0.0f;
	static float migigezi5 = 0.0f;
	static float idouspeed5 = 0.5;

	if (hidarigezi5 <= 600 && hidarigezi5 >= 100)//hidari�̐��l��600�`100�̊ԂȂ�摜���ړ� 
	{
		hidarigezi5 = hidarigezi5 - 5;//hidari�̐��l(�Q�[�W)�����炷
		CUBE_5_X = CUBE_5_X + idouspeed5;//�ړ�
		CUBE_5_Y = CUBE_5_Y + idouspeed5;//�ړ�
	}
	else if (hidarigezi5 = 100 && migigezi5 <= 600 && migigezi5 >= 100)//migi�̐��l��600�`100����hidari�̐��l��100�Ȃ�ړ�
	{
		migigezi5 = migigezi5 - 5;//migi�̐��l(�Q�[�W)�����炷
		CUBE_5_X = CUBE_5_X - idouspeed5;//�ړ�
		CUBE_5_Y = CUBE_5_Y - idouspeed5;//�ړ�
	}
	else if (hidarigezi5 <= 100 && migigezi5 <= 100)//hidari�̐��l��100����migi�̐��l��100�Ȃ�hidari,migi�̐��l�̏����� 
	{
		hidarigezi5 = 600;//hidari�̐��l�����ʂ�ɂ���
		migigezi5 = 600;//migi�̐��l�����ƒʂ�ɂ���
	}

	ataricube5(CUBE_5_X, CUBE_5_Y, CUBE_5_Z);//�X�V�����L���[�u�̍��W�������蔻��ɑ���

	D3DXMatrixIdentity(&g_mtxWorld05);//���������邽�߂̏�����
	D3DXMatrixScaling(&g_mtxWorld05kakudai, CUBE_HABA, CUBE_HABA, CUBE_HABA);//���f���̊g��֐�
	D3DXMatrixMultiply(&g_mtxWorld05, &g_mtxWorld05, &g_mtxWorld05kakudai);//����
	D3DXMatrixTranslation(&g_mtxWorld05move, CUBE_5_X, CUBE_5_Y, CUBE_5_Z);//�L���[�u�̕��s�ړ�
	D3DXMatrixMultiply(&g_mtxWorld05, &g_mtxWorld05, &g_mtxWorld05move);//����

																		//�L���[�u06
																		//�摜�����̍��܂ōs�����玟�͈��̉E�Ɉړ����܂����Ɉړ�������(2)
	static float hidarigezi6 = 0.0f;
	static float migigezi6 = 0.0f;
	static float idouspeed6 = 0.5;

	if (hidarigezi6 <= 600 && hidarigezi6 >= 100)//hidari�̐��l��600�`100�̊ԂȂ�ړ� 
	{
		hidarigezi6 = hidarigezi6 - 5;//hidari�̐��l(�Q�[�W)�����炷
		CUBE_6_X = CUBE_6_X + idouspeed6;//�ړ�
	}
	else if (hidarigezi6 = 100 && migigezi6 <= 600 && migigezi6 >= 100)//migi�̐��l��600�`100����hidari�̐��l��100�Ȃ�ړ�
	{
		migigezi6 = migigezi6 - 5;//migi�̐��l(�Q�[�W)�����炷
		CUBE_6_X = CUBE_6_X - idouspeed6;//�ړ�
	}
	else if (hidarigezi6 <= 100 && migigezi6 <= 100)//hidari�̐��l��100����migi�̐��l��100�Ȃ�hidari,migi�̐��l�̏����� 
	{
		hidarigezi6 = 600;//hidari�̐��l�����ʂ�ɂ���
		migigezi6 = 600;//migi�̐��l�����ƒʂ�ɂ���
	}

	ataricube6(CUBE_6_X, CUBE_6_Y, CUBE_6_Z);//�X�V�����L���[�u�̍��W�������蔻��ɑ���

	D3DXMatrixIdentity(&g_mtxWorld06);//���������邽�߂̏�����
	D3DXMatrixScaling(&g_mtxWorld06kakudai, CUBE_HABA, CUBE_HABA, CUBE_HABA);//���f���̊g��֐�
	D3DXMatrixMultiply(&g_mtxWorld06, &g_mtxWorld06, &g_mtxWorld06kakudai);//����
	D3DXMatrixTranslation(&g_mtxWorld06move, CUBE_6_X, CUBE_6_Y, CUBE_6_Z);//�L���[�u�̕��s�ړ��֐�
	D3DXMatrixMultiply(&g_mtxWorld06, &g_mtxWorld06, &g_mtxWorld06move);//����



}
//3D�摜��\��
void DrawPolygon3D(void) {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

											//�e�N�X�`��4
	pDevice->SetTexture(0, g_pTexture[0]);

	//���_�̍쐬
	VERTEX3D v[] = {
		//��O
		//���W								//�@��						//�J���[							//�e�N�X�`��
		{ D3DXVECTOR3(-0.5f,  0.5f, -0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f), D3DCOLOR_RGBA(255,   255, 255, 255),D3DXVECTOR2(0 , 0) },//����[0]
		{ D3DXVECTOR3(0.5f,  0.5f, -0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f), D3DCOLOR_RGBA(255,   255, 255, 255),D3DXVECTOR2(0.25 , 0) },//�E��[1]
		{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f), D3DCOLOR_RGBA(255,   255, 255, 255),D3DXVECTOR2(0 , 0.25) },//����[2]

		{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f), D3DCOLOR_RGBA(255,   255, 255, 255),D3DXVECTOR2(0 , 0.25) },//����[2]
		{ D3DXVECTOR3(0.5f,  0.5f, -0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f), D3DCOLOR_RGBA(255,   255, 255, 255),D3DXVECTOR2(0.25 , 0) },//�E��[1]
		{ D3DXVECTOR3(0.5f, -0.5f, -0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f), D3DCOLOR_RGBA(255,   255, 255, 255),D3DXVECTOR2(0.25 , 0.25) },//�E��[3]



																																	   //��
		{ D3DXVECTOR3(0.5f,  0.5f, 0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25 , 0) },//����[4]
		{ D3DXVECTOR3(-0.5f,  0.5f, 0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5 , 0) },//�E��[5]
		{ D3DXVECTOR3(0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25 , 0.25) },//����[6]

		{ D3DXVECTOR3(0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25 , 0.25) },//����[6]
		{ D3DXVECTOR3(-0.5f,  0.5f, 0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5 , 0) },//�E��[5]
		{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5 , 0.25) },//�E��[7]

																																	 //�E
		{ D3DXVECTOR3(0.5f,  0.5f, -0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5,0) },//�E��O[1]
		{ D3DXVECTOR3(0.5f,  0.5f,  0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.75,0) },//�E���[4]
		{ D3DXVECTOR3(0.5f, -0.5f, -0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5,0.25) },//�E���O[3]

		{ D3DXVECTOR3(0.5f, -0.5f, -0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5,0.25) },//�E���O[3]
		{ D3DXVECTOR3(0.5f,  0.5f,  0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.75,0) },//�E���[4]
		{ D3DXVECTOR3(0.5f, -0.5f,  0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.75,0.25) },//�E����[6]

																																	//��
		{ D3DXVECTOR3(-0.5f,  0.5f,  0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.75,0) },//�����[5]
		{ D3DXVECTOR3(-0.5f,  0.5f, -0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(1,0) },//[0]
		{ D3DXVECTOR3(-0.5f, -0.5f,  0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.75,0.25) },//[7]

		{ D3DXVECTOR3(-0.5f, -0.5f,  0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.75,0.25) },//[7]
		{ D3DXVECTOR3(-0.5f,  0.5f, -0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(1,0) },//[0]
		{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(1,0.25) },//[2]

																																   //��
		{ D3DXVECTOR3(-0.5f,  0.5f,  0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0,0.25) },//[5]
		{ D3DXVECTOR3(0.5f,  0.5f,  0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25,0.25) },//[4]
		{ D3DXVECTOR3(-0.5f,  0.5f, -0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0,0.5) },//[0]

		{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0,0.5) },//[0]
		{ D3DXVECTOR3(0.5f,  0.5f, 0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25,0.25) },//[4]
		{ D3DXVECTOR3(0.5f, 0.5f, -0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25,0.5) },//[1]

																																   //��
		{ D3DXVECTOR3(-0.5f,  -0.5f, -0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25,0.25) },//[2]
		{ D3DXVECTOR3(0.5f,  -0.5f, -0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5,0.25) },//[3]
		{ D3DXVECTOR3(-0.5f,  -0.5f,  0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25,0.5) },//[7]

		{ D3DXVECTOR3(-0.5f, -0.5f,  0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.25,0.5) },//[7]
		{ D3DXVECTOR3(0.5f, -0.5f, -0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5,0.25) },//[3]
		{ D3DXVECTOR3(0.5f, -0.5f,  0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f), D3DCOLOR_RGBA(255, 255,   255, 255),D3DXVECTOR2(0.5,0.5) },//[6]
	};

	WORD index[] = {
		0,1,2,
		2,1,3,
		4,5,6,
		6,5,7,
		1,4,3,
		3,4,6,
		5,0,7,
		7,0,2,
		5,4,0,
		0,4,1,
		2,3,7,
		7,3,6
	};

	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);



	//�`��(�t�@���`���ŁA�ʂP�A���_�z��ւ̃A�h���X�A�T�C�Y�͒��_�\����)
	//�L���[�u01
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld01);
	//�`��(�t�@���`����,�ʂP��,���_�z��ւ̃A�h���X,�T�C�Y�͒��_�\����)
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &v[0], sizeof(VERTEX3D));

	//�L���[�u02
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld02);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &v[0], sizeof(VERTEX3D));

	//�L���[�u03
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld03);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &v[0], sizeof(VERTEX3D));

	//�L���[�u04
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld04);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &v[0], sizeof(VERTEX3D));

	//�L���[�u05
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld05);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &v[0], sizeof(VERTEX3D));

	//�L���[�u06
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld06);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &v[0], sizeof(VERTEX3D));
}