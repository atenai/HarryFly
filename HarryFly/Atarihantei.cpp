//=======================================================================================
//						あたり判定描画
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
static float atariyokoidou = 0.0f;//あたり判定用横移動の箱
static float ataritateidou = 0.0f;//あたり判定用縦移動の箱
static float atariokuidou = 0.0f;//あたり判定用奥移動の箱

//キューブ///////////////////////////////////
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
//キューブ///////////////////////////////////



//時間
static int atarizikan = 0;

//構造体を回す（ループ）させるための変数
static int Ui = 0;//構造体をループさせるための変数
//ボンベ///////////////////////////////////////
typedef struct 
{
	float ataribonbex;//ボンベの座標x
	float ataribonbey;//ボンベの座標y
	float ataribonbez;//ボンベの座標z
	bool bHitbonbe;//あたり判定
	bool tadanbonbe;//多段ヒット修正
}BONBE_ATARI;

static BONBE_ATARI Bonbeatari[6];//構造体でアイテムをいくつ作るかを宣言
//ボンベ///////////////////////////////////////

//コイン///////////////////////////////////////
//コイン
static int coin = 0;

typedef struct
{
	float ataricoinx;//ボンベの座標x
	float ataricoiny;//ボンベの座標y
	float ataricoinz;//ボンベの座標z
	bool bHitcoin;//あたり判定
	bool tadancoin;//多段ヒット修正
}COIN_ATARI;

static COIN_ATARI Coinatari[10];//構造体でアイテムをいくつ作るかを宣言
//コイン///////////////////////////////////////


//あたり判定の計算公式
bool atari(float zibunx, float zibuny, float zibunz, float zibunhankei, float ITEMx, float ITEMy, float ITEMz, float ITEMhankei)
{

	float x = zibunx - ITEMx; //自分のx座標 - 敵のx座標 = xの自分と敵の距離を出す
	float y = zibuny - ITEMy; //自分のy座標 - 敵のy座標 = yの自分と敵の距離を出す
	float z = zibunz - ITEMz; //自分のz座標 - 敵のz座標 = zの自分と敵の距離を出す

	float zibunITEMkixyori = x*x + y*y + z*z; //底辺の2乗 + 対辺の2乗 = 斜辺の2乗がでる(自分と敵の距離を出す)

	float zibunITEMhankei = zibunhankei + ITEMhankei; //自分と敵の半径を足した長さを出す

	return zibunITEMkixyori < (zibunITEMhankei * zibunITEMhankei); //自分と敵の距離 < 自分と敵の半径を足した長さ の2乗(長さを比較し敵と自分の半径を足した長さよりも小さい場合Trueを返す)
}

void Initatari(void) 
{
	for (Ui = 0; Ui < 6; Ui++)//構造体の数だけ回す 
	{
		Bonbeatari[Ui].bHitbonbe = false;
		Bonbeatari[Ui].ataribonbex = 0;
		Bonbeatari[Ui].ataribonbey = 0;
		Bonbeatari[Ui].ataribonbez = 0;
		Bonbeatari[Ui].tadanbonbe = true;//多段ヒット修正
	}
	for (Ui = 0; Ui < 10; Ui++)//構造体の数だけ回す 
	{
		Coinatari[Ui].bHitcoin = false;
		Coinatari[Ui].ataricoinx = 0;
		Coinatari[Ui].ataricoiny = 0;
		Coinatari[Ui].ataricoinz = 0;
		Coinatari[Ui].tadancoin = true;//多段ヒット修正
	}
}

