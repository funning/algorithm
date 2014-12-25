#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "Log.h"
#define LOG_BUF 2047
#define BUF_LEN 256
#define LOG_FILE_NAME "TKLog.txt"
#define LOG_PATH "/sdcard"
//
//#define TRACE_ERROR(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "tiger", __VA_ARGS__))
//#define TRACE_DEBUG(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "tiger", __VA_ARGS__))
//#define TRACE_INFO(...) ((void)__android_log_print(ANDROID_LOG_INFO, "tiger", __VA_ARGS__))
//
//static void tk_write_fs (const char* message){
//	struct stat buf;
//	tk_uint32 ret = 0;
//	FILE* fd = 0;
//	tk_uint32 write_size = 0;
//	char logfile [BUF_LEN] = {0};
//	char namebuff [BUF_LEN] = {0};
//	char* timebuff = NULL;
//
//	if(message == TK_NULL){
//		return;
//	}
//	strcat (logfile, LOG_PATH);
//
//	if (lstat (logfile, &buf)){
//		TRACE_DEBUG ("%s, lstat error : %s\n", __FUNCTION__, logfile);
//		return;
//	}
//	if (S_ISLNK (buf.st_mode)){
//		readlink (logfile, namebuff, BUF_LEN);
//		strcpy (logfile, namebuff);
//	}
//	strcat (logfile, "/");
//	strcat (logfile, LOG_FILE_NAME);
//	//TRACE_DEBUG ("%s, file name : %s\n", __FUNCTION__, logfile);
//	fd = fopen (logfile, "a+");
//	if (fd == NULL){
//		//TRACE_ERROR ("open file : %s error\n", logfile);
//		return;
//	}
//	time_t timep;
//	time (&timep);
//	timebuff = ctime(&timep);
//	if (timebuff != NULL){
//		fwrite(timebuff, 1, strlen(timebuff) - 1, fd);
//		fwrite(" ", 1, 1, fd);
//	}
//	if(message[strlen(message -1)] != '\n'){
//		strcat(message, "\n");
//	}
//	ret = fwrite (message, 1, strlen (message), fd);
//	//TRACE_DEBUG ("%s, ret : %d, write size : %d \n", __FUNCTION__, ret, write_size);
//
//	fclose (fd);
//}
//
//void tk_format_log_file(void){
//	struct stat buf;
//	char logfile [BUF_LEN] = {0};
//	char namebuff [BUF_LEN] = {0};
//
//	strcat (logfile, LOG_PATH);
//
//	if (lstat (logfile, &buf)){
//		TRACE_DEBUG ("%s, lstat error : %s\n", __FUNCTION__, logfile);
//		return;
//	}
//	if (S_ISLNK (buf.st_mode)){
//		readlink (logfile, namebuff, BUF_LEN);
//		strcpy (logfile, namebuff);
//	}
//	strcat (logfile, "/");
//	strcat (logfile, LOG_FILE_NAME);
//	tk_x_fdelete(logfile);
//
//}

void tk_trace_error (const char* format, ...){
	va_list ap;
	char message [LOG_BUF + 1] = {0};
	const char* fmt = TK_NULL;

	if(format == TK_NULL){
		fmt = "null";
	}else{
		fmt = format;
	}
	va_start(ap, fmt);
	vsnprintf(message, LOG_BUF, fmt, ap);
	va_end(ap);

//	TRACE_ERROR (message);
//	tk_write_fs (message);
	printf("%s", message);
}

void tk_trace_debug (const char* format, ...){
	va_list ap;
	char message [LOG_BUF + 1] = {0};
	const char* fmt = TK_NULL;

	if(format == TK_NULL){
		fmt = "null";
	}else{
		fmt = format;
	}
	va_start(ap, fmt);
	vsnprintf(message, LOG_BUF, fmt, ap);
	va_end(ap);

//	TRACE_DEBUG (message);
//	tk_write_fs (message);
	printf("%s", message);
}

void tk_trace_info (const char* format, ...){
	va_list ap;
	char message [LOG_BUF + 1] = {0};
	const char* fmt = TK_NULL;

	if(format == TK_NULL){
		fmt = "null";
	}else{
		fmt = format;
	}
	va_start(ap, fmt);
	vsnprintf(message, LOG_BUF, fmt, ap);
//	TRACE_INFO (message);
	va_end(ap);

//	tk_write_fs (message);
	printf("%s", message);
}

void tk_dummy_free(void* ptr) {
    return;
}
//
//tk_int32 tk_random_number(tk_int32 hi)  {
//	tk_int32 value = 0;
//
//	srand((int)time(0));
//    value = rand();
//    if(hi < 0) {
//        hi = -hi;
//        value = value % (hi + 1);
//        value = -value;
//        return value;
//    } else {
//        return value % (hi + 1);
//    }
//}
int tk_x_get_kk_active_socket_count(void) {
	return 0;
}
#ifndef TK_LOG_LEVEL
#error TK_LOG_LEVEL not defined!
#endif

void tk_x_panic(const char* file, int line, const char* expression) {
	TK_TRACE_INFO(("tk_panic file= %s,line=%d,exp=%s",file,line,expression));
//	assert(0);
}

//
//#if TK_LOG_LEVEL < TK_LOG_MAX
//void tk_trace_message(tk_pstrc message) {
//#ifndef TK_S_UNITY
//	//TRACE_DEBUG(message);
//	//tk_write_fs(message);
//	tk_trace_debug(message);
//#endif
//}
//
//void tk_trace_datetime(tk_pstrc info, const tk_date_time* time) {
//#ifndef TK_S_UNITY
//	TK_TRACE_INFO(("%s:%d-%d-%d %d:%d:%d",
//		info, time->year, time->month, time->day, time->hour, time->minute, time->second));
//#endif
//}
//
//void tk_dump_memory(const void* ptr, int len) {
//#ifndef TK_S_UNITY
//    tk_pbytec p = (tk_pbytec)ptr;
//    int n;
//    char line[128], *s;
//
//    n = 0;
//    s = line;
//    while(len-- > 0) {
//        *s++ = '0';
//        *s++ = 'x';
//        *s=(p[0]>>4)+'0';
//        if(*s>'9')
//            *s+='a'-'9'-1;
//        ++s;
//        *s=(p[0]&0xf)+'0';
//        if(*s>'9')
//            *s+='a'-'9'-1;
//        ++s;
//        if(len)
//            *s++ = ',';
//        *s = '\0';
//        ++p;
//        ++n;
//        if(n==16) {
//            n=0;
//            //TRACE_DEBUG(line);
//            //tk_write_fs(line);
//            tk_trace_debug(line);
//            s = line;
//        }
//    }
//    if(n) {
//    	//TRACE_DEBUG(line);
//    	//tk_write_fs(line);
//    	tk_trace_debug(line);
//    }
//#endif
//}
//#endif /*TK_LOG_LEVEL < TK_LOG_MAX*/
