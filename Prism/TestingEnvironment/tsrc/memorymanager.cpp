#include "memorymanager.h"
#include <core/logger.h>

namespace Prism {

	MemoryManager::MemoryManager(uint32_t memsize, uint32_t blocksize) {

		// Check if memsize > blocksize.
		if (memsize < blocksize) {
			CORE_ERROR("MemoryManager blocksize can not be greater than memsize.");
			CORE_ERROR("MemoryManager is defaulting to memsize {}bytes and blocksize {}bytes.");
			memsize = 256;
			blocksize = 32;
		}

		// Check if the blocks are uneven.
		int remainder = memsize % blocksize;
		memsize = memsize - remainder;
		if (remainder != 0) {
			std::string msg = "MemoryManager memsize and blocksize don't create event partitions, {}bytes remain, memsize approximated to {}bytes instead.";
			CORE_WARN(msg, remainder, memsize);
		}

		int numBlocks = memsize / blocksize;
		_mempoolSize = memsize;
		_memblockSize = blocksize;
		_memPoolPtr = calloc(_mempoolSize, 1);
		for (int i = 0; i < numBlocks; i++) _memblocks.emplace_back(new MemoryBlock);

		CORE_INFO("MemoryManager allocated {}bytes split into {} blocks.", memsize, numBlocks);
	}

	MemoryManager::~MemoryManager() {
		for (auto p : _memblocks) delete p;
		free(_memPoolPtr);
	}

	MemoryBlock::MemoryBlock() {}

	MemoryBlock::~MemoryBlock() {}

}