void Updateatari(void)
{
	////////////////あたり判定処理//////////////////////////////////////////////////
	//プレイヤー & キューブ1//////////////////////////////////////////
	bool bHit1 = atari(//atarihantei.h//あたり判定
		atariyokoidou, ataritateidou, atariokuidou, 3.5,//プレイヤーの位置
		ataricubex1, ataricubey1, ataricubez1, 0.5//キューブの位置
	);
	if (bHit1) 
	{
		//当たった場合の処理
		getnum(3);//ゲームオーバーに移動//main.hに数字が行き、その後main.cppに行く
		//atarizikan += 2;//時間を足す
		//getzikan(atarizikan);//atarizikanの数値をgetzikanに送る
		//atarizikan = 0;//atarizikanを0にする
		//coin += 1;//coinの数を足す
		//getcoin(coin);//coinの数値をgetcoinに送る
		//coin = 0;//coinを0にする
	}
	//プレイヤー & キューブ1//////////////////////////////////////////
	//プレイヤー & キューブ2//////////////////////////////////////////
	bool bHit2 = atari(//atarihantei.h//あたり判定
		atariyokoidou, ataritateidou, atariokuidou, 3.5,//プレイヤーの位置
		ataricubex2, ataricubey2, ataricubez2, 0.5//キューブの位置
	);
	if (bHit2)
	{
		//当たった場合の処理
		getnum(3);//ゲームオーバーに移動//main.hに数字が行き、その後main.cppに行く
		//atarizikan += 2;//時間を足す
		//getzikan(atarizikan);//atarizikanの数値をgetzikanに送る
		//atarizikan = 0;//atarizikanを0にする
		//coin += 1;//coinの数を足す
		//getcoin(coin);//coinの数値をgetcoinに送る
		//coin = 0;//coinを0にする
	}
	//プレイヤー & キューブ2//////////////////////////////////////////
	//プレイヤー & キューブ3//////////////////////////////////////////
	bool bHit3 = atari(//atarihantei.h//あたり判定
		atariyokoidou, ataritateidou, atariokuidou, 3.5,//プレイヤーの位置
		ataricubex3, ataricubey3, ataricubez3, 0.5//キューブの位置
	);
	if (bHit3) 
	{
		//当たった場合の処理
		getnum(3);//ゲームオーバーに移動//main.hに数字が行き、その後main.cppに行く
		//atarizikan += 2;//時間を足す
		//getzikan(atarizikan);//atarizikanの数値をgetzikanに送る
		//atarizikan = 0;//atarizikanを0にする
		//coin += 1;//coinの数を足す
		//getcoin(coin);//coinの数値をgetcoinに送る
		//coin = 0;//coinを0にする
	}
	//プレイヤー & キューブ3//////////////////////////////////////////
	//プレイヤー & キューブ4//////////////////////////////////////////
	bool bHit4 = atari(//atarihantei.h//あたり判定
		atariyokoidou, ataritateidou, atariokuidou, 3.5,//プレイヤーの位置
		ataricubex4, ataricubey4, ataricubez4, 0.5//キューブの位置
	);
	if (bHit4) 
	{
		//当たった場合の処理
		getnum(3);//ゲームオーバーに移動//main.hに数字が行き、その後main.cppに行く
		//atarizikan += 2;//時間を足す
		//getzikan(atarizikan);//atarizikanの数値をgetzikanに送る
		//atarizikan = 0;//atarizikanを0にする
		//coin += 1;//coinの数を足す
		//getcoin(coin);//coinの数値をgetcoinに送る
		//coin = 0;//coinを0にする
	}
	//プレイヤー & キューブ4//////////////////////////////////////////
	//プレイヤー & キューブ5//////////////////////////////////////////
	bool bHit5 = atari(//atarihantei.h//あたり判定
		atariyokoidou, ataritateidou, atariokuidou, 3.5,//プレイヤーの位置
		ataricubex5, ataricubey5, ataricubez5, 0.5//キューブの位置
	);
	if (bHit5)
	{
		//当たった場合の処理
		getnum(3);//ゲームオーバーに移動//main.hに数字が行き、その後main.cppに行く
		//atarizikan += 2;//時間を足す
		//getzikan(atarizikan);//atarizikanの数値をgetzikanに送る
		//atarizikan = 0;//atarizikanを0にする
		//coin += 1;//coinの数を足す
		//getcoin(coin);//coinの数値をgetcoinに送る
		//coin = 0;//coinを0にする
	}
	//プレイヤー & キューブ5//////////////////////////////////////////
	//プレイヤー & キューブ6//////////////////////////////////////////
	bool bHit6 = atari(//atarihantei.h//あたり判定
		atariyokoidou, ataritateidou, atariokuidou, 3.5,//プレイヤーの位置
		ataricubex6, ataricubey6, ataricubez6, 0.5//キューブの位置
	);
	if (bHit6) 
	{
		//当たった場合の処理
		getnum(3);//ゲームオーバーに移動//main.hに数字が行き、その後main.cppに行く
		//atarizikan += 2;//時間を足す
		//getzikan(atarizikan);//atarizikanの数値をgetzikanに送る
		//atarizikan = 0;//atarizikanを0にする
		//coin += 1;//coinの数を足す
		//getcoin(coin);//coinの数値をgetcoinに送る
		//coin = 0;//coinを0にする
	}
	//プレイヤー & キューブ6//////////////////////////////////////////

	//プレイヤー & ボンベ//////////////////////////////////////////
	for (Ui = 0; Ui < 6; Ui++)//構造体の数だけ回す 
	{
		Bonbeatari[Ui].bHitbonbe = atari(//atarihantei.h//あたり判定
			atariyokoidou, ataritateidou, atariokuidou, 3.5,//プレイヤーの位置
			Bonbeatari[Ui].ataribonbex, Bonbeatari[Ui].ataribonbey, Bonbeatari[Ui].ataribonbez, 0.5//ボンベの位置
		);
		if (Bonbeatari[Ui].bHitbonbe == true && Bonbeatari[Ui].tadanbonbe == true)
		{
			//当たった場合の処理
			//getnum(3);//ゲームオーバーに移動//main.hに数字が行き、その後main.cppに行く
			atarizikan += 50;//時間を足す
			getzikan(atarizikan);//atarizikanの数値をgetzikanに送る
			atarizikan = 0;//atarizikanを0にする
			//coin += 1;//coinの数を足す
			//getcoin(coin);//coinの数値をgetcoinに送る
			//coin = 0;//coinを0にする
			Bonbeatari[Ui].tadanbonbe = false;//多段ヒット修正
			hihixyouzibonbe(Ui, false);//ボンベの描画を非表示にする
		}
	}
	//プレイヤー & ボンベ//////////////////////////////////////////

	//プレイヤー & コイン//////////////////////////////////////////
	for (Ui = 0; Ui < 10; Ui++)//構造体の数だけ回す 
	{
		Coinatari[Ui].bHitcoin = atari(//atarihantei.h//あたり判定
			atariyokoidou, ataritateidou, atariokuidou, 3.5,//プレイヤーの位置
			Coinatari[Ui].ataricoinx, Coinatari[Ui].ataricoiny, Coinatari[Ui].ataricoinz, 0.5//ボンベの位置
		);
		if (Coinatari[Ui].bHitcoin == true && Coinatari[Ui].tadancoin == true)
		{
			//当たった場合の処理
			//getnum(3);//ゲームオーバーに移動//main.hに数字が行き、その後main.cppに行く
			//atarizikan += 10;//時間を足す
			//getzikan(atarizikan);//atarizikanの数値をgetzikanに送る
			//atarizikan = 0;//atarizikanを0にする
			coin += 1;//coinの数を足す
			getcoin(coin);//coinの数値をgetcoinに送る
			coin = 0;//coinを0にする
			Coinatari[Ui].tadancoin = false;//多段ヒット修正
			hihixyouzicoin(Ui, false);//ボンベの描画を非表示にする
		}
	}
	//プレイヤー & コイン//////////////////////////////////////////

	////////////////あたり判定処理//////////////////////////////////////////////////
}

