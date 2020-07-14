#pragma once

// --- Library Files -----------------------
#include <imgui.h>

// --- Core Files --------------------------
#include "src/core/core.h"
#include "src/core/logger.h"
#include "src/core/events.h"
#include "src/core/layer.h"
#include "src/core/input.h"
#include "src/core/timestep.h"

// --- Application -------------------------
#include "src/application.h"

// --- Layers ------------------------------
#include "src/imgui/imgui_layer.h"

// --- Renderer ----------------------------
#include "src/renderer/renderer.h"
#include "src/renderer/camera.h"
#include "src/renderer/vertexarray.h"
#include "src/renderer/buffer.h"
#include "src/renderer/shader.h"
#include "src/renderer/texture.h"

#include "src/platform/opengl/ogl_shader.h"

// --- Entry -------------------------------
#include "src/core/entry.h"