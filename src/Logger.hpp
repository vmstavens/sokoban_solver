#pragma once

#include <fstream>
#include <string>

#define LOGGER Logger::GetLogger()

class Logger
{
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


public:
	// Methods ////////////////////////////////////////////////

	// create instance of Logger class
	static Logger* GetLogger();

	// log a message
	void Log(const std::string& sMessage);

	// operator overload
	Logger &operator<<(const std::string& sMessage);
};
