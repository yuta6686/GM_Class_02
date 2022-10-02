// 入力用の構造体定義
struct BufInType
{
    float3 pos;
    float f;
    int status;
};

// 出力用の構造体定義
struct BufOutType
{
    int i;
    int status;
};

struct PARTICLE
{

    int status; // 状態
    int type;
    float3 pos; // 位置
    float3 vel; // 速度
    float3 acc; // 加速度
    float3 rot; //	回転	
    float3 rot_vel;
    float size; // 大きさ
    int life; // 消滅時間(フレーム数)
    bool use;
    bool use_torii;

    float4 col; // 色

    float4 m_ColorOverLifeTime_Start;
    float4 m_ColorOverLifeTime_End;

    float m_SizeOverLifeTime_Start;
    float m_SizeOverLifeTime_End;
};

// 読み取り専用の構造化バッファー
// アンオーダードアクセスバッファーとして作成されたバッファを使用する
StructuredBuffer<BufInType> BufferIn : register(t0);

// 読み書き可能な構造化バッファー
// アンオーダードアクセスバッファーとして作成されたバッファを使用する
RWStructuredBuffer<BufOutType> BufferOut : register(u0);

[numthreads(2, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    //BufferOut[DTid.x].i = BufferIn[DTid.x].i + (int) BufferIn[DTid.x].f + 5;
    BufferOut[DTid.x].i = BufferIn[DTid.x].pos.x
    + BufferIn[DTid.x].pos.y * 2
    + BufferIn[DTid.x].pos.z * 3 + 1;
    
    BufferOut[DTid.x].status = BufferIn[DTid.x].status + 1;
}