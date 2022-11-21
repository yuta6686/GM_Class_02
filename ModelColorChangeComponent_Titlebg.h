#pragma once
/** ---------------------------------------------------------
 *  ModelColorChangeComponent_Titlebg [ModelColorChangeComponent_Titlebg.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/21
 * ------------------------summary--------------------------
 * @brief  
 ** ---------------------------------------------------------*/
#include "model_color_change_component.h"

class ModelColorChangeComponent_Titlebg :
	public ModelColorChangeComponent
{
private:
	std::shared_ptr<class Scene> m_Scene;
	std::vector<class CO_3DPloygonTest*> m_poly3d;
public:
	virtual void Init()override;
	virtual void Update() override;	
};

