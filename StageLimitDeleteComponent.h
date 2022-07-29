#pragma once
#include "Component.h"
class StageLimitDeleteComponent :
    public Component
{
private:
    float X_MIN = -100.0F;
    float X_MAX = 100.0F;

    float Y_MIN = -100.0F;
    float Y_MAX = 100.0F;

    float Z_MIN = -100.0F;
    float Z_MAX = 100.0F;

    bool m_NoLimit = false;
public:    
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;

    /// <summary>
    /// SetLimit   
    /// </summary>
    /// <param name="xyz">'x' or 'y' or 'z'</param>
    /// <param name="min">min limit value</param>
    /// <param name="max">max limit value</param>
    void SetLimit(char xyz, float min, float max) {
        switch (xyz)
        {
        case 'x':
        case 'X':
            X_MIN = min;
            X_MAX = max;
            break;
        case 'y':
        case 'Y':
            Y_MIN = min;
            Y_MAX = max;
            break;
        case 'z':
        case 'Z':
            Z_MIN = min;
            Z_MAX = max;
            break;
        default:
            m_NoLimit = true;
            break;
        }
    }
};

