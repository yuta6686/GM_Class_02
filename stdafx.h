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
#include <typeindex>
#include <fstream>
#include <iostream>
#include <sstream>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

//#include "imgui_node_editor.h"




#include <cereal.hpp>
#include <archives/json.hpp>
#include <types/vector.hpp>
#include <types/list.hpp>
#include <types/string.hpp>

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
#include "texture_compoennt.h"
#include "serealize_archive.h"