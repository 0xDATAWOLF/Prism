#pragma once
#include <vector>
#include <stdint.h>
#include <stdlib.h>

namespace Prism {

	enum class MemBlockType {
		Null, Layer
	};

	class MemoryBlock {
	public:
		MemoryBlock();
		virtual ~MemoryBlock();

		inline bool IsUsed() { return _blockUsed; }
		inline MemBlockType GetMemBlockType() { return _type; }
		inline void SetUsed(bool u, void* o, MemBlockType m) {
			_blockUsed = u; _objectPtr = o; _type = m; }

	private:
		MemBlockType _type{ MemBlockType::Null };
		bool _blockUsed{ false };
		void* _objectPtr{ nullptr };
	};

	class MemoryManager {

	public:
		MemoryManager(uint32_t memsize = 256, uint32_t blocksize = 32);
		virtual ~MemoryManager();

	private:
		uint64_t _mempoolSize;
		uint64_t _memblockSize;
		void* _memPoolPtr = nullptr;
		std::vector<MemoryBlock*> _memblocks;

	};

}