#pragma once
#include "Component.h"
#include "geometry_shader.h"
class GeometryShaderComponent :
    public Component
{
private:
    std::shared_ptr<GeometryShader> _geometryShader;
    int _gShaderType;
public:
    GeometryShaderComponent();
    GeometryShaderComponent(const int& type);

    void SetGeometryShaderType(const int& shaderType);

    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;

};

