#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <fstream>
#include <unistd.h>
#include <iomanip>
#include <map>
#include <mutex>
#include <iostream>

#define LOG_ENABLED 0

namespace LOGGER
{
    enum log_level
    {
        TRACE,
        DEBUG,
        INFO,
        ERROR,
        FATAL
    };

    inline std::ostream &operator<<(std::ostream &out, const log_level &value)
    {
        static std::map<log_level, std::string> strings;
        if (strings.size() == 0)
        {
#define INSERT_ELEMENT(p) strings[p] = #p
            INSERT_ELEMENT(TRACE);
            INSERT_ELEMENT(DEBUG);
            INSERT_ELEMENT(INFO);
            INSERT_ELEMENT(ERROR);
            INSERT_ELEMENT(FATAL);
#undef INSERT_ELEMENT
        }

        return out << strings[value];
    }

    class logger
    {
    public:
        static std::ofstream *getInstance(pid_t tid, std::string filename = "")
        {

            std::ofstream *ofs = nullptr;
            if (LOG_ENABLED)
            {
                if (loggerMap.find(tid) != loggerMap.end())
                {
                    ofs = loggerMap.find(tid)->second;
                }
                else
                {
                    std::ostringstream ss_;
                    ss_ << filename << "_" << tid << ".log";
                    std::ofstream *_log;
                    _log = new std::ofstream(ss_.str().c_str(), std::ios_base::out | std::ios_base::app);
                    loggerMap[tid] = _log;
                    std::mutex *_mutex = new std::mutex();
                    mutexMap[_log] = _mutex;
                    ofs = _log;
                }
            }
            return ofs;
        }

        static void log_lock(pid_t tid)
        {
            if (LOG_ENABLED)
            {
                std::ofstream *ofs = nullptr;
                if (loggerMap.find(tid) != loggerMap.end())
                {
                    ofs = loggerMap.find(tid)->second;
                    mutexMap.find(ofs)->second->lock();
                }
            }
        }

        static void log_unlock(pid_t tid)
        {
            if (LOG_ENABLED)
            {
                std::ofstream *ofs = nullptr;
                if (loggerMap.find(tid) != loggerMap.end())
                {
                    ofs = loggerMap.find(tid)->second;
                    mutexMap.find(ofs)->second->unlock();
                }
            }
        }

        static void close_log(pid_t tid)
        {
            if (LOG_ENABLED)
            {
                if (loggerMap.find(tid) != loggerMap.end())
                {
                    mutexMap.erase(mutexMap.find(loggerMap.find(tid)->second));
                    loggerMap.erase(loggerMap.find(tid));
                }
            }
        }

        static void log(pid_t tid, log_level lvl, std::string msg)
        {
            if (LOG_ENABLED)
            {
                std::ofstream *ofs = nullptr;
                if (loggerMap.find(tid) != loggerMap.end())
                {
                    ofs = loggerMap.find(tid)->second;
                    *ofs << lvl << " - " << msg << std::endl;
                }
            }
            else
            {
                std::cout << lvl << " - " << msg << std::endl;
            }
        }

        logger() = delete;
        ~logger() = delete;

    private:
        inline static std::map<pid_t, std::ofstream *> loggerMap;
        inline static std::map<std::ofstream *, std::mutex *> mutexMap;
    };

}

#define LOGGER_T std::ofstream

#define INIT_LOGGER(_filename) LOGGER::logger::getInstance(gettid(), _filename)

#define CLOSE_LOGGER() LOGGER::logger::close_log(gettid());

#define L_TRACE LOGGER::TRACE
#define L_DEBUG LOGGER::DEBUG
#define L_INFO LOGGER::INFO
#define L_ERROR LOGGER::ERROR
#define L_FATAL LOGGER::FATAL

#define LOG(_lvl, x)                                                                                   \
    {                                                                                                  \
        time_t now = time(0);                                                                          \
        struct tm _now;                                                                                \
        LOGGER::logger::log_lock(gettid());                                                            \
        std::stringstream ss;                                                                          \
        gmtime_r(&now, &_now);                                                                           \
        ss << std::put_time(&_now, "%Y-%m-%d %H:%M:%S") << " - " << __PRETTY_FUNCTION__ << " - " << x; \
        LOGGER::logger::log(gettid(), _lvl, ss.str());                                                 \
        LOGGER::logger::log_unlock(gettid());                                                          \
    }

#endif // __LOGGER_H__