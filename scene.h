#pragma once
/** ---------------------------------------------------------
 *  [scene.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/5/17
 * ------------------------summary--------------------------
 * @brief  sceneの元クラス
 ** ---------------------------------------------------------*/

enum LAYER {
	LAYER_BEGIN = 0,
	LAYER_FIRST,
	LAYER_3D,
	LAYER_AUDIO,
	LAYER_ENEMY,
	LAYER_LUMINANCE, // https://yuta6686.atlassian.net/browse/AS-41 輝度抽出用
	LAYER_BLUR_X,
	LAYER_BLUR_Y,
	LAYER_COPY,
	LAYER_TO_RENDERING_TEXTURE,
	LAYER_RENDERING_TEXTURE,
	LAYER_BLOOM,
	LAYER_2D,
	LAYER_PARTICLE,	
	LAYER_NUM_MAX,
};
class GameObject;
class Scene
{
protected:
	std::list<GameObject*> m_GameObject[LAYER_NUM_MAX];
	std::map<std::string, bool> m_Container;
public:
	inline static bool parameters_by_scene = true;


	inline Scene() {}
	inline virtual ~Scene() {}

	virtual void Init() = 0;

	void Unload();


	virtual void UnInit();

	virtual void Update();

	virtual void Draw();


	GameObject* AddGameObject(GameObject* pGameObject, int layer);

	template <typename T>//テンプレート解放
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject[Layer].push_back(gameObject);

		return gameObject;
	}

	std::vector<GameObject*> GetGameObjectLayer(const int& Layer);

	template <typename T>
	T* GetGameObject() {
		for (int i = 0; i < LAYER_NUM_MAX; i++) {
			for (auto obj : m_GameObject[i]) {

				//	型を調べる(RTTI動的型情報)
				if (typeid(*obj) == typeid(T)) {
					return (T*)obj;
				}
			}
		}
		return nullptr;
	}

	template <typename T>
	std::vector<T*> GetGameObjects() {
		std::vector<T*> objects;
		for (int i = 0; i < LAYER_NUM_MAX; i++) {
			for (auto obj : m_GameObject[i]) {

				//	型を調べる(RTTI動的型情報)
				if (typeid(*obj) == typeid(T)) {
					objects.push_back((T*)obj);
				}
			}
		}
		return objects;
	}


private:



};


