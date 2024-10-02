#include <string>
#include <iostream>

#include "ansi_macros.hpp"

class Logger {
public:
    enum log_level {DEBUG, INFO, WARNING, CRITICAL};

protected:
    const char * name;
    const log_level level;

    class Log {
    public:
        template<typename T>
        const Log & operator<<(T& input) const { 
            std::cout << input;
            return *this;
        }
        ~Log(){
            std::cout << std::endl;
            std::cout.flush();
        }
    };

    static const char* get_level_text(log_level level) {
        switch(level) {
            case DEBUG:
                return ANSI_ESCAPE(ANSI_TEXT_CYAN) "DEBUG" ANSI_ESCAPE(ANSI_TEXT_DEFAULT);
            case INFO:
                return ANSI_ESCAPE(ANSI_TEXT_BLUE) "INFO" ANSI_ESCAPE(ANSI_TEXT_DEFAULT);
            case WARNING:
                return ANSI_ESCAPE(ANSI_TEXT_YELLOW) "WARNING" ANSI_ESCAPE(ANSI_TEXT_DEFAULT);
            case CRITICAL:
                return ANSI_ESCAPE(ANSI_TEXT_RED) "CRITICAL" ANSI_ESCAPE(ANSI_TEXT_DEFAULT);
            default:
                std::cout << "Logger Level Error";
                return "";
        }
    }
public:
    constexpr Logger(const char * _name, log_level _log_level = INFO):
        name(_name), level(_log_level) {}
    
    template<typename T>
    const Log operator<<(const T& input) const { 
        return log(input);
    }

    template<typename T>
    const Log log(const T& input) const {
        std::cout << '[' << ANSI_ESCAPE(ANSI_TEXT_GREEN) << name << ' ' << get_level_text(level) << "] " << input;
        return Log();
    }
    template<typename T>
    const Log log_debug(const T& input) const {
        std::cout << '[' << ANSI_ESCAPE(ANSI_TEXT_GREEN) << name << ' ' << get_level_text(DEBUG) << "] " << input;
        return Log();
    }
    template<typename T>
    const Log log_info(const T& input) const {
        std::cout << '[' << ANSI_ESCAPE(ANSI_TEXT_GREEN) << name << ' ' << get_level_text(INFO) << "] " << input;
        return Log();
    }
    template<typename T>
    const Log log_warning(const T& input) const {
        std::cout << '[' << ANSI_ESCAPE(ANSI_TEXT_GREEN) << name << ' ' << get_level_text(WARNING) << "] " << input;
        return Log();
    }
    template<typename T>
    const Log log_critical(const T& input) const {
        std::cout << '[' << ANSI_ESCAPE(ANSI_TEXT_GREEN) << name << ' ' << get_level_text(CRITICAL) << "] " << input;
        return Log();
    }
};