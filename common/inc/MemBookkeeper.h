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
 *   TKMemBookkeeper.h
 *
 * Project:
 * --------
 *   TigerMap 4.0
 *
 * Description:
 *   
 * Date: 2011-5-3
 ******************************************************************************/

#ifndef TKMEMBOOKKEEPER_H_
#define TKMEMBOOKKEEPER_H_


int tk_bookkeeper_mem_alloc(void* ptr, unsigned int size, char* file, unsigned int line_no);
void tk_bookkeeper_mem_free(void* ptr, char* file, unsigned int line_no);

int tk_bookkeeper_get_mem_leak_count(void);
int tk_bookkeeper_get_mem_peak_size(void);

void tk_bookkeeper_mem_report(void);
void tk_check_memory_leaks(void);


#endif /* TKMEMBOOKKEEPER_H_ */
