#pragma once

namespace Walnut
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: mTime(time)
		{

		}
		float GetSeconds() const { return mTime; }
		float GetMilliSeconds() const { return mTime * 1000.0f; }
	private:
		float mTime;
	};
}