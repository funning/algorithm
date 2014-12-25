#include "MemAdapter.h"
#include <stdlib.h>

#include <string.h>
#include "Log.h"
unsigned int tk_mem_malloc_count = 0;

#ifdef TK_SHOW_MEM_DETAIL

	unsigned int _tk_mem_peak_size = 0;
	unsigned int _tk_mem_heap_size = 0;

	static unsigned int _malloced_size = 0;
#endif

void* tk_malloc_debug(unsigned int size, char* file, unsigned int line) {
	if(size > 0) {
	        tk_mem_malloc_count++;
	#ifdef TK_S_CHECKING_MEMORY_LEAKS
	        {
	            void* mem_ptr = malloc(size);
				if(mem_ptr == TK_NULL) {
					TK_TRACE_DEBUG(("tk_x_malloc_mem: can't malloc %d mem, file %s, line %d", size, file, line));
				}
				tk_bookkeeper_mem_alloc(mem_ptr, size, file, line);
				TK_TRACE_INFO(("tk_malloc_debug mem_ptr = %p\n", mem_ptr));
	            return mem_ptr;
	        }
	#else	//	#ifdef TK_S_CHECKING_MEMORY_LEAKS
	        return malloc(size);
	#endif	//	#ifdef TK_S_CHECKING_MEMORY_LEAKS
	    } else {
	        return TK_NULL;
	    }
}



void tk_free_debug(void* p, char* file, unsigned int line) {
	if(p) {
	        if(tk_mem_malloc_count == 0) {
	            TK_TRACE_INFO(("tk_x_free_mem: ERROR: memory free too much"));
	            return;
	        }

	#ifdef TK_S_CHECKING_MEMORY_LEAKS
	// 		TK_TRACE_DEBUG(("tk_x_free_mem: mem_ptr %p, file %s, line %d", p, file, line));
	        tk_bookkeeper_mem_free(p, file, line);
	#endif	//#ifdef TK_S_CHECKING_MEMORY_LEAKS
	        free(p);
	        tk_mem_malloc_count--;
	    }
}

void* tk_calloc_debug(unsigned int num, unsigned int size, char* file, unsigned int line) {
	unsigned int sz = num * size;
	void* ptr = tk_malloc_debug(sz, file, line);
	if (ptr)
		memset(ptr, 0, sz);
	return ptr;
}

//static tk_pstr _get_meminfo() {
//	tk_int32 fd = tk_x_fopen("/proc/meminfo", TK_FS_READ_ONLY);
//	tk_pstr buffer = TK_NULL;
//
//	tk_uint32 size[1] = { 64 };
//
//	if (fd != -1)
//		;	//size[0] = tk_x_fsize(fd, size);
//	else
//		return buffer;
//
//	if (size[0] > 0) {
//		buffer = tk_calloc(1, size[0] + 1);
//		if (buffer) {
//			tk_uint32 actual[1] = { -1 };
//			tk_x_fread(fd, buffer, size[0], actual);
//
//			TK_TRACE_DEBUG(("%s tk_mem_left_size buffer = %s\n", __FILE__, buffer));
//		}
//	}
//	tk_x_fclose(fd);
//	return buffer;
//}
//
//tk_uint32 tk_mem_left_size() {
//	tk_pstr meminfo = _get_meminfo();
//	tk_uint32 freemem = 0;
//	if (meminfo) {
//		tk_pstr pos = tk_strstr(meminfo, "MemFree: ");
//		TK_TRACE_DEBUG(("tk_mem_left_size MemFree %s \n", meminfo));
//		if (pos)
//			tk_sscanf(pos, "MemFree:                %d   kB ", &freemem);
//		tk_free(meminfo);
//	}
//	TK_TRACE_DEBUG(("tk_mem_left_size freemem = %d\n", freemem));
//	return freemem * 1024;
//}
//
//
//tk_uint32 tk_x_mem_total_size(tk_void) {
//	tk_pstr meminfo = _get_meminfo();
//	tk_uint32 totalmem = 0;
//	if (meminfo) {
//		tk_pstr pos = tk_strstr(meminfo, "MemTotal: ");
//		if (pos)
//			tk_sscanf(pos, "MemTotal:               %d   kB ", &totalmem);
//		tk_free(meminfo);
//	}
//	return totalmem * 1024;
//}


unsigned int tk_mem_left_size() {
	return 10240;
}


unsigned int tk_x_mem_total_size(void) {
	return 10240;
}
