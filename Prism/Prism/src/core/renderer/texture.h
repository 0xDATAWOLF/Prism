#pragma once
#include <string>
#include <cstdint>

namespace Prism {

	// -------------------------------------------------------
	// --- Texture -------------------------------------------
	// -------------------------------------------------------

	class Texture { // base interface for texture classes

	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind() = 0;

	};



	// -------------------------------------------------------
	// --- Texture2D -----------------------------------------
	// -------------------------------------------------------

	class Texture2D : public Texture {

	public:
		virtual ~Texture2D() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind() = 0;

		static Texture2D* Create(std::string filepath);

	};

}