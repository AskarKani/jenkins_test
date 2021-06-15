#ifndef logger_CLASS_H
#define logger_CLASS_H

#include <cstdarg>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Disable Intellisense errors related to Logger macro expansion when using format specifiers from <cinttypes>
#ifdef __INTELLISENSE__
#pragma diag_suppress 18
#endif

#define LOGGER  Logger::GetLogger()
#define LOGLINE LOGGER->Log("%s(%d)", __FILE__, __LINE__)
#define LOG(format, ...) \
    LOGGER->Log("%s(%d): " format, Logger::GetFileNameFromPath(__FILE__).c_str(), __LINE__, ##__VA_ARGS__)

//!  Class of Logger
/*!
 * This class is in charge of logging messages in the log file (and on the screen - depending on flag).
 */
class Logger
{
public:  /// static functions
    /**
     *   Funtion to create the instance of logger class.
     *   \return singleton object of Logger class..
     */
    static Logger* GetLogger();

protected:  /// static variables
    /**
     *   Singleton logger class object pointer.
     **/
    static Logger* instance;

public:  /// public methods
         /**
          *   Logs a message
          *   \param message message to be logged.
          */
    void Log(const std::string& message);

    /**
     *   Variable Length Logger function
     *   \param format string for the message to be logged.
     */
    void Log(const char* format, ...);

    /**
     *   << overloaded function to Logs a message
     *   \param sMessage message to be logged.
     */
    Logger& operator<<(const std::string& message);

    /**
     *   Funtion to get current date/time, format is YYYY-MM-DD.HH:mm:ss
     *   \return string representing current date time.
     */
    const std::string CurrentDateTime() const;

    /// toggle console logging
    void setConsoleLogging(bool bEnable);
    bool isConsoleLogging(void) const;

    /// set file path/name
    void setLogFileName(const std::string& sPath);
    const std::string& getLogFileName(void) const;

    // std::istringstream& getLogStream();

public:
    static std::string GetFileNameFromPath(const std::string& file_path);

protected:  /// protected methods
            /*! Constructor */
    Logger();

    /*! Destructor */
    ~Logger();

    /*! Copy Constructor
     *	 \param [in] logger The logger instance.
     */
    Logger(const Logger&) {};

    /**
     *   Assignment operator for the Logger class.
     */
    Logger& operator=(const Logger&)
    {
        return *this;
    };

protected:  /// member variables
    std::istringstream logStream;

    /**
     *   Log file name.
     **/
    std::string log_filename;

    /**
     *   Log file stream object.
     **/
    std::ofstream log_file;

    /*! The logging flag representing if the message is also displayed on the screen or not.*/
    bool console_logging;
};
#endif