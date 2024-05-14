#include <vector>
#include "client_logger.h"
#include <iostream>
#include <map>
#include <fstream>

std::map<std::string, std::pair<std::ofstream*, size_t> > client_logger::_global_streams =
        std::map<std::string, std::pair<std::ofstream*, size_t> >();

client_logger::client_logger(std::map<std::string, std::set<logger::severity>> const& builder_streams)
{
    for (auto &builder_stream : builder_streams)
    {
        auto stream = _global_streams.find(builder_stream.first);
        std::ofstream* file = nullptr;

        if(stream == _global_streams.end())
        {
            if(builder_stream.first != "console")
            {
                file = new std::ofstream;
                file->open(builder_stream.first);
            }
            _global_streams.insert(std::make_pair(builder_stream.first, std::make_pair(file, 1)));
        }
        else
        {
            file = stream->second.first;
            stream->second.second++;
        }

        _streams.insert(std::make_pair(builder_stream.first, std::make_pair(file, builder_stream.second)));
    }
}

client_logger::~client_logger() noexcept
{

    for(auto &stream : _streams)
    {
        auto global_stream = _global_streams.find(stream.first);

        if(--(global_stream->second.second) == 0)
        {
            if(global_stream->second.first != nullptr)
            {
                global_stream->second.first->flush();
                global_stream->second.first->close();
                delete global_stream->second.first;
            }

            _global_streams.erase(global_stream);
        }
    }
}


logger const *client_logger::log(const std::string &text, logger::severity severity) const noexcept
{
    for (auto &stream: _streams)
    {
        if (stream.second.second.find(severity) != stream.second.second.end())
        {
            if (stream.first == "console")
            {
                std::cout << "[" << current_datetime_to_string() << "][" << severity_to_string(severity) << "]" << text << std::endl;
            }
            else
            {
                if (stream.second.first == nullptr)
                {
                    std::cout << "be" << std::endl;
                    std::cout << "[" << current_datetime_to_string() << "][" << severity_to_string(severity) << "]" << text << std::endl;
                }
                else
                {
                    (*stream.second.first) << "[" << current_datetime_to_string() << "][" << severity_to_string(severity) << "]" << text << std::endl;
                }
            }
        }
    }
    return this;
}
