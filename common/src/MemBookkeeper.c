/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Beijing TigerKnows Technology Co. Ltd. (C) 2011
*
 ********************************************************************************
 * Filename:
 * ---------
 *   TKMemBookkeeper.c
 *
 * Project:
 * --------
 *   TigerMap 4.0
 *
 * Description:
 *   
 * Date: 2011-5-3
 ******************************************************************************/
#include "MemAdapter.h"
#include "MemBookkeeper.h"

#ifdef TK_S_CHECKING_MEMORY_LEAKS

extern int tk_x_get_kk_active_socket_count(void);

extern unsigned int tk_mem_malloc_count;

//#define TK_S_SIMPLE_MEM_LEAKS_CHECKING

#ifdef TK_S_SIMPLE_MEM_LEAKS_CHECKING   //简单的内存泄漏检测
extern unsigned int _tk_mem_peak_size;

int tk_bookkeeper_get_mem_leak_count(void) {
    return tk_mem_malloc_count;
}

int tk_bookkeeper_get_mem_peak_size(void) {
	return _tk_mem_peak_size;
}

void tk_bookkeeper_mem_report(void) {
    TK_TRACE_ERROR(("ERROR: tk_bookkeeper_mem_report, leak count=%d", tk_mem_malloc_count));
}
int tk_bookkeeper_mem_alloc(void* ptr, unsigned int size, char* file, unsigned int line_no) {
}

void tk_bookkeeper_mem_free(void* ptr, char* file, unsigned int line_no) {
}


#else //#ifdef TK_S_SIMPLE_MEM_LEAKS_CHECKING   //复杂的内存泄漏检测

typedef struct {
	void* ptr;
	short file_id;
	short line_no;
	int   size;
}tk_struct_bookkeeper_meminfo;

#define MAX_FILE_NUMBER 1000
#define MAX_MALLOC_CALLED_TIMES 5000
static char** _file_names;
static tk_struct_bookkeeper_meminfo* _malloc_ptrs;
int _file_count;
int _malloc_count;
int _malloc_size;
int _peak_count;
int _peak_size;

int tk_bookkeeper_get_mem_leak_count(void) {
    return _malloc_count;
}

int tk_bookkeeper_get_mem_peak_size(void) {
	return _peak_size;
}

void tk_bookkeeper_mem_report(void) {
	tk_struct_bookkeeper_meminfo* p = _malloc_ptrs;
	char* file_name;
	int i;
	TK_TRACE_ERROR(("tk_bookkeeper_mem_report, leak count=%d\n", _malloc_count));
	for(i=0 ; i<_malloc_count ; ++i,++p) {
		file_name = p->file_id >=0 ? _file_names[p->file_id] : "--";
		TK_TRACE_ERROR(("    %d.%s,%d,%d", i+1, file_name, p->line_no, p->size));
	}
}

static void _bookkeeper_mem_init(void) {
	static int tk_bookkeeper_mem_init_in_work = TK_FALSE;
	if(tk_bookkeeper_mem_init_in_work == TK_TRUE)//此静态变量的赋值和判断是防止和内存申请互相调用行程递归。
		return;
	tk_bookkeeper_mem_init_in_work = TK_TRUE;
	if(!_file_names)
		_file_names = (char**)tk_malloc(MAX_FILE_NUMBER * sizeof(_file_names[0]));
	if(!_malloc_ptrs)
		_malloc_ptrs = (tk_struct_bookkeeper_meminfo*)tk_malloc(MAX_MALLOC_CALLED_TIMES * sizeof(_malloc_ptrs[0]));
	tk_bookkeeper_mem_init_in_work = TK_FALSE;
}
static void _bookkeeper_mem_destroy(void) {
	int i;
	static int tk_bookkeeper_mem_destroy_in_work = TK_FALSE;
	if(tk_bookkeeper_mem_destroy_in_work != TK_FALSE)//此静态变量的赋值和判断是防止和内存申请互相调用行程递归。
		return;
	tk_bookkeeper_mem_destroy_in_work = TK_TRUE;
	for(i=0 ; i<_file_count ; ++i)
		tk_free(_file_names[i]);
	tk_free(_file_names);
	tk_free(_malloc_ptrs);
	_file_names = TK_NULL;
	_malloc_ptrs = TK_NULL;
	_file_count = 0;
	_malloc_count = 0;
	_malloc_size = 0;
	tk_bookkeeper_mem_destroy_in_work = TK_FALSE;
}

