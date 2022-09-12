#include "AnimationModel.h"
#include "renderer.h"

void AnimationModel::Load(const char* FileName)
{
	const std::string modelPath(FileName);

	m_AiScene = aiImportFile(FileName, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded);


	assert(m_AiScene);


	m_VertexBuffer = new ID3D11Buffer * [m_AiScene->mNumMeshes];
	m_IndexBuffer = new ID3D11Buffer * [m_AiScene->mNumMeshes];

	for (unsigned int m = 0; m < m_AiScene->mNumMeshes; m++) {
		aiMesh* mesh = m_AiScene->mMeshes[m];

		//	頂点バッファ生成
		{

			VERTEX_3D* vertex = new VERTEX_3D[mesh->mNumVertices];

			for (unsigned int v = 0; v < mesh->mNumVertices; v++) {
				vertex[v].Position = D3DXVECTOR3{ mesh->mVertices[v].x,mesh->mVertices[v].y,mesh->mVertices[v].z };
				vertex[v].Normal = D3DXVECTOR3{ mesh->mNormals[v].x,mesh->mNormals[v].y ,mesh->mNormals[v].z };
				vertex[v].TexCoord = D3DXVECTOR2{ mesh->mTextureCoords[0][v].x,mesh->mTextureCoords[0][v].y };
				vertex[v].Diffuse = D3DXVECTOR4{ 1.0f,1.0f,1.0f,1.0f };
			}

			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = sizeof(VERTEX_3D) * mesh->mNumVertices;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;


			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = vertex;

			Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer[m]);

			delete[] vertex;
		}

		//	インデックスバッファ生成
		{
			unsigned int* index = new unsigned int[mesh->mNumFaces * 3];

			for (unsigned int f = 0; f < mesh->mNumFaces; f++) {
				const aiFace* face = &mesh->mFaces[f];

				assert(face->mNumIndices == 3);

				index[f * 3 + 0] = face->mIndices[0];
				index[f * 3 + 1] = face->mIndices[1];
				index[f * 3 + 2] = face->mIndices[2];
			}

			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(unsigned int) * mesh->mNumFaces * 3;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = index;

			Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer[m]);

			delete[] index;
		}

	}

	//	テクスチャ読み込み
	for (unsigned int m = 0; m < m_AiScene->mNumMaterials; m++) {
		aiString path;

		if (m_AiScene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
		{
			if (path.data[0] == '*')
			{
				//	FBXファイル内から読み込み
				if (m_Texture[path.data] == NULL)
				{
					ID3D11ShaderResourceView* texture;
					int id = atoi(&path.data[1]);

					D3DX11CreateShaderResourceViewFromMemory(
						Renderer::GetDevice(),
						(const unsigned char*)m_AiScene->mTextures[id]->pcData,
						m_AiScene->mTextures[id]->mWidth,
						NULL, NULL, &texture, NULL);

					m_Texture[path.data] = texture;
				}
				else
				{
					//	外部ファイルから読み込み
				}
			}
			else
			{
				m_Texture[path.data] = NULL;
			}
		}
	}
}

void AnimationModel::Unload()
{
	for (unsigned int m = 0; m < m_AiScene->mNumMeshes; m++) {
		m_VertexBuffer[m]->Release();
		m_IndexBuffer[m]->Release();
	}

	delete[] m_VertexBuffer;
	delete[] m_IndexBuffer;

	///for (std::pair<std::string, ID3D11ShaderResourceView*> pair : m_Texture)
	for (std::pair<std::string, ID3D11ShaderResourceView*> pair : m_Texture)
	{
		if (pair.second == nullptr)continue;
		pair.second->Release();
	}

	aiReleaseImport(m_AiScene);
}

void AnimationModel::Update()
{
}

void AnimationModel::Draw()
{
	//	プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//	マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	for (unsigned int m = 0; m < m_AiScene->mNumMeshes; m++) {
		aiMesh* mesh = m_AiScene->mMeshes[m];
		aiMaterial* aimat = m_AiScene->mMaterials[mesh->mMaterialIndex];

		//	テクスチャ設定
		aiString path;
		aimat->GetTexture(aiTextureType_DIFFUSE, 0, &path);
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[path.data]);

		//	頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1,
			&m_VertexBuffer[m], &stride, &offset);

		//	インデックスバッファ設定
		Renderer::GetDeviceContext()->IASetIndexBuffer(
			m_IndexBuffer[m], DXGI_FORMAT_R32_UINT, 0);


		//	ポリゴン描画
		Renderer::GetDeviceContext()->DrawIndexed(mesh->mNumFaces * 3, 0, 0);
	}
}
