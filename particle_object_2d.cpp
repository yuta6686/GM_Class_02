#include "particle_object_2d.h"

void ParticleObject_2D::Init()
{
	//	テクスチャ初期化--------------------------
	m_Textures.resize(m_TextureName.size());

	for (unsigned int i = 0; i < m_TextureName.size(); i++)
	{		
		m_Textures[i] = ResourceManger<Texture>::GetResource(m_TextureName[i].c_str());
	}

	//	頂点データ初期化
	VERTEX_3D vertex[4];
	vertex[0].Position = D3DXVECTOR3(-m_WidthHeight.x, -m_WidthHeight.y, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(m_WidthHeight.x, -m_WidthHeight.y, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-m_WidthHeight.x, m_WidthHeight.y, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(m_WidthHeight.x, m_WidthHeight.y, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//	頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = m_vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

//	シェーダ初期化---------------------------------------
	m_VertexShader =
		ResourceManger<VertexShader>::GetResource(VertexShader::GetFileNames()[SHADER_UNLIT]);
	m_PixelShader =
		ResourceManger<PixelShader>::GetResource(PixelShader::GetFileNames()[SHADER_UNLIT]);

//	パーティクルデータ初期化--------------------------------
	m_Particles.resize(PARTICLE_MAX);

	#pragma omp parallel for
	for (unsigned int i = 0; i < m_Particles.size(); i++) {
		m_Particles[i].status = 0;
		m_Particles[i].pos = { 0.0f,0.0f,0.0f };
		m_Particles[i].vel = { 0.0f,-0.5f,0.0f };
		m_Particles[i].rot = { 0.0f,0.0f,0.0f };
		m_Particles[i].acc = { 0.0f,0.1f,0.0f };
		m_Particles[i].m_SizeOverLifeTime_Start = 0.0f;
		m_Particles[i].m_SizeOverLifeTime_End = 1.0f;
		m_Particles[i].size = m_Particles[i].m_SizeOverLifeTime_Start;
		m_Particles[i].use = false;		
		m_Particles[i].col4 = m_Particles[i].m_Color4OverLifeTime_Start;
	}
}

void ParticleObject_2D::Uninit()
{
	m_VertexBuffer->Release();
}

void ParticleObject_2D::Update()
{
	for (unsigned int i = 0; i < m_Particles.size(); i++) {
		//	寿命で終了
		if (m_Particles[i].status >= m_Particles[i].life)
		{
			m_Particles[i].use = false;
			m_Particles[i].status = 0;
		}


		//	使われていなかったら戻る
		if (!m_Particles[i].use) continue;

		//	加速度
		m_Particles[i].vel += m_Particles[i].acc;

		//	速度
		m_Particles[i].pos += m_Particles[i].vel;

		//	回転速度
		m_Particles[i].rot += m_Particles[i].rot_vel;

		//	寿命に応じた色
		D3DXVec4Lerp(&m_Particles[i].col4,
			&m_Particles[i].m_Color4OverLifeTime_Start,
			&m_Particles[i].m_Color4OverLifeTime_End,
			(float)m_Particles[i].status / (float)m_Particles[i].life);

		//	寿命に応じたサイズ
		MyMath::FloatLerp(&m_Particles[i].size,
			&m_Particles[i].m_SizeOverLifeTime_Start,
			&m_Particles[i].m_SizeOverLifeTime_End,
			(float)m_Particles[i].status / (float)m_Particles[i].life);

		//	寿命測定
		m_Particles[i].status++;
	}
}

void ParticleObject_2D::Draw()
{


	//	シェーダ
	m_VertexShader->Draw();
	m_PixelShader->Draw();


	

	Renderer::SetAddBlend(true);

	for (unsigned int i= 0; i < m_Particles.size(); i++) {
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		vertex[0].Position = D3DXVECTOR3(-m_WidthHeight.x, -m_WidthHeight.y, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[0].Diffuse = m_Particles[i].col4;
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		
		vertex[1].Position = D3DXVECTOR3(m_WidthHeight.x, -m_WidthHeight.y, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[1].Diffuse = m_Particles[i].col4;
		vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
		
		vertex[2].Position = D3DXVECTOR3(-m_WidthHeight.x, m_WidthHeight.y, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[2].Diffuse = m_Particles[i].col4;
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		
		vertex[3].Position = D3DXVECTOR3(m_WidthHeight.x, m_WidthHeight.y, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[3].Diffuse = m_Particles[i].col4;
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		Renderer::SetWorldViewProjection2D();

		//ワールドマトリクス設定
		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale,
			m_Particles[i].size,
			m_Particles[i].size,
			m_Particles[i].size);
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Particles[i].rot.x,
			m_Particles[i].rot.y,
			m_Particles[i].rot.z);
		D3DXMatrixTranslation(&trans,
			m_Particles[i].pos.x,
			m_Particles[i].pos.y,
			m_Particles[i].pos.z
		);
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(&world);				

		//頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

		
		m_Textures[m_Particles[i].type]->Draw();
	}
	
	Renderer::SetAddBlend(false);
}

void ParticleObject_2D::DrawImgui()
{
}

void ParticleObject_2D::SetParticle_Rising()
{
	PARTICLE2D par;
	par.m_Color4OverLifeTime_Start = { 1.0f,1.0f,1.0f,1.0f };
	par.m_Color4OverLifeTime_End = { 0.0f,1.0f,1.0f,0.0f };
	par.col4 = par.m_Color4OverLifeTime_Start;
	par.life = 120;	
	par.pos.x = MyMath::Random(0.0f, (float)SCREEN_WIDTH);
	par.pos.y = SCREEN_HEIGHT;
	par.pos.z = 0.0f;
	par.vel.x = MyMath::Random(-1.0f,1.0f);
	par.vel.y = MyMath::Random(-10.0f,-1.0f);
	par.vel.z = 0.0f;
	par.rot = { 0.0f,0.0f,0.0f };
	par.rot_vel.z = MyMath::Random(-0.5f,0.5f);
	par.m_SizeOverLifeTime_End = 0.0f;
	par.m_SizeOverLifeTime_Start = 0.3f;
	par.size = par.m_SizeOverLifeTime_Start;
	par.acc = { 0.0f,0.0f,0.0f };
	par.status = 0;
	par.type = (rand() % 2) + PARTICLE_TYPE_2D_CIRCLE;
	par.use = true;	

	SetParticles(par);
}

void ParticleObject_2D::SetParticle_Descent(const D3DXVECTOR4& end_color)
{
	PARTICLE2D par;
	par.m_Color4OverLifeTime_Start = { 1.0f,1.0f,1.0f,1.0f };
	par.m_Color4OverLifeTime_End = end_color;
	par.col4 = par.m_Color4OverLifeTime_Start;
	par.life = 120;
	par.pos.x = MyMath::Random(0.0f, (float)SCREEN_WIDTH);
	par.pos.y = 0.0f;
	par.pos.z = 0.0f;
	par.vel.x = MyMath::Random(-1.0f, 1.0f);
	par.vel.y = MyMath::Random(1.0f, 10.0f);
	par.vel.z = 0.0f;
	par.rot = { 0.0f,0.0f,0.0f };
	par.rot_vel.z = MyMath::Random(-0.5f, 0.5f);
	par.m_SizeOverLifeTime_End = 0.0f;
	par.m_SizeOverLifeTime_Start = 0.3f;
	par.size = par.m_SizeOverLifeTime_Start;
	par.acc = { 0.0f,0.0f,0.0f };
	par.status = 0;
	par.type = rand() % PARTICLE_TYPE_2D_CIRCLE;
	par.use = true;

	SetParticles(par);
}

void ParticleObject_2D::SetParticle_Gather(const D3DXVECTOR4& end_color)
{
	PARTICLE2D par;
	par.m_Color4OverLifeTime_Start = end_color;
	par.m_Color4OverLifeTime_End = {1.0f,0.0f,0.0f,0.0f};
	par.col4 = par.m_Color4OverLifeTime_Start;
	par.life = 120;

	int rand_num = rand() % 4;
	switch (rand_num)
	{
	case 0:
		//	下
		par.pos.x = MyMath::Random(0.0f, (float)SCREEN_WIDTH);
		par.pos.y = SCREEN_HEIGHT;
		par.pos.z = 0.0f;
		break;
	case 1:
		//	上
		par.pos.x = MyMath::Random(0.0f, (float)SCREEN_WIDTH);
		par.pos.y = 0.0f;
		par.pos.z = 0.0f;
		break;
	case 2:
		//	右
		par.pos.x = SCREEN_WIDTH;
		par.pos.y = MyMath::Random(0.0f,(float)SCREEN_HEIGHT);
		par.pos.z = 0.0f;
		break;
	case 3:
		//	左
		par.pos.x = 0.0f;
		par.pos.y = MyMath::Random(0.0f, (float)SCREEN_HEIGHT);
		par.pos.z = 0.0f;
		break;
	default:
		break;
	}


	D3DXVECTOR3 dir = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f) - par.pos;

	par.vel = dir * MyMath::Random(0.001f,0.05f);

	par.rot = { 0.0f,0.0f,0.0f };
	par.rot_vel.z = MyMath::Random(-0.01f, 0.01f);
	par.m_SizeOverLifeTime_End = 0.0f;
	par.m_SizeOverLifeTime_Start = 0.3f;
	par.size = par.m_SizeOverLifeTime_Start;
	par.acc =  dir * -0.003f;
	par.status = 0;
	par.type = rand() % PARTICLE_TYPE_2D_MAX;
	par.use = true;

	SetParticles(par);
}

void ParticleObject_2D::SetParticle_Explosion(const D3DXVECTOR3& pos)
{
	PARTICLE2D par;
	par.m_Color4OverLifeTime_Start = { 1.0f,1.0f,1.0f,1.0f };
	par.m_Color4OverLifeTime_End = {1.0f,1.0f,1.0f,0.0f};
	par.col4 = par.m_Color4OverLifeTime_Start;
	par.life = 120;
	par.pos = pos;
	par.pos.x += MyMath::Random(-100.0f, 100.0f);
	par.pos.y += MyMath::Random(-50.0f, 50.0f);
	par.vel.x = MyMath::Random(-1.0f, 1.0f) * 5.0f;
	par.vel.y = MyMath::Random(-1.0f, 1.0f) * 5.0f;
	par.vel.z = 0.0f;
	par.rot = { 0.0f,0.0f,0.0f };
	par.rot_vel.z = MyMath::Random(-0.5f, 0.5f);
	par.m_SizeOverLifeTime_End = 0.0f;
	par.m_SizeOverLifeTime_Start = 0.3f;
	par.size = par.m_SizeOverLifeTime_Start;
	par.acc = { 0.0f,0.0f,0.0f };
	par.status = 0;
	par.type = rand() % PARTICLE_TYPE_2D_CIRCLE;
	par.use = true;

	SetParticles(par);
}

void ParticleObject_2D::SetParticles(const PARTICLE2D& particle)
{
	for (unsigned int i = 0; i < m_Particles.size(); i++) {
		if (m_Particles[i].use)continue;
		m_Particles[i] = particle;
		break;
	}
}
