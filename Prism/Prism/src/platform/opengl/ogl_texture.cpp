#include "core/core.h"
#include "platform/opengl/ogl_texture.h"

#include <glad/glad.h>

namespace Prism {

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

	void OpenGLTexture2D::Bind() {
		glBindTextureUnit(0, _tid);
	}

}