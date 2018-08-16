#ifndef __LOG_H__
#define __LOG_H__

#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "BASIC_UI_WITH_EDC"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#if !defined(DBG)
#define __D(fmt, arg...) dlog_print(DLOG_DEBUG, LOG_TAG, "%s: %s[%d]\t " #fmt "\n", __FILENAME__, __func__, __LINE__, ##arg)
#endif

#if !defined(WRN)
#define __W(fmt, arg...) dlog_print(DLOG_WARN, LOG_TAG, "%s: %s[%d]\t " #fmt "\n", __FILENAME__, __func__, __LINE__, ##arg)
#endif

#if !defined(ERR)
#define __E(fmt, arg...) dlog_print(DLOG_ERROR, LOG_TAG, "%s: %s[%d]\t " #fmt "\n", __FILENAME__, __func__, __LINE__, ##arg)
#endif

#if !defined(INF)
#define __I(fmt, arg...) dlog_print(DLOG_INFO, LOG_TAG, "%s: %s[%d]\t " #fmt "\n", __FILENAME__, __func__, __LINE__, ##arg)
#endif

#if !defined(FATAL)
#define __F(fmt, arg...) dlog_print(DLOG_FATAL, LOG_TAG, "%s: %s[%d]\t " #fmt "\n", __FILENAME__, __func__, __LINE__, ##arg);
#endif

#endif /* __LOG_H__ */
