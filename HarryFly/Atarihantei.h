#pragma once
//=======================================================================================
//						�����蔻��`��
//						2017.06.05
//=======================================================================================

#ifndef _ATARIHANTEI_H_
#define _ATARIHANTEI_H_

bool atari(float zibunx, float zibuny, float zibunz, float zibunhankei, float ITEMx, float ITEMy, float ITEMz, float ITEMhankei);
void Initatari(void);//�����蔻��̏���������
void Updateatari(void);//�����蔻��̍X�V����
void atariidou(float x, float y, float z);//Xmodel�̏�����atarihantei.cpp�֐����𑗂�
void ataricube1(float cx, float cy, float cz);//Polygon3D�̏�����atarihantei.cpp�֐����𑗂�
void ataricube2(float cx, float cy, float cz);//Polygon3D�̏�����atarihantei.cpp�֐����𑗂�
void ataricube3(float cx, float cy, float cz);//Polygon3D�̏�����atarihantei.cpp�֐����𑗂�
void ataricube4(float cx, float cy, float cz);//Polygon3D�̏�����atarihantei.cpp�֐����𑗂�
void ataricube5(float cx, float cy, float cz);//Polygon3D�̏�����atarihantei.cpp�֐����𑗂�
void ataricube6(float cx, float cy, float cz);//Polygon3D�̏�����atarihantei.cpp�֐����𑗂�
void ataribonbe(int bonbesu, float ix, float iy, float iz);//Item.cpp�̏�����atarihantei.cpp�֐����𑗂�
void ataricoin(int coinsu, float ix, float iy, float iz);//Item.cpp�̏�����atarihantei.cpp�֐����𑗂�
#endif //_ATARIHANTEI_H_

