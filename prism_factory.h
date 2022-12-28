#pragma once
#include "factory.h"
#include "co_prism.h"

struct PrismGenerateParameter
{	
	void SetPrismParameter(CO_Prism* prism);
	void SetPrism(CO_Prism* prism);

	// ���O
	std::string _name;

	// Transform
	D3DXVECTOR3 _position, _rotation, _scale;

	// Blink Parameter
	float _speed, _min, _max;
	int _axis = AXIS_Y; // �ł��Ȃ�������int�ŊǗ�����

	// ���}�b�s���O�p
	std::string _fileName_EnvironmentMapping; 

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(_name),
			CEREAL_NVP(_position),
			CEREAL_NVP(_rotation),
			CEREAL_NVP(_scale),
			CEREAL_NVP(_speed),
			CEREAL_NVP(_min),
			CEREAL_NVP(_max),
			CEREAL_NVP(_axis),
			CEREAL_NVP(_fileName_EnvironmentMapping));
	}
};

class PrismFactory :
    public Factory
{
public:    
    virtual void Create() override;


public:
			
	inline static const std::string PRISM_FILE_NAME = "_prism.json";

	template<class Archive>
	static void serialize(Archive& archive, std::vector<PrismGenerateParameter>& param)
	{
		archive(param);
	}
};

class PrismGenerator :
	public ComponentObject
{
	// �f�V���A���C�Y����Ƃ��̃f�[�^��ێ��������
	std::vector<PrismGenerateParameter> _prismParam;
	std::vector<CO_Prism*> _prism;	
	std::shared_ptr<Scene> _scene;

	int _itemCurrent = 0;
public:
	virtual void Init()override;
	/*virtual void Update()override;*/
	virtual void DrawImgui()override;

	
	// �f�V���A���C�Y�������ʂ��܂Ƃ߂�AddGameObjcet���Ă�
	void AddPrisms(std::vector<PrismGenerateParameter> param);


private:
	void GetPrismObjects();

	// PrismGenerateParameter��CO_Prism�̕ϊ����K�v�ɂȂ�������
};
