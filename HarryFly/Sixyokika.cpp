#include "Xmodel.h"
#include "Main.h"
#include "Camera.h"
#include "Sixyokika.h"

static int Ui = 0;//�\���̂����[�v�����邽�߂̕ϐ�


void Updatesixyokika(void)
{
	//����������
	sixyokikacoin(0);//coin�̐��l��getcoin�ɑ���//�X�R�A�[�̐����p���̏�����
	getiou(0.0f, 0.0f, 0.0f);//X���f���̈ړ��̏�����
	sixyokikazikan(230);//atarizikan�̐��l��getzikan�ɑ���;//�Q�[���I�[�o�[�p�̎��Ԃ��v�锠�̏�����
	getcamera();//�J�����������p�֐�
	for (Ui = 0; Ui < 6; Ui++)//�\���̂̐������� 
	{
		sixyyokikadrawbonbe(Ui, true);//�{���x�̏�����
		sixyyokikaataribonbe(Ui, true);//�{���x�̏�����
		
	}
	for (Ui = 0; Ui < 10; Ui++)//�\���̂̐������� 
	{
		
		sixyyokikadrawcoin(Ui, true);//�R�C���̏�����
		sixyyokikaataricoin(Ui, true);//�R�C���̏�����
	}
}
