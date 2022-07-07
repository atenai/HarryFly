//=============================================================================
//
// ���C�� [main.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include<Windows.h>//#include<stdio.h>�̑���
#include<d3d9.h>
#include<d3dx9.h>
#include "Polygon.h"//Polygon.cpp���g����Polygon.h���g����悤�ɂ���
#include<stdio.h>
#include "Main.h"
#include "Cube.h"
#include "Grit.h"
#include "Camera.h"
#include"input.h"
#include "Xmodel.h"
#include "MeshField.h"
#include "Atarihantei.h"
#include "Number.h"
#include "Score.h"
#include "Sixyokika.h"
#include "Bonbe.h"
#include "Coin.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
///////////////���̃v���O�����̒��g�̓E�B���h�E��\��������///////////////////////////////////////////
#define CLASS_NAME "�N���X�l�[��"//�����u������
#define WINDOW_NAME "�n���[�t���C"//�����u������//�������񖽖�
///////////////���̃v���O�����̒��g�̓E�B���h�E��\��������///////////////////////////////////////////

//===============
//�O���[�o���ϐ�
//===============
LPDIRECT3D9			g_pD3D = NULL;			//Direct3D�C���^�[�t�F�C�X
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//Direct3D�f���@�C�X
LPDIRECT3DDEVICE9 GetDevice() { return g_pD3DDevice; }

