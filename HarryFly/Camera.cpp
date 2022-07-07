//=============================================================================
//
// �J���� [Camera.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include"Camera.h"
#include"Main.h"
#include"input.h"
#include "Sixyokika.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//�J�������W
static float eyeX = 0.0f;
static float eyeY = 7.0f;
static float eyeZ = -35.0f;
//���_���W
static float atX = 0.0f;
static float atY = 0.0f;
static float atZ = 0.0f;

//�J����
static D3DXMATRIX g_mtxView;
static D3DXMATRIX g_mtxPro;
static D3DXVECTOR3 g_UP_Vector(0.f, 1.f, 0.f);//��x�N�g��
static D3DXVECTOR3 g_mae_Vector(0.f, 0.f, 1.f);//�O�x�N�g��
static D3DXVECTOR3 g_RIGHT_Vector(1.f, 0.f, 0.f);//�E�x�N�g��
static D3DXVECTOR3 g_eye_pos(eyeX, eyeY, eyeZ);//�J�������W//eye
static D3DXVECTOR3 g_at_pos(atX, atY, atZ);//���_���W//at

static float g_Move_Speed = 0.4f;//���E�㉺�̃J�����ړ��X�s�[�h�̐��l
static float g_okuMove_Speed = 0.4f;//�X�y�[�X�L�[�ɂ��J���������ֈړ�����X�s�[�h�A�b�v�̐��l
static float sabun = 0.0f;//�J�����ƕ��̂̍������v�Z���鐔�l
static float g_sabunMove_Speed = 0.1f;//�J�����̍����Ԃ�ړ��X�s�[�h���A�b�v���鐔�l
static float g_zidouMove_Speed = 0.5f;//�J���������֎����ړ�����X�s�[�h�̐��l






