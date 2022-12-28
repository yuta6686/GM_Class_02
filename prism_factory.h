#pragma once
#include "factory.h"
#include "co_prism.h"

struct PrismGenerateParameter
{	
	void SetPrismParameter(CO_Prism* prism);
	void SetPrism(CO_Prism* prism);

	// 名前
	std::string _name;

	// Transform
	D3DXVECTOR3 _position, _rotation, _scale;

	// Blink Parameter
	float _speed, _min, _max;
	int _axis = AXIS_Y; // できなかったらintで管理する

	// 環境マッピング用
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
	// デシリアライズするときのデータを保持するもの
	std::vector<PrismGenerateParameter> _prismParam;
	std::vector<CO_Prism*> _prism;	
	std::shared_ptr<Scene> _scene;

	int _itemCurrent = 0;
public:
	virtual void Init()override;
	/*virtual void Update()override;*/
	virtual void DrawImgui()override;

	
	// デシリアライズした結果をまとめてAddGameObjcetしてる
	void AddPrisms(std::vector<PrismGenerateParameter> param);


private:
	void GetPrismObjects();

	// PrismGenerateParameterとCO_Prismの変換が必要になったら作る
};