static int nflag = 0;//�^�C�g���˃Q�[���v���C�˃Q�[���I�[�o�[�˃^�C�g��
int zikan = 230;//�Q�[���I�[�o�[�p�̎��Ԃ��v�锠
int coinsu = 0;//�X�R�A�[�̐����p��
bool g_bPress = true;//�^�C�g���s�R�s�R
int g_nCnt = 0;//

			  //===============
			  //�v���g�^�C�v�錾
			  //===============
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//�E�B���h�E�v���V�[�W�� �R�[���o�b�N
bool Init(HINSTANCE nInstance, HWND hWnd, BOOL bWindow);//HRESULT//����������
void Uninit(void);//�I������
void Update(void);//�X�V����
void Draw(void);//�摜�\��
void gametitle(void);//�Q�[���^�C�g��
void gamestart(void);//�Q�[�����
void gameclear(void);//�Q�[���N���A�[
void gameover(void);//�Q�[���I�[�o�[

					////////////////�������灪�̒��g��������/////////////////////////////////////	

					//�v���g�^�C�v�錾//�����͉��̏��������e�̂�//������Ȃ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{//1
	switch (uMsg)
	{//switch(uMsg)�̎n�܂蒆�J�b�R2
		case WM_DESTROY://�E�B���h�E�������(�~�{�^����������)�v���O�������I�����铮��
			PostQuitMessage(0);//�A�v���P�[�V�����̏I���𑣂�
			break;

		case WM_KEYDOWN:
		{//4
			switch (wParam)//wParam�͒ǉ���������
			{//5
				case VK_ESCAPE://[ESC]�L�[�������ꂽ��H
				{//6
					int nID;//nID�Ƃ����������
					nID = MessageBox(hWnd, "�ꎞ��~��\n�Q�[�����I�����܂����H", "ESC�L�[", MB_YESNO);//MB_YESNO��yes��no�̃��b�Z�[�W�{�^�����o��
					if (nID == IDYES)//����YES����������{}�̒����N������
					{//7
						DestroyWindow(hWnd);//Window����
					}//7
					break;
				}//6
				break;

				case VK_RETURN://�G���^�[�L�[�������ꂽ��H
					if (nflag == 0)//�����^�C�g����ʂ�������
					{
						nflag = 1;//�Q�[���v���C��ʂֈړ�
					}
					if (nflag == 2 || nflag == 3)//�Q�[���N���A�[��ʂ܂��̓Q�[���I�[�o�[��ʂ�������
					{
						nflag = 0;//�^�C�g����ʂֈړ�
					}
				break;
			}//5
			break;//switch(wParam)��break
		}//4
		

	default://switch(uMsg)
	break;//switch(uMsg)
	}//switch(uMsg)�̏I��蒆�J�b�R2
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}//1


 //===========
 //���C���֐�
 //===========
 //int main(void)�̑��肪���̓z��//�G���g���[�|�C���g//������Ȃ�
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{//1


 ///////////////���̃v���O�����̒��g�̓E�B���h�E��\��������///////////////////////////////////////////
 //WNDCLASSEX�\���̂ŃE�B���h�E�N���X�̃p�����[�^���w��
 //��
 //RegisterClassEx()�ł��̃E�B���h�E�N���X��o�^
 //��
 //CreateWindow()�œo�^�����N���X�����ƂɃE�B���h�E�����
 //��
 //ShowWindow()��UpdateWindow()�ŕ\������Ƃ�����A�̗���i�Z�b�g�j

 //�E�B���h�E�N���X�\���̂̐ݒ�
	WNDCLASSEX  wcex =
	{//2
		sizeof(WNDCLASSEX),
		CS_VREDRAW | CS_HREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};//2

	  //�E�B���h�E�\���̂��������������Ă����o�[�W������
	  //WNDCLASSEX wcex;
	  //wcex.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wcex);//�E�B���h�E�N���X�̓o�^,createwindowex�Ŏg���̂ɐ�ΕK�v�i�g��Ȃ��Ɠ����Ȃ��j

	HWND hWnd = CreateWindowEx//�E�B���h�E�̍쐬
	(
		0,//�g���E�B���h�E�X�^�C��
		CLASS_NAME,//"����"//�o�^����Ă���N���X��
		WINDOW_NAME,//"�E�B���h�E�\���E�F�[�C"//�E�B���h�E��
		WS_OVERLAPPEDWINDOW,//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,//�E�B���h�E�̉������̈ʒu
		CW_USEDEFAULT,//�E�B���h�E�̏c�����̈ʒu
		SCREEN_WIDTH, //��(1366)//�E�B���h�E�̕�
		SCREEN_HEIGHT, //����(768)//�E�B���h�E�̍���
		NULL,//�e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
		NULL,//���j���[�n���h���܂��͎��ʎq
		hInstance,//�A�v���P�[�V�����C���X�^���X�̃n���h��
		NULL//�E�B���h�E�쐬�f�[�^
	);

	ShowWindow(hWnd, nCmdShow);//�E�B���h�E�\��
	UpdateWindow(hWnd);//�E�B���h�E�\��


	MSG msg;//���b�Z�[�W�\����


	DWORD dwTimeNow = timeGetTime();//�������ɏ���
	DWORD dwTimeOld = timeGetTime();//�������ɏ���

									//---- �������֐� ----
	if (!Init(hInstance, hWnd, TRUE))//����������
	{
		MessageBox(hWnd, "���������������܂����I", "���b�Z�[�W", MB_OK);
		return -1;
	}

	//======================�Q�[�����[�v�J�n==============
	//����\
	timeBeginPeriod(1);

	for (;;)//for����
	{
		//���b�Z�[�W���[�v�܂�E�B���h�E��\������������
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))//Windows����C�x���g���b�Z�[�W���󂯎��
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W����
				TranslateMessage(&msg);//WM_KEYDOWN���b�Z�[�W����WM_CHAR���b�Z�[�W���쐬
				DispatchMessage(&msg);//�E�B���h�E�v���V�[�W���ɃC�x���g���b�Z�[�W��]��
			}
		}
		else
		{
			//�Q�[������
			dwTimeNow = timeGetTime();//���̎��� = timeGetTime();
									  //		�~���b�@�@�@�~���b
			if ((dwTimeNow - dwTimeOld) >= (1000 / 60))//if((���̎��� - �O�̃t���[���̎���) >= (1000/60))
			{
				//nflag���R�R�ɓ����
				//�^�C�g���˃Q�[���v���C�˃Q�[���I�[�o�[�˃^�C�g��
				if (nflag == 0)
				{
					//�^�C�g�����
					gametitle();
				}

				if (nflag == 1)
				{
					//�Q�[���J�n
					gamestart();
				}

				if (nflag == 2)
				{
					//�Q�[���N���A�[
					gameclear();
				}

				if (nflag == 3)
				{
					//�Q�[���I�[�o�[
					gameover();
				}

				//�^�C�g����ʂɖ߂鏈��
				if (nflag == 4)
				{


					//�^�C�g����ʂɖ߂�
					nflag = 0;
				}

				dwTimeOld = timeGetTime();//�O�t���[���̎��� = ���̎���;
			}
		}
	}

	timeEndPeriod(1);
	//=======================�Q�[�����[�v����============================


	Uninit();//�I������

			 ///////////////���̃v���O�����̒��g�̓E�B���h�E��\��������///////////////////////////////////////////	
	return(int)msg.wParam;
}//1


 //==============
 //  �������֐�
 //==============
bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)//HRESULT
{//1

 //Direct3D�C���^�[�t�F�C�X�̎擾
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{//2
		return FALSE;
	}//2

	D3DDISPLAYMODE d3ddm;
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{//3
		return FALSE;
	}//3

	 // �f�o�C�X�̃v���[���e�[�V�����p�����[�^
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));//��ɏ���������
	d3dpp.BackBufferWidth = SCREEN_WIDTH;//���̃X�N���[���̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//���̃X�N���[���̍���
	d3dpp.BackBufferFormat = d3ddm.Format;//�F���̎w��
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//���ꂵ���I�΂Ȃ��@�����M�����ǂ�������
	d3dpp.EnableAutoDepthStencil = TRUE;//���true
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//��΃R���ɂ���
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//�f�o�C�X�I�u�W�F�N�g�̍쐬
	//[�f�o�C�X�쐬����]<�`��>��<���_����>
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{//4
		MessageBox(NULL, "g_pD3DDevice�̎擾�Ɏ��s���܂���", "���s", MB_OK);
		return false;
	}//4


	if (!InitPolygon())//�|���S���̏���������
	{//5
		MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "���s", MB_OK);
		return false;
	}//5
	 /////////////////////���������������́��ɓ����////////////////////////////
	Initatari();//�����蔻��̏���������
	InitPolygon3D();//�|���S��3D�̏���������(�L���[�u)
	InitMesh();//�n�ʂ̏���������
	InitKeyboard(hInstance, hWnd);//�L�[���͂̏���������
	InitXmodel();//X���f���̏���������
	Initbonbe();//�{���x�̏�����
	Initcoin();//�R�C���̏�����
	/////////////////////���������������́��ɓ����////////////////////////////
	return true;
}//1

 //==============
 //  �I���֐�
 //==============
void Uninit(void)
{//1
	UninitPolygon();//�N���G�C�g�֌W�͕Ԃ�//�|���S���̏I������
	UninitPolygon3D();//�|���S��3D�̏I������(�L���[�u)
	UninitMesh();//���b�V���t�B�[���h�̏I������
	UninitXmodel();//Xmodel�̏I������
	Uninitcoin();//�R�C���̏I������
	Uninitbonbe();//�{���x�̏I������

	if (g_pD3DDevice != NULL)
	{//�f�o�C�X�̊J��//2
		g_pD3DDevice->Release();//����ŊJ�������
		g_pD3DDevice = NULL;//�A�h���X���c���Ă���̂�NULL�ŏ㏑��
	}//2

	if (g_pD3D != NULL)
	{//Direct3D�I�u�W�F�N�g�̊J��//3
		g_pD3D->Release();
		g_pD3D = NULL;
	}//3
	UninitKeyboard();//main.cpp(void Uninit(void))
}//1

 //==============
 // �@�X�V�֐�
 //==============
void Update(void)
{//1
 ////////////////////���C�g�ƃ}�e���A���̐ݒ�////////////////
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main.h
											//�}�e���A���ݒ�
	D3DMATERIAL9 mat;
	ZeroMemory(&mat, sizeof(mat));
	mat.Diffuse.r = 1.0f;
	mat.Diffuse.g = 1.0f;
	mat.Diffuse.b = 1.0f;
	mat.Diffuse.a = 1.0f;
	//�}�e���A���̐F��ς���
	mat.Ambient.r = 1.0f;
	mat.Ambient.g = 1.0f;
	mat.Ambient.b = 1.0f;
	mat.Ambient.a = 1.0f;
	pDevice->SetMaterial(&mat);

	//���C�g�̐ݒ�
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vecDir(-1.0f, 0.0f, 0.0f);//(X,Y,Z)�̌��̓�����������w�肷��
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;

	light.Ambient.r = 1.0f;
	light.Ambient.g = 1.0f;
	light.Ambient.b = 1.0f;
	light.Ambient.a = 1.0f;
	pDevice->SetLight(0, &light);//���C�g�ԍ�0�`3
	pDevice->LightEnable(0, TRUE);//0�ԃ��C�g�I���I
								  //�O���[�o���A���r�G���g�̐ݒ�
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	////////////////////���C�g�ƃ}�e���A���̐ݒ�////////////////
	//////////////////�������火�̒��g��������/////////////////////////////////
	zikan--;//���t���[�����Ԃ������Ă���
	if (zikan <= 0)//����zikan�����̐��l�ȏ�ɂȂ����� 
	{
		nflag = 3;//�Q�[���I�[�o�[�Ɉړ�
	}

	UpdateCamera();//�J�����̍X�V����
	UpdatePolygon3D();//�|���S��3D�̍X�V����(�L���[�u)
	UpdateGrit();//���摜�̍X�V����
	UpdateXmodel();//X���f���̍X�V����
	Updatebonbe();//�{���x�̍X�V����
	Updatecoin();//�R�C���̍X�V����
	UpdateMesh();//���b�V���t�B�[���h�̍X�V����
	UpdateKeyboard();//main.cpp(void Updata(void))//�L�[���͂̍X�V����
	Updateatari();//�����蔻��̍X�V����//�����蔻��̏����͍Ō�ɂ��Ȃ��ƍ��W�����m�ɑ����Ȃ�

	

	////////////////�������灪�̒��g��������/////////////////////////////////////	
}//1

 //==============
 // �@�`��֐�
 //==============
