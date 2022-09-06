#pragma once

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"

#include "main.h"
#include "renderer.h"
#include "Resource.h"

#pragma comment(lib,"assimp.lib")

class AnimationModel 
	:public Resource
{
private:
	const aiScene* m_AiScene = NULL;
	ID3D11Buffer** m_VertexBuffer;
	ID3D11Buffer** m_IndexBuffer;
public:
	void Load(const char* FileName);
	void Unload();
	void Update();
	void Draw();
};

