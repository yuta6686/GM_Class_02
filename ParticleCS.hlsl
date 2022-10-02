struct PARTICLE
{
    int status;
    int life;

    float size;
    float m_SizeOverLifeTime_Start;
    float m_SizeOverLifeTime_End;

    bool use;
    float3 acc;
    float3 vel;
    float3 pos;
    float4 col;
    float3 rot; //	回転	
    float3 rot_vel;    
    
    float4 m_ColorOverLifeTime_Start;
    float4 m_ColorOverLifeTime_End;
};


// 読み取り専用の構造化バッファー
// アンオーダードアクセスバッファーとして作成されたバッファを使用する
StructuredBuffer<PARTICLE> In : register(t0);

// 読み書き可能な構造化バッファー
// アンオーダードアクセスバッファーとして作成されたバッファを使用する
RWStructuredBuffer<PARTICLE> Out : register(u0);

[numthreads(2, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
   
    //Out[DTid.x] = In[DTid.x];
    Out[DTid.x].status = In[DTid.x].status + 1;
    
    Out[DTid.x].acc = In[DTid.x].acc;
    Out[DTid.x].col = In[DTid.x].col;
    Out[DTid.x].life = In[DTid.x].life;
    Out[DTid.x].m_ColorOverLifeTime_End = In[DTid.x].m_ColorOverLifeTime_End;
    Out[DTid.x].m_ColorOverLifeTime_Start = In[DTid.x].m_ColorOverLifeTime_Start;
    Out[DTid.x].m_SizeOverLifeTime_End = In[DTid.x].m_SizeOverLifeTime_End;
    Out[DTid.x].m_SizeOverLifeTime_Start = In[DTid.x].m_SizeOverLifeTime_Start;
    Out[DTid.x].pos = In[DTid.x].pos;
    Out[DTid.x].rot = In[DTid.x].rot;
    Out[DTid.x].rot_vel = In[DTid.x].rot_vel;
    Out[DTid.x].size = In[DTid.x].size;    
    Out[DTid.x].use = In[DTid.x].use;
    
    if (Out[DTid.x].use == false)
        return;
    
    Out[DTid.x].vel = In[DTid.x].vel;    
    Out[DTid.x].vel += Out[DTid.x].acc;
    Out[DTid.x].pos += Out[DTid.x].vel;
    Out[DTid.x].rot += Out[DTid.x].rot_vel;
    
    float time = (float)Out[DTid.x].status / (float)Out[DTid.x].life;
    Out[DTid.x].col = lerp(Out[DTid.x].m_ColorOverLifeTime_Start, Out[DTid.x].m_ColorOverLifeTime_End
    , time);
    
    
    Out[DTid.x].size = lerp(Out[DTid.x].m_SizeOverLifeTime_Start, Out[DTid.x].m_SizeOverLifeTime_End, pow(time, 2.0f));
    
    
    //Out[DTid.x].vel += Out[DTid.x].acc;
    //Out[DTid.x].pos += Out[DTid.x].vel;
    //Out[DTid.x].rot += Out[DTid.x].rot_vel;
    
    //Out[DTid.x].col =
    //lerp(Out[DTid.x].m_ColorOverLifeTime_Start, Out[DTid.x].m_ColorOverLifeTime_End, (float) Out[DTid.x].status / (float) Out[DTid.x].life);
    
    
    //Out[DTid.x].size =     
    //lerp(Out[DTid.x].m_SizeOverLifeTime_Start, Out[DTid.x].m_SizeOverLifeTime_End,
    //pow((float) Out[DTid.x].status / (float) Out[DTid.x].life, 2.0f));

    //Out[DTid.x].status++;

}