#include <GLFW/glfw3.h>
#include <imgui.h>
#include <core/application.h>
#include <core/imgui/imgui_layer.h>
#include <platform/opengl/imguiopenglrenderer.h>

namespace Prism {

	ImGUILayer::ImGUILayer() : Layer("ImGUILayer"), _LTime(0.0f) {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		//ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

	}

	ImGUILayer::~ImGUILayer() {
	
	}

	void ImGUILayer::Update() {

		Application& app = Application::Get();
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(app.GetWindowWidth(), app.GetWindowHeight());

		float currentTime = (float)glfwGetTime();
		io.DeltaTime = _LTime > 0.0 ? (currentTime - _LTime) : (1.0f / 60.0f);
		_LTime = currentTime;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void ImGUILayer::OnEvent(IEvent* ev) {
		
		IDispatcher dispatcher(ev);
		dispatcher.Forward<MouseButtonDownEvent>(std::bind(&ImGUILayer::OnMouseButtonDown, this, std::placeholders::_1));
		dispatcher.Forward<MouseButtonReleasedEvent>(std::bind(&ImGUILayer::OnMouseButtonReleased, this, std::placeholders::_1));
		dispatcher.Forward<MouseMoveEvent>(std::bind(&ImGUILayer::OnMouseMove, this, std::placeholders::_1));
		dispatcher.Forward<MouseScrollEvent>(std::bind(&ImGUILayer::OnMouseScroll, this, std::placeholders::_1));
		dispatcher.Forward<KeyDownEvent>(std::bind(&ImGUILayer::OnKeyDown, this, std::placeholders::_1));
		dispatcher.Forward<KeyReleasedEvent>(std::bind(&ImGUILayer::OnKeyReleased, this, std::placeholders::_1));
		dispatcher.Forward<KeyTypedEvent>(std::bind(&ImGUILayer::OnKeyTyped, this, std::placeholders::_1));
		dispatcher.Forward<WindowResizeEvent>(std::bind(&ImGUILayer::OnWindowResize, this, std::placeholders::_1));

	}

    bool ImGUILayer::OnMouseButtonDown(MouseButtonDownEvent* ev) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[ev->GetButton()] = true;
        return false;
    }

    bool ImGUILayer::OnMouseButtonReleased(MouseButtonReleasedEvent* ev) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[ev->GetButton()] = false;
		return false;
    }

    bool ImGUILayer::OnMouseMove(MouseMoveEvent* ev) {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(ev->GetXpos(), ev->GetYpos());
        return false;
    }

    bool ImGUILayer::OnMouseScroll(MouseScrollEvent* ev) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += ev->GetYpos();
		io.MouseWheelH += ev->GetXpos();
		return false;
    }

    bool ImGUILayer::OnKeyDown(KeyDownEvent* ev) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[ev->GetKey()] = true;
		io.KeyCtrl = io.KeysDown[GLFW_KEY_RIGHT_CONTROL] || io.KeysDown[GLFW_KEY_LEFT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_RIGHT_SHIFT] || io.KeysDown[GLFW_KEY_LEFT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_RIGHT_ALT] || io.KeysDown[GLFW_KEY_LEFT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_RIGHT_SUPER] || io.KeysDown[GLFW_KEY_LEFT_SUPER];
        return false;
    }

    bool ImGUILayer::OnKeyReleased(KeyReleasedEvent* ev) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[ev->GetKey()] = false;
		return false;
    }

    bool ImGUILayer::OnKeyTyped(KeyTypedEvent* ev) {
		ImGuiIO& io = ImGui::GetIO();
		int16_t key = ev->GetKeyCode();
		if (key > 0 && key < 0x10000) io.AddInputCharacter((uint16_t)key);
        return false;
    }

    bool ImGUILayer::OnWindowResize(WindowResizeEvent* ev) {
		Application& app = Application::Get();
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(ev->GetWidth(), ev->GetHeight());

        return false;
    }

}