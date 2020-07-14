#pragma once
#include <unordered_map>
#include <memory>
#include <string>

namespace Prism {

	// -------------------------------------------------------
	// --- Shader --------------------------------------------
	// -------------------------------------------------------

	enum class ShaderType { Null = 0, Vertex, Pixel };

	class Shader {

	public:
		virtual ~Shader() {};

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual std::string GetName() const = 0;

		static Shader* Create(std::string filepath);

	};

	// -------------------------------------------------------
	// --- Shader Library ------------------------------------
	// -------------------------------------------------------

	class ShaderLibrary {

	public:
		virtual ~ShaderLibrary() {};

		void Add(std::string filepath);
		bool Exists(std::string name);
		std::shared_ptr<Shader>& Get(std::string name);
	
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> _shaders;

	};

}