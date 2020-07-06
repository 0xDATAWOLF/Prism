#pragma once
#include <core/core.h>

namespace Prism {

	class Shader {

	public:
		Shader(std::string, std::string);
		virtual ~Shader();
		void Bind();
		void Unbind();

	protected:
		uint32_t _prog;

	};

}