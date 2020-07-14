#include "windowsinput.h"
#include "application.h"

namespace Prism {

	const std::map<MouseBtn, uint32_t> WindowsInputInterface::PrismToGLFWMouseBtnBindings = {
		{ MouseBtn::Button0,			GLFW_MOUSE_BUTTON_1 },
		{ MouseBtn::Button1,			GLFW_MOUSE_BUTTON_2 },
		{ MouseBtn::Button2,			GLFW_MOUSE_BUTTON_3 },
		{ MouseBtn::Button3,			GLFW_MOUSE_BUTTON_4 },
		{ MouseBtn::Button4,			GLFW_MOUSE_BUTTON_5 },
		{ MouseBtn::Button5,			GLFW_MOUSE_BUTTON_6 },
		{ MouseBtn::Button6,			GLFW_MOUSE_BUTTON_7 },
		{ MouseBtn::Button7,			GLFW_MOUSE_BUTTON_8 },
		{ MouseBtn::ButtonLast,			GLFW_MOUSE_BUTTON_8 },
		{ MouseBtn::ButtonLeft,			GLFW_MOUSE_BUTTON_LEFT },
		{ MouseBtn::ButtonRight,		GLFW_MOUSE_BUTTON_RIGHT },
		{ MouseBtn::ButtonMiddle,		GLFW_MOUSE_BUTTON_MIDDLE },
	};

