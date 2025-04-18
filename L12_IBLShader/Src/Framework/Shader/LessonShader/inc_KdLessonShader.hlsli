// 定数バッファ(オブジェクト単位)
cbuffer cbObject : register(b0)
{
	float2	g_UVOffset;
	float2	g_UVTiling;

	// アウトライン描画フラグ
	int		g_EnableOutLineDraw;
};

// 定数バッファ(メッシュ単位)
cbuffer cbMesh : register(b1)
{
	// オブジェクト情報
	row_major float4x4 g_mWorld;	// ワールド変換行列
};

cbuffer cbMaterial : register(b2)
{
	float4	g_BaseColor;		// ベース色
	float3	g_Emissive;			// 自己発光色
	float	g_Metallic;			// 金属度
	float	g_Roughness;		// 粗さ
};

// 頂点シェーダから出力するデータ
struct VSOutput
{
	float4 Pos	 : SV_Position;	// 射影座標
	float3 wPos  : TEXCOORD0;	// ワールド3D座標

	float2 UV	 : TEXCOORD1;	// UV座標
	float4 Color : TEXCOORD2;	// 色

	float3 wN	 : TEXCOORD3;	// ワールド法線
	float3 wT	 : TEXCOORD4;	// ワールド接線
	float3 wB	 : TEXCOORD5;	// ワールド従法線

	float2 UV2	 : TEXCOORD6;	// UV座標（その２）
};
