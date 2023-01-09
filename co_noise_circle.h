#pragma once
/** ---------------------------------------------------------
 *  [co_noise_circle.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2023/1/9
 * ------------------------summary--------------------------
 * @brief  �~�`��Noise���H�I�Ȃ��
 * @link  https://yuta6686.atlassian.net/browse/AS-9
 * - �����̋����͌����������B
 * - Shader�ŌŒ肳�ꂽ�l���g���Ă�̂ŁB
 ** ---------------------------------------------------------*/

#include "component_object.h"
class CO_NoiseCircle :
    public ComponentObject
{
	ID3D11Buffer* m_VertexBuffer = NULL;

	std::shared_ptr<Texture> m_Texture;

	std::shared_ptr <VertexShader> m_VertexShader;
	std::shared_ptr<PixelShader> m_PixelShader;
public:
	void InitInternal()override;
	void UninitInternal()override;
	void UpdateInternal()override;
	void DrawInternal()override;
	void DrawImguiInternal()override;
};

