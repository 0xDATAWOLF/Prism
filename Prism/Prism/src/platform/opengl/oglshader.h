#include <core/renderer/shader.h>

namespace Prism {

	class OpenGLShader : public Shader {

	public:
		OpenGLShader();
		virtual ~OpenGLShader();

		virtual void AddShaderSource(std::string, ShaderType);
		virtual void Compile();
		virtual void Bind();
		virtual void Unbind();

	protected:
		uint32_t GenerateShader(ShaderType);

		std::vector<uint32_t> _shaders;
		uint32_t _program;

	};

}