void Draw(void)
{//1
	g_pD3DDevice->Clear(
		0, NULL, //�w�肵���擪�A�h���X�̋�`�Ȃǂ̂��̂�NULL�̂Ƃ낱�ɉ��L������̂���NULL��
		(D3DCLEAR_TARGET | //�F��Clear
			D3DCLEAR_ZBUFFER),//�[�b�g�o�b�t�@��Clear
		D3DCOLOR_RGBA(142, 209, 224, 255),//�w�i�F�̕ύX
		1.0f, 0);//1.0f���[�b�g�o�b�t�@��Clear���l�A�X�e���V�������̒l��Clear����̂�

				 //Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//2

	 //////////////////�������火�̒��g��������//���̒���Draw�n������///////////////////////////////
	 //���̒��ɕ`�悵�����v���O�����������
		if (nflag == 0)
		{
			

			//�^�C�g�����
			SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//�|���S���J���[�̐ݒ�
			DrawPolygon(
				TEX_1,//�g���e�N�X�`��,
				0.f, //x���W,
				0.f,//y���W,
				1366,//�e�N�X�`���̕\�����鉡�̒���,//���̉摜�̉��̒�����32
				768,//�e�N�X�`���̕\������c�̒���,//���̉摜�̏c�̒�����32
				0,//���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
				0,//���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
				800,//���̉摜�̐؂��肽����
				600 //���̉摜�̐؂��肽������
			);

			//�e�N�X�`���s�R�s�R
			g_nCnt++;
			if (g_nCnt % 30 == 0)
			{
				switch (g_bPress) 
				{
				case false:
					g_bPress = true;
					break;
				case true:
					g_bPress = false;
					break;
				}
			}

			if (g_bPress == true) {
				DrawPolygon(
					TEX_6,//�g���e�N�X�`��,
					0.f, //x���W,
					0.f,//y���W,
					1366,//�e�N�X�`���̕\�����鉡�̒���,//���̉摜�̉��̒�����32
					768,//�e�N�X�`���̕\������c�̒���,//���̉摜�̏c�̒�����32
					0,//���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
					0,//���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
					800,//���̉摜�̐؂��肽����
					600 //���̉摜�̐؂��肽������
				);
			}
			//�e�N�X�`���s�R�s�R

			Updatesixyokika();//����������
		}

		if (nflag == 1)
		{
			//�Q�[���v���C
			
			DrawPolygon3D();//3D�摜��\��(�L���[�u)
			
			DrawXmodel();//X���f����\��
			Drawbonbe();//�{���x��\��
			Drawcoin();//�R�C����\��
			DrawGrit();//���摜��\��
			DrawMesh();//�n�ʂ�\��
			DrawPolygon(TEX_4, 10, 550, 250, 175, 0, 0, 1000, 500);//2D�摜(UI)��\��//UI�͈�ԉ��ɂ��Ȃ��Ɖ摜�������Ă��܂��B//768-175=593
			DrawScore(coinsu, 3, 300.0f, 300.0f, true);//�X�R�A�[�\��
			DrawScore(zikan, 3, 0.0f, 0.0f, true);//���ԕ\��
		}

		if (nflag == 2)
		{
			//�Q�[���N���A�[
			SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//�|���S���J���[�̐ݒ�
															   //�摜��\��
			DrawPolygon(
				TEX_2,//�g���e�N�X�`��,
				0, //x���W,600
				0, //y���W,
				1366, //�e�N�X�`���̕\�����鉡�̒���,//���̉摜�̉��̒�����140
				768, //�e�N�X�`���̕\������c�̒���,//���̉摜�̏c�̒�����200
				0,//���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
				0,//���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
				1280,//���̉摜�̐؂��肽����
				720//���̉摜�̐؂��肽������
			);

			SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//�|���S���J���[�̐ݒ�
															   //�摜��\��
			DrawPolygon(
				TEX_7,//�g���e�N�X�`��,
				445, //x���W,600
				540, //y���W,
				200, //�e�N�X�`���̕\�����鉡�̒���,//���̉摜�̉��̒�����140
				100, //�e�N�X�`���̕\������c�̒���,//���̉摜�̏c�̒�����200
				0,//���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
				0,//���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
				800,//���̉摜�̐؂��肽����
				600//���̉摜�̐؂��肽������
			);
			DrawScore(coinsu, 3, 660.0f, 550.0f, true);//�X�R�A�[�\��
			DrawScore(zikan, 3, 0.0f, 0.0f, true);//���ԕ\��

		
		}

		if (nflag == 3)
		{
			//�Q�[���I�[�o�[
			SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//�|���S���J���[�̐ݒ�
															   //�摜��\��
			DrawPolygon(
				TEX_3,//�g���e�N�X�`��,
				0, //x���W,100
				0, //y���W,50
				1366, //�e�N�X�`���̕\�����鉡�̒���,//���̉摜�̉��̒�����
				768, //�e�N�X�`���̕\������c�̒���,//���̉摜�̏c�̒�����
				0,//���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
				0,//���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
				1280,//���̉摜�̐؂��肽����
				720//���̉摜�̐؂��肽������
			);

			SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//�|���S���J���[�̐ݒ�
															   //�摜��\��
			DrawPolygon(
				TEX_7,//�g���e�N�X�`��,
				445, //x���W,600
				540, //y���W,
				200, //�e�N�X�`���̕\�����鉡�̒���,//���̉摜�̉��̒�����140
				100, //�e�N�X�`���̕\������c�̒���,//���̉摜�̏c�̒�����200
				0,//���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
				0,//���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
				800,//���̉摜�̐؂��肽����
				600//���̉摜�̐؂��肽������
			);
			DrawScore(coinsu, 3, 660.0f, 550.0f, true);//�X�R�A�[�\��
			DrawScore(zikan, 3, 0.0f, 0.0f, true);//���ԕ\��


		}
		////////////////�������灪�̒��g��������//���̒���Draw�n������///////////////////////////////////		

	}//2
	g_pD3DDevice->EndScene();//Direct3D�ɂ��`��̏I��
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);//�`�悪�I����ăf�o�C�X�Ƀv���[���g����
}//1