	const std::map<Key, uint32_t> WindowsInputInterface::PrismToGLFWKeyBindings = {
		{ Key::Space,			GLFW_KEY_SPACE },
		{ Key::Apostrophe,		GLFW_KEY_APOSTROPHE },
		{ Key::Comma,			GLFW_KEY_COMMA },
		{ Key::Minus,			GLFW_KEY_MINUS },
		{ Key::Period,			GLFW_KEY_PERIOD },
		{ Key::Slash,			GLFW_KEY_SLASH },
		{ Key::D0,				GLFW_KEY_0 },
		{ Key::D1,				GLFW_KEY_1 },
		{ Key::D2,				GLFW_KEY_2 },
		{ Key::D3,				GLFW_KEY_3 },
		{ Key::D4,				GLFW_KEY_4 },
		{ Key::D5,				GLFW_KEY_5 },
		{ Key::D6,				GLFW_KEY_6 },
		{ Key::D7,				GLFW_KEY_7 },
		{ Key::D8,				GLFW_KEY_8 },
		{ Key::D9,				GLFW_KEY_9 },
		{ Key::Semicolon,		GLFW_KEY_SEMICOLON },
		{ Key::Equal,			GLFW_KEY_EQUAL },
		{ Key::A,				GLFW_KEY_A },
		{ Key::B,				GLFW_KEY_B },
		{ Key::C,				GLFW_KEY_C },
		{ Key::D,				GLFW_KEY_D },
		{ Key::E,				GLFW_KEY_E },
		{ Key::F,				GLFW_KEY_F },
		{ Key::G,				GLFW_KEY_G },
		{ Key::H,				GLFW_KEY_H },
		{ Key::I,				GLFW_KEY_I },
		{ Key::J,				GLFW_KEY_J },
		{ Key::K,				GLFW_KEY_K },
		{ Key::L,				GLFW_KEY_L },
		{ Key::M,				GLFW_KEY_M },
		{ Key::N,				GLFW_KEY_N },
		{ Key::O,				GLFW_KEY_O },
		{ Key::P,				GLFW_KEY_P },
		{ Key::Q,				GLFW_KEY_Q },
		{ Key::R,				GLFW_KEY_R },
		{ Key::S,				GLFW_KEY_S },
		{ Key::T,				GLFW_KEY_T },
		{ Key::U,				GLFW_KEY_U },
		{ Key::V,				GLFW_KEY_V },
		{ Key::W,				GLFW_KEY_W },
		{ Key::X,				GLFW_KEY_X },
		{ Key::Y,				GLFW_KEY_Y },
		{ Key::Z,				GLFW_KEY_Z },
		{ Key::LeftBracket,		GLFW_KEY_LEFT_BRACKET },
		{ Key::RightBracket,	GLFW_KEY_RIGHT_BRACKET },
		{ Key::Backslash,		GLFW_KEY_BACKSLASH },
		{ Key::World1,			GLFW_KEY_WORLD_1 },
		{ Key::World2,			GLFW_KEY_WORLD_2 },
		{ Key::GraveAccent,		GLFW_KEY_GRAVE_ACCENT },
		{ Key::Escape,			GLFW_KEY_ESCAPE },
		{ Key::Enter,			GLFW_KEY_ENTER },
		{ Key::Tab,				GLFW_KEY_TAB },
		{ Key::Backspace,		GLFW_KEY_BACKSPACE },
		{ Key::Insert,			GLFW_KEY_INSERT },
		{ Key::Delete,			GLFW_KEY_DELETE },
		{ Key::Right,			GLFW_KEY_RIGHT },
		{ Key::Left,			GLFW_KEY_LEFT },
		{ Key::Down,			GLFW_KEY_DOWN },
		{ Key::Up,				GLFW_KEY_UP },
		{ Key::PageUp,			GLFW_KEY_PAGE_UP },
		{ Key::PageDown,		GLFW_KEY_PAGE_DOWN },
		{ Key::Home,			GLFW_KEY_HOME },
		{ Key::End,				GLFW_KEY_END },
		{ Key::CapsLock,		GLFW_KEY_CAPS_LOCK },
		{ Key::ScrollLock,		GLFW_KEY_SCROLL_LOCK },
		{ Key::NumLock,			GLFW_KEY_NUM_LOCK },
		{ Key::PrintScreen,		GLFW_KEY_PRINT_SCREEN },
		{ Key::Pause,			GLFW_KEY_PAUSE },
		{ Key::F1,				GLFW_KEY_F1 },
		{ Key::F2,				GLFW_KEY_F2 },
		{ Key::F3,				GLFW_KEY_F3 },
		{ Key::F4,				GLFW_KEY_F4 },
		{ Key::F5,				GLFW_KEY_F5 },
		{ Key::F6,				GLFW_KEY_F6 },
		{ Key::F7,				GLFW_KEY_F7 },
		{ Key::F8,				GLFW_KEY_F8 },
		{ Key::F9,				GLFW_KEY_F9 },
		{ Key::F10,				GLFW_KEY_F10 },
		{ Key::F11,				GLFW_KEY_F11 },
		{ Key::F12,				GLFW_KEY_F12 },
		{ Key::F13,				GLFW_KEY_F13 },
		{ Key::F14,				GLFW_KEY_F14 },
		{ Key::F15,				GLFW_KEY_F15 },
		{ Key::F16,				GLFW_KEY_F16 },
		{ Key::F17,				GLFW_KEY_F17 },
		{ Key::F18,				GLFW_KEY_F18 },
		{ Key::F19,				GLFW_KEY_F19 },
		{ Key::F20,				GLFW_KEY_F20 },
		{ Key::F21,				GLFW_KEY_F21 },
		{ Key::F22,				GLFW_KEY_F22 },
		{ Key::F23,				GLFW_KEY_F23 },
		{ Key::F24,				GLFW_KEY_F24 },
		{ Key::F25,				GLFW_KEY_F25 },
		{ Key::KP0,				GLFW_KEY_KP_0 },
		{ Key::KP1,				GLFW_KEY_KP_1 },
		{ Key::KP2,				GLFW_KEY_KP_2 },
		{ Key::KP3,				GLFW_KEY_KP_3 },
		{ Key::KP4,				GLFW_KEY_KP_4 },
		{ Key::KP5,				GLFW_KEY_KP_5 },
		{ Key::KP6,				GLFW_KEY_KP_6 },
		{ Key::KP7,				GLFW_KEY_KP_7 },
		{ Key::KP8,				GLFW_KEY_KP_8 },
		{ Key::KP9,				GLFW_KEY_KP_9 },
		{ Key::KPDecimal,		GLFW_KEY_KP_DECIMAL },
		{ Key::KPDivide,		GLFW_KEY_KP_DIVIDE },
		{ Key::KPMultiply,		GLFW_KEY_KP_MULTIPLY },
		{ Key::KPSubtract,		GLFW_KEY_KP_SUBTRACT },
		{ Key::KPAdd,			GLFW_KEY_KP_ADD },
		{ Key::KPEnter,			GLFW_KEY_KP_ENTER },
		{ Key::KPEqual,			GLFW_KEY_KP_EQUAL },
		{ Key::LeftShift,		GLFW_KEY_LEFT_SHIFT },
		{ Key::LeftControl,		GLFW_KEY_LEFT_CONTROL },
		{ Key::LeftAlt,			GLFW_KEY_LEFT_ALT },
		{ Key::LeftSuper,		GLFW_KEY_LEFT_SUPER },
		{ Key::RightShift,		GLFW_KEY_RIGHT_SHIFT },
		{ Key::RightControl,	GLFW_KEY_RIGHT_CONTROL },
		{ Key::RightAlt,		GLFW_KEY_RIGHT_ALT },
		{ Key::RightSuper,		GLFW_KEY_RIGHT_SUPER },
		{ Key::Menu,			GLFW_KEY_MENU },
	};

	void WindowsInputInterface::ValidateHoldStates() {

		for (const auto& lastFrameKeyState : _lastFrameKeys) {
			auto pair = PrismToGLFWKeyBindings.find(lastFrameKeyState.key);
			if (pair != PrismToGLFWKeyBindings.end()) {
				uint32_t glfwKey = pair->second;
				GLFWwindow* window = (GLFWwindow*)Application::Get().GetNativeWindow();
				if (glfwGetKey(window, glfwKey) == GLFW_TRUE) SetKeyPressed(lastFrameKeyState.key);
			}
		}

		for (const auto& lastFrameMouseBtnState : _lastFrameMouseBtns) {
			auto pair = PrismToGLFWMouseBtnBindings.find(lastFrameMouseBtnState.mb);
			if (pair != PrismToGLFWMouseBtnBindings.end()) {
				uint32_t glfwMb = pair->second;
				GLFWwindow* window = (GLFWwindow*)Application::Get().GetNativeWindow();
				if (glfwGetKey(window, glfwMb) == GLFW_TRUE) SetMouseBtnPressed(lastFrameMouseBtnState.mb);
			}
		}

	}

}
