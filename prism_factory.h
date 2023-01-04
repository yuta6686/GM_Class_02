#pragma once
#include "factory.h"
#include "co_prism.h"

struct PrismTexture
{
	inline static int _itemCurrent = 0;
	inline static const std::vector<const char*> _texture =
	{
		"asset\\texture\\swordOfKirito.png",
		"asset\\texture\\enviroment.dds",
	};

	static const char* GetNowTexture()
	{
		return _texture[_itemCurrent];
	}
};

struct PrismGenerateParameter
{	
	// prism����p�����[�^�����o���āAthis�ɃZ�b�g����
	void TakeOutPrismParameter(CO_Prism* prism);

	// prism��this�̃p�����[�^���Z�b�g����
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

	bool operator != (const PrismGenerateParameter& param)
	{
		if (this->_name != param._name ||
			this->_position != param._position ||
			this->_rotation != param._rotation ||
			this->_scale != param._scale ||
			this->_speed != param._speed ||
			this->_min != param._min ||
			this->_max != param._max ||
			this->_axis != param._axis ||
			this->_fileName_EnvironmentMapping !=
			param._fileName_EnvironmentMapping) {
			return true;
		}
		return false;
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

	PrismGenerateParameter _previousPrismParam;

	int _itemCurrent = 0;
	float _pos_max = 20.0f;

	D3DXVECTOR3 _pos_collision = { 0.0f,0.0f,0.0f };

	class ChainOfResponsibility* _chain;
public:
	virtual void Init()override;	
	virtual void Update()override;
	virtual void Uninit()override;
	virtual void DrawImgui()override;
		

	/** AddPrisms
	 * �f�V���A���C�Y�������ʂ��܂Ƃ߂�AddGameObjcet���Ă�.
	 * 
	 * \param param �f�V���A���C�Y���ꂽ���ʂ����炤
	 */
	void AddPrisms(std::vector<PrismGenerateParameter> param);
	void AddPrism(PrismGenerateParameter param);

	// PrismGenerator��Release�ŕ\�����Ȃ��悤�ɂ��� https://yuta6686.atlassian.net/browse/AS-7
	static void AddPrismFirst(std::vector<PrismGenerateParameter> param);

	// �S����CO_Prism���폜�Ɩ��O�̃��Z�b�g
	void RemovePrisms();	

private:
	void GetPrismObjects();
	void UpdatePrism();

	// ���݂ƑO�̃t���[���̑I������Ă���_prismParam���ύX����Ă�����true
	bool IsChangeBlinkParameter(const PrismGenerateParameter& now);

private:
	// ImGui�ł̑���i�{�^�����ƂɊ֐�������j

	
	// ����
	void Generate();

	// �V���A���C�Y
	void Serialize();

	// �o�b�N�A�b�v�p	
	void SerializeBackUp_End();
	
	// �f�V���A���C�Y �ǉ�Version
	void DesirializeAdd();

	// �f�V���A���C�Y �㏑��Version
	void DesirializeAdress();

	// ���X�g�{�b�N�X �q�G�����L�[�̓�������
	void ShowListBox();

	// ���J���p
	void ShowParameter();

private:
	template<class Archive>
	static void serialize(Archive& archive, std::vector<PrismGenerateParameter>& param)
	{
		archive(param);
	}
};
