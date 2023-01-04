#pragma once
#include "component_object.h"
class CO_Prism :
    public ComponentObject
{
    std::string _name;
    inline static std::map<std::string, bool> _isDuplication;

    std::string IsDuplicationName(std::string name,int index = 0);


    bool _isSelect = false;

    ShaderComponent* _shaderComponent;
public:
    virtual void InitInternal()override;
    virtual void UninitInternal()override;
    virtual void UpdateInternal()override;
    virtual void DrawInternal()override;
    virtual void DrawImguiInternal()override;

// name
    void SetName(const std::string& name ,bool notJudge = false);
    std::string GetName()const;

    void ResetMyName();


// isSelect
    void SetIsSelect(bool flag = true)
    {
        _isSelect = flag;
    }

// move
    void Movement(const D3DXVECTOR3& diff);
    void Rotation(const D3DXVECTOR3& diff);
    void Scaling(const D3DXVECTOR3& diff);

// Component
    class TextureComponent* _textureComponent;
    class BlinkPositionComponent* _blinkPositionComponent;

    class Camera* _camera;
};

