#pragma once

#include <fstream>
#include <string>

#define LOGGER Logger::GetLogger()

class Logger
{

public:
	// Attributes /////////////////////////////////////////////
	enum class LOG_TYPE
	{
		INFO,
		WARNING,
		ERROR,
		CRITICAL
	};

	// Methods ////////////////////////////////////////////////

	// create instance of Logger class
	static Logger *GetLogger();

	// log a message
	void Log(const std::string &sMessage, LOG_TYPE logType = LOG_TYPE::INFO, bool time_stamp = true);

	// clear log file
	void clear();

	// operator overload
	Logger &operator<<(const std::string &sMessage);

private:
	// log file name
	static constexpr auto m_filename = "Log.txt";

	// singleton logger class object pointer.
	static Logger* m_This;

	// log file stream object
	static std::ofstream m_logfile;

	Logger();
	Logger(const Logger& log);
	~Logger();

	std::string enum2str(LOG_TYPE logType);


};
