#pragma once
#include "component_object.h"
class CO_Prism :
    public ComponentObject
{
    std::string _name;
    inline static std::map<std::string, bool> _isDuplication;

    std::string IsDuplicationName(std::string name,int index = 0);
public:
    virtual void Init()override;
    virtual void Uninit()override;
    virtual void Update()override;
    virtual void Draw()override;
    virtual void DrawImgui()override;

// name
    void SetName(const std::string& name);
    std::string GetName()const;

// Component
    class TextureComponent* _textureComponent;
    class BlinkPositionComponent* _blinkPositionComponent;
};

