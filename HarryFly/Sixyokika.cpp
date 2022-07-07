#include "Xmodel.h"
#include "Main.h"
#include "Camera.h"
#include "Sixyokika.h"

static int Ui = 0;//構造体をループさせるための変数


void Updatesixyokika(void)
{
	//初期化処理
	sixyokikacoin(0);//coinの数値をgetcoinに送る//スコアーの数字用箱の初期化
	getiou(0.0f, 0.0f, 0.0f);//Xモデルの移動の初期化
	sixyokikazikan(230);//atarizikanの数値をgetzikanに送る;//ゲームオーバー用の時間を計る箱の初期化
	getcamera();//カメラ初期化用関数
	for (Ui = 0; Ui < 6; Ui++)//構造体の数だけ回す 
	{
		sixyyokikadrawbonbe(Ui, true);//ボンベの初期化
		sixyyokikaataribonbe(Ui, true);//ボンベの初期化
		
	}
	for (Ui = 0; Ui < 10; Ui++)//構造体の数だけ回す 
	{
		
		sixyyokikadrawcoin(Ui, true);//コインの初期化
		sixyyokikaataricoin(Ui, true);//コインの初期化
	}
}
