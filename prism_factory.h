#pragma once
#include "factory.h"
#include "co_prism.h"

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
	float _pos_max = 20.0f;
public:
	virtual void Init()override;	
	virtual void Uninit()override;
	virtual void DrawImgui()override;
		

	/** AddPrisms
	 * デシリアライズした結果をまとめてAddGameObjcetしてる.
	 * 
	 * \param param デシリアライズされた結果をもらう
	 */
	void AddPrisms(std::vector<PrismGenerateParameter> param);
	void AddPrism(PrismGenerateParameter param);

	// 全部のCO_Prismを削除と名前のリセット
	void RemovePrisms();	

private:
	void GetPrismObjects();
	void UpdatePrism();
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