//Xmodelのokuidouがxに入るtateidouがyに入るokuidouがzに入る
void atariidou(float x, float y, float z)
{
	atariyokoidou = x;//xの値をatariyokoidouに入れる
	ataritateidou = y;//yの値をataritateidouに入れる
	atariokuidou = z;//zの値をatariokuidouに入れる
}
//cube1のあたり判定に数値を送る
void ataricube1(float cx, float cy, float cz)
{
	ataricubex1 = cx;//cxの値をataricubexに入れる
	ataricubey1 = cy;//cyの値をataricubeyに入れる
	ataricubez1 = cz;//czの値をataricubezに入れる
}
//cube2のあたり判定に数値を送る
void ataricube2(float cx, float cy, float cz)
{
	ataricubex2 = cx;//cxの値をataricubexに入れる
	ataricubey2 = cy;//cyの値をataricubeyに入れる
	ataricubez2 = cz;//czの値をataricubezに入れる
}
//cube3のあたり判定に数値を送る
void ataricube3(float cx, float cy, float cz)
{
	ataricubex3 = cx;//cxの値をataricubexに入れる
	ataricubey3 = cy;//cyの値をataricubeyに入れる
	ataricubez3 = cz;//czの値をataricubezに入れる
}
//cube4のあたり判定に数値を送る
void ataricube4(float cx, float cy, float cz)
{
	ataricubex4 = cx;//cxの値をataricubexに入れる
	ataricubey4 = cy;//cyの値をataricubeyに入れる
	ataricubez4 = cz;//czの値をataricubezに入れる
}
//cube5のあたり判定に数値を送る
void ataricube5(float cx, float cy, float cz)
{
	ataricubex5 = cx;//cxの値をataricubexに入れる
	ataricubey5 = cy;//cyの値をataricubeyに入れる
	ataricubez5 = cz;//czの値をataricubezに入れる
}
//cube6のあたり判定に数値を送る
void ataricube6(float cx, float cy, float cz)
{
	ataricubex6 = cx;//cxの値をataricubexに入れる
	ataricubey6 = cy;//cyの値をataricubeyに入れる
	ataricubez6 = cz;//czの値をataricubezに入れる
}

//ボンベのあたり判定に数値を送る
void ataribonbe(int bonbesu, float ix, float iy, float iz)
{
		Bonbeatari[bonbesu].ataribonbex = ix;//ixの値をataribonbexに入れる
		Bonbeatari[bonbesu].ataribonbey = iy;//iyの値をataribonbeyに入れる
		Bonbeatari[bonbesu].ataribonbez = iz;//izの値をataribonbezに入れる
}

void sixyyokikaataribonbe(int bonbesu, bool ataribonbe)
{
	Bonbeatari[bonbesu].tadanbonbe = ataribonbe;
}

//コインのあたり判定に数値を送る
void ataricoin(int coinsu, float ix, float iy, float iz)
{
	Coinatari[coinsu].ataricoinx = ix;//ixの値をataricoinxに入れる
	Coinatari[coinsu].ataricoiny = iy;//iyの値をataricoinyに入れる
	Coinatari[coinsu].ataricoinz = iz;//izの値をataricoinzに入れる
}

void sixyyokikaataricoin(int coinsu, bool ataricoin)
{
	Coinatari[coinsu].tadancoin = ataricoin;
}