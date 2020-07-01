#pragma once
#include <map>
#include <GLFW/glfw3.h>
#include <core/input.h>
#include <core/application.h>

namespace Prism {

	class WindowsInputStrategy : public InputStrategy {

	public:
		WindowsInputStrategy();
		virtual ~WindowsInputStrategy();
		virtual bool f_IsKeyPressed(Key);
		virtual bool f_IsKeyHeld(Key);
		virtual bool f_IsMouseButtonPressed(MouseBtn);
		virtual std::pair<float, float> f_GetMouseCursorPosition();

	protected:
		typedef std::map<Key, std::pair<Key, int32_t>> InputMap;
		typedef std::pair<Key, int32_t> InputPair;
		const InputMap _prismToGlfwKeyMap{ // Paired for bi-dir conversion
			{ Key::Space,			InputPair{Key::Space, GLFW_KEY_SPACE} },
			{ Key::Apostrophe,		InputPair{Key::Apostrophe, GLFW_KEY_APOSTROPHE} },
			{ Key::Comma,			InputPair{Key::Comma, GLFW_KEY_COMMA} },
			{ Key::Minus,			InputPair{Key::Minus, GLFW_KEY_MINUS} },
			{ Key::Period,			InputPair{Key::Period, GLFW_KEY_PERIOD} },
			{ Key::Slash,			InputPair{Key::Slash, GLFW_KEY_SLASH} },
			{ Key::D0,				InputPair{Key::D0, GLFW_KEY_0} },
			{ Key::D1,				InputPair{Key::D1, GLFW_KEY_1} },
			{ Key::D2,				InputPair{Key::D2, GLFW_KEY_2} },
			{ Key::D3,				InputPair{Key::D3, GLFW_KEY_3} },
			{ Key::D4,				InputPair{Key::D4, GLFW_KEY_4} },
			{ Key::D5,				InputPair{Key::D5, GLFW_KEY_5} },
			{ Key::D6,				InputPair{Key::D6, GLFW_KEY_6} },
			{ Key::D7,				InputPair{Key::D7, GLFW_KEY_7} },
			{ Key::D8,				InputPair{Key::D8, GLFW_KEY_8} },
			{ Key::D9,				InputPair{Key::D9, GLFW_KEY_9} },
			{ Key::Semicolon,		InputPair{Key::Semicolon, GLFW_KEY_SEMICOLON} },
			{ Key::Equal,			InputPair{Key::Equal, GLFW_KEY_EQUAL} },
			{ Key::A,				InputPair{Key::A, GLFW_KEY_A} },
			{ Key::B,				InputPair{Key::B, GLFW_KEY_B} },
			{ Key::C,				InputPair{Key::C, GLFW_KEY_C} },
			{ Key::D,				InputPair{Key::D, GLFW_KEY_D} },
			{ Key::E,				InputPair{Key::E, GLFW_KEY_E} },
			{ Key::F,				InputPair{Key::F, GLFW_KEY_F} },
			{ Key::G,				InputPair{Key::G, GLFW_KEY_G} },
			{ Key::H,				InputPair{Key::H, GLFW_KEY_H} },
			{ Key::I,				InputPair{Key::I, GLFW_KEY_I} },
			{ Key::J,				InputPair{Key::J, GLFW_KEY_J} },
			{ Key::K,				InputPair{Key::K, GLFW_KEY_K} },
			{ Key::L,				InputPair{Key::L, GLFW_KEY_L} },
			{ Key::M,				InputPair{Key::M, GLFW_KEY_M} },
			{ Key::N,				InputPair{Key::N, GLFW_KEY_N} },
			{ Key::O,				InputPair{Key::O, GLFW_KEY_O} },
			{ Key::P,				InputPair{Key::P, GLFW_KEY_P} },
			{ Key::Q,				InputPair{Key::Q, GLFW_KEY_Q} },
			{ Key::R,				InputPair{Key::R, GLFW_KEY_R} },
			{ Key::S,				InputPair{Key::S, GLFW_KEY_S} },
			{ Key::T,				InputPair{Key::T, GLFW_KEY_T} },
			{ Key::U,				InputPair{Key::U, GLFW_KEY_U} },
			{ Key::V,				InputPair{Key::V, GLFW_KEY_V} },
			{ Key::W,				InputPair{Key::W, GLFW_KEY_W} },
			{ Key::X,				InputPair{Key::X, GLFW_KEY_X} },
			{ Key::Y,				InputPair{Key::Y, GLFW_KEY_Y} },
			{ Key::Z,				InputPair{Key::Z, GLFW_KEY_Z} },
			{ Key::LeftBracket,		InputPair{Key::LeftBracket, GLFW_KEY_LEFT_BRACKET} },
			{ Key::RightBracket,	InputPair{Key::RightBracket, GLFW_KEY_RIGHT_BRACKET} },
			{ Key::Backslash,		InputPair{Key::Backslash, GLFW_KEY_BACKSLASH} },
			{ Key::World1,			InputPair{Key::World1, GLFW_KEY_WORLD_1} },
			{ Key::World2,			InputPair{Key::World2, GLFW_KEY_WORLD_2} },
			{ Key::GraveAccent,		InputPair{Key::GraveAccent, GLFW_KEY_GRAVE_ACCENT} },
			{ Key::Escape,			InputPair{Key::Escape, GLFW_KEY_ESCAPE} },
			{ Key::Enter,			InputPair{Key::Enter, GLFW_KEY_ENTER} },
			{ Key::Tab,				InputPair{Key::Tab, GLFW_KEY_TAB} },
			{ Key::Backspace,		InputPair{Key::Backspace, GLFW_KEY_BACKSPACE} },
			{ Key::Insert,			InputPair{Key::Insert, GLFW_KEY_INSERT} },
			{ Key::Delete,			InputPair{Key::Delete, GLFW_KEY_DELETE} },
			{ Key::Right,			InputPair{Key::Right, GLFW_KEY_RIGHT} },
			{ Key::Left,			InputPair{Key::Left, GLFW_KEY_LEFT} },
			{ Key::Down,			InputPair{Key::Down, GLFW_KEY_DOWN} },
			{ Key::Up,				InputPair{Key::Up, GLFW_KEY_UP} },
			{ Key::PageUp,			InputPair{Key::PageUp, GLFW_KEY_PAGE_UP} },
			{ Key::PageDown,		InputPair{Key::PageDown, GLFW_KEY_PAGE_DOWN} },
			{ Key::Home,			InputPair{Key::Home, GLFW_KEY_HOME} },
			{ Key::End,				InputPair{Key::End, GLFW_KEY_END} },
			{ Key::CapsLock,		InputPair{Key::CapsLock, GLFW_KEY_CAPS_LOCK} },
			{ Key::ScrollLock,		InputPair{Key::ScrollLock, GLFW_KEY_SCROLL_LOCK} },
			{ Key::NumLock,			InputPair{Key::NumLock, GLFW_KEY_NUM_LOCK} },
			{ Key::PrintScreen,		InputPair{Key::PrintScreen, GLFW_KEY_PRINT_SCREEN} },
			{ Key::Pause,			InputPair{Key::Pause, GLFW_KEY_PAUSE} },
			{ Key::F1,				InputPair{Key::F1, GLFW_KEY_F1} },
			{ Key::F2,				InputPair{Key::F2, GLFW_KEY_F2} },
			{ Key::F3,				InputPair{Key::F3, GLFW_KEY_F3} },
			{ Key::F4,				InputPair{Key::F4, GLFW_KEY_F4} },
			{ Key::F5,				InputPair{Key::F5, GLFW_KEY_F5} },
			{ Key::F6,				InputPair{Key::F6, GLFW_KEY_F6} },
			{ Key::F7,				InputPair{Key::F7, GLFW_KEY_F7} },
			{ Key::F8,				InputPair{Key::F8, GLFW_KEY_F8} },
			{ Key::F9,				InputPair{Key::F9, GLFW_KEY_F9} },
			{ Key::F10,				InputPair{Key::F10, GLFW_KEY_F10} },
			{ Key::F11,				InputPair{Key::F11, GLFW_KEY_F11} },
			{ Key::F12,				InputPair{Key::F12, GLFW_KEY_F12} },
			{ Key::F13,				InputPair{Key::F13, GLFW_KEY_F13} },
			{ Key::F14,				InputPair{Key::F14, GLFW_KEY_F14} },
			{ Key::F15,				InputPair{Key::F15, GLFW_KEY_F15} },
			{ Key::F16,				InputPair{Key::F16, GLFW_KEY_F16} },
			{ Key::F17,				InputPair{Key::F17, GLFW_KEY_F17} },
			{ Key::F18,				InputPair{Key::F18, GLFW_KEY_F18} },
			{ Key::F19,				InputPair{Key::F19, GLFW_KEY_F19} },
			{ Key::F20,				InputPair{Key::F20, GLFW_KEY_F20} },
			{ Key::F21,				InputPair{Key::F21, GLFW_KEY_F21} },
			{ Key::F22,				InputPair{Key::F22, GLFW_KEY_F22} },
			{ Key::F23,				InputPair{Key::F23, GLFW_KEY_F23} },
			{ Key::F24,				InputPair{Key::F24, GLFW_KEY_F24} },
			{ Key::F25,				InputPair{Key::F25, GLFW_KEY_F25} },
			{ Key::KP0,				InputPair{Key::KP0, GLFW_KEY_KP_0} },
			{ Key::KP1,				InputPair{Key::KP1, GLFW_KEY_KP_1} },
			{ Key::KP2,				InputPair{Key::KP2, GLFW_KEY_KP_2} },
			{ Key::KP3,				InputPair{Key::KP3, GLFW_KEY_KP_3} },
			{ Key::KP4,				InputPair{Key::KP4, GLFW_KEY_KP_4} },
			{ Key::KP5,				InputPair{Key::KP5, GLFW_KEY_KP_5} },
			{ Key::KP6,				InputPair{Key::KP6, GLFW_KEY_KP_6} },
			{ Key::KP7,				InputPair{Key::KP7, GLFW_KEY_KP_7} },
			{ Key::KP8,				InputPair{Key::KP8, GLFW_KEY_KP_8} },
			{ Key::KP9,				InputPair{Key::KP9, GLFW_KEY_KP_9} },
			{ Key::KPDecimal,		InputPair{Key::KPDecimal, GLFW_KEY_KP_DECIMAL} },
			{ Key::KPDivide,		InputPair{Key::KPDivide, GLFW_KEY_KP_DIVIDE} },
			{ Key::KPMultiply,		InputPair{Key::KPMultiply, GLFW_KEY_KP_MULTIPLY} },
			{ Key::KPSubtract,		InputPair{Key::KPSubtract, GLFW_KEY_KP_SUBTRACT} },
			{ Key::KPAdd,			InputPair{Key::KPAdd, GLFW_KEY_KP_ADD} },
			{ Key::KPEnter,			InputPair{Key::KPEnter, GLFW_KEY_KP_ENTER} },
			{ Key::KPEqual,			InputPair{Key::KPEqual, GLFW_KEY_KP_EQUAL} },
			{ Key::LeftShift,		InputPair{Key::LeftShift, GLFW_KEY_LEFT_SHIFT} },
			{ Key::LeftControl,		InputPair{Key::LeftControl, GLFW_KEY_LEFT_CONTROL} },
			{ Key::LeftAlt,			InputPair{Key::LeftAlt, GLFW_KEY_LEFT_ALT} },
			{ Key::LeftSuper,		InputPair{Key::LeftSuper, GLFW_KEY_LEFT_SUPER} },
			{ Key::RightShift,		InputPair{Key::RightShift, GLFW_KEY_RIGHT_SHIFT} },
			{ Key::RightControl,	InputPair{Key::RightControl, GLFW_KEY_RIGHT_CONTROL} },
			{ Key::RightAlt,		InputPair{Key::RightAlt, GLFW_KEY_RIGHT_ALT} },
			{ Key::RightSuper,		InputPair{Key::RightSuper, GLFW_KEY_RIGHT_SUPER} },
			{ Key::Menu,			InputPair{Key::Menu, GLFW_KEY_MENU} },

		};
	
