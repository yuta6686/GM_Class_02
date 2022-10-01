// 入力用の構造体定義
struct BufInType
{
    int i;
    float f;
};

// 出力用の構造体定義
struct BufOutType
{
    int i;
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
    BufferOut[DTid.x].i = BufferIn[DTid.x].i + (int) BufferIn[DTid.x].f;
    
}