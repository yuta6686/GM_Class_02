// ���͗p�̍\���̒�`
struct BufInType
{
    float3 pos;
    float f;
    int status;
};

// �o�͗p�̍\���̒�`
struct BufOutType
{
    int i;
    int status;
};

struct PARTICLE
{

    int status; // ���
    int type;
    float3 pos; // �ʒu
    float3 vel; // ���x
    float3 acc; // �����x
    float3 rot; //	��]	
    float3 rot_vel;
    float size; // �傫��
    int life; // ���Ŏ���(�t���[����)
    bool use;
    bool use_torii;

    float4 col; // �F

    float4 m_ColorOverLifeTime_Start;
    float4 m_ColorOverLifeTime_End;

    float m_SizeOverLifeTime_Start;
    float m_SizeOverLifeTime_End;
};

// �ǂݎ���p�̍\�����o�b�t�@�[
// �A���I�[�_�[�h�A�N�Z�X�o�b�t�@�[�Ƃ��č쐬���ꂽ�o�b�t�@���g�p����
StructuredBuffer<BufInType> BufferIn : register(t0);

// �ǂݏ����\�ȍ\�����o�b�t�@�[
// �A���I�[�_�[�h�A�N�Z�X�o�b�t�@�[�Ƃ��č쐬���ꂽ�o�b�t�@���g�p����
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