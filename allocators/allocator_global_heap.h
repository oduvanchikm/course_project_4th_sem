#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_GLOBAL_HEAP_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_GLOBAL_HEAP_H

#include <allocator.h>
#include "../logger/logger_guardant.h"


class allocator_global_heap final:
    public allocator,
    private logger_guardant
{

private:
    
    logger *_logger;

public:
    
    explicit allocator_global_heap(
        logger *logger = nullptr);
    
    ~allocator_global_heap() override;
    
    allocator_global_heap(
        allocator_global_heap const &other) = delete;
    
    allocator_global_heap &operator=(
        allocator_global_heap const &other) = delete;
    
    allocator_global_heap(
        allocator_global_heap &&other) noexcept = delete;


    allocator_global_heap &operator=(
        allocator_global_heap &&other) noexcept = delete;

public:
    
    [[nodiscard]] void *allocate(
        size_t value_size,
        size_t values_count) override;
    
    void deallocate(
        void *at) override;

public:
    
    void foo()
    {};

private:
    
    inline logger *get_logger() const override;

};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_GLOBAL_HEAP_H