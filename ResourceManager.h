#pragma once
#include "main.h"
#include "renderer.h"
#include "model.h"
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


//class ModelManager
//{
//private:
//	static inline std::map<std::string, std::shared_ptr<Model>> m_ModelContainer;
//
//	static std::shared_ptr<Model> createModel(std::string fileName) {
//		
//		std::shared_ptr<Model> newModel = std::make_shared<Model>();
//		newModel->Load(fileName.c_str());
//		
//		return newModel;
//	}
//
//public:
//	static std::shared_ptr<Model> GetModel(std::string fileName) 
//	{
//		 auto it = m_ModelContainer.find(fileName);
//		
//		if (it != m_ModelContainer.end()) {						
//			return it->second;
//		}
//
//		std::shared_ptr<Model> newModel;
//		newModel = createModel(fileName);
//
//		m_ModelContainer.insert(std::make_pair(fileName, newModel));
//		return newModel;
//	}
//
//	static void AllRelease() {
//		for (auto model : m_ModelContainer) {
//			model.second->Unload();
//		}
//	}
//};