		typedef std::map<MouseBtn, std::pair<MouseBtn, int32_t>> ButtonMap;
		typedef std::pair<MouseBtn, int32_t> ButtonPair;
		ButtonMap _ptrismToGlfwMouseBtnMap{
			{ MouseBtn::Button0, {MouseBtn::Button0, GLFW_MOUSE_BUTTON_1} },
			{ MouseBtn::Button1, {MouseBtn::Button1, GLFW_MOUSE_BUTTON_2} },
			{ MouseBtn::Button2, {MouseBtn::Button2, GLFW_MOUSE_BUTTON_3} },
			{ MouseBtn::Button3, {MouseBtn::Button3, GLFW_MOUSE_BUTTON_4} },
			{ MouseBtn::Button4, {MouseBtn::Button4, GLFW_MOUSE_BUTTON_5} },
			{ MouseBtn::Button5, {MouseBtn::Button5, GLFW_MOUSE_BUTTON_6} },
			{ MouseBtn::Button6, {MouseBtn::Button6, GLFW_MOUSE_BUTTON_7} },
			{ MouseBtn::Button7, {MouseBtn::Button7, GLFW_MOUSE_BUTTON_8} },
			{ MouseBtn::ButtonLast, {MouseBtn::ButtonLast, GLFW_MOUSE_BUTTON_8} },
			{ MouseBtn::ButtonLeft, {MouseBtn::ButtonLeft, GLFW_MOUSE_BUTTON_LEFT} },
			{ MouseBtn::ButtonRight, {MouseBtn::ButtonRight, GLFW_MOUSE_BUTTON_RIGHT} },
			{ MouseBtn::ButtonMiddle, {MouseBtn::ButtonMiddle, GLFW_MOUSE_BUTTON_MIDDLE} },
		};

	};

}