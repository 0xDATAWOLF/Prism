#pragma once
#include "renderer/texture.h"
#include <stb_image.h>

namespace Prism {

	class OpenGLTexture2D : public Texture2D {
	
	public:
		OpenGLTexture2D(std::string filepath);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;
		virtual void Bind() override;

	private:
		std::string _filepath;
		uint32_t _tid;
		uint32_t _width{ 0 };
		uint32_t _height{ 0 };

	};

}