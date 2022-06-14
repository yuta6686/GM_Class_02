#pragma once
#include "gameObject.h"
class Effect_explosion :
    public GameObject
{
private:
    ID3D11Buffer* m_VertexBuffer = NULL;
    std::shared_ptr<Texture> m_Texture;

	std::shared_ptr <VertexShader> m_VertexShader;
	std::shared_ptr<PixelShader> m_PixelShader;

	int m_Count;

	static const int TEX_WIDHT_NUM = 4;
	static const int TEX_HEIGHT_NUM = 4;
	static const int TEX_NUM = 16;

	void InitVertex(VERTEX_3D* vertex);
public:
	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;
};

