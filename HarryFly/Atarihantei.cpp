//=======================================================================================
//						�����蔻��`��
//						2017.06.05
//=======================================================================================
#include <math.h>
#include "Atarihantei.h"
#include "Main.h"
#include "Cube.h"
#include "Xmodel.h"
#include "Sixyokika.h"
#include "Bonbe.h"
#include "Coin.h"


//Xmodel
static float atariyokoidou = 0.0f;//�����蔻��p���ړ��̔�
static float ataritateidou = 0.0f;//�����蔻��p�c�ړ��̔�
static float atariokuidou = 0.0f;//�����蔻��p���ړ��̔�

//�L���[�u///////////////////////////////////
//cube1
static float ataricubex1 = 0.0f;
static float ataricubey1 = 0.0f;
static float ataricubez1 = 0.0f;

//cube2
static float ataricubex2 = 0.0f;
static float ataricubey2 = 0.0f;
static float ataricubez2 = 0.0f;

//cube3
static float ataricubex3 = 0.0f;
static float ataricubey3 = 0.0f;
static float ataricubez3 = 0.0f;

//cube4
static float ataricubex4 = 0.0f;
static float ataricubey4 = 0.0f;
static float ataricubez4 = 0.0f;

//cube5
static float ataricubex5 = 0.0f;
static float ataricubey5 = 0.0f;
static float ataricubez5 = 0.0f;

//cube6
static float ataricubex6 = 0.0f;
static float ataricubey6 = 0.0f;
static float ataricubez6 = 0.0f;
//�L���[�u///////////////////////////////////



//����
static int atarizikan = 0;

//�\���̂��񂷁i���[�v�j�����邽�߂̕ϐ�
static int Ui = 0;//�\���̂����[�v�����邽�߂̕ϐ�
//�{���x///////////////////////////////////////
typedef struct 
{
	float ataribonbex;//�{���x�̍��Wx
	float ataribonbey;//�{���x�̍��Wy
	float ataribonbez;//�{���x�̍��Wz
	bool bHitbonbe;//�����蔻��
	bool tadanbonbe;//���i�q�b�g�C��
}BONBE_ATARI;

static BONBE_ATARI Bonbeatari[6];//�\���̂ŃA�C�e����������邩��錾
//�{���x///////////////////////////////////////

//�R�C��///////////////////////////////////////
//�R�C��
static int coin = 0;

typedef struct
{
	float ataricoinx;//�{���x�̍��Wx
	float ataricoiny;//�{���x�̍��Wy
	float ataricoinz;//�{���x�̍��Wz
	bool bHitcoin;//�����蔻��
	bool tadancoin;//���i�q�b�g�C��
}COIN_ATARI;

static COIN_ATARI Coinatari[10];//�\���̂ŃA�C�e����������邩��錾
//�R�C��///////////////////////////////////////


//�����蔻��̌v�Z����
bool atari(float zibunx, float zibuny, float zibunz, float zibunhankei, float ITEMx, float ITEMy, float ITEMz, float ITEMhankei)
{

	float x = zibunx - ITEMx; //������x���W - �G��x���W = x�̎����ƓG�̋������o��
	float y = zibuny - ITEMy; //������y���W - �G��y���W = y�̎����ƓG�̋������o��
	float z = zibunz - ITEMz; //������z���W - �G��z���W = z�̎����ƓG�̋������o��

	float zibunITEMkixyori = x*x + y*y + z*z; //��ӂ�2�� + �Εӂ�2�� = �Εӂ�2�悪�ł�(�����ƓG�̋������o��)

	float zibunITEMhankei = zibunhankei + ITEMhankei; //�����ƓG�̔��a�𑫂����������o��

	return zibunITEMkixyori < (zibunITEMhankei * zibunITEMhankei); //�����ƓG�̋��� < �����ƓG�̔��a�𑫂������� ��2��(�������r���G�Ǝ����̔��a�𑫂������������������ꍇTrue��Ԃ�)
}

void Initatari(void) 
{
	for (Ui = 0; Ui < 6; Ui++)//�\���̂̐������� 
	{
		Bonbeatari[Ui].bHitbonbe = false;
		Bonbeatari[Ui].ataribonbex = 0;
		Bonbeatari[Ui].ataribonbey = 0;
		Bonbeatari[Ui].ataribonbez = 0;
		Bonbeatari[Ui].tadanbonbe = true;//���i�q�b�g�C��
	}
	for (Ui = 0; Ui < 10; Ui++)//�\���̂̐������� 
	{
		Coinatari[Ui].bHitcoin = false;
		Coinatari[Ui].ataricoinx = 0;
		Coinatari[Ui].ataricoiny = 0;
		Coinatari[Ui].ataricoinz = 0;
		Coinatari[Ui].tadancoin = true;//���i�q�b�g�C��
	}
}

