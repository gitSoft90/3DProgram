// カメラやライトのデータが使える様になる
#include "../inc_KdCommon.hlsli"
#include "inc_KdLessonShader.hlsli"

// 頂点シェーダから出力するデータ
struct VSOutput
{
	float4 Pos : SV_Position;
};

VSOutput main( float4 pos : POSITION )
{
	VSOutput Out;

	// 受け取った位置をそのまま渡す
	Out.Pos = pos;

	// ココ大事！（座標変換）
	Out.Pos = mul(pos,		g_mWorld);	// ローカル座標系 -> ワールド座標系へ変換
	Out.Pos = mul(Out.Pos,	g_mView);	// ワールド座標系 -> ビュー座標系へ変換
	Out.Pos = mul(Out.Pos,	g_mProj);	// ビュー座標系	  -> 射影座標系へ変換

	return Out;
}
