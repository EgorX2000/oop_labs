#pragma once

#include <algorithm>
#include <cstddef>
#include <memory_resource>
#include <stdexcept>
#include <vector>

class FixedMemoryResource : public std::pmr::memory_resource {
   public:
    explicit FixedMemoryResource(size_t blockSize, size_t blockCount)
        : blockSize_(blockSize),
          blockCount_(blockCount),
          memoryPool_(blockSize * blockCount),
          freeBlocks_() {
        for (size_t i = 0; i < blockCount; ++i) {
            freeBlocks_.push_back(&memoryPool_[i * blockSize_]);
        }
    }

    ~FixedMemoryResource() override {
        memoryPool_.clear();
        freeBlocks_.clear();
    }

   protected:
    void* do_allocate(size_t bytes, size_t alignment) override {
        if (bytes > blockSize_ || freeBlocks_.empty()) {
            throw std::bad_alloc();
        }

        void* block = freeBlocks_.back();
        freeBlocks_.pop_back();
        return block;
    }

    void do_deallocate(void* p, size_t bytes, size_t alignment) override {
        if (p) {
            freeBlocks_.push_back(static_cast<char*>(p));
        }
    }

    bool do_is_equal(
        const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

   private:
    size_t blockSize_;
    size_t blockCount_;
    std::vector<char> memoryPool_;
    std::vector<void*> freeBlocks_;
};