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
     * ��ͷ�ļ��ṩ���º������Ķ��壺
     * 
     * 	tk_malloc(size)
     * 	tk_calloc(num, size)
     *  tk_free(ptr)			//ptr��ΪTK_NULL
     *  tk_free_func(ptr)		//ptr��ΪTK_NULL������array_list��OOC����Ҫָ����������ָ��ĵط�
     *  tk_mem_left_size		//ʣ������ڴ��С������������APE�������ڴ�©��
     *  
     *  Ӧ�ò㣨������������ڴ�ģ��ͼ������ڴ�ģ���⣩�����������Ϸ�ʽ���е��ã�������ñ��ļ������漰�������������
     * 
     ***************************************************************/

    //tk_free_func���ܱ��ض���Ϊtk_adapter_free_func��������ĸ��ݲ�ͬƽ̨�ľ�������
    void tk_adapter_free_func(void* ptr, char* file, unsigned int line);

    //���ݲ�ͬƽ̨�������C��׼��calloc���ã���tk_calloc�����ض���Ϊcalloc
    //����tk_calloc�����ض���Ϊtk_adapter_calloc
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
