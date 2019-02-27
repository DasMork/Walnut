#pragma once

#include "Event.h"

namespace Walnut
{
	class WALNUT_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return mKeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			: mKeyCode(keycode)
		{
		}

		int mKeyCode;
	};

	class WALNUT_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), mRepeatCount(repeatCount)
		{
		}

		inline int GetRepeatCount() const { return mRepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << mKeyCode << " ( " << mRepeatCount << " )";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);
	private:
		int mRepeatCount;
	};

	class WALNUT_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode)
		{
		}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << mKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);
	};


}