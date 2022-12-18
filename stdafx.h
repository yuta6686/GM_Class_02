#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <unordered_map>
#include <time.h>
#include <typeinfo>
#include <io.h>
#include <thread>
#include <functional>
#include <omp.h>


#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

//#include "imgui_node_editor.h"

#include "ImGuizmo.h"
#include "ImSequencer.h"
//#include "ImZoomSlider.h"
#include "ImCurveEdit.h"
//#include "GraphEditor.h"


#include <cereal.hpp>
#include <archives/json.hpp>
#include <types/vector.hpp>
#include <types/list.hpp>

#include "my_imgui.h"

#include "main.h"
#include "scene.h"
#include "manager.h"
#include "resource_manager.h"
#include "gameObject.h"
#include "resource.h"
#include "component_object.h"
#include "component.h"
#include "renderer.h"

