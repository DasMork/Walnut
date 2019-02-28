#pragma once

#include "Core.h"

namespace Walnut
{
	class WALNUT_API Input
	{
	public:
		inline static bool GetKey(int keycode) { return sInstance->GetKeyImpl(keycode); }

		inline static bool GetMouseButton(int button) { return sInstance->GetMouseButtonImpl(button); }
		inline static std::pair<float, float> GetMousePos() { return sInstance->GetMousePosImpl(); }
		inline static float GetMousePosX() { return sInstance->GetMousePosXImpl(); }
		inline static float GetMousePosY() { return sInstance->GetMousePosYImpl(); }

	protected:
		virtual bool GetKeyImpl(int keycode) = 0;

		virtual bool GetMouseButtonImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual float GetMousePosXImpl() = 0;
		virtual float GetMousePosYImpl() = 0;

	private:
		static Input* sInstance;
	};
}