#pragma once
#include "resource.h"
class PixelShader :
	public Resource
{
	ID3D11PixelShader* m_PixelShader;
public:


	// Resource ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void Draw() override;

	virtual void Load(const char* FileName) override;

	virtual void Unload() override;

	inline static std::map<SHADER_TYPE, std::string> GetFileNames() { return _fileNames; }
private:
	inline static const std::map<SHADER_TYPE, std::string> _fileNames = {
		{SHADER_TYPE::SHADER_DEFAULT,"vertexLightingPS.cso"},
		{SHADER_TYPE::SHADER_UNLIT,"unlitTexturePS.cso"},
		{SHADER_TYPE::SHADER_UNLIT_NO_MATERIAL,"unlitTexturePS.cso"},
		{SHADER_TYPE::SHADER_NOISE,"testPS.cso"},
		{SHADER_TYPE::SHADER_NOISE_CIRCLE,"noise_circle_ps.cso"},
		{SHADER_TYPE::SHADER_RENDERING_TEXTURE,"rendering_texture_ps.cso"},
		{SHADER_TYPE::SHADER_BLURX,"post_effect_blur_ps.cso"},
		{SHADER_TYPE::SHADER_BLURY,"post_effect_blur_ps.cso"},
		{SHADER_TYPE::SHADER_ENEMY,"enemy_ps.cso"},
		{SHADER_TYPE::SHADER_ENVIRONMENT_MAPPING,"env_mapping_ps.cso"},
		{SHADER_TYPE::SHADER_ENVIRONMENT_MAPPING_SELECT,"env_mapping_select_ps.cso"},
		{SHADER_TYPE::SHADER_LUMINANCE,"luminance_ps.cso"},
		{SHADER_TYPE::SHADER_PARTICLE,"ParticlePS.cso"},
		{SHADER_TYPE::SHADER_STEALTH,"StealthPS.cso"},
		{SHADER_TYPE::SHADER_BLOOM,"PSBloomFinal.cso"},
		{SHADER_TYPE::SHADER_DEPTH_OF_FIELD,"depth_of_field_ps.cso"}
	};
};

