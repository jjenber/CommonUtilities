#pragma once
#include <wtypes.h>
#include <bitset>

namespace CommonUtilities
{
	enum class KeyCode
	{
		NotBoundKey,
		Space,
		Escape,
		Enter,
		Backspace,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		Insert,
		Home,
		PageUp,
		Delete,
		End,
		PageDown,
		Up,
		Left,
		Down,
		Right,
		Tab,
		CapsLock,
		Shift,
		Control,
		Alt,
		NumPadNumLock,
		Divide,
		Multiply,
		Minus,
		Plus,
		NumPad0,
		NumPad1,
		NumPad2,
		NumPad3,
		NumPad4,
		NumPad5,
		NumPad6,
		NumPad7,
		NumPad8,
		NumPad9,
		NumPadComma,
		Comma,
		Period,
		UnderScore,
		LessThan,
		Nr_0,
		Nr_1,
		Nr_2,
		Nr_3,
		Nr_4,
		Nr_5,
		Nr_6,
		Nr_7,
		Nr_8,
		Nr_9,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		Count,
	};

	enum class MouseButton
	{
		Left,
		Right,
		Count
	};

	class InputHandler
	{
	public:
		InputHandler();
		InputHandler(const InputHandler&)			 = delete;
		InputHandler(InputHandler&&)				 = delete;
		InputHandler operator=(const InputHandler&)	 = delete;
		InputHandler operator=(InputHandler&&)		 = delete;

		bool UpdateEvents(UINT aMessage, WPARAM aWParam, LPARAM aLParam);
		void ClearFrame();
		
		bool GetKey(KeyCode aKeyCode) const;
		bool GetKeyDown(KeyCode aKeyCode) const;
		bool GetKeyUp(KeyCode aKeyCode) const;

		bool GetMouseButton(MouseButton aButton) const;
		bool GetMouseButtonDown(MouseButton aButton) const;
		bool GetMouseButtonUp(MouseButton aButton) const;

		int GetMouseX() const;
		int GetMouseY() const;
		int GetMouseDeltaX() const;
		int GetMouseDeltaY() const;
		int GetMouseWheelDelta() const;

		void SetCursorPosition(HWND aWindow, const int aX, const int aY);

	private:
		KeyCode VkToKeyCode(WPARAM aWParam) const;
		int myMouseX;
		int myMouseXLast;
		int myMouseY;
		int myMouseYLast;
		int myMouseWheelDelta;
		std::bitset<static_cast<size_t>(KeyCode::Count)> myKeyboardStateLast;
		std::bitset<static_cast<size_t>(KeyCode::Count)> myKeyboardState;
		std::bitset<static_cast<size_t>(MouseButton::Count)> myMouseState;
		std::bitset<static_cast<size_t>(MouseButton::Count)> myMouseStateLast;
	};
}

