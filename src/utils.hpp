#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

const std::string CurrentDateTime()
{
	auto current_time = std::chrono::system_clock::now();
	std::time_t current_time_str = std::chrono::system_clock::to_time_t(current_time);
	return std::ctime(&current_time_str);
}
