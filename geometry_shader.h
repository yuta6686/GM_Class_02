#pragma once
/** ---------------------------------------------------------
 *  [geometry_shader.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2023/2/13
 * ------------------------summary--------------------------
 * @brief  
 * @link: https://yuta6686.atlassian.net/browse/AS-57
 ** ---------------------------------------------------------*/
#include "resource.h"

enum GEOMETRY_SHADER_TYPE
{
    GSHADER_TYPE_TEST,
};

class GeometryShader :
    public Resource
{
private:
    ID3D11GeometryShader* _geometryShader;
public:    
    // Resource ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Draw() override;

    virtual void Load(const char* FileName) override;

    virtual void Unload() override;

    static std::map<GEOMETRY_SHADER_TYPE, std::string> GetFileNames();
private:
    inline static const std::map<GEOMETRY_SHADER_TYPE, std::string> _fileNames =
    {
        {GEOMETRY_SHADER_TYPE::GSHADER_TYPE_TEST,"testGS.cso"},
    };
};

