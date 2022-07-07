//=============================================================================
//
// メイン [main.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include<Windows.h>//#include<stdio.h>の代わり
#include<d3d9.h>
#include<d3dx9.h>
#include "Polygon.h"//Polygon.cppを使う為Polygon.hを使えるようにする
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
// マクロ定義
//*****************************************************************************
///////////////このプログラムの中身はウィンドウを表示するやつ///////////////////////////////////////////
#define CLASS_NAME "クラスネーム"//文字置き換え
#define WINDOW_NAME "ハリーフライ"//文字置き換え//下村さん命名
///////////////このプログラムの中身はウィンドウを表示するやつ///////////////////////////////////////////

//===============
//グローバル変数
//===============
LPDIRECT3D9			g_pD3D = NULL;			//Direct3Dインターフェイス
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//Direct3Dデヴァイス
LPDIRECT3DDEVICE9 GetDevice() { return g_pD3DDevice; }

static int nflag = 0;//タイトル⇒ゲームプレイ⇒ゲームオーバー⇒タイトル
int zikan = 230;//ゲームオーバー用の時間を計る箱
int coinsu = 0;//スコアーの数字用箱
bool g_bPress = true;//タイトルピコピコ
int g_nCnt = 0;//

			  //===============
			  //プロトタイプ宣言
			  //===============
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//ウィンドウプロシージャ コールバック
bool Init(HINSTANCE nInstance, HWND hWnd, BOOL bWindow);//HRESULT//初期化処理
void Uninit(void);//終了処理
void Update(void);//更新処理
void Draw(void);//画像表示
void gametitle(void);//ゲームタイトル
void gamestart(void);//ゲーム画面
void gameclear(void);//ゲームクリアー
void gameover(void);//ゲームオーバー

					////////////////ここから↑の中身をいじる/////////////////////////////////////	

					//プロトタイプ宣言//ここは俺の書いた内容のみ//いじらない
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{//1
	switch (uMsg)
	{//switch(uMsg)の始まり中カッコ2
		case WM_DESTROY://ウィンドウを閉じたら(×ボタン押したら)プラグラムが終了する動作
			PostQuitMessage(0);//アプリケーションの終了を促す
			break;

		case WM_KEYDOWN:
		{//4
			switch (wParam)//wParamは追加情報を入れる
			{//5
				case VK_ESCAPE://[ESC]キーが押されたら？
				{//6
					int nID;//nIDという箱を作る
					nID = MessageBox(hWnd, "一時停止中\nゲームを終了しますか？", "ESCキー", MB_YESNO);//MB_YESNOはyesかnoのメッセージボタンが出る
					if (nID == IDYES)//もしYESを押したら{}の中を起動する
					{//7
						DestroyWindow(hWnd);//Windowを壊す
					}//7
					break;
				}//6
				break;

				case VK_RETURN://エンターキーが押されたら？
					if (nflag == 0)//もしタイトル画面だったら
					{
						nflag = 1;//ゲームプレイ画面へ移動
					}
					if (nflag == 2 || nflag == 3)//ゲームクリアー画面またはゲームオーバー画面だったら
					{
						nflag = 0;//タイトル画面へ移動
					}
				break;
			}//5
			break;//switch(wParam)のbreak
		}//4
		

	default://switch(uMsg)
	break;//switch(uMsg)
	}//switch(uMsg)の終わり中カッコ2
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}//1


 //===========
 //メイン関数
 //===========
 //int main(void)の代わりが下の奴↓//エントリーポイント//いじらない
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{//1


 ///////////////このプログラムの中身はウィンドウを表示するやつ///////////////////////////////////////////
 //WNDCLASSEX構造体でウィンドウクラスのパラメータを指定
 //↓
 //RegisterClassEx()でそのウィンドウクラスを登録
 //↓
 //CreateWindow()で登録したクラスをもとにウィンドウを作り
 //↓
 //ShowWindow()とUpdateWindow()で表示するという一連の流れ（セット）

 //ウィンドウクラス構造体の設定
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

	  //ウィンドウ構造体をいちいち書いていくバージョン↓
	  //WNDCLASSEX wcex;
	  //wcex.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wcex);//ウィンドウクラスの登録,createwindowexで使うのに絶対必要（使わないと動かない）

	HWND hWnd = CreateWindowEx//ウィンドウの作成
	(
		0,//拡張ウィンドウスタイル
		CLASS_NAME,//"うんこ"//登録されているクラス名
		WINDOW_NAME,//"ウィンドウ表示ウェーイ"//ウィンドウ名
		WS_OVERLAPPEDWINDOW,//ウィンドウスタイル
		CW_USEDEFAULT,//ウィンドウの横方向の位置
		CW_USEDEFAULT,//ウィンドウの縦方向の位置
		SCREEN_WIDTH, //幅(1366)//ウィンドウの幅
		SCREEN_HEIGHT, //高さ(768)//ウィンドウの高さ
		NULL,//親ウィンドウまたはオーナーウィンドウのハンドル
		NULL,//メニューハンドルまたは識別子
		hInstance,//アプリケーションインスタンスのハンドル
		NULL//ウィンドウ作成データ
	);

	ShowWindow(hWnd, nCmdShow);//ウィンドウ表示
	UpdateWindow(hWnd);//ウィンドウ表示


	MSG msg;//メッセージ構造体


	DWORD dwTimeNow = timeGetTime();//自分風に書く
	DWORD dwTimeOld = timeGetTime();//自分風に書く

									//---- 初期化関数 ----
	if (!Init(hInstance, hWnd, TRUE))//初期化処理
	{
		MessageBox(hWnd, "初期化が完了しました！", "メッセージ", MB_OK);
		return -1;
	}

	//======================ゲームループ開始==============
	//分解能
	timeBeginPeriod(1);

	for (;;)//for泣き
	{
		//メッセージループつまりウィンドウを表示させ続ける
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))//Windowsからイベントメッセージを受け取る
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//メッセージ処理
				TranslateMessage(&msg);//WM_KEYDOWNメッセージからWM_CHARメッセージを作成
				DispatchMessage(&msg);//ウィンドウプロシージャにイベントメッセージを転送
			}
		}
		else
		{
			//ゲーム処理
			dwTimeNow = timeGetTime();//今の時間 = timeGetTime();
									  //		ミリ秒　　　ミリ秒
			if ((dwTimeNow - dwTimeOld) >= (1000 / 60))//if((今の時間 - 前のフレームの時間) >= (1000/60))
			{
				//nflagをココに入れる
				//タイトル⇒ゲームプレイ⇒ゲームオーバー⇒タイトル
				if (nflag == 0)
				{
					//タイトル画面
					gametitle();
				}

				if (nflag == 1)
				{
					//ゲーム開始
					gamestart();
				}

				if (nflag == 2)
				{
					//ゲームクリアー
					gameclear();
				}

				if (nflag == 3)
				{
					//ゲームオーバー
					gameover();
				}

				//タイトル画面に戻る処理
				if (nflag == 4)
				{


					//タイトル画面に戻る
					nflag = 0;
				}

				dwTimeOld = timeGetTime();//前フレームの時間 = 今の時間;
			}
		}
	}

	timeEndPeriod(1);
	//=======================ゲームループ完了============================


	Uninit();//終了処理

			 ///////////////このプログラムの中身はウィンドウを表示するやつ///////////////////////////////////////////	
	return(int)msg.wParam;
}//1


 //==============
 //  初期化関数
 //==============
bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)//HRESULT
{//1

 //Direct3Dインターフェイスの取得
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

	 // デバイスのプレゼンテーションパラメータ
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));//零に初期化する
	d3dpp.BackBufferWidth = SCREEN_WIDTH;//裏のスクリーンの幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//裏のスクリーンの高さ
	d3dpp.BackBufferFormat = d3ddm.Format;//色数の指定
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//これしか選ばない　同期信号をどう扱うか
	d3dpp.EnableAutoDepthStencil = TRUE;//絶対true
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//絶対コレにする
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//デバイスオブジェクトの作成
	//[デバイス作成制御]<描画>と<頂点処理>
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{//4
		MessageBox(NULL, "g_pD3DDeviceの取得に失敗しました", "失敗", MB_OK);
		return false;
	}//4


	if (!InitPolygon())//ポリゴンの初期化処理
	{//5
		MessageBox(NULL, "テクスチャの読み込みに失敗しました", "失敗", MB_OK);
		return false;
	}//5
	 /////////////////////初期化処理をこの↓に入れる////////////////////////////
	Initatari();//あたり判定の初期化処理
	InitPolygon3D();//ポリゴン3Dの初期化処理(キューブ)
	InitMesh();//地面の初期化処理
	InitKeyboard(hInstance, hWnd);//キー入力の初期化処理
	InitXmodel();//Xモデルの初期化処理
	Initbonbe();//ボンベの初期化
	Initcoin();//コインの初期化
	/////////////////////初期化処理をこの↑に入れる////////////////////////////
	return true;
}//1

 //==============
 //  終了関数
 //==============
