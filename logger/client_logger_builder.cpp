#include "client_logger_builder.h"

client_logger_builder::client_logger_builder()
{
    this->_format_string = "%d %t %s %m";
}

client_logger_builder::~client_logger_builder() noexcept
= default;

logger_builder* client_logger_builder::add_format_string(const std::string &format_string)
{
    this->_format_string = format_string;

    return this;
}

logger_builder *client_logger_builder::add_file_stream(std::string const &stream_file_path, logger::severity severity)
{
    if(_builder_streams.find(stream_file_path) != _builder_streams.end())
    {
        _builder_streams[stream_file_path].insert(severity);
    }

    else
    {
        _builder_streams.insert({stream_file_path, {severity}});
    }

    return this;

}



logger_builder *client_logger_builder::add_console_stream(logger::severity severity)
{

    if(_builder_streams.find("console") != _builder_streams.end())
    {
        _builder_streams["console"].insert(severity);
    }

    else
    {
        _builder_streams.insert({"console", {severity}});
    }

    return this;
}

logger_builder *client_logger_builder::clear()
{
    _builder_streams.clear();

    return this;
}

logger *client_logger_builder::build() const
{
    return new client_logger(_builder_streams, this->_format_string);
}
