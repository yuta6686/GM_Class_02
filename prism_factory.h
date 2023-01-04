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
	// prismからパラメータを取り出して、thisにセットする
	void TakeOutPrismParameter(CO_Prism* prism);

	// prismにthisのパラメータをセットする
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
	// デシリアライズするときのデータを保持するもの
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
	 * デシリアライズした結果をまとめてAddGameObjcetしてる.
	 * 
	 * \param param デシリアライズされた結果をもらう
	 */
	void AddPrisms(std::vector<PrismGenerateParameter> param);
	void AddPrism(PrismGenerateParameter param);

	// PrismGeneratorをReleaseで表示しないようにする https://yuta6686.atlassian.net/browse/AS-7
	static void AddPrismFirst(std::vector<PrismGenerateParameter> param);

	// 全部のCO_Prismを削除と名前のリセット
	void RemovePrisms();	

private:
	void GetPrismObjects();
	void UpdatePrism();

	// 現在と前のフレームの選択されている_prismParamが変更されていたらtrue
	bool IsChangeBlinkParameter(const PrismGenerateParameter& now);

private:
	// ImGuiでの操作（ボタンごとに関数化する）

	
	// 生成
	void Generate();

	// シリアライズ
	void Serialize();

	// バックアップ用	
	void SerializeBackUp_End();
	
	// デシリアライズ 追加Version
	void DesirializeAdd();

	// デシリアライズ 上書きVersion
	void DesirializeAdress();

	// リストボックス ヒエラルキーの内部処理
	void ShowListBox();

	// 情報開示用
	void ShowParameter();

private:
	template<class Archive>
	static void serialize(Archive& archive, std::vector<PrismGenerateParameter>& param)
	{
		archive(param);
	}
};
