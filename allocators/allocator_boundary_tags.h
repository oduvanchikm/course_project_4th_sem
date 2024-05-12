#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BOUNDARY_TAGS_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BOUNDARY_TAGS_H

#include <allocator_guardant.h>
#include <allocator_with_fit_mode.h>
#include <../logger/logger_guardant.h>
#include <mutex>

class allocator_boundary_tags final:
    private allocator_guardant,
    public allocator_with_fit_mode,
    private logger_guardant
{

private:
    
    void *_trusted_memory;

public:
    
    ~allocator_boundary_tags() override;
    
    allocator_boundary_tags(
        allocator_boundary_tags const &other) = delete;
    
    allocator_boundary_tags &operator=(
        allocator_boundary_tags const &other) = delete;
    
    allocator_boundary_tags(
        allocator_boundary_tags &&other) noexcept;
    
    allocator_boundary_tags &operator=(
        allocator_boundary_tags &&other) noexcept;

public:
    
    explicit allocator_boundary_tags(
            size_t space_size,
            allocator *parent_allocator = nullptr,
            logger *logger = nullptr,
            fit_mode allocate_fit_mode = allocator_with_fit_mode::fit_mode::first_fit);

public:
    
    [[nodiscard]] void *allocate(
        size_t value_size,
        size_t values_count) override;
    
    void deallocate(
        void *at) override;

public:
    
    inline void set_fit_mode(
        allocator_with_fit_mode::fit_mode mode) override;

private:
    
    inline allocator *get_allocator() const noexcept override;

private:
    
    inline logger *get_logger() const override;

private:

    size_t get_small_meta_size() const noexcept;

    size_t get_ancillary_space_size() const noexcept;

    inline size_t get_size_of_allocator() const noexcept;

    inline allocator_with_fit_mode::fit_mode get_fit_mode() const noexcept;

    inline std::mutex* get_mutex() const noexcept;

    inline size_t get_available_size() const noexcept;

    inline void* get_first_occupied_block() const noexcept;

    size_t get_size_occupied_block(void* block_address) const noexcept;

    inline void* get_previous_occupied_block(void* block_address) const noexcept;

    inline void* get_next_occupied_block(void* block_address) const noexcept;

    size_t get_available_block_size(void* block_address) const;

    unsigned char* get_end_of_block(void* block_address) const noexcept;

    unsigned char* get_start_of_block(void* block_address) const noexcept;

    void my_logger(std::string const &message, logger::severity severity) const;

};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BOUNDARY_TAGS_H