static short _bookkeeper_mem_get_file_id(char* file) {
	int i = _file_count-1;
	if(!file)
		return -1;
	while(i>=0) {
		if(strcmp(_file_names[i], file) == 0)
			break;
		--i;
	}
	if(i>=0)
		return i;
	i = _file_count++;
//	TK_ASSERT(i<MAX_FILE_NUMBER);
	_file_names[i] = tk_malloc(strlen(file)+1);
	strcpy(_file_names[i], file);
	return i;
}


int tk_bookkeeper_mem_alloc(void* ptr, unsigned int size, char* file, unsigned int line_no) {
    static int tk_bookkeeper_mem_alloc_in_work = TK_FALSE;
    if(tk_bookkeeper_mem_alloc_in_work != TK_FALSE)
        return TK_SUCCESS;
    tk_bookkeeper_mem_alloc_in_work = TK_TRUE;
	_bookkeeper_mem_init();
//	TK_ASSERT(_malloc_count<MAX_MALLOC_CALLED_TIMES);
	_malloc_ptrs[_malloc_count].ptr = ptr;
	_malloc_ptrs[_malloc_count].file_id = _bookkeeper_mem_get_file_id(file);
	_malloc_ptrs[_malloc_count].line_no = (short)line_no;
	_malloc_ptrs[_malloc_count].size = size;
	++_malloc_count;
	if(_malloc_count > _peak_count)
		_peak_count = _malloc_count;
	_malloc_size += size;
	if(_malloc_size > _peak_size)
		_peak_size = _malloc_size;
	tk_bookkeeper_mem_alloc_in_work = TK_FALSE;
	return TK_SUCCESS;
}

void tk_bookkeeper_mem_free(void* ptr, char* file, unsigned int line_no) {
    static int tk_bookkeeper_mem_free_in_work = TK_FALSE;
	int i = _malloc_count-1;
    if(_malloc_count == 0)
        return;
    if(tk_bookkeeper_mem_free_in_work != TK_FALSE)
        return;
    tk_bookkeeper_mem_free_in_work = TK_TRUE;
	while(i>=0) {
		if(_malloc_ptrs[i].ptr == ptr) {
			_malloc_size -= _malloc_ptrs[i].size;
			--_malloc_count;
			while(i<_malloc_count) {
				_malloc_ptrs[i] = _malloc_ptrs[i+1];
				++i;
			}
			break;
		}
		--i;
	}
	if(_malloc_count == 0)
		_bookkeeper_mem_destroy();
	tk_bookkeeper_mem_free_in_work = TK_FALSE;
}

#endif //#ifdef TK_S_SIMPLE_MEM_LEAKS_CHECKING

static tk_bool _do_mem_leak_checking_now(void) {//todo

    
    return TK_TRUE;
}

void tk_check_memory_leaks(void) {
    if(!_do_mem_leak_checking_now())
        return;
    
    TK_TRACE_INFO(("tk_check_memory_leaks: tk_mem_left_size: %d, mem leaks count: %d, (%d including mem bookkeeper)", 
            tk_mem_left_size(), tk_bookkeeper_get_mem_leak_count(), tk_mem_malloc_count));
    TK_TRACE_INFO(("tk_x_get_kk_active_socket_count: %d", tk_x_get_kk_active_socket_count()));
    if(tk_bookkeeper_get_mem_leak_count() != 0
            || tk_x_get_kk_active_socket_count() != 0) {
        char prompt[64] = {0};
        sprintf(prompt, "内存泄漏%d次, KK未关闭Socket %d个",
                tk_bookkeeper_get_mem_leak_count(), tk_x_get_kk_active_socket_count());
        TK_TRACE_ERROR(("tk_check_memory_leaks: %s", prompt));
        tk_bookkeeper_mem_report();
//        tk_show_prompt_screen("提示", prompt, TK_NULL);
    }
}

#else //#ifdef TK_S_CHECKING_MEMORY_LEAKS

int tk_bookkeeper_mem_alloc(void* ptr, unsigned int size, char* file, unsigned int line_no) {
	return 0;
}
void tk_bookkeeper_mem_free(void* ptr, char* file, unsigned int line_no) {
}
int tk_bookkeeper_get_mem_peak_size(void) {
	return 0;
}

void tk_bookkeeper_mem_report(void) {}
#endif //#ifdef TK_S_CHECKING_MEMORY_LEAKS

