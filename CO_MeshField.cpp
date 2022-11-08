#include "CO_MeshField.h"
#include "DebugScene.h"
#include "player.h"


#define HASH_CODE_MAX       (256)
#define HASH_CODE_TABLE_NUM     (HASH_CODE_MAX*2)

int g_HashCode[HASH_CODE_TABLE_NUM] = {};

void CO_MeshField::Remap(const int& seed)
{
    SettingHash(seed);

    //  ��ŃR���|�[�l���g������
       //  ���_�o�b�t�@����
    {
        //  ��
        for (int x = 0; x <= VertexNum_Horizontal; x++)
        {
            //  �c
            for (int z = 0; z <= VertexNum_Virtical; z++)
            {
                float fx = (float)x / VertexNum_Horizontal * 4.0f;
                float fz = (float)z / VertexNum_Virtical * 4.0f;

                float y = powf(PerlinNoise(fx, fz) * 4.0f, 4.0f);
                m_Vertex[x][z].Position = D3DXVECTOR3((x - 10) * 5.0f, y, (z - 10) * -5.0f);
                m_Vertex[x][z].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
                m_Vertex[x][z].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
                m_Vertex[x][z].TexCoord = D3DXVECTOR2(0.5f * x, z * 0.5f);
            }
        }

        for (int x = 1; x <= VertexNum_Horizontal - 1; x++)
        {
            //  �c
            for (int z = 1; z <= VertexNum_Virtical - 1; z++)
            {
                D3DXVECTOR3 vx, vz, vn;
                vx = m_Vertex[x + 1][z].Position
                    - m_Vertex[x - 1][z].Position;
                vz = m_Vertex[x][z - 1].Position
                    - m_Vertex[x][z + 1].Position;

                D3DXVec3Cross(&vn, &vz, &vx);
                D3DXVec3Normalize(&vn, &vn);
                m_Vertex[x][z].Normal = vn;
            }
        }

        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(VERTEX_3D) * VertexNum_Horizontal * VertexNum_Virtical;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.pSysMem = m_Vertex;

        Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
    }

    //  �C���f�b�N�X�o�b�t�@���� 
    {
        unsigned int index[((VertexNum_Virtical + 2) * 2) * VertexNum_Horizontal - 2];
        int i = 0;
        for (int x = 0; x < VertexNum_Horizontal; x++)
        {
            for (int z = 0; z < VertexNum_Virtical + 1; z++) {
                index[i] = x * (VertexNum_Virtical + 1) + z;
                i++;

                index[i] = (x + 1) * (VertexNum_Virtical + 1) + z;
                i++;
            }
            if (x == 19)
                break;

            index[i] = (x + 1) * (VertexNum_Horizontal + 1) + VertexNum_Virtical;
            i++;

            index[i] = (x + 1) * (VertexNum_Horizontal + 1);
            i++;
        }

        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(unsigned int) * (((VertexNum_Virtical + 2) * 2) * VertexNum_Horizontal - 2);
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.pSysMem = index;

        Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
    }
}

void CO_MeshField::Move()
{
    static float movex = 0.0f;

    //  ��ŃR���|�[�l���g������
       //  ���_�o�b�t�@����
    {
        //  ��
        for (int x = 0; x <= VertexNum_Horizontal; x++)
        {
            //  �c
            for (int z = 0; z <= VertexNum_Virtical; z++)
            {
                float fx = (float)x / VertexNum_Horizontal * mWidth + movex;
                float fz = (float)z / VertexNum_Virtical * mDepth;

                float y = powf(fabsf( PerlinNoise(fx, fz) * mHeightMul), mHeightPower);
                m_Vertex[x][z].Position = D3DXVECTOR3((x - 10) * 5.0f, y, (z - 10) * -5.0f);
                m_Vertex[x][z].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
                m_Vertex[x][z].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
                m_Vertex[x][z].TexCoord = D3DXVECTOR2(0.5f * x, z * 0.5f);
            }
        }

        for (int x = 1; x <= VertexNum_Horizontal - 1; x++)
        {
            //  �c
            for (int z = 1; z <= VertexNum_Virtical - 1; z++)
            {
                D3DXVECTOR3 vx, vz, vn;
                vx = m_Vertex[x + 1][z].Position
                    - m_Vertex[x - 1][z].Position;
                vz = m_Vertex[x][z - 1].Position
                    - m_Vertex[x][z + 1].Position;

                D3DXVec3Cross(&vn, &vz, &vx);
                D3DXVec3Normalize(&vn, &vn);
                m_Vertex[x][z].Normal = vn;
            }
        }

        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(VERTEX_3D) * VertexNum_Horizontal * VertexNum_Virtical;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.pSysMem = m_Vertex;

        Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
    }

    //  �C���f�b�N�X�o�b�t�@���� 
    {
        unsigned int index[((VertexNum_Virtical + 2) * 2) * VertexNum_Horizontal - 2];
        int i = 0;
        for (int x = 0; x < VertexNum_Horizontal; x++)
        {
            for (int z = 0; z < VertexNum_Virtical + 1; z++) {
                index[i] = x * (VertexNum_Virtical + 1) + z;
                i++;

                index[i] = (x + 1) * (VertexNum_Virtical + 1) + z;
                i++;
            }
            if (x == 19)
                break;

            index[i] = (x + 1) * (VertexNum_Horizontal + 1) + VertexNum_Virtical;
            i++;

            index[i] = (x + 1) * (VertexNum_Horizontal + 1);
            i++;
        }

        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(unsigned int) * (((VertexNum_Virtical + 2) * 2) * VertexNum_Horizontal - 2);
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.pSysMem = index;

        Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
    }

    movex += mMoveSpeed;
}

