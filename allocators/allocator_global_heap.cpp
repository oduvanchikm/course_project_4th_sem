#include <allocator_global_heap.h>
#include <string>

allocator_global_heap::allocator_global_heap(logger *logger)
{
    if (logger != nullptr)
    {
        logger->debug("ALLOCATOR_GLOBAL_HEAP: constructor has called");
    }

    _logger = logger;
}

allocator_global_heap::~allocator_global_heap()
{
    debug_with_guard("ALLOCATOR_GLOBAL_HEAP: destructor has called");
}

[[nodiscard]] void *allocator_global_heap::allocate(size_t value_size, size_t values_count)
{
    debug_with_guard("ALLOCATOR_GLOBAL_HEAP: allocate method is started");

    size_t requested_size = value_size * values_count;

    size_t common_size = requested_size + sizeof(size_t) + sizeof(allocator*);

    void* target_block;

    try
    {
        target_block = ::operator new(common_size);
    }
    catch (std::bad_alloc const &ex)
    {
        error_with_guard("ALLOCATOR_GLOBAL_HEAP: can't allocate memory");
        throw std::bad_alloc();
    }

    auto** allocator_ptr = reinterpret_cast<allocator**>(target_block);
    *allocator_ptr = this;
    auto* block_size = reinterpret_cast<size_t*>(allocator_ptr) + 1;
    *block_size = requested_size;

    debug_with_guard("ALLOCATOR_GLOBAL_HEAP: allocate method has finished");

    return reinterpret_cast<unsigned char*>(target_block) + sizeof(size_t) + sizeof(allocator*);
}

void allocator_global_heap::deallocate(void *at)
{
    trace_with_guard("ALLOCATOR_GLOBAL_HEAP: deallocate method is started");

    void* block = reinterpret_cast<void *>(reinterpret_cast<unsigned char*>(at) - sizeof(size_t));
    size_t* block_size = reinterpret_cast<size_t*>(block);

    allocator* allocator_ptr;

    allocator_ptr = *reinterpret_cast<allocator**>(block_size - 1);
    if (allocator_ptr != this)
    {
        error_with_guard("ALLOCATOR_GLOBAL_HEAP: can't deallocate memory");
        throw std::bad_alloc();
    }

    ::operator delete(allocator_ptr);

    debug_with_guard("ALLOCATOR_GLOBAL_HEAP: deallocate method has finished");
}

inline logger *allocator_global_heap::get_logger() const
{
    return _logger;
}