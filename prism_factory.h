#pragma once
#include "factory.h"
#include "co_prism.h"

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
	float _pos_max = 20.0f;
public:
	virtual void Init()override;	
	virtual void Uninit()override;
	virtual void DrawImgui()override;
		

	/** AddPrisms
	 * �f�V���A���C�Y�������ʂ��܂Ƃ߂�AddGameObjcet���Ă�.
	 * 
	 * \param param �f�V���A���C�Y���ꂽ���ʂ����炤
	 */
	void AddPrisms(std::vector<PrismGenerateParameter> param);
	void AddPrism(PrismGenerateParameter param);

	// �S����CO_Prism���폜�Ɩ��O�̃��Z�b�g
	void RemovePrisms();	

private:
	void GetPrismObjects();
	void UpdatePrism();
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
