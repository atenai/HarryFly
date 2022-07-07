#include <windows.h>
#include "Number.h"
//void DrawScore(int �\�������X�R�A�[(����), int �X�R�A�[�̉E�g, float �\��������X���W, float �\��������Y���W, bool �X�R�A�[�̉E�g��0�Ŗ��߂邩�ǂ���)
void DrawScore(int nScore, int nDig, float x, float y, bool bZero)
{
	//���l��
	if (nDig < 0)//nDig��0��菬�����Ƃ�
	{
		nDig = 0;//nDig��0
		for(;;)//�������[�v
		{
			nScore /= 10;//nScore ��= 10
			if (nScore == 0)//����nScore��0�Ȃ�
			{
				break;
			}
			nDig++;
		}
	}

	//�J���X�g�l
	int maxScore = 10;

	for (int i = 1; i < nDig; i++)
	{
		maxScore *= 10;
	}
	maxScore--;

	nScore = min(maxScore, nScore);

	for (int i = 1; i <= nDig; i++)
	{
		int n = nScore % 10;		
		DrawNumber(n, x + NUMBER_WIDTH * (nDig - i), y);
		nScore /= 10;
		if (nScore == 0 && !bZero)
		{
			break;
		}
	}
}