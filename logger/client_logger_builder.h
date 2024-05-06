#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_CLIENT_LOGGER_BUILDER_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_CLIENT_LOGGER_BUILDER_H

#include "logger_builder.h"
#include "client_logger.h"
#include <map>

class client_logger_builder final : public logger_builder
{

private:

    std::map<std::string, std::set<logger::severity>> _streams_in_builder;

public:

    client_logger_builder();

    client_logger_builder(
            client_logger_builder const &other) = delete;

    client_logger_builder &operator=(
            client_logger_builder const &other) = delete;

    client_logger_builder(
            client_logger_builder &&other) noexcept = delete;

    client_logger_builder &operator=(
            client_logger_builder &&other) noexcept = delete;

    ~client_logger_builder() noexcept override;

public:

    logger_builder *add_file_stream(
            std::string const &stream_file_path,
            logger::severity severity) override;

    logger_builder *add_console_stream(
            logger::severity severity) override;

    logger_builder *clear() override;

    [[nodiscard]] logger *build() const override;

};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_CLIENT_LOGGER_BUILDER_H