//
// Created by Enting Wu on 11/21/21.
//
#ifndef CREATINGBETTERINTERFACES03_LOGGER_H
#define CREATINGBETTERINTERFACES03_LOGGER_H

#include <memory>
#include <sstream>
#include <string>

namespace helpers {
    enum class log_level: int {
        off = 0,
        error,
        warning,
        info,
        default_level = info,
        debug,
        _last,
    };

    class logger {
    public:
        static logger get_logger(); // singleton
        // copying the logger
        logger(const logger&) = default;
        logger& operator=(const logger&) = default;
        ~logger() = default;

        // Move leaves the object in a default state
        logger(logger&&) = delete;
        logger& operator=(logger&&) = delete;

        log_level get_level() const;
        void set_level(log_level level);
        void write(log_level, const std::string& msg) const;
    private:
        logger() = default;
        struct logger_impl;
        std::shared_ptr<logger_impl> impl_;
    };

    namespace detail{
        template<typename MessagePart>
        inline void stream_parts(std::stringstream& stream, const MessagePart& part) {
            stream << part;
        }

        template<typename MessagePart, typename... MessageParts>
        inline void stream_parts(std::stringstream& stream, const MessagePart& part, const MessageParts& ...more_parts) {
            stream << part;
            stream_parts(stream, more_parts...);
        }

        template<typename... MessageParts>
        inline void write_log(logger &logger, log_level level, const MessageParts& ...parts) {
            if (level > logger.get_level()) {
                return;
            }
            std::stringstream s;
            detail::stream_parts(s, parts...);
            logger.write(level, s.str());
        }
    }
}

#endif //CREATINGBETTERINTERFACES03_LOGGER_H
