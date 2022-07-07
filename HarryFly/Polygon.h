#pragma once
//=============================================================================
//  
// �|���S���`��
//
//�@      
//=============================================================================

#ifndef _POLYGON_H_
#define _POLYGON_H_

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE;

//�e�N�X�`���񋓌^(0)
typedef enum
{
	TEX_1 = 0,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,
	TEX_6,
	TEX_7,
	TEX_MAX
}TEXTURE_NUM;

bool InitPolygon(void);//�|���S���̏���������
void UninitPolygon(void);//�|���S���̏I������
void SetPolygonColor(D3DCOLOR color);//�|���S���J���[�̐ݒ�
void DrawPolygon(//�摜��\��
	int texNum,//�g���e�N�X�`��,
	float dx, //�`��ʒuX��
	float dy, //�`��ʒuY��
	int dw, //�e�N�X�`���̕\�����鉡�̒���
	int dh, //�e�N�X�`���̕\������c�̒���
	int tcx, //���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
	int tcy, //���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
	int tcw, //���̉摜�̐؂��肽����
	int tch //���̉摜�̐؂��肽������
);//�|���S���̕`�揈��

#endif // _POLYGON_H_

