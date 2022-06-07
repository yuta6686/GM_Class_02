#pragma once
#include <map>
#include <string>
#include <memory>
#include <iterator>
#include "main.h"
#include "renderer.h"
#include "model.h"
class ModelManager
{
private:
	static inline std::map<std::string, std::shared_ptr<Model>> m_ModelContainer;

	static std::shared_ptr<Model> createModel(std::string fileName) {
		
		std::shared_ptr<Model> newModel = std::make_shared<Model>();
		newModel->Load(fileName.c_str());
		
		return newModel;
	}

public:
	static std::shared_ptr<Model> GetModel(std::string fileName) 
	{
		 auto it = m_ModelContainer.find(fileName);
		
		if (it != m_ModelContainer.end()) {						
			return it->second;
		}

		std::shared_ptr<Model> newModel;
		newModel = createModel(fileName);

		m_ModelContainer.insert(std::make_pair(fileName, newModel));
		return newModel;
	}

	static void AllRelease() {
		for (auto model : m_ModelContainer) {
			model.second->Unload();
		}
	}
};

