#include "client_logger.h"

std::map<std::string, std::pair<std::ofstream*, size_t>> client_logger::_global_streams =
        std::map<std::string, std::pair<std::ofstream*, size_t>>();

client_logger::client_logger(std::map<std::string, std::set<severity>> const &builder)
{
    std::ofstream* stream = nullptr;

    for (auto i = builder.begin(); i != builder.end(); ++i)
    {
        auto global_stream = _global_streams.find(i->first);

        if (global_stream == _global_streams.end())
        {
            if (global_stream->first != "console")
            {
                stream = new std::ofstream(i->first, std::ios::out);
            }
            else
            {
                stream = nullptr;
            }

            _global_streams.insert(std::make_pair(i->first, std::make_pair(stream, 1)));
        }
        else
        {
            stream = global_stream->second.first;
            global_stream->second.second++;
        }

        auto streams_in_streams = _all_streams.find(i->first);

        if (streams_in_streams == _all_streams.end())
        {
            _all_streams.insert(std::make_pair(i->first, std::make_pair(stream, i->second)));
        }
    }
}

client_logger::client_logger(client_logger const &other) :
    _all_streams(other._all_streams)
{
    for (auto &map : _global_streams)
    {
        map.second.second++;
    }
}

client_logger &client_logger::operator=(client_logger const &other)
{
    if (this != &other)
    {
        _all_streams = other._all_streams;

        for (auto &map : _all_streams)
        {
            _global_streams[map.first].second++;
        }

    }
    return *this;
}

client_logger::client_logger(client_logger &&other) noexcept :
    _all_streams(std::move(other._all_streams))
{

}

client_logger &client_logger::operator=(client_logger &&other) noexcept
{
    if (this != &other)
    {
        _all_streams = std::move(other._all_streams);
    }
    return *this;
}

client_logger::~client_logger() noexcept
{
    for (auto &stream : _all_streams)
    {
        auto global_logger = _global_streams[stream.first];

        global_logger.second--;

        if(!global_logger.second)
        {
            if (global_logger.first != nullptr)
            {
                if (global_logger.first->is_open())
                {
                    global_logger.first->close();
                }
                delete global_logger.first;
            }
            _global_streams.erase(stream.first);
        }
    }
}

logger const *client_logger::log(const std::string &text, logger::severity severity) const noexcept
{
    auto string_severity = severity_to_string(severity);
    auto string_date_time = current_datetime_to_string();

    for (auto &stream : _all_streams)
    {
        if (stream.second.second.find(severity) != stream.second.second.end())
        {
            if (stream.second.first == nullptr)
            {
                std::cout << "[" << string_date_time << "][" << string_severity << "]" << text << std::endl;
            }
            else
            {
                *(stream.second.first) << "[" << string_date_time << "][" << string_severity << "]" << text;
            }
        }
    }
    return this;
}



