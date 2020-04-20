#ifndef SKF_CLOUD_LOGS_H
#define SKF_CLOUD_LOGS_H

#include "errors.h"
#include <iostream>
#include <unistd.h>
#include <cstring>


/** \addtogroup Utils
 *  @{
 */

#define MANAGER_DEBUG_LEVEL		0
#define PARSER_DEBUG_LEVEL		1
#define IPC_DEBUG_LEVEL			0
#define ENGINE_DEBUG_LEVEL		1
#define CLOUD_DEBUG_LEVEL		0
#define MONITORING_DEBUG_LEVEL	0

#define DEBUG_FD 1

/**
 * @namespace Logs
 *
 * @brief this namespace contains tools for logs
 */
namespace Logs {
	void		basic(int);
	void		manager_log(const char *log, int level);
	void		parser_log(const char *log, int level);
	void		engine_log(const char *log, int level);
	void		cloud_log(const char *log, int level);
	void		monitoring_log(const char *log, int level);
};

/** @}*/

#endif //SKF_CLOUD_LOGS_H
