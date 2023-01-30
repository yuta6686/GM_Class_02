#pragma once
/** ---------------------------------------------------------
 *  [resource_manager.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2023/1/29
 * ------------------------summary--------------------------
 * @brief 度ロードしたリソースを2度目ロードするときに、同じリソースを取得させる
 *		　シーンをまたいだときに、何度もロードするのを防ぐ
 * 
 * @link https://yuta6686.atlassian.net/browse/AS-49
 ** ---------------------------------------------------------*/

#include "renderer.h"
#include "model.h"
#include "model_variable.h"

// 参考:https://qiita.com/FlatMountain/items/0b446900ccd058ec9d43
template <typename T>
class ResourceManger {
private:
	// Resourceを管理するコンテナ
	static inline std::map<std::string, std::shared_ptr<T>> _container;

	// Resourceの生成
	static std::shared_ptr<T> CreateResource(std::string fileName) {

		std::shared_ptr<T> newResource = std::make_shared<T>();
		newResource->Load(fileName.c_str());

		return newResource;
	}

public:
	// Resourceの取得 
	static std::shared_ptr<T> GetResource(std::string fileName)
	{
		// ファイル名で検索
		auto it = _container.find(fileName);

		// コンテナ内にあれば、そのリソースを返す
		if (it != _container.end()) {
			return it->second;
		}

		// コンテナ内になければ、新しくリソースを作成してコンテナに登録
		std::shared_ptr<T> newResource;
		newResource = CreateResource(fileName);
		_container.insert(std::make_pair(fileName, newResource));

		return newResource;
	}

	// ゲーム終了時にReleaseする
	static void AllRelease() {
		for (auto resource : _container) {
			resource.second->Unload();
		}
		_container.clear();
	}
};


