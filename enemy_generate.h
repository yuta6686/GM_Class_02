#pragma once
/** ---------------------------------------------------------
 *  [enemy_generate.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/12/27
 * ------------------------summary--------------------------
 * @brief  エネミー生成
 * ImGuiでボタンを押すと生成できる
 ** ---------------------------------------------------------*/
#include "component_object.h"

#include "scene.h"
#include "player.h"
#include "Enemy_Interface.h"

enum VERTICAL_DEPLOY_AXIS {
	VDA_X = 0,
	VDA_MX,
	VDA_Y,	
	VDA_Z,
	VDA_MZ
};

// GameObjectのシリアライズ
template<class Archive>
void serialize(Archive& archive,GameObject* enemy)
{	
	D3DXVECTOR3 pos = enemy->GetPosition();
	D3DXVECTOR3 rot = enemy->GetRotation();
	D3DXVECTOR3 sca = enemy->GetScale();
	archive(CEREAL_NVP(pos), CEREAL_NVP(rot), CEREAL_NVP(sca));
}

// EnemyをSerializeするための保存用構造体
class SerializeEnemy {
public:

	D3DXVECTOR3 _position;
	D3DXVECTOR3 _rotation;
	D3DXVECTOR3 _scale;

	int _hp;
	int _index;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(_position), CEREAL_NVP(_rotation), CEREAL_NVP(_scale),
			CEREAL_NVP(_hp), CEREAL_NVP(_index));
	}
};
class SerializeEnemys 
{
public:
	SerializeEnemys() {};
	SerializeEnemys(std::vector<GameObject*> Enemys);

	// シリアライズ用に一時変数を保持
	std::vector<SerializeEnemy> _serializeEnemy;

	// デシリアライズした結果をゲームオブジェクトとして追加する
	std::vector<GameObject*> AddDeserializeEnemys();

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(_serializeEnemy));
	}
};

class EnemyGenerate :
	public ComponentObject
{
private:
	std::shared_ptr<Scene> m_Scene;
	std::string m_FileName = "asset\\file\\EnemyGenerate";
	std::string m_Extension = ".txt";
	std::string m_Version = "_EnemyIndex";

	const std::string _menuName = "EnemyGenerate";

	inline static const std::string _serialize_file_name = "_out.json";
	int m_SaveFileIndex = 2;
	int m_LoadFileIndex = 2;
	int m_NowFileNum = 2;
	inline static ImVec4 window_color = ImVec4(0.0f, 0.0f, 0.2f, 0.5f);

	//  Load Stage_Wave
	int m_StageNum = 1;
	int m_WaveNum = 1;
	inline static const int STAGE_NUM_MAX = 3;
	inline static const int WAVE_NUM_MAX = 3;

	//  CircleDeploy
	int m_NumLayer = 1;
	int m_NumLayer_Max = 16;
	float m_Radius = 10.0f;
	float m_Offset = 0.0f;

	//	Vertical Deploy
	int m_VerticalDeployNum = 3;
	float m_VerticalDelpoyWidth = 5.0f;
	int m_Axis = VDA_X;

	bool IsEnemyGenerateMode = false;

	//  GenerateTransform    	
	D3DXVECTOR3 _scale3 = { 1.0f,1.0f,1.0f };
	int _hp = 1;
	int _enemy_index = 0;

	Player* m_Player;
public:
	void SetEnemyGenerateMode(bool flag);

	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

	virtual void DrawImgui()override;

private:
	void Generate(std::vector<GameObject*> enemys, std::vector<class Cylinder*> clies);
	void Save(std::vector<GameObject* > enemys, std::vector<class Cylinder*> clies);
	void Load(std::vector<GameObject*> enemys, std::vector<class Cylinder*> cliies);

	// シリアライズ
	void SerializeMenu();
	void Serialize(std::vector<GameObject*> enemys, std::vector<class Cylinder*> cliies);

	// デシリアライズ
	void Deserialize();

	template<class Archive>
	void serialize(Archive& archive, SerializeEnemys& serializeEnemys)
	{			
		archive(CEREAL_NVP(serializeEnemys));
	}

};