void Updateatari(void)
{
	////////////////�����蔻�菈��//////////////////////////////////////////////////
	//�v���C���[ & �L���[�u1//////////////////////////////////////////
	bool bHit1 = atari(//atarihantei.h//�����蔻��
		atariyokoidou, ataritateidou, atariokuidou, 3.5,//�v���C���[�̈ʒu
		ataricubex1, ataricubey1, ataricubez1, 0.5//�L���[�u�̈ʒu
	);
	if (bHit1) 
	{
		//���������ꍇ�̏���
		getnum(3);//�Q�[���I�[�o�[�Ɉړ�//main.h�ɐ������s���A���̌�main.cpp�ɍs��
		//atarizikan += 2;//���Ԃ𑫂�
		//getzikan(atarizikan);//atarizikan�̐��l��getzikan�ɑ���
		//atarizikan = 0;//atarizikan��0�ɂ���
		//coin += 1;//coin�̐��𑫂�
		//getcoin(coin);//coin�̐��l��getcoin�ɑ���
		//coin = 0;//coin��0�ɂ���
	}
	//�v���C���[ & �L���[�u1//////////////////////////////////////////
	//�v���C���[ & �L���[�u2//////////////////////////////////////////
	bool bHit2 = atari(//atarihantei.h//�����蔻��
		atariyokoidou, ataritateidou, atariokuidou, 3.5,//�v���C���[�̈ʒu
		ataricubex2, ataricubey2, ataricubez2, 0.5//�L���[�u�̈ʒu
	);
	if (bHit2)
	{
		//���������ꍇ�̏���
		getnum(3);//�Q�[���I�[�o�[�Ɉړ�//main.h�ɐ������s���A���̌�main.cpp�ɍs��
		//atarizikan += 2;//���Ԃ𑫂�
		//getzikan(atarizikan);//atarizikan�̐��l��getzikan�ɑ���
		//atarizikan = 0;//atarizikan��0�ɂ���
		//coin += 1;//coin�̐��𑫂�
		//getcoin(coin);//coin�̐��l��getcoin�ɑ���
		//coin = 0;//coin��0�ɂ���
	}
	//�v���C���[ & �L���[�u2//////////////////////////////////////////
	//�v���C���[ & �L���[�u3//////////////////////////////////////////
	bool bHit3 = atari(//atarihantei.h//�����蔻��
		atariyokoidou, ataritateidou, atariokuidou, 3.5,//�v���C���[�̈ʒu
		ataricubex3, ataricubey3, ataricubez3, 0.5//�L���[�u�̈ʒu
	);
	if (bHit3) 
	{
		//���������ꍇ�̏���
		getnum(3);//�Q�[���I�[�o�[�Ɉړ�//main.h�ɐ������s���A���̌�main.cpp�ɍs��
		//atarizikan += 2;//���Ԃ𑫂�
		//getzikan(atarizikan);//atarizikan�̐��l��getzikan�ɑ���
		//atarizikan = 0;//atarizikan��0�ɂ���
		//coin += 1;//coin�̐��𑫂�
		//getcoin(coin);//coin�̐��l��getcoin�ɑ���
		//coin = 0;//coin��0�ɂ���
	}
	//�v���C���[ & �L���[�u3//////////////////////////////////////////
	//�v���C���[ & �L���[�u4//////////////////////////////////////////
	bool bHit4 = atari(//atarihantei.h//�����蔻��
		atariyokoidou, ataritateidou, atariokuidou, 3.5,//�v���C���[�̈ʒu
		ataricubex4, ataricubey4, ataricubez4, 0.5//�L���[�u�̈ʒu
	);
	if (bHit4) 
	{
		//���������ꍇ�̏���
		getnum(3);//�Q�[���I�[�o�[�Ɉړ�//main.h�ɐ������s���A���̌�main.cpp�ɍs��
		//atarizikan += 2;//���Ԃ𑫂�
		//getzikan(atarizikan);//atarizikan�̐��l��getzikan�ɑ���
		//atarizikan = 0;//atarizikan��0�ɂ���
		//coin += 1;//coin�̐��𑫂�
		//getcoin(coin);//coin�̐��l��getcoin�ɑ���
		//coin = 0;//coin��0�ɂ���
	}
	//�v���C���[ & �L���[�u4//////////////////////////////////////////
	//�v���C���[ & �L���[�u5//////////////////////////////////////////
	bool bHit5 = atari(//atarihantei.h//�����蔻��
		atariyokoidou, ataritateidou, atariokuidou, 3.5,//�v���C���[�̈ʒu
		ataricubex5, ataricubey5, ataricubez5, 0.5//�L���[�u�̈ʒu
	);
	if (bHit5)
	{
		//���������ꍇ�̏���
		getnum(3);//�Q�[���I�[�o�[�Ɉړ�//main.h�ɐ������s���A���̌�main.cpp�ɍs��
		//atarizikan += 2;//���Ԃ𑫂�
		//getzikan(atarizikan);//atarizikan�̐��l��getzikan�ɑ���
		//atarizikan = 0;//atarizikan��0�ɂ���
		//coin += 1;//coin�̐��𑫂�
		//getcoin(coin);//coin�̐��l��getcoin�ɑ���
		//coin = 0;//coin��0�ɂ���
	}
	//�v���C���[ & �L���[�u5//////////////////////////////////////////
	//�v���C���[ & �L���[�u6//////////////////////////////////////////
	bool bHit6 = atari(//atarihantei.h//�����蔻��
		atariyokoidou, ataritateidou, atariokuidou, 3.5,//�v���C���[�̈ʒu
		ataricubex6, ataricubey6, ataricubez6, 0.5//�L���[�u�̈ʒu
	);
	if (bHit6) 
	{
		//���������ꍇ�̏���
		getnum(3);//�Q�[���I�[�o�[�Ɉړ�//main.h�ɐ������s���A���̌�main.cpp�ɍs��
		//atarizikan += 2;//���Ԃ𑫂�
		//getzikan(atarizikan);//atarizikan�̐��l��getzikan�ɑ���
		//atarizikan = 0;//atarizikan��0�ɂ���
		//coin += 1;//coin�̐��𑫂�
		//getcoin(coin);//coin�̐��l��getcoin�ɑ���
		//coin = 0;//coin��0�ɂ���
	}
	//�v���C���[ & �L���[�u6//////////////////////////////////////////

	//�v���C���[ & �{���x//////////////////////////////////////////
	for (Ui = 0; Ui < 6; Ui++)//�\���̂̐������� 
	{
		Bonbeatari[Ui].bHitbonbe = atari(//atarihantei.h//�����蔻��
			atariyokoidou, ataritateidou, atariokuidou, 3.5,//�v���C���[�̈ʒu
			Bonbeatari[Ui].ataribonbex, Bonbeatari[Ui].ataribonbey, Bonbeatari[Ui].ataribonbez, 0.5//�{���x�̈ʒu
		);
		if (Bonbeatari[Ui].bHitbonbe == true && Bonbeatari[Ui].tadanbonbe == true)
		{
			//���������ꍇ�̏���
			//getnum(3);//�Q�[���I�[�o�[�Ɉړ�//main.h�ɐ������s���A���̌�main.cpp�ɍs��
			atarizikan += 50;//���Ԃ𑫂�
			getzikan(atarizikan);//atarizikan�̐��l��getzikan�ɑ���
			atarizikan = 0;//atarizikan��0�ɂ���
			//coin += 1;//coin�̐��𑫂�
			//getcoin(coin);//coin�̐��l��getcoin�ɑ���
			//coin = 0;//coin��0�ɂ���
			Bonbeatari[Ui].tadanbonbe = false;//���i�q�b�g�C��
			hihixyouzibonbe(Ui, false);//�{���x�̕`����\���ɂ���
		}
	}
	//�v���C���[ & �{���x//////////////////////////////////////////

	//�v���C���[ & �R�C��//////////////////////////////////////////
	for (Ui = 0; Ui < 10; Ui++)//�\���̂̐������� 
	{
		Coinatari[Ui].bHitcoin = atari(//atarihantei.h//�����蔻��
			atariyokoidou, ataritateidou, atariokuidou, 3.5,//�v���C���[�̈ʒu
			Coinatari[Ui].ataricoinx, Coinatari[Ui].ataricoiny, Coinatari[Ui].ataricoinz, 0.5//�{���x�̈ʒu
		);
		if (Coinatari[Ui].bHitcoin == true && Coinatari[Ui].tadancoin == true)
		{
			//���������ꍇ�̏���
			//getnum(3);//�Q�[���I�[�o�[�Ɉړ�//main.h�ɐ������s���A���̌�main.cpp�ɍs��
			//atarizikan += 10;//���Ԃ𑫂�
			//getzikan(atarizikan);//atarizikan�̐��l��getzikan�ɑ���
			//atarizikan = 0;//atarizikan��0�ɂ���
			coin += 1;//coin�̐��𑫂�
			getcoin(coin);//coin�̐��l��getcoin�ɑ���
			coin = 0;//coin��0�ɂ���
			Coinatari[Ui].tadancoin = false;//���i�q�b�g�C��
			hihixyouzicoin(Ui, false);//�{���x�̕`����\���ɂ���
		}
	}
	//�v���C���[ & �R�C��//////////////////////////////////////////

	////////////////�����蔻�菈��//////////////////////////////////////////////////
}

