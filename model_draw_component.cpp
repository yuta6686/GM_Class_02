#include "model_draw_component.h"
#include "model.h"


void ModelDrawComponent::SetSourcePath(std::string path) {
    m_SourcePath = path;
}

void ModelDrawComponent::SetIsVariable(bool flag) {
    m_IsVariable = flag;
}

void ModelDrawComponent::SetDiffuse(D3DXCOLOR diff) 
{
    m_Model_variable->SetDiffuse(diff); 
}

void ModelDrawComponent::Init()
{
    if (m_IsVariable) {
        m_Model_variable =
            ResourceManager<Model_variable>::GetResource(m_SourcePath.c_str());
    }
    else
    {
        m_Model =
            ResourceManager<Model>::GetResource(m_SourcePath.c_str());
    }

}
void ModelDrawComponent::Uninit()
{
    //m_Model->Unload();
    //m_Model_variable->Unload();
}
;

void ModelDrawComponent::Draw()
{
    if (m_IsVariable) {
        Renderer::SetAlphaToCoverage();
        m_Model_variable->Draw();
        Renderer::SetDefaultBlend();
    }
    else
    {
        m_Model->Draw();
    }

};