void UpdateCamera(void)
{
	

	//�J����
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	g_mae_Vector = g_at_pos - g_eye_pos;//�O�x�N�g�������_���W�[�J�������W

	D3DXVec3Cross(&g_RIGHT_Vector, &g_mae_Vector, &g_UP_Vector);//D3DXVec3Cross(&�E�x�N�g��,&�O�x�N�g��,&��x�N�g��);
	D3DXVec3Normalize(&g_RIGHT_Vector, &g_RIGHT_Vector);//�E�x�N�g�����m�[�}���C�Y����P�ʉ�

														//////////////////////////////�������ړ�///////////////////////////////////

														//�J����
														//�O���ւ̃J�����̎����ړ�
	D3DXVECTOR3 vec = g_mae_Vector;
	vec.y = 0;
	D3DXVec3Normalize(&vec, &vec);
	g_eye_pos += vec * g_zidouMove_Speed;
	g_at_pos += vec * g_zidouMove_Speed;

	if (GetKeyboardPress(DIK_SPACE)) {//�X�y�[�X�L�[�������Ă���ԉ��ړ����X�s�[�h�A�b�v�I

									  //�J����
		vec = g_mae_Vector;//D3DXVECTOR3 vec = �O�x�N�g��
		vec.y = 0;//vec.y=0;
		D3DXVec3Normalize(&vec, &vec);//D3DXVec3Normalize(&vec,&vec);
		g_eye_pos += vec * g_okuMove_Speed;//�J�������W(eye) += vec * ���x//back�ɐi�ނƂ���-=
		g_at_pos += vec * g_okuMove_Speed;//���_���W(at) += vec * ���x///back�ɐi�ނƂ���-=

		sabun = sabun + 1;//�����𑫂��Ă���
	}
	else
	{
		if (sabun >= 0 && !GetKeyboardPress(DIK_SPACE)) {//�����̐��l�����鎞���X�y�[�X�L�[��������Ă��Ȃ��ꍇ���̓��e���s�I
			vec = g_mae_Vector;
			vec.y = 0;
			D3DXVec3Normalize(&vec, &vec);
			g_eye_pos += vec * g_sabunMove_Speed;
			g_at_pos += vec * g_sabunMove_Speed;

			sabun = sabun - 1;//�����������Ă���
		}
	}

	if (g_eye_pos.z >= 280 && g_at_pos.z >= 350) {//�J�����̉��ړ��͈̔͐���
		g_zidouMove_Speed = 0;
		g_okuMove_Speed = 0;
		g_sabunMove_Speed = 0;
	}

	//////////////////////////////�������ړ�///////////////////////////////////

	///////////////////////////////���E�ړ�&���E��]///////////////////////
	if (GetKeyboardPress(DIK_A))//����A�L�[�����͂��ꂽ��
	{

		//�J����
		D3DXVECTOR3 vec = g_RIGHT_Vector;
		vec.y = 0;
		D3DXVec3Normalize(&vec, &vec);
		g_eye_pos += vec * g_Move_Speed;//back�ꍇ��-=
		g_at_pos += vec * g_Move_Speed;

	}
	else if (GetKeyboardPress(DIK_D))//����D�L�[�����͂��ꂽ��
	{

		//�J����
		D3DXVECTOR3 vec = g_RIGHT_Vector;
		vec.y = 0;
		D3DXVec3Normalize(&vec, &vec);
		g_eye_pos -= vec * g_Move_Speed;//back�ꍇ��-=
		g_at_pos -= vec * g_Move_Speed;

	}


	//�J�����̈ړ��͈͂̌Œ�
	if (g_eye_pos.x <= -16 && g_at_pos.x <= -16)//�J�����̍��ړ��͈͂̌Œ�
	{
		g_eye_pos.x = -16;
		g_at_pos.x = -16;
	}

	if (g_eye_pos.x >= 16 && g_at_pos.x >= 16)//�J�����̉E�ړ��͈͂̌Œ�
	{
		g_eye_pos.x = 16;
		g_at_pos.x = 16;
	}

	///////////////////////////////���E�ړ�&���E��]///////////////////////

	/////////////////////////////////�㉺�ړ�////////////////////////////////////
	if (GetKeyboardPress(DIK_W))//����W�L�[�����͂��ꂽ��
	{

		//�J����
		vec = g_UP_Vector;
		vec.x = 0;
		vec.z = 0;
		D3DXVec3Normalize(&vec, &vec);
		g_eye_pos += vec * g_Move_Speed;//back�ꍇ��-=
		g_at_pos += vec * g_Move_Speed;
	}
	else if (GetKeyboardPress(DIK_S))//����S�L�[�����͂��ꂽ��
	{

		//�J����
		vec = g_UP_Vector;
		vec.x = 0;
		vec.z = 0;
		D3DXVec3Normalize(&vec, &vec);
		g_eye_pos -= vec * g_Move_Speed;//back�ꍇ��-=
		g_at_pos -= vec * g_Move_Speed;

	}


	//�J�����̈ړ��͈͂̌Œ�
	if (g_eye_pos.y <= 7 && g_at_pos.y <= 0)//�J�����̉��ړ��͈͂̌Œ�
	{
		g_eye_pos.y = 7;
		g_at_pos.y = 0;
	}

	if (g_eye_pos.y >= 23 && g_at_pos.y >= 16)//�J�����̏�ړ��͈͂̌Œ�
	{
		g_eye_pos.y = 23;
		g_at_pos.y = 16;
	}

	/////////////////////////////////�㉺�ړ�////////////////////////////////////


	//�J����
	//�r���[�s��
	D3DXMatrixLookAtLH(&g_mtxView, &g_eye_pos, &g_at_pos, &g_UP_Vector);
	//�v���W�F�N�V�����s��
	D3DXMatrixPerspectiveFovLH(&g_mtxPro, D3DX_PI / 3, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);


	//SetTransform���
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxPro);
}

//�J�����������p�֐�
void getcamera(void) {
	g_eye_pos = D3DXVECTOR3(eyeX, eyeY, eyeZ);//�J�������W//eye
	g_at_pos = D3DXVECTOR3(atX, atY, atZ);//���_���W//at
	sabun = 0.0f;//�X�s�[�h�A�b�v�����ۂ̃J���������̏�����
}