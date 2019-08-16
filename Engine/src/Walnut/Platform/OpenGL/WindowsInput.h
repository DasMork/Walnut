#pragma once

#include "Walnut/Input.h"

namespace Walnut
{
	class WindowsInput : public Input
	{
	protected:
		// Geerbt über Input
		virtual bool GetKeyImpl(int keycode) override;
		virtual bool GetMouseButtonImpl(int button) override;

		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual float GetMousePosXImpl() override;
		virtual float GetMousePosYImpl() override;

	};
}