#pragma once
#include <string>
#include <cstdint>

#include "core/core.h"

namespace Prism {

	// -------------------------------------------------------
	// --- Texture -------------------------------------------
	// -------------------------------------------------------

	class Texture { // base interface for texture classes

	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual bool operator==(const Texture&) = 0;

		virtual void Bind(uint32_t index = 0) = 0;

	};



	// -------------------------------------------------------
	// --- Texture2D -----------------------------------------
	// -------------------------------------------------------

	class Texture2D : public Texture {

	public:
		virtual ~Texture2D() = default;

		virtual void SetData(void* data, uint32_t size) = 0;
		virtual bool operator==(const Texture&) = 0;

		static Ref<Texture2D> Create(std::string filepath);
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);

	};

}