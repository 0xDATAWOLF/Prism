#include "core/core.h"
#include "platform/opengl/ogl_texture.h"

namespace Prism {

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) {
		_width = width;
		_height = height;
		_textureDataType = GL_RGBA8;
		_baseTextureDataType = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &_tid);
		glTextureStorage2D(_tid, 1, _textureDataType, _width, _height);

		glTextureParameteri(_tid, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_tid, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	}

	OpenGLTexture2D::OpenGLTexture2D(std::string filepath) {
		_filepath = filepath;
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		PRISM_ASSERT(data, "Failed to load image!");
		_width = width;
		_height = height;

		GLenum a{ 0 }, b{ 0 };
		if (channels == 3) { a = GL_RGB8; b = GL_RGB; }
		if (channels == 4) { a = GL_RGBA8; b = GL_RGBA; }
		PRISM_ASSERT((a & b), "Unknown number of channels!");

		glCreateTextures(GL_TEXTURE_2D, 1, &_tid);
		glTextureStorage2D(_tid, 1, a, _width, _height);

		glTextureParameteri(_tid, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_tid, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(_tid, 0, 0, 0, _width, _height, b, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &_tid);
	}


	uint32_t OpenGLTexture2D::GetWidth() const { return _width; }
	uint32_t OpenGLTexture2D::GetHeight() const { return _height; }

	void OpenGLTexture2D::Bind(uint32_t index) {
		glBindTextureUnit(index, _tid);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size) {
		uint32_t bpp = (_baseTextureDataType == GL_RGBA) ? 4 : 3;
		PRISM_ASSERT((_width * _height * bpp) == size, "Size not set correctly.");
		glTextureSubImage2D(_tid, 0, 0, 0, _width, _height, _baseTextureDataType, GL_UNSIGNED_BYTE, data);
	}

	bool OpenGLTexture2D::operator==(const Texture& rhs) {
		return (_tid == ((OpenGLTexture2D&)rhs)._tid);
	}

}