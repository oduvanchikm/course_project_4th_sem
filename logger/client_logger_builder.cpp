#include "client_logger_builder.h"

logger_builder *client_logger_builder::add_file_stream(std::string const &stream_file_path, logger::severity severity)
{

    if (stream_file_path.empty())
    {
        _streams_in_builder.insert({stream_file_path, {severity}});
    }

    _streams_in_builder[stream_file_path].insert(severity);

    return this;
}

// abs file std::weakly_canonical

logger_builder *client_logger_builder::add_console_stream(logger::severity severity)
{
    add_file_stream("", severity);

    return this;
}

logger_builder *client_logger_builder::clear()
{
    _streams_in_builder.clear();

    return this;
}

logger *client_logger_builder::build() const
{
    return new client_logger(_streams_in_builder);
}

client_logger_builder::client_logger_builder()
{

}

client_logger_builder::~client_logger_builder() noexcept
{

}