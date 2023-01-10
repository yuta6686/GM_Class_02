#pragma once

#include "renderer.h"
#include "model.h"
#include "model_variable.h"
template <typename T>
class ResourceManger {
private:
	static inline std::map<std::string, std::shared_ptr<T>> m_Container;

	static std::shared_ptr<T> createResource(std::string fileName) {

		std::shared_ptr<T> newResource = std::make_shared<T>();
		newResource->Load(fileName.c_str());

		return newResource;
	}

public:
	static std::shared_ptr<T> GetResource(std::string fileName)
	{
		auto it = m_Container.find(fileName);

		if (it != m_Container.end()) {
			return it->second;
		}

		std::shared_ptr<T> newResource;
		newResource = createResource(fileName);

		m_Container.insert(std::make_pair(fileName, newResource));
		return newResource;
	}

	static void AllRelease() {
		for (auto resource : m_Container) {
			resource.second->Unload();
		}
	}
};


