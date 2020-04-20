#include "logs.h"

#include <iostream>
#include <chrono>
#include <ctime>

void Logs::basic(int level)
{
	std::time_t	end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char		*date = std::ctime(&end_time);

	if (write(1, "[", 1) == -1 || write(1, date, strlen(date) -1) == -1 || write(1, "]", 1) == -1)
		throw ERROR_WRITE;
	if (write(1, "[", 1) == -1 || write(1, std::to_string(level).c_str(), std::to_string(level).size()) == -1|| write(1, "]", 1) == -1)
		throw ERROR_WRITE;
}

/**
 * @brief This function is a debugging tool.
 *
 * Only the levels equals or lower than the DEBUG_LEVEL define will be printed. This allows you to select how verbose you want your program to be.
 *
 * @param log log to display
 * @param level log priority (0 == maximum priority)
 */
void		Logs::manager_log(const char *log, int level)
{
	if (MANAGER_DEBUG_LEVEL >= level) {
		Logs::basic(level);
		if ((write(1, "[manager] ", strlen("[manager] "))) == -1)
			throw ERROR_WRITE;
		if (write(DEBUG_FD, log, strlen(log)) == -1)
			throw ERROR_WRITE;
	}
}

/**
 * @brief This function is a debugging tool.
 *
 * Only the levels equals or lower than the DEBUG_LEVEL define will be printed. This allows you to select how verbose you want your program to be.
 *
 * @param log log to display
 * @param level log priority (0 == maximum priority)
 */
void		Logs::parser_log(const char *log, int level)
{
	if (PARSER_DEBUG_LEVEL >= level) {
		Logs::basic(level);
		if ((write(1, "[parser] ", strlen("[parser] "))) == -1)
			throw ERROR_WRITE;
		if (write(DEBUG_FD, log, strlen(log)) == -1)
			throw ERROR_WRITE;
	}
}

/**
 * @brief This function is a debugging tool.
 *
 * Only the levels equals or lower than the DEBUG_LEVEL define will be printed. This allows you to select how verbose you want your program to be.
 *
 * @param log log to display
 * @param level log priority (0 == maximum priority)
 */
void		Logs::engine_log(const char *log, int level)
{
	if (ENGINE_DEBUG_LEVEL >= level) {
		Logs::basic(level);
		if ((write(1, "[engine] ", strlen("[engine] "))) == -1)
			throw ERROR_WRITE;
		if (write(DEBUG_FD, log, strlen(log)) == -1)
			throw ERROR_WRITE;
	}
}
/**
 * @brief This function is a debugging tool.
 *
 * Only the levels equals or lower than the DEBUG_LEVEL define will be printed. This allows you to select how verbose you want your program to be.
 *
 * @param log log to display
 * @param level log priority (0 == maximum priority)
 */
void		Logs::cloud_log(const char *log, int level)
{
	if (CLOUD_DEBUG_LEVEL >= level) {
		Logs::basic(level);
		if ((write(1, "[cloud] ", strlen("[cloud] "))) == -1)
			throw ERROR_WRITE;
		if (write(DEBUG_FD, log, strlen(log)) == -1)
			throw ERROR_WRITE;
	}
}

/**
 * @brief This function is a debugging tool.
 *
 * Only the levels equals or lower than the DEBUG_LEVEL define will be printed. This allows you to select how verbose you want your program to be.
 *
 * @param log log to display
 * @param level log priority (0 == maximum priority)
 */
void		Logs::monitoring_log(const char *log, int level)
{
	if (MONITORING_DEBUG_LEVEL >= level) {
		Logs::basic(level);
		if ((write(1, "[monitoring] ", strlen("[monitoring] "))) == -1)
			throw ERROR_WRITE;
		if (write(DEBUG_FD, log, strlen(log)) == -1)
			throw ERROR_WRITE;
	}
}
