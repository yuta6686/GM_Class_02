#pragma once
#include "ComponentObject.h"
#include "model_variable.h"
#include "model.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "BlinkComponent.h"
#include <fstream>
#include <iostream>
#include <sstream>

struct FIELD_OBJECT {
    std::shared_ptr<Model> _model;

    D3DXVECTOR3 _position;    
    D3DXVECTOR3 _rotation;
    D3DXVECTOR3 _scale;

    float _blink;
};
class CO_Torii_Broken :
    public ComponentObject
{
private:    
    std::shared_ptr <VertexShader> m_VertexShader;
    std::shared_ptr<PixelShader> m_PixelShader;

    std::vector<std::shared_ptr<Model>> m_Models;
    std::vector< FIELD_OBJECT> m_Objects;
    std::vector< BlinkComponent*> m_Blink;
    std::string m_ModelName = "asset\\model\\torii\\torii_broken_";
    std::string m_Obj = ".obj";

    std::string m_FileName = "asset\\file\\Torii\\torii_";
    std::string m_Extension = ".txt";
    int m_SaveFileIndex = 0;
    int m_LoadFileIndex = 0;
    int m_NowFileNum = 2;

    int m_MinIndex = 1;
    int m_MaxIndex = 50;
    
public:

    bool SetObjects(const int& index, const FIELD_OBJECT& fo)
    {
        if (index < 0 || index >= m_MaxIndex)return false;
        m_Objects[index] = fo;
        return true;
    }
    virtual void Init()override {
        AddComponent<TransformInit>(COMLAYER_FIRST);

        for (int i = 1; i <= 50; i++)
        {
            std::ostringstream oss;
            if (i <= 9) {
                oss << 0 << 0;
            }
            else if (i >= 10) {
                oss << 0;
            }

            oss << i;
            m_Models.push_back(ResourceManger<Model>::GetResource(m_ModelName.c_str() + oss.str() + m_Obj.c_str()));
        }

        m_VertexShader =
            ResourceManger<VertexShader>::GetResource(VertexShader::UNLIT_VERTEX_SHADER.c_str());
        m_PixelShader =
            ResourceManger<PixelShader>::GetResource(PixelShader::UNLIT_PIXEL_SHADER.c_str());
      
        for (int i = 0; i < m_MaxIndex; i++) {
            FIELD_OBJECT fo;
            fo._position = { 0.0f,0.0f,0.0f };
            fo._rotation = { 0.0f,0.0f,0.0f };
            fo._scale = { 3.0f,3.0f,3.0f };
            fo._model = m_Models[i];
            fo._blink = 0.0f;
            m_Objects.push_back(fo);
            m_Blink.push_back(AddComponent<BlinkComponent>(COMLAYER_SECOND));
            m_Blink[i]->SetParameter(MyMath::Random(0.001f, 0.005f), MyMath::Random(0.5f,0.75f), MyMath::Random(1.25f,1.5f));
            if (i == 3 || i==14) {
                m_Blink[i]->SetParameter(0.0f, 1.0f, 1.0f);
            }
        }

        for (int i = 1; i < 100; i++) {
            std::ostringstream oss;
            oss << i;
            std::ifstream ifs(m_FileName.c_str() + oss.str() + m_Extension.c_str());

            if (!ifs) {
                m_NowFileNum = i;
                break;
            }
        }
        
        std::ostringstream oss;

        oss << m_LoadFileIndex;

        std::ifstream ifs(m_FileName.c_str() + oss.str() + m_Extension.c_str());
        std::string str_buf;
        std::string str_conma_buf;
        std::vector<std::string> str_buf_vec;

        int index = 0;

        while (getline(ifs, str_buf)) {
            std::istringstream istream(str_buf);

            while (getline(istream, str_conma_buf, ',')) {
                str_buf_vec.push_back(str_conma_buf);
            }

            m_Objects[index]._position.x = stof(str_buf_vec[0]);
            m_Objects[index]._position.y = stof(str_buf_vec[1]);
            m_Objects[index]._position.z = stof(str_buf_vec[2]);

            m_Objects[index]._rotation.x = stof(str_buf_vec[3]);
            m_Objects[index]._rotation.y = stof(str_buf_vec[4]);
            m_Objects[index]._rotation.z = stof(str_buf_vec[5]);

            m_Objects[index]._scale.x = stof(str_buf_vec[6]);
            m_Objects[index]._scale.y = stof(str_buf_vec[7]);
            m_Objects[index]._scale.z = stof(str_buf_vec[8]);

            index++;

            str_buf_vec.clear();
        }

        ComponentObject::Init();
    }

    virtual void Update()override
    {
        for (unsigned int i = 0; i < m_Objects.size(); i++)
        {
            m_Objects[i]._blink = m_Blink[i]->GetBlinkValue();
        }

        ComponentObject::Update();
    }

    virtual void Draw()override
    {
     



#ifdef _DEBUG
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f,1.0f,1.0f,0.0f));

        ImGui::Begin("Torii_Objects");

        if (ImGui::Button("Save_Torii")) {
            if (m_SaveFileIndex == m_NowFileNum) {
                m_NowFileNum++;
            }

            std::ostringstream oss;

            oss << m_SaveFileIndex;

            //	FileName + FileIndex + Extension
            std::ofstream ofs(m_FileName.c_str() + oss.str() + m_Extension.c_str());

            if (!ofs) {
                ImGui::Text("Could not open file.");
            }

            for (int i = 0; i < m_Objects.size(); i++) {

                ofs << std::showpoint
                    << m_Objects[i]._position.x << ","
                    << m_Objects[i]._position.y << ","
                    << m_Objects[i]._position.z << ","
                    << m_Objects[i]._rotation.x << ","
                    << m_Objects[i]._rotation.y << ","
                    << m_Objects[i]._rotation.z << ","
                    << m_Objects[i]._scale.x << ","
                    << m_Objects[i]._scale.y << ","
                    << m_Objects[i]._scale.z << std::endl;
            }
        }

        if (ImGui::Button("Load_Torii")) {

            std::ostringstream oss;

            oss << m_LoadFileIndex;

            std::ifstream ifs(m_FileName.c_str() + oss.str() + m_Extension.c_str());
            std::string str_buf;
            std::string str_conma_buf;
            std::vector<std::string> str_buf_vec;

            int index = 0;

            while (getline(ifs, str_buf)) {
                std::istringstream istream(str_buf);

                while (getline(istream, str_conma_buf, ',')) {
                    str_buf_vec.push_back(str_conma_buf);
                }

                m_Objects[index]._position.x = stof(str_buf_vec[0]);
                m_Objects[index]._position.y = stof(str_buf_vec[1]) * m_Objects[index]._blink;
                m_Objects[index]._position.z = stof(str_buf_vec[2]);

                m_Objects[index]._rotation.x = stof(str_buf_vec[3]);
                m_Objects[index]._rotation.y = stof(str_buf_vec[4]);
                m_Objects[index]._rotation.z = stof(str_buf_vec[5]);

                m_Objects[index]._scale.x = stof(str_buf_vec[6]);
                m_Objects[index]._scale.y = stof(str_buf_vec[7]);
                m_Objects[index]._scale.z = stof(str_buf_vec[8]);

                index++;

                str_buf_vec.clear();
            }
        }

        ImGui::SliderInt("SaveFileIndex", &m_SaveFileIndex, 1, m_NowFileNum, "%d");

        ImGui::Separator();

        ImGui::SliderInt("LoadFileIndex", &m_LoadFileIndex, 1, m_NowFileNum - 1, "%d");

        ImGui::Separator();
