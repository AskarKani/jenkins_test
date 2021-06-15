#include "Logger.h"

#include <chrono>
#include <cstdio>
#include <ctime>
#include <experimental/filesystem>
#include <iomanip>
#include <mutex>
#include <sstream>

Logger* Logger::instance = NULL;

std::string Logger::GetFileNameFromPath(const std::string& file_path)
{
    return std::experimental::filesystem::path {file_path}.filename().string();
}

Logger::Logger()
    : log_filename("main.log")
    , console_logging(false)
{
	int c = 5/0;
    log_file.open(log_filename.c_str(), std::ios_base::app);
}

Logger::~Logger()
{
    log_file.close();
}

Logger* Logger::GetLogger()
{
    if (instance == NULL)
    {
        instance = new Logger();
    }
    return instance;
}

void Logger::Log(const char* format, ...)
{
    constexpr std::size_t message_buffer_size = 4096;
    char message[message_buffer_size];

    va_list args;
    va_start(args, format);

    vsnprintf(message, message_buffer_size, format, args);

    log_file << CurrentDateTime() << ": ";
    log_file << message << "\n";
    log_file.flush();

    if (console_logging)
    {
        std::cout << message << "\n";
    }

    va_end(args);
}

void Logger::Log(const std::string& message)
{
    log_file << CurrentDateTime() << ": ";
    log_file << message << "\n";
    log_file.flush();

    if (console_logging)
    {
        std::cout << message << "\n";
    }
}

Logger& Logger::operator<<(const std::string& message)
{
    log_file << "\n" << CurrentDateTime() << ": ";
    log_file << message << "\n";
    log_file.flush();

    if (console_logging)
    {
        std::cout << "\n" << message << "\n";
    }

    return *this;
}

const std::string Logger::CurrentDateTime(void) const
{
    using namespace std::chrono;
    static std::mutex localtime_tm_mutex;

    std::time_t timestamp = std::time(nullptr);
    if (timestamp == static_cast<std::time_t>(-1))
    {
        return {};
    }

    std::tm calendar_time;
    {
        std::lock_guard<std::mutex> lock {localtime_tm_mutex};
        std::tm* calendar_time_ptr = std::localtime(&timestamp);
        if (calendar_time_ptr == nullptr)
        {
            return {};
        }
        calendar_time = *calendar_time_ptr;
    }

    // Use chrono::system_clock to get ms
    auto ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() %
              duration_cast<milliseconds>(seconds {1}).count();

    std::stringstream formatted_time;
    formatted_time << std::put_time(&calendar_time, "%Y-%m-%d %H:%M:%S");  // date+time
    formatted_time << '.' << std::setfill('0') << std::setw(3) << ms;      // ms
    formatted_time << std::put_time(&calendar_time, " (UTC%z)");           // time zone

    return formatted_time.str();
}

void Logger::setConsoleLogging(bool bEnable)
{
    console_logging = bEnable;
}

bool Logger::isConsoleLogging(void) const
{
    return console_logging;
}

void Logger::setLogFileName(const std::string& sPath)
{
    log_filename = sPath;
    log_file.close();
    log_file.open(log_filename.c_str(), std::ios_base::app);
}

const std::string& Logger::getLogFileName(void) const
{
    return log_filename;
}
