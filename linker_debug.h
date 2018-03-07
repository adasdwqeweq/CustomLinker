//
//  linker_debug.h
//  Goblin_Shell_4.1.2
//
//  Created by liu meng on 2018/1/30.
//  Copyright © 2018年 com.qunar. All rights reserved.
//

#ifndef _LINKER_DEBUG_H_
#define _LINKER_DEBUG_H_
#include <stdio.h>
#include <android/log.h>
#define LOG_TAG "liumeng"
#define LINKER_DEBUG_TO_LOG  1
#define TRACE_DEBUG          1
#define DO_TRACE_LOOKUP      1
#define DO_TRACE_RELO        1
#define TIMING               0
#define STATS                0
#define COUNT_PAGES          0


#undef TRUE
#undef FALSE
#define TRUE                 1
#define FALSE                0

#include "linker_format.h"
extern int debug_verbosity;
extern int format_log(int, const char *, const char *, ...);
extern int format_fd(int, const char *, ...);
#define DL_INFO(fmt, args...)  \
 __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,fmt, ##args)
#define DL_ERR(fmt, args...)    \
 __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,fmt, ##args)
#define _PRINTVF(v,f,x...)   do {} while(0)
#define PRINT(fmt,args...)   \
 __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,fmt, ##args)
#define INFO(fmt,args...)    \
 __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,fmt, ##args)
#define TRACE(fmt,args...)   \
 __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,fmt, ##args)
#define WARN(fmt,args...)    \
 __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,fmt, ##args)
#define ERROR(fmt,args...)    \
 __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,fmt, ##args)
#define DEBUG(fmt,args...)   \
 __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,fmt, ##args)
#define TEMP_FAILURE_RETRY(exp) ({         \
typeof (exp) _rc;                      \
do {                                   \
_rc = (exp);                       \
} while (_rc == -1 && errno == EINTR); \
_rc; })
#define RELOC_ABSOLUTE        0
#define RELOC_RELATIVE        1
#define RELOC_COPY            2
#define RELOC_SYMBOL          3
#define NUM_RELOC_STATS       4
struct _link_stats {
    int reloc[NUM_RELOC_STATS];
};
extern struct _link_stats linker_stats;

#define DEBUG_DUMP_PHDR(phdr, name, pid) do { \
DEBUG("%5d %s (phdr = 0x%08x)\n", (pid), (name), (unsigned)(phdr));   \
DEBUG("\t\tphdr->offset   = 0x%08x\n", (unsigned)((phdr)->p_offset)); \
DEBUG("\t\tphdr->p_vaddr  = 0x%08x\n", (unsigned)((phdr)->p_vaddr));  \
DEBUG("\t\tphdr->p_paddr  = 0x%08x\n", (unsigned)((phdr)->p_paddr));  \
DEBUG("\t\tphdr->p_filesz = 0x%08x\n", (unsigned)((phdr)->p_filesz)); \
DEBUG("\t\tphdr->p_memsz  = 0x%08x\n", (unsigned)((phdr)->p_memsz));  \
DEBUG("\t\tphdr->p_flags  = 0x%08x\n", (unsigned)((phdr)->p_flags));  \
DEBUG("\t\tphdr->p_align  = 0x%08x\n", (unsigned)((phdr)->p_align));  \
} while (0)

#endif /* _LINKER_DEBUG_H_ */

