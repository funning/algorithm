#ifndef TKLOG_H__
#define TKLOG_H__

#include "stdio.h"
#define TK_LOG_DEBUG  0
#define TK_LOG_TUNNING 1
#define TK_LOG_INFO 2
#define TK_LOG_WARN 3
#define TK_LOG_ERROR 4
#define TK_LOG_FATAL 5
#define TK_LOG_MAX 6

#define TK_NULL 0
#ifndef TK_LOG_LEVEL
#define TK_LOG_LEVEL TK_LOG_ERROR
#endif

#if TK_LOG_LEVEL <= TK_LOG_ERROR
#define TK_TRACE_ERROR(arg)  tk_trace_error arg
#else
#define TK_TRACE_ERROR(...)
#endif

#if TK_LOG_LEVEL <= TK_LOG_DEBUG
#define TK_TRACE_DEBUG(arg)  tk_trace_debug arg
#else
#define TK_TRACE_DEBUG(...)
#endif

#if TK_LOG_LEVEL <= TK_LOG_INFO
#define TK_TRACE_INFO(arg)   tk_trace_info arg
#else
#define TK_TRACE_INFO(...)
#endif

void tk_trace_error (const char* format, ...);
void tk_trace_debug (const char* format, ...);
void tk_trace_info (const char* format, ...);
#define TK_SUCCESS 1
typedef enum {
    TK_FALSE,
    TK_TRUE
} tk_bool;
#endif