LPDIRECT3DDEVICE9 GetD3DDevice(void)
{//1
	return g_pD3DDevice;
}//1

 //�^�C�g�����
void gametitle(void) {
	//�`��
	Draw();
}

//�Q�[�����
void gamestart(void) {
	//�X�V
	Update();
	//�`��
	Draw();
}

//�Q�[���N���A�[
void gameclear(void) {
	//�`��
	Draw();
}

//�Q�[���I�[�o�[
void gameover(void) {
	//�`��
	Draw();
}

//main.h���琔���������Ă���֐�
void getnum(int num)
{
	nflag = num;//main.h���琔���������Ă���nflag�ɓ���鏈��
}

//sixyokika.h���琔���������Ă���֐�
void getcoin(int coinnum)
{
	coinsu = coinsu + coinnum;//sixyokika.h���琔���������Ă���coin�ɓ���鏈��
}

//sixyokika.h���琔���������Ă���֐�
void sixyokikacoin(int coinnum)
{
	coinsu = coinnum;//sixyokika.h���琔���������Ă���coin�ɓ���鏈��
}

//sixyokika.h���琔���������Ă���֐�
void getzikan(int zikannum)
{
	zikan = zikan + zikannum;//sixyokika.h���琔���������Ă���zikan�ɓ���鏈��
}

//sixyokika.h���琔���������Ă���֐�
void sixyokikazikan(int zikannum)
{
	zikan = zikannum;//sixyokika.h���琔���������Ă���zikan�ɓ���鏈��
}