void CO_MeshField::DrawImgui()
{
    if (ImGui::CollapsingHeader("MeshField")) {
        ImGui::Text("Height:%.2f", GetHeight(mpScene->GetGameObject<Player>()->GetPosition()));
        ImGui::Text("Bloeck X:%d, Z:%d", GetBloeckNumX(mpScene->GetGameObject<Player>()->GetPosition()), 
            GetBloeckNumZ(mpScene->GetGameObject<Player>()->GetPosition()));

        if (ImGui::TreeNode("Parameter")) {
            ImGui::SliderFloat("MoveSpeed", &mMoveSpeed, -0.02f, 0.02f, "%.4f");
            ImGui::SliderFloat("Height Power", &mHeightPower, 0.0f, 10.0f, "%.2f");
            ImGui::SliderFloat("Height Mul", &mHeightMul, 0.0f, 10.0f, "%.2f");
            ImGui::SliderFloat("Width", &mWidth, 0.0f, 10.0f, "%.2f");
            ImGui::SliderFloat("Depth", &mDepth, 0.0f, 10.0f, "%.2f");

            ImGui::TreePop();
        }
    }
}

void CO_MeshField::Init()
{
    SettingHash(MyMath::Random(0,100));

    //  ��ŃR���|�[�l���g������
    //  ���_�o�b�t�@����
    {
        //  ��
        for (int x = 0; x <= VertexNum_Horizontal; x++)
        {
            //  �c
            for (int z = 0; z <= VertexNum_Virtical; z++)
            {
                float fx = (float)x / VertexNum_Horizontal * 4.0f;
                float fz = (float)z / VertexNum_Virtical * 4.0f;

                float y = powf(PerlinNoise(fx, fz) * 4.0f, 4.0f);
                m_Vertex[x][z].Position = D3DXVECTOR3((x - 10) * 5.0f, y, (z - 10) * -5.0f);
                m_Vertex[x][z].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
                m_Vertex[x][z].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
                m_Vertex[x][z].TexCoord = D3DXVECTOR2(0.5f * x, z * 0.5f);
            }
        }

        for (int x = 1; x <= VertexNum_Horizontal-1; x++)
        {
            //  �c
            for (int z = 1; z <= VertexNum_Virtical-1; z++)
            {
                D3DXVECTOR3 vx, vz, vn;
                vx = m_Vertex[x + 1][z].Position
                    - m_Vertex[x - 1][z].Position;
                vz = m_Vertex[x][z - 1].Position
                    - m_Vertex[x][z + 1].Position;

                D3DXVec3Cross(&vn, &vz, &vx);
                D3DXVec3Normalize(&vn, &vn);
                m_Vertex[x][z].Normal = vn;
            }
        }

        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(VERTEX_3D) * VertexNum_Horizontal * VertexNum_Virtical;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.pSysMem = m_Vertex;

        Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
    }

    //  �C���f�b�N�X�o�b�t�@���� 
    {
        unsigned int index[((VertexNum_Virtical + 2) * 2) * VertexNum_Horizontal - 2];
        int i = 0;
        for (int x = 0; x < VertexNum_Horizontal; x++)
        {
            for (int z = 0; z < VertexNum_Virtical + 1; z++) {
                index[i] = x * (VertexNum_Virtical + 1) + z;
                i++;

                index[i] = (x + 1) * (VertexNum_Virtical + 1) + z;
                i++;
            }
            if (x == VertexNum_Horizontal-1)
                break;

            index[i] = (x + 1) * (VertexNum_Horizontal + 1) + VertexNum_Virtical;
            i++;

            index[i] = (x + 1) * (VertexNum_Horizontal + 1);
            i++;
        }

        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(unsigned int) * (((VertexNum_Virtical + 2) * 2) * VertexNum_Horizontal - 2);
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.pSysMem = index;

        Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
    }

    //�e�N�X�`���ǂݍ���
    // �ʏ�e�N�X�`��1����
    D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
        "asset\\texture\\water.png",
        NULL,
        NULL,
        &m_Texture,
        NULL);

    assert(m_Texture);

    // �ʏ�e�N�X�`��2����
    D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
        "asset\\texture\\water1.png",
        NULL,
        NULL,
        &m_Texture2,
        NULL);

    assert(m_Texture2);

    // �m�[�}���e�N�X�`��
    D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
        "asset\\texture\\normalmap.png",
        NULL,
        NULL,
        &m_NormalTexture,
        NULL);

    assert(m_NormalTexture);

    // �s�N�Z���e�N�X�`��
    D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
        "asset\\texture\\pixelNoiseColor.png",
        NULL,
        NULL,
        &m_PixelNoiseTexture,
        NULL);

    assert(m_PixelNoiseTexture);


    m_VertexShader =
        ResourceManger<VertexShader>::GetResource("MeshFieldVS.cso");
    m_PixelShader =
        ResourceManger<PixelShader>::GetResource("MeshFieldPS.cso");

    m_Position = { 0.0f,0.0f,0.0f };
    m_Rotation = { 0.0f,0.0f,0.0f };
    float sca = 1.0f;
    m_Scale = { sca,sca,sca };

    ComponentObject::Init();

    mpScene = Manager::GetScene();

    m_TypeName = "MeshField";
}