#endif // _DEBUG

        for (unsigned int i = 0; i < m_Objects.size(); i++) {

#ifdef _DEBUG
            std::ostringstream oss;
            oss <<"Object_" << i;
            if(ImGui::TreeNode(oss.str().c_str()))
            {
                ImGui::SliderFloat("_position.x", &m_Objects[i]._position.x, -200.0f, 200.0f, "%.2f");
                ImGui::SliderFloat("_position.y", &m_Objects[i]._position.y, -100.0f, 100.0f, "%.2f");
                ImGui::SliderFloat("_position.z", &m_Objects[i]._position.z, -200.0f, 200.0f, "%.2f");

                ImGui::SliderFloat("_rotation.x", &m_Objects[i]._rotation.x, 0.0f, 2.0f * D3DX_PI, "%.2f");
                ImGui::SliderFloat("_rotation.y", &m_Objects[i]._rotation.y, 0.0f, 2.0f * D3DX_PI, "%.2f");
                ImGui::SliderFloat("_rotation.z", &m_Objects[i]._rotation.z, 0.0f, 2.0f * D3DX_PI, "%.2f");

                ImGui::SliderFloat("_scale.x", &m_Objects[i]._scale.x, 0.0f, 200.0f, "%.2f");
                ImGui::SliderFloat("_scale.y", &m_Objects[i]._scale.y, 0.0f, 200.0f, "%.2f");
                ImGui::SliderFloat("_scale.z", &m_Objects[i]._scale.z, 0.0f, 200.0f, "%.2f");
                ImGui::TreePop();
            }
            

#endif // _DEBUG  
            //	シェーダ
            m_VertexShader->Draw();
            m_PixelShader->Draw();

            //ワールドマトリクス設定
            D3DXMATRIX world, scale, rot, trans;
            D3DXMatrixScaling(&scale,
                m_Objects[i]._scale.x,
                m_Objects[i]._scale.y,
                m_Objects[i]._scale.z);
            D3DXMatrixRotationYawPitchRoll(&rot,
                m_Objects[i]._rotation.x,
                m_Objects[i]._rotation.y,
                m_Objects[i]._rotation.z);
            D3DXMatrixTranslation(&trans,
                m_Objects[i]._position.x,
                m_Objects[i]._position.y * m_Blink[i]->GetBlinkValue() ,
                m_Objects[i]._position.z);
            world = scale * rot * trans;
            Renderer::SetWorldMatrix(&world);

            m_Objects[i]._model->Draw();

        }
#ifdef _DEBUG
        ImGui::PopStyleColor();

        ImGui::End();
#endif // _DEBUG
        ComponentObject::Draw();
    }

    virtual void DrawImgui()override
    {
        


        ComponentObject::DrawImgui();
    }
};

