/*****************************************************************************
 *  Copyright Statement:
 *  --------------------
 *  This software is protected by Copyright and the information contained
 *  herein is confidential. The software may not be copied and the information
 *  contained herein may not be used or disclosed except with the written
 *  permission of Beijing TigerKnows Technology Co. Ltd. (C) 2009
 *
 ********************************************************************************
 * Filename:
 * ---------
 *   TKMemAdapter.h
 *
 * Project:
 * --------
 *   TigerMap 3.0
 *
 * Description:
 *   
 * Author:
 *   
 * Date: 2009-09-27
 ******************************************************************************/

#ifndef TKMEMADAPTER_H_
#define TKMEMADAPTER_H_ 

#include "Log.h"
#include "DriverMem.h"
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    /****************************************************************
     * 
     * 本头文件提供以下函数或宏的定义：
     * 
     * 	tk_malloc(size)
     * 	tk_calloc(num, size)
     *  tk_free(ptr)			//ptr可为TK_NULL
     *  tk_free_func(ptr)		//ptr可为TK_NULL，用于array_list和OOC等需要指定析构函数指针的地方
     *  tk_mem_left_size		//剩余可用内存大小，不包括加载APE产生的内存漏洞
     *  
     *  应用层（除了驱动层的内存模块和加载器内存模块外）仅允许以以上方式进行调用，请勿调用本文件将中涉及到其他函数或宏
     * 
     ***************************************************************/

    //tk_free_func可能被重定义为tk_adapter_free_func，详见下文根据不同平台的具体配置
    void tk_adapter_free_func(void* ptr, char* file, unsigned int line);

    //根据不同平台情况，若C标准库calloc可用，则tk_calloc将被重定义为calloc
    //否则，tk_calloc将被重定义为tk_adapter_calloc
    void* tk_adapter_calloc(unsigned int num, unsigned int size, char* file, unsigned int line);

    void* tk_x_calloc_debug(unsigned int num, unsigned int size, char* file, unsigned int line) ;
    void tk_x_free_debug(void* ptr, char* file, unsigned int line) ;

#if !defined(TK_LOG_LEVEL) || !defined(TK_LOG_MAX)
	#error TK_LOG_LEVEL or TK_LOG_MAX not defined!
#endif //#if !defined(TK_LOG_LEVEL) || !defined(TK_LOG_MAX)

#if TK_LOG_LEVEL >= TK_LOG_MAX
	#ifdef TK_S_CHECKING_MEMORY_LEAKS
		#undef TK_S_CHECKING_MEMORY_LEAKS
	#endif //#ifdef TK_S_CHECKING_MEMORY_LEAKS
	#define tk_malloc(size) tk_malloc_debug(size, 0, 0)
	#define tk_calloc(num, size) tk_calloc_debug(num, size, 0, 0)
	#define tk_free(ptr) tk_free_debug(ptr, 0, 0)
#else //#if TK_LOG_LEVEL >= TK_LOG_MAX
	#ifndef TK_S_CHECKING_MEMORY_LEAKS
		#define TK_S_CHECKING_MEMORY_LEAKS
	#endif //#ifndef TK_S_CHECKING_MEMORY_LEAKS
	#define tk_malloc(size) tk_malloc_debug(size, __FILE__, __LINE__)
	#define tk_calloc(num, size) tk_calloc_debug(num, size, __FILE__, __LINE__)
	#define tk_free(ptr) tk_free_debug(ptr, __FILE__, __LINE__)

#endif //#if TK_LOG_LEVEL >= TK_LOG_MAX


#define tk_mem_total_size	tk_x_mem_total_size

#define tk_free_func ((void(*)(void*))(tk_free_func_direct))

#ifdef __cplusplus
}
#endif //__cplusplus

#endif /* TKMEMADAPTER_H_ */