void CO_MeshField::Uninit()
{
    m_VertexBuffer->Release();
    m_IndexBuffer->Release();
    m_Texture->Release();
    m_Texture2->Release();
    m_NormalTexture->Release();
    m_PixelNoiseTexture->Release();
}

void CO_MeshField::Update()
{
    if (GetKeyboardTrigger(DIK_R))
    {
        static int seed = 0;
        Remap(seed);
        seed++;
    }


    Move();
    

    ComponentObject::Update();
}
void CO_MeshField::Draw()
{
    m_VertexShader->Draw();
    m_PixelShader->Draw();

    //���[���h�}�g���N�X�ݒ�
    D3DXMATRIX world, scale, rot, trans;
    D3DXMatrixScaling(&scale,
        m_Scale.x,
        m_Scale.y,
        m_Scale.z);
    D3DXMatrixRotationYawPitchRoll(&rot,
        m_Rotation.x,
        m_Rotation.y,
        m_Rotation.z);
    D3DXMatrixTranslation(&trans,
        m_Position.x,
        m_Position.y,
        m_Position.z);
    world = scale * rot * trans;
    Renderer::SetWorldMatrix(&world);

    //  ���_�o�b�t�@�ݒ�

    UINT stride = sizeof(VERTEX_3D);
    UINT offset = 0;
    Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

    //  �C���f�b�N�X�o�b�t�@�ݒ�
    Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

    //  �}�e���A���ݒ�
    MATERIAL material;
    ZeroMemory(&material, sizeof(material));
    material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    Renderer::SetMaterial(material);

    //  �e�N�X�`���ݒ�
    Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
    Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_NormalTexture);
    Renderer::GetDeviceContext()->PSSetShaderResources(2, 1, &m_PixelNoiseTexture);
    Renderer::GetDeviceContext()->PSSetShaderResources(3, 1, &m_Texture2);

    //  �v���~�e�B�u�g�|���W�ݒ�
    Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    //  �|���S���`��
    Renderer::GetDeviceContext()->DrawIndexed((VertexNum_Horizontal + 2) * VertexNum_Virtical - 2, 0, 0);
}


void CO_MeshField::SettingHash(unsigned int seed)
{
    // �������C�u����������.
        srand(seed);

        
    //�n�b�V���R�[�h������.
    memset(g_HashCode, 0, sizeof(unsigned int) * _countof(g_HashCode));

    //�����_���e�[�u������.
    const int TABLE_NUM = HASH_CODE_MAX;
    unsigned int randomTable[TABLE_NUM] = {};
    for (int i = 0; i < _countof(randomTable); ++i) {
        randomTable[i] = rand() % HASH_CODE_MAX;
    }

    //�n�b�V���R�[�h����.
    for (int i = 0; i < _countof(g_HashCode); ++i) {
        g_HashCode[i] = randomTable[i % TABLE_NUM];
    }
}

unsigned int CO_MeshField::GetHash(int x, int y)
{
    x %= HASH_CODE_MAX;
    y %= HASH_CODE_MAX;
    return g_HashCode[x + g_HashCode[y]];
}



float CO_MeshField::Fade(float t)
{
    return (6 * powf(t, 5) - 15 * powf(t, 4) + 10 * powf(t, 3));
}


