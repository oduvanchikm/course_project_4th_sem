#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BUDDIES_SYSTEM_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BUDDIES_SYSTEM_H

#include "allocator_guardant.h"
#include "allocator.h"
#include "allocator_with_fit_mode.h"
#include <cmath>
#include <mutex>
#include <sstream>
#include <thread>
#include "../logger/logger_guardant.h"

class allocator_buddies_system final:
        private allocator_guardant,
        public allocator_with_fit_mode,
        private logger_guardant
{

private:

    void *_trusted_memory;

public:

    ~allocator_buddies_system() override;

    allocator_buddies_system(
            allocator_buddies_system const &other) = delete;

    allocator_buddies_system &operator=(
            allocator_buddies_system const &other) = delete;

    allocator_buddies_system(
            allocator_buddies_system &&other) noexcept;

    allocator_buddies_system &operator=(
            allocator_buddies_system &&other) noexcept;

public:

    explicit allocator_buddies_system(
            size_t space_size_power_of_two,
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

    inline void set_fit_mode(allocator_with_fit_mode::fit_mode mode) override;

private:

    size_t get_ancillary_space_size() const noexcept;

private:

    void* get_buddy(void* target_block_first_buddy) noexcept;

    void* get_start_allocated_memory_address() noexcept;

    bool is_free_block(void *block_memory) const;

private:

    inline allocator *get_allocator() const override;

    inline logger *get_logger() const override;

    allocator_with_fit_mode::fit_mode get_fit_mode() const noexcept;

    std::mutex* get_mutex() noexcept;

    void* get_first_available_block() const noexcept;

    short get_power_of_block_size(void* available_block_address) const;

    void* get_next_block(void* block_address) const noexcept;

    void* get_next_available_block(void* address_block) const;

    short get_power_of_two_up(size_t number);

    size_t* get_free_size() const noexcept;

    size_t get_meta_block() const;

};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BUDDIES_SYSTEM_H
