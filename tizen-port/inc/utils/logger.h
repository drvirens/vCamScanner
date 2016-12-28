
#ifndef __LOGGER_H__
#define __LOGGER_H__

#define LOG_TAG "selfcamera"

#include <dlog.h>

#define INF(fmt, arg...) dlog_print(DLOG_INFO, LOG_TAG, fmt,  ##arg)
#define DBG(fmt, arg...) dlog_print(DLOG_DEBUG, LOG_TAG, fmt,  ##arg)
#define ERR(fmt, arg...) dlog_print(DLOG_ERROR, LOG_TAG, fmt,  ##arg)

#define WARN_IF(expr, fmt, arg...) { \
	if (expr) { \
		ERR(fmt, ##arg); \
	} \
}

#define RETM_IF(expr, fmt, arg...) { \
	if (expr) { \
		ERR(fmt, ##arg); \
		return; \
	} \
}

#define RETVM_IF(expr, val, fmt, arg...) { \
	if (expr) { \
		ERR(fmt, ##arg); \
		return (val); \
	} \
}

#endif /* __LOGGER_H__ */
