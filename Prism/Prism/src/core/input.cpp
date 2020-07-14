#include "core/logger.h"
#include "core/input.h"

#include "platform/windows/windowsinput.h"

namespace Prism {

	std::shared_ptr<InputInterface> Input::_interface = std::make_shared<WindowsInputInterface>();

	void InputInterface::SwapStates() {
		_lastFrameKeys = std::move(_currentFrameKeys);
		_lastFrameMouseBtns = std::move(_currentFrameMouseBtns);
		_currentFrameKeys.clear();
		_currentFrameMouseBtns.clear();
	}

	bool InputInterface::IsKeyPressed(Key k) {
		for (const auto& currentKeyState : _currentFrameKeys) {
			if (currentKeyState.key == k) return true;
		}
		return false;
	}

	bool InputInterface::IsKeyReleased(Key k) {
		for (const auto& currentKeyState : _currentFrameKeys) {
			if (currentKeyState.key == k) {
				return false;
			}
		}
		for (const auto& lastKeyState : _lastFrameKeys) {
			if (lastKeyState.key == k) {
				return true;
			}
		}
		return false;
	}

	bool InputInterface::IsMouseBtnPressed(MouseBtn mb) {
		for (const auto& currentMouseBtnState : _currentFrameMouseBtns) {
			if (currentMouseBtnState.mb == mb) return true;
		}
		return false;
	}

	bool InputInterface::IsMouseBtnReleased(MouseBtn mb) {
		for (const auto& currentMouseBtnState : _currentFrameMouseBtns) {
			if (currentMouseBtnState.mb == mb) return false;
		}
		for (const auto& lastMouseBtnState : _lastFrameMouseBtns) {
			if (lastMouseBtnState.mb == mb) return true;
		}
		return false;
	}

	uint32_t InputInterface::IsKeyHeld(Key k) {
		for (const auto& currentKeyState : _currentFrameKeys) {
			if (currentKeyState.key == k) return currentKeyState.holdframes;
		}
		return 0;
	}

	uint32_t InputInterface::IsMouseBtnHeld(MouseBtn mb) {
		for (const auto& currentMouseBtnState : _currentFrameMouseBtns) {
			if (currentMouseBtnState.mb == mb) return currentMouseBtnState.holdframes;
		}
		return 0;
	}

	void InputInterface::SetKeyPressed(Key key) {

		for (const auto& lastKeyState : _lastFrameKeys) {
			if (lastKeyState.key == key) {
				_currentFrameKeys.push_back({ key, lastKeyState.holdframes + 1 });
				return;
			}
		}

		_currentFrameKeys.push_back({ key, 0 });

	}

	void InputInterface::SetMouseBtnPressed(MouseBtn mb) {

		for (const auto& lastMouseBtnState : _lastFrameMouseBtns) {
			if (lastMouseBtnState.mb == mb) {
				_currentFrameMouseBtns.push_back({ mb, lastMouseBtnState.holdframes + 1 });
				return;
			}
		}

		_currentFrameMouseBtns.push_back({ mb, 0 });

	}

}