float CO_MeshField::Grad(unsigned int hash, float a, float b)
{
    unsigned int key = hash % 0x4;
    switch (key)
    {
    case 0x0:   return a;   //a * 1.0f + b * 0.0f.
    case 0x1:   return -a;  //a * -1.0f + b * 0.0f.
    case 0x2:   return -b;  //a * 0.0f + b * -1.0f.
    case 0x3:   return b;   //a * 0.0f + b * 1.0f.
    };
    return 0.0f;
}

float CO_MeshField::PerlinNoise(float x, float y)
{
    //�������Ə������ɕ�����.
    int xi = (int)floorf(x);
    int yi = (int)floorf(y);
    float xf = x - xi;
    float yf = y - yi;

    //�i�q�_����n�b�V�������o���C���̒l����Ɍ��z���擾����.
    float a00 = Grad(GetHash(xi, yi), xf, yf);
    float a10 = Grad(GetHash(xi + 1, yi), xf - 1.0f, yf);
    float a01 = Grad(GetHash(xi, yi + 1), xf, yf - 1.0f);
    float a11 = Grad(GetHash(xi + 1, yi + 1), xf - 1.0f, yf - 1.0f);

    //��Ԃ�������.
    xf = Fade(xf);
    yf = Fade(yf);

    //�ʒu�ɍ��킹�Ċi�q�_�̂ǂ̓_�����ԉe�����󂯂邩�����߂�.
    //(���z�֐����œ��ς�����Ă���̂ŁC�x�N�g���̌����ɂ���Ă͕��̒l���o��D�͈͂�-1.0f~1.0f).
    //(�Ȃ̂ŁC���̒l�ɂ��邽�߂�1.0f�𑫂���2.0f�Ŋ����Ă���).
    return Lerp(Lerp(a00, a10, xf), Lerp(a01, a11, xf), yf);
}




float CO_MeshField::valueNoise(float x,float y)
{

    //�������Ə������ɕ�����.
    int xi = (int)floorf(x);
    int yi = (int)floorf(y);
    float xf = x - xi;
    float yf = y - yi;

    //�i�q�_�����o��.
    float a00 = GetValue(xi, yi);
    float a10 = GetValue(xi + 1, yi);
    float a01 = GetValue(xi, yi + 1);
    float a11 = GetValue(xi + 1, yi + 1);

    //�����������g���Ă��̂܂ܐ��`��Ԃ��Ă��܂��Ɛ܂���O���t�ɂȂ��Ă��܂��̂�.
    //���`��Ԃ���O�ɏ����������܎���Ԋ֐��Řc�߂��Ⴄ.
    xf = Fade(xf);
    yf = Fade(yf);

    //�ʒu����ɁC�e�i�q�_����̉e�����l�������l���Z�o����.
    return Lerp(Lerp(a00, a10, xf), Lerp(a01, a11, xf), yf);
}

float CO_MeshField::GetValue(int x, int y)
{
    return (float)GetHash(x, y) / (float)(HASH_CODE_MAX - 1);
}
int CO_MeshField::GetBloeckNumX(const D3DXVECTOR3& Position)
{
    return Position.x / 5.0f + 10.0f;
}
int CO_MeshField::GetBloeckNumZ(const D3DXVECTOR3& Position)
{
    return Position.z / -5.0f + 10.0f;
}

float CO_MeshField::GetHeight(const D3DXVECTOR3& Position)
{
    int x, z;

    //  �u���b�N�ԍ��Z�o
    x = Position.x / 5.0f + 10.0f;
    z = Position.z / -5.0f + 10.0f;

    D3DXVECTOR3 pos0, pos1, pos2, pos3;

    pos0 = m_Vertex[x][z].Position;
    pos1 = m_Vertex[x + 1][z].Position;
    pos2 = m_Vertex[x][z + 1].Position;
    pos3 = m_Vertex[x + 1][z + 1].Position;

    D3DXVECTOR3 v12, v1p, c;

    v12 = pos2 - pos1;
    v1p = Position - pos1;

    D3DXVec3Cross(&c, &v12, &v1p);

    float py;
    D3DXVECTOR3 n;

    if (c.y > 0.0f)
    {
        //  ����|���S��
        D3DXVECTOR3 v10;
        v10 = pos0 - pos1;
        D3DXVec3Cross(&n, &v10, &v12);
    }
    else
    {
        //  �E���|���S��
        D3DXVECTOR3 v13;
        v13 = pos3 - pos1;
        D3DXVec3Cross(&n, &v12, &v13);
    }

    //  �����擾
    py = -((Position.x - pos1.x) * n.x
        + (Position.z - pos1.z) * n.z) / n.y + pos1.y;

    return py;
}



float CO_MeshField::Lerp(float a, float b, float t)
{
    return (a + (b - a) * t);
}
