struct testin
{
    int a, b, c;
};
struct testout
{
    int a, b, c;
};

StructuredBuffer<testin> TestIn : register(t0);
RWStructuredBuffer<testout> TestOut : register(u0);

[numthreads(2, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    TestOut[DTid.x].a = TestIn[DTid.x].a + 1;
    TestOut[DTid.x].b = TestIn[DTid.x].b + 2;
    TestOut[DTid.x].c = TestIn[DTid.x].c + 3;
}