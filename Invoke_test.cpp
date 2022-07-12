//#include "Invoke_test.h"
//#include "ResourceManager.h"
//
//void Invoke_test::Init()
//{
//	m_Model = ResourceManger<Model>::GetResource("asset\\model\\cylinder.obj");
//
//	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
//
//
//
//	m_VertexShader = ResourceManger<VertexShader>::GetResource("vertexLightingVS.cso");
//	m_PixelShader = ResourceManger<PixelShader>::GetResource("vertexLightingPS.cso");
//}
//
//void Invoke_test::Uninit()
//{
//}
//
//void Invoke_test::Update()
//{
//	GameObject_Invoke::Update();
//}
//
//void Invoke_test::Draw()
//{	
//	//VertexShaderのDraw読んでからPixelShaderのDraw
//	m_VertexShader->Draw();
//	m_PixelShader->Draw();
//
//
//	//ワールドマトリクス設定
//	D3DXMATRIX world, scale, rot, trans;
//	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
//	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
//	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
//	world = scale * rot * trans;
//	Renderer::SetWorldMatrix(&world);
//
//
//	m_Model->Draw();
//}
//
//void Invoke_test::TestMove()
//{
//	m_Position.x += 1.0f;	
//}
