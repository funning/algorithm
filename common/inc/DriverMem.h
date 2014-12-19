/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Beijing TigerKnows Technology Co. Ltd. (C) 2011
 *******************************************************************************
 * Filename:
 * ---------
 *   TKDriverMem.h
 *
 * Project:
 * --------
 *
 * Description:
 *
 * Author:
 *
 * Date:
 ******************************************************************************/

#ifndef TKDRIVERMEM_H_
 
#define TKDRIVERMEM_H_

typedef struct node{
	void* data;
	struct node* next;
}listNode;
void* tk_malloc_debug(unsigned int size, char* file, unsigned int line);
void  tk_free_debug(void* ptr, char* file, unsigned int line) ;
unsigned int tk_mem_left_size_in_ape(void);
void* tk_calloc_debug(unsigned int num, unsigned int size, char* file, unsigned int line) ;

#endif //#ifndef TKDRIVERMEM_H_
