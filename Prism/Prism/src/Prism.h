#pragma once

// --- Library Files -----------------------
#include <imgui.h>

// --- Core Files --------------------------
#include <core/core.h>
#include <core/logger.h>
#include <core/events.h>
#include <core/application.h>
#include <core/layer.h>
#include <core/input.h>
#include <core/timestep.h>

// --- Layers ------------------------------
#include <core/imgui/imgui_layer.h>

// --- Renderer ----------------------------
#include <core/renderer/renderer.h>
#include <core/renderer/camera.h>
#include <core/renderer/vertexarray.h>
#include <core/renderer/buffer.h>
#include <core/renderer/shader.h>
#include <core/renderer/texture.h>

#include <platform/opengl/ogl_shader.h>

// --- Entry -------------------------------
#include <core/entry.h>