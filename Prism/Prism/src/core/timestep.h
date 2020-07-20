#pragma once
#include <chrono>

namespace Prism {

	class Timestep {

	public:
		friend Application;

		Timestep()
			: _t1(std::chrono::high_resolution_clock::now()),
			  _t2(std::chrono::high_resolution_clock::now()) {};
		~Timestep() {};

		inline float GetDeltaInSeconds() const {
			return std::chrono::duration<float>(_t2 - _t1).count();
		}

		inline float GetDeltaInMilliseconds() const {
			return std::chrono::duration<float>(_t2 - _t1).count()*1000;
		};

	private:
		inline void Update() {
			_t1 = _t2;
			_t2 = std::chrono::high_resolution_clock::now();
		}

	private:
		std::chrono::high_resolution_clock::time_point _t1;
		std::chrono::high_resolution_clock::time_point _t2;

	};

};