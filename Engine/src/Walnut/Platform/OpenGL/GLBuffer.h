#pragma once
#include "Walnut/Graphics/Buffer.h"


namespace Walnut
{
	class GLVertexBuffer : public VertexBuffer
	{
	public:
		GLVertexBuffer(float* vertices, uint32_t size);
		virtual ~GLVertexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		void SetLayout(const BufferLayout& layout) override;
		const BufferLayout& GetLayout() const override { return mLayout; }
	private:
		uint32_t mRenderID;
		BufferLayout mLayout;
	};

	class GLIndexBuffer : public IndexBuffer
	{
	public:
		GLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~GLIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		inline uint32_t GetCount() const override { return mCount; }

	private:
		uint32_t mRenderID;
		uint32_t mCount;
	};
}
