#pragma once
//=============================================================================
//  
// ������
//
//�@      
//=============================================================================

#ifndef _SIXYOKIKA_H_
#define _SIXYOKIKA_H_

void Updatesixyokika(void);//�X�V����

void getiou(float yokoidounum, float tateidounum, float okuidounum);//X���f���̈ړ��̏�����
void getcoin(int coinnum);//coin�̐������ړ�����֐�
void sixyokikacoin(int coinnum);//coin�̐������ړ�����֐�
void getzikan(int zikannum);//zikan�̐������ړ�����֐�
void sixyokikazikan(int zikannum);//zikan�̐������ړ�����֐�
void getcamera(void);//�J�����̏���������

void sixyyokikadrawbonbe(int bonbesu, bool drawbonbe);//�{���x�̏�����
void sixyyokikaataribonbe(int bonbesu, bool ataribonbe);//�{���x�̏�����
void sixyyokikadrawcoin(int coinsu, bool drawcoin);//�R�C���̏�����
void sixyyokikaataricoin(int coinsu, bool ataricoin);//�R�C���̏�����
#endif // _SIXYOKIKA_H_
