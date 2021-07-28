#include "Logger.hpp"
#include "utils.hpp"

Logger* Logger::m_This = NULL;
std::ofstream Logger::m_logfile;

Logger::Logger() {}

Logger::Logger(const Logger& log) { }

Logger::~Logger() {}

std::string Logger::enum2str(LOG_TYPE logType)
{
	std::string prefix;
	switch (logType)
	{
	case LOG_TYPE::INFO:
		prefix = " [INFO] ";
		break;
	case LOG_TYPE::WARNING:
		prefix = " [WARNING] ";
		break;
	case LOG_TYPE::ERROR:
		prefix = " [ERROR] ";
		break;
	case LOG_TYPE::CRITICAL:
		prefix = " [CRITICAL] ";
		break;
	default:
		break;
	}
	return prefix;
}

Logger* Logger::GetLogger()
{
	if (m_This == nullptr)
	{
		m_This = new Logger();
		m_logfile.open(m_filename, std::ios::out | std::ios::app);
	}
	return m_This;
}

void Logger::Log(const std::string &sMessage, LOG_TYPE logType, bool time_stamp)
{
	if (time_stamp)
	{
		m_logfile << CurrentDateTime() << enum2str(logType) << ":\t";
		m_logfile << sMessage << "\n";
	}
	else
		m_logfile << sMessage << "\n";
}

Logger &Logger::operator<<(const std::string &sMessage)
{
	m_logfile << CurrentDateTime() << ":\t";
	m_logfile << sMessage << "\n";
	return *this;
}

void Logger::clear()
{
	std::ofstream ofs;
	ofs.open("Log.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}