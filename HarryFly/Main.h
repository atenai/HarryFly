#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#include<d3d9.h>//���������!!
#include<d3dx9.h>//���������!!

#define SCREEN_WIDTH (1366)//�X�N���[���̉��̒���
#define SCREEN_HEIGHT (768)//�X�N���[���̏c�̒���

LPDIRECT3DDEVICE9 GetD3DDevice(void);
LPDIRECT3DDEVICE9 GetDevice(void);



void getnum(int num);//�Q�[���I�[�o�[�Ɉړ������邽�߂̐����ړ��p�֐�


#endif // _MAIN_H_

