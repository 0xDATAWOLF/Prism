#pragma once
#include "renderer/texture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Prism {

	class OpenGLTexture2D : public Texture2D {
	
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(std::string filepath);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;
		virtual void Bind(uint32_t index = 0) override;
		virtual void SetData(void* data, uint32_t size) override;

		uint32_t GetIdentifier();

		virtual bool operator==(const Texture&);

	private:
		std::string _filepath;
		uint32_t _tid;
		uint32_t _width{ 0 };
		uint32_t _height{ 0 };
		GLenum _textureDataType;
		GLenum _baseTextureDataType;

	};

}