//Xmodel��okuidou��x�ɓ���tateidou��y�ɓ���okuidou��z�ɓ���
void atariidou(float x, float y, float z)
{
	atariyokoidou = x;//x�̒l��atariyokoidou�ɓ����
	ataritateidou = y;//y�̒l��ataritateidou�ɓ����
	atariokuidou = z;//z�̒l��atariokuidou�ɓ����
}
//cube1�̂����蔻��ɐ��l�𑗂�
void ataricube1(float cx, float cy, float cz)
{
	ataricubex1 = cx;//cx�̒l��ataricubex�ɓ����
	ataricubey1 = cy;//cy�̒l��ataricubey�ɓ����
	ataricubez1 = cz;//cz�̒l��ataricubez�ɓ����
}
//cube2�̂����蔻��ɐ��l�𑗂�
void ataricube2(float cx, float cy, float cz)
{
	ataricubex2 = cx;//cx�̒l��ataricubex�ɓ����
	ataricubey2 = cy;//cy�̒l��ataricubey�ɓ����
	ataricubez2 = cz;//cz�̒l��ataricubez�ɓ����
}
//cube3�̂����蔻��ɐ��l�𑗂�
void ataricube3(float cx, float cy, float cz)
{
	ataricubex3 = cx;//cx�̒l��ataricubex�ɓ����
	ataricubey3 = cy;//cy�̒l��ataricubey�ɓ����
	ataricubez3 = cz;//cz�̒l��ataricubez�ɓ����
}
//cube4�̂����蔻��ɐ��l�𑗂�
void ataricube4(float cx, float cy, float cz)
{
	ataricubex4 = cx;//cx�̒l��ataricubex�ɓ����
	ataricubey4 = cy;//cy�̒l��ataricubey�ɓ����
	ataricubez4 = cz;//cz�̒l��ataricubez�ɓ����
}
//cube5�̂����蔻��ɐ��l�𑗂�
void ataricube5(float cx, float cy, float cz)
{
	ataricubex5 = cx;//cx�̒l��ataricubex�ɓ����
	ataricubey5 = cy;//cy�̒l��ataricubey�ɓ����
	ataricubez5 = cz;//cz�̒l��ataricubez�ɓ����
}
//cube6�̂����蔻��ɐ��l�𑗂�
void ataricube6(float cx, float cy, float cz)
{
	ataricubex6 = cx;//cx�̒l��ataricubex�ɓ����
	ataricubey6 = cy;//cy�̒l��ataricubey�ɓ����
	ataricubez6 = cz;//cz�̒l��ataricubez�ɓ����
}

//�{���x�̂����蔻��ɐ��l�𑗂�
void ataribonbe(int bonbesu, float ix, float iy, float iz)
{
		Bonbeatari[bonbesu].ataribonbex = ix;//ix�̒l��ataribonbex�ɓ����
		Bonbeatari[bonbesu].ataribonbey = iy;//iy�̒l��ataribonbey�ɓ����
		Bonbeatari[bonbesu].ataribonbez = iz;//iz�̒l��ataribonbez�ɓ����
}

void sixyyokikaataribonbe(int bonbesu, bool ataribonbe)
{
	Bonbeatari[bonbesu].tadanbonbe = ataribonbe;
}

//�R�C���̂����蔻��ɐ��l�𑗂�
void ataricoin(int coinsu, float ix, float iy, float iz)
{
	Coinatari[coinsu].ataricoinx = ix;//ix�̒l��ataricoinx�ɓ����
	Coinatari[coinsu].ataricoiny = iy;//iy�̒l��ataricoiny�ɓ����
	Coinatari[coinsu].ataricoinz = iz;//iz�̒l��ataricoinz�ɓ����
}

void sixyyokikaataricoin(int coinsu, bool ataricoin)
{
	Coinatari[coinsu].tadancoin = ataricoin;
}