void Uninit(void)
{//1
	UninitPolygon();//クリエイト関係は返す//ポリゴンの終了処理
	UninitPolygon3D();//ポリゴン3Dの終了処理(キューブ)
	UninitMesh();//メッシュフィールドの終了処理
	UninitXmodel();//Xmodelの終了処理
	Uninitcoin();//コインの終了処理
	Uninitbonbe();//ボンベの終了処理

	if (g_pD3DDevice != NULL)
	{//デバイスの開放//2
		g_pD3DDevice->Release();//これで開放される
		g_pD3DDevice = NULL;//アドレスが残っているのでNULLで上書き
	}//2

	if (g_pD3D != NULL)
	{//Direct3Dオブジェクトの開放//3
		g_pD3D->Release();
		g_pD3D = NULL;
	}//3
	UninitKeyboard();//main.cpp(void Uninit(void))
}//1

 //==============
 // 　更新関数
 //==============
void Update(void)
{//1
 ////////////////////ライトとマテリアルの設定////////////////
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main.h
											//マテリアル設定
	D3DMATERIAL9 mat;
	ZeroMemory(&mat, sizeof(mat));
	mat.Diffuse.r = 1.0f;
	mat.Diffuse.g = 1.0f;
	mat.Diffuse.b = 1.0f;
	mat.Diffuse.a = 1.0f;
	//マテリアルの色を変える
	mat.Ambient.r = 1.0f;
	mat.Ambient.g = 1.0f;
	mat.Ambient.b = 1.0f;
	mat.Ambient.a = 1.0f;
	pDevice->SetMaterial(&mat);

	//ライトの設定
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vecDir(-1.0f, 0.0f, 0.0f);//(X,Y,Z)の光の当たる方向を指定する
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;

	light.Ambient.r = 1.0f;
	light.Ambient.g = 1.0f;
	light.Ambient.b = 1.0f;
	light.Ambient.a = 1.0f;
	pDevice->SetLight(0, &light);//ライト番号0～3
	pDevice->LightEnable(0, TRUE);//0番ライトオン！
								  //グローバルアンビエントの設定
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	////////////////////ライトとマテリアルの設定////////////////
	//////////////////ここから↓の中身をいじる/////////////////////////////////
	zikan--;//毎フレーム時間を引いていく
	if (zikan <= 0)//もしzikanがこの数値以上になったら 
	{
		nflag = 3;//ゲームオーバーに移動
	}

	UpdateCamera();//カメラの更新処理
	UpdatePolygon3D();//ポリゴン3Dの更新処理(キューブ)
	UpdateGrit();//線画像の更新処理
	UpdateXmodel();//Xモデルの更新処理
	Updatebonbe();//ボンベの更新処理
	Updatecoin();//コインの更新処理
	UpdateMesh();//メッシュフィールドの更新処理
	UpdateKeyboard();//main.cpp(void Updata(void))//キー入力の更新処理
	Updateatari();//あたり判定の更新処理//あたり判定の処理は最後にしないと座標が正確に送られない

	

	////////////////ここから↑の中身をいじる/////////////////////////////////////	
}//1

 //==============
 // 　描画関数
 //==============
void Draw(void)
{//1
	g_pD3DDevice->Clear(
		0, NULL, //指定した先頭アドレスの矩形などのものをNULLのとろこに下記何個あるのかをNULLの
		(D3DCLEAR_TARGET | //色をClear
			D3DCLEAR_ZBUFFER),//ゼットバッファをClear
		D3DCOLOR_RGBA(142, 209, 224, 255),//背景色の変更
		1.0f, 0);//1.0fがゼットバッファのClear数値、ステンシルを何の値でClearするのか

				 //Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//2

	 //////////////////ここから↓の中身をいじる//この中にDraw系を入れる///////////////////////////////
	 //この中に描画したいプログラムをいれる
		if (nflag == 0)
		{
			

			//タイトル画面
			SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//ポリゴンカラーの設定
			DrawPolygon(
				TEX_1,//使うテクスチャ,
				0.f, //x座標,
				0.f,//y座標,
				1366,//テクスチャの表示する横の長さ,//元の画像の横の長さは32
				768,//テクスチャの表示する縦の長さ,//元の画像の縦の長さは32
				0,//元の画像の切り取り開始場所（横）（画像の左から数える）
				0,//元の画像の切り取り開始場所（縦）（画像の上から数える）
				800,//元の画像の切り取りたい幅
				600 //元の画像の切り取りたい高さ
			);

			//テクスチャピコピコ
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
					TEX_6,//使うテクスチャ,
					0.f, //x座標,
					0.f,//y座標,
					1366,//テクスチャの表示する横の長さ,//元の画像の横の長さは32
					768,//テクスチャの表示する縦の長さ,//元の画像の縦の長さは32
					0,//元の画像の切り取り開始場所（横）（画像の左から数える）
					0,//元の画像の切り取り開始場所（縦）（画像の上から数える）
					800,//元の画像の切り取りたい幅
					600 //元の画像の切り取りたい高さ
				);
			}
			//テクスチャピコピコ

			Updatesixyokika();//初期化処理
		}

		if (nflag == 1)
		{
			//ゲームプレイ
			
			DrawPolygon3D();//3D画像を表示(キューブ)
			
			DrawXmodel();//Xモデルを表示
			Drawbonbe();//ボンベを表示
			Drawcoin();//コインを表示
			DrawGrit();//線画像を表示
			DrawMesh();//地面を表示
			DrawPolygon(TEX_4, 10, 550, 250, 175, 0, 0, 1000, 500);//2D画像(UI)を表示//UIは一番下にしないと画像が透けてしまう。//768-175=593
			DrawScore(coinsu, 3, 300.0f, 300.0f, true);//スコアー表示
			DrawScore(zikan, 3, 0.0f, 0.0f, true);//時間表示
		}

		if (nflag == 2)
		{
			//ゲームクリアー
			SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//ポリゴンカラーの設定
															   //画像を表示
			DrawPolygon(
				TEX_2,//使うテクスチャ,
				0, //x座標,600
				0, //y座標,
				1366, //テクスチャの表示する横の長さ,//元の画像の横の長さは140
				768, //テクスチャの表示する縦の長さ,//元の画像の縦の長さは200
				0,//元の画像の切り取り開始場所（横）（画像の左から数える）
				0,//元の画像の切り取り開始場所（縦）（画像の上から数える）
				1280,//元の画像の切り取りたい幅
				720//元の画像の切り取りたい高さ
			);

			SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//ポリゴンカラーの設定
															   //画像を表示
			DrawPolygon(
				TEX_7,//使うテクスチャ,
				445, //x座標,600
				540, //y座標,
				200, //テクスチャの表示する横の長さ,//元の画像の横の長さは140
				100, //テクスチャの表示する縦の長さ,//元の画像の縦の長さは200
				0,//元の画像の切り取り開始場所（横）（画像の左から数える）
				0,//元の画像の切り取り開始場所（縦）（画像の上から数える）
				800,//元の画像の切り取りたい幅
				600//元の画像の切り取りたい高さ
			);
			DrawScore(coinsu, 3, 660.0f, 550.0f, true);//スコアー表示
			DrawScore(zikan, 3, 0.0f, 0.0f, true);//時間表示

		
		}

		if (nflag == 3)
		{
			//ゲームオーバー
			SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//ポリゴンカラーの設定
															   //画像を表示
			DrawPolygon(
				TEX_3,//使うテクスチャ,
				0, //x座標,100
				0, //y座標,50
				1366, //テクスチャの表示する横の長さ,//元の画像の横の長さは
				768, //テクスチャの表示する縦の長さ,//元の画像の縦の長さは
				0,//元の画像の切り取り開始場所（横）（画像の左から数える）
				0,//元の画像の切り取り開始場所（縦）（画像の上から数える）
				1280,//元の画像の切り取りたい幅
				720//元の画像の切り取りたい高さ
			);

			SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//ポリゴンカラーの設定
															   //画像を表示
			DrawPolygon(
				TEX_7,//使うテクスチャ,
				445, //x座標,600
				540, //y座標,
				200, //テクスチャの表示する横の長さ,//元の画像の横の長さは140
				100, //テクスチャの表示する縦の長さ,//元の画像の縦の長さは200
				0,//元の画像の切り取り開始場所（横）（画像の左から数える）
				0,//元の画像の切り取り開始場所（縦）（画像の上から数える）
				800,//元の画像の切り取りたい幅
				600//元の画像の切り取りたい高さ
			);
			DrawScore(coinsu, 3, 660.0f, 550.0f, true);//スコアー表示
			DrawScore(zikan, 3, 0.0f, 0.0f, true);//時間表示


		}
		////////////////ここから↑の中身をいじる//この中にDraw系を入れる///////////////////////////////////		

	}//2
	g_pD3DDevice->EndScene();//Direct3Dによる描画の終了
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);//描画が終わってデバイスにプレゼントする
}//1



