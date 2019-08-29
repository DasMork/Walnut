#pragma once

namespace Walnut
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetID() const = 0;

		static Texture* Create(const std::string& filePath);

	};
}
