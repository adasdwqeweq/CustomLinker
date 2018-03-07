#ifndef _LINKER_H_
#define _LINKER_H_

#include <unistd.h>
#include <sys/types.h>
#include "elf.h"
#include "exec_elf.h"
#include "Utils.h"
#include "auxvec.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include <pthread.h>
#include <jni.h>
#include <sys/mman.h>
#include <sys/atomics.h>
#include "public.h"
#undef PAGE_MASK
#undef PAGE_SIZE
#define PAGE_SIZE 4096
#define PAGE_MASK 4095
void debugger_init();
const char *addr_to_name(unsigned addr);

/* magic shared structures that GDB knows about */

struct link_map
{
    uintptr_t l_addr;
    char * l_name;
    uintptr_t l_ld;
    struct link_map * l_next;
    struct link_map * l_prev;
};

/* needed for dl_iterate_phdr to be passed to the callbacks provided */
struct dl_phdr_info
{
    Elf32_Addr dlpi_addr;
    const char *dlpi_name;
    const Elf32_Phdr *dlpi_phdr;
    Elf32_Half dlpi_phnum;
};


// Values for r_debug->state

struct r_debug
{
    int32_t r_version;
    struct link_map * r_map;
    void (*r_brk)(void);
    int32_t r_state;
    uintptr_t r_ldbase;
};

typedef struct soinfo soinfo;



struct soinfo
{
    const char name[SOINFO_NAME_LEN];
    Elf32_Phdr *phdr;
    int phnum;
    unsigned entry;
    unsigned base;
    unsigned size;

    int unused;  // DO NOT USE, maintained for compatibility.

    unsigned *dynamic;

    unsigned wrprotect_start;
    unsigned wrprotect_end;

    soinfo *next;
    unsigned flags;

    const char *strtab;
    Elf32_Sym *symtab;

    unsigned nbucket;
    unsigned nchain;
    unsigned *bucket;
    unsigned *chain;

    unsigned *plt_got;

    Elf32_Rel *plt_rel;
    unsigned plt_rel_count;

    Elf32_Rel *rel;
    unsigned rel_count;

    unsigned *preinit_array;
    unsigned preinit_array_count;

    unsigned *init_array;
    unsigned init_array_count;
    unsigned *fini_array;
    unsigned fini_array_count;

    void (*init_func)(void);
    void (*fini_func)(void);

#ifdef ANDROID_ARM_LINKER
    /* ARM EABI section used for stack unwinding. */
    unsigned *ARM_exidx;
    unsigned ARM_exidx_count;
#endif

    unsigned refcount;
    struct link_map linkmap;

    int constructors_called;

    Elf32_Addr gnu_relro_start;
    unsigned gnu_relro_len;

};


extern soinfo libdl_info;



soinfo *find_library(const char *name);
unsigned unload_library(soinfo *si);
Elf32_Sym *lookup_in_library(soinfo *si, const char *name);
Elf32_Sym *lookup(const char *name, soinfo **found, soinfo *start);
soinfo *find_containing_library(const void *addr);
Elf32_Sym *find_containing_symbol(const void *addr, soinfo *si);

void call_constructors_recursive(soinfo *si);

#ifdef ANDROID_ARM_LINKER
typedef long unsigned int *_Unwind_Ptr;
_Unwind_Ptr dl_unwind_find_exidx(_Unwind_Ptr pc, int *pcount);
#elif defined(ANDROID_X86_LINKER)
int dl_iterate_phdr(int (*cb)(struct dl_phdr_info *, size_t, void *), void *);
#endif

#endif