LPDIRECT3DDEVICE9 GetD3DDevice(void)
{//1
	return g_pD3DDevice;
}//1

 //タイトル画面
void gametitle(void) {
	//描画
	Draw();
}

//ゲーム画面
void gamestart(void) {
	//更新
	Update();
	//描画
	Draw();
}

//ゲームクリアー
void gameclear(void) {
	//描画
	Draw();
}

//ゲームオーバー
void gameover(void) {
	//描画
	Draw();
}

//main.hから数字を持ってくる関数
void getnum(int num)
{
	nflag = num;//main.hから数字を持ってきてnflagに入れる処理
}

//sixyokika.hから数字を持ってくる関数
void getcoin(int coinnum)
{
	coinsu = coinsu + coinnum;//sixyokika.hから数字を持ってきてcoinに入れる処理
}

//sixyokika.hから数字を持ってくる関数
void sixyokikacoin(int coinnum)
{
	coinsu = coinnum;//sixyokika.hから数字を持ってきてcoinに入れる処理
}

//sixyokika.hから数字を持ってくる関数
void getzikan(int zikannum)
{
	zikan = zikan + zikannum;//sixyokika.hから数字を持ってきてzikanに入れる処理
}

//sixyokika.hから数字を持ってくる関数
void sixyokikazikan(int zikannum)
{
	zikan = zikannum;//sixyokika.hから数字を持ってきてzikanに入れる処理
}
