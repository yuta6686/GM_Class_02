#pragma once
/** ---------------------------------------------------------
 *  [resource_manager.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2023/1/29
 * ------------------------summary--------------------------
 * @brief �x���[�h�������\�[�X��2�x�ڃ��[�h����Ƃ��ɁA�������\�[�X���擾������
 *		�@�V�[�����܂������Ƃ��ɁA���x�����[�h����̂�h��
 * 
 * @link https://yuta6686.atlassian.net/browse/AS-49
 ** ---------------------------------------------------------*/

#include "renderer.h"
#include "model.h"
#include "model_variable.h"

// �Q�l:https://qiita.com/FlatMountain/items/0b446900ccd058ec9d43
template <typename T>
class ResourceManger {
private:
	// Resource���Ǘ�����R���e�i
	static inline std::map<std::string, std::shared_ptr<T>> _container;

	// Resource�̐���
	static std::shared_ptr<T> CreateResource(std::string fileName) {

		std::shared_ptr<T> newResource = std::make_shared<T>();
		newResource->Load(fileName.c_str());

		return newResource;
	}

public:
	// Resource�̎擾 
	static std::shared_ptr<T> GetResource(std::string fileName)
	{
		// �t�@�C�����Ō���
		auto it = _container.find(fileName);

		// �R���e�i���ɂ���΁A���̃��\�[�X��Ԃ�
		if (it != _container.end()) {
			return it->second;
		}

		// �R���e�i���ɂȂ���΁A�V�������\�[�X���쐬���ăR���e�i�ɓo�^
		std::shared_ptr<T> newResource;
		newResource = CreateResource(fileName);
		_container.insert(std::make_pair(fileName, newResource));

		return newResource;
	}

	// �Q�[���I������Release����
	static void AllRelease() {
		for (auto resource : _container) {
			resource.second->Unload();
		}
		_container.clear();
	}
};


