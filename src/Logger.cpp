#include "Logger.hpp"
#include "utils.hpp"

Logger* Logger::m_This = NULL;
std::ofstream Logger::m_logfile;

Logger::Logger() {}

Logger::Logger(const Logger& log) { }

Logger::~Logger() {}

Logger* Logger::GetLogger()
{
	if (m_This == nullptr)
	{
		m_This = new Logger();
		m_logfile.open(m_filename, std::ios::out | std::ios::app);
	}
	return m_This;
}

void Logger::Log(const std::string &sMessage)
{
	m_logfile << CurrentDateTime() << ":\t";
	m_logfile << sMessage << "\n";
}

Logger &Logger::operator<<(const std::string &sMessage)
{
	m_logfile << CurrentDateTime() << ":\t";
	m_logfile << sMessage << "\n";
	return *this;
}