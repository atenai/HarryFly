#include <d3dx9.h>
#include "Number.h"
#include "Polygon.h"
//void DrawNumber(int 表したい数, float 表示するX座標, float 表示するY座標)
void DrawNumber(int n, float x, float y)
{
	int nX=0, nY=0;
	if (n < 0 || n>9)
	{
		return;
	}
	if (n > 4)
	{
		nX = n - 5;
		nY = 1;
	}
	else
	{
		nX = n;
		nY = 0;
	}
	SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//ポリゴンカラーの設定
	DrawPolygon(TEX_5, x, y, NUMBER_WIDTH, NUMBER_HEIGHT, 0+29*nX, 0+32*nY, 29, 32);//テクスチャの描画
}