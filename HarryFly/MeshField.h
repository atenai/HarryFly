#pragma once
//=============================================================================
//  
// ���b�V���t�B�[���h
//
//�@      
//=============================================================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

typedef struct
{
	char FileName[256];
	int width;
	int height;
}TEXTUREMESH;

typedef enum
{
	MESH_NUK = -1,
	MESH_HORO,
	MESH_BLACK,
	MESH_ZIMEN,
	MESH_KUSA,
	MESH_MAXIMUM,
}TEXTURE_ENUMMESH;

static const TEXTUREMESH cTextuerMesh[] =
{
	{ "./recource/texture/horoCube.png",1024,1024, },
	{ "./recource/texture/black.png",10,10, },
	{ "./recource/texture/zimen.jpg",125,125, },
	{ "./recource/texture/kusa.png",10,10, },
};

void InitMesh(void);//����������
void UninitMesh(void);
void UpdateMesh(void);//�X�V����
void DrawMesh(void);//�摜��\��

#endif // _MESHFIELD_H_


