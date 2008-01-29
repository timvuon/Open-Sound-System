#ifndef _OS_H_
#define _OS_H_

/*
 * Purpose: OS specific definitions for Linux
 *
 * Under Linux os.h (this file) defines just the macros, functions and
 * structures used by the code compiled in the development system. However
 * there are other Linux specific definitions contained in {!nlink Linux/wrap.h}
 * that are used both by the code compiled in the devlopment and target systems.
 * This means that some definitions found in os.h under some other operating
 * systems may be in wrap.h under Linux.
 */
#define COPYING9 Copyright (C) Hannu Savolainen and Dev Mazumdar 2000-2007. All rights reserved.

#define OS_VERSION "2.6.x"
#define __EXTENDED__
#define OSS_MAINLINE_BUILD

/*
 * Debugging and misc settings
 */
#undef  DO_TIMINGS
#undef  MUTEX_CHECKS
#undef  MEMDEBUG
#define VDEV_SUPPORT

/*
 * Enable support for per-application features such as /dev/dsp device
 * selection based on command name. Requires working GET_PROCESS_NAME
 * macro implementation.
 */
#define APPLIST_SUPPORT
#define USE_DEVICE_SUBDIRS
#define EXTERN_C

#define __invalid_size_argument_for_IOC 0	/* Dummy define to cure some broken ioctl.h versions */

#include <sys/types.h>
#include <sys/param.h>
#include <sys/signal.h>
#include <sys/errno.h>
#include <sys/file.h>
#include "oss_ddi.h"
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <asm/poll.h>
#include "kernel/OS/Linux/wrapper/wrap.h"

#undef HZ
extern int oss_hz;
#define OSS_HZ oss_hz

/* The soundcard.h could be in a nonstandard place so include it here. */
#include "soundcard.h"

struct _oss_device_t
{
  int cardnum;
  int dev_type;
  int instance;
  int available;
  dev_info_t *dip;
  void *devc;
  char *name;
  char nick[16];
  char handle[32];
  int num_audio_engines;
  int num_audioplay, num_audiorec, num_audioduplex;
  int num_mididevs;
  int num_mixerdevs;
  int major;
  struct module *owner;		/* Pointer to THISMODULE (needed by osscore.c) */
  char modname[32];

  volatile int refcount;	/* Nonzero means that the device is needed by some other (virtual) driver. */

/* Interrupts */

  ddi_iblock_cookie_t iblock_cookie;	/* Dummy field under Linux */
  void *irqparms;

/* PCI related fields */

#ifdef _KERNEL
  ddi_acc_handle_t pci_config_handle;
  ddi_acc_handle_t acc_handle;
  int swap_mode;		/* 0=DDI_STRUCTURE_NEVERSWAP_ACC, 1=DDI_STRUCTURE_LE_ACC */
#endif
};

#define ALLOW_BUFFER_MAPPING
#define ALLOW_SELECT
#define SEL_IN		0
#define SEL_OUT		1
#define SEL_EX		0xffffffff

/* Busy wait routine */
#define oss_udelay drv_usecwait
/* System wall timer access */
#define GET_JIFFIES()	oss_get_jiffies()

extern inline unsigned int
__inb (unsigned short port)
{
  unsigned int _v;
  __asm__ __volatile__ ("in" "b" " %" "w" "1,%" "b" "0":"=a" (_v):"d" (port),
			"0" (0));
  return _v;
}
extern inline unsigned int
__inw (unsigned short port)
{
  unsigned int _v;
  __asm__ __volatile__ ("in" "w" " %" "w" "1,%" "w" "0":"=a" (_v):"d" (port),
			"0" (0));
  return _v;
}
extern inline unsigned int
__inl (unsigned short port)
{
  unsigned int _v;
  __asm__ __volatile__ ("in" "l" " %" "w" "1,%" "" "0":"=a" (_v):"d" (port));
  return _v;
}

extern inline void
__outb (unsigned char value, unsigned short port)
{
  __asm__ __volatile__ ("out" "b" " %" "b" "0,%" "w" "1"::"a" (value),
			"d" (port));
}
extern inline void
__outw (unsigned short value, unsigned short port)
{
  __asm__ __volatile__ ("out" "w" " %" "w" "0,%" "w" "1"::"a" (value),
			"d" (port));
}
extern inline void
__outl (unsigned int value, unsigned short port)
{
  __asm__ __volatile__ ("out" "l" " %" "0,%" "w" "1"::"a" (value),
			"d" (port));
}

#define INB(osb,a)	__inb(a)
#define INW(osb,a)	__inw(a)
#define INL(osb,a)	__inl(a)

#define OUTB(osb, d, a) __outb(d, a)

#define OUTW(osb, d, a)	__outw(d, a)
#define OUTL(osb, d, a)	__outl(d, a)

#define PCI_READL(osp, p)  (*(volatile unsigned int *) (p))
#define PCI_WRITEL(osp, addr, data) (*(volatile unsigned int *) (addr) = (data))
#define PCI_READW(osp, p)  (*(volatile unsigned short *) (p))
#define PCI_WRITEW(osp, addr, data) (*(volatile unsigned short *) (addr) = (data))
#define PCI_READB(osp, p)  (*(volatile unsigned char *) (p))
#define PCI_WRITEB(osp, addr, data) (*(volatile unsigned char *) (addr) = (data))

/*
 * When a error (such as EINVAL) is returned by a function,
 * the following macro is used. The driver assumes that a
 * error is signalled by returning a negative value.
 */

/* 
   KERNEL_MALLOC() allocates requested number of memory  and 
   KERNEL_FREE is used to free it. 
   These macros are never called from interrupt, in addition the
   nbytes will never be more than 4096 bytes. Generally the driver
   will allocate memory in blocks of 4k. If the kernel has just a
   page level memory allocation, 4K can be safely used as the size
   (the nbytes parameter can be ignored).
*/
#ifdef MEMDEBUG
extern void *oss_kmem_alloc (size_t size, char *file, int line);
extern void oss_kmem_free (void *addr);
#define KERNEL_MALLOC(nbytes)	oss_kmem_alloc(nbytes, __FILE__, __LINE__)
#define KERNEL_FREE(addr)	oss_kmem_free(addr)
extern void *oss_contig_malloc (oss_device_t * osdev, int sz,
				oss_uint64_t memlimit,
				oss_native_word * phaddr, char *file,
				int line);
extern void oss_contig_free (oss_device_t * osdev, void *p, int sz);
extern oss_native_word oss_virt_to_bus (void *addr);
#define CONTIG_MALLOC(osdev, sz, memlimit, phaddr)	oss_contig_malloc(osdev, sz, memlimit, phaddr, __FILE__, __LINE__)
#define CONTIG_FREE(osdev, p, sz)	oss_contig_free(osdev, p, sz)
#else
#define KERNEL_MALLOC(nbytes)	oss_kmem_alloc(nbytes)
#define KERNEL_FREE(addr)	oss_kmem_free(addr)
#define CONTIG_MALLOC(osdev, sz, memlimit, phaddr)	oss_contig_malloc(osdev, sz, memlimit, phaddr)
#define CONTIG_FREE(osdev, p, sz)	oss_contig_free(osdev, p, sz)
#endif

/*
 * PMALLOC is used to allocate memory that will get automatically freed when
 * OSS unloads. Usable for per-instance structures allocated when OSS modules
 * are being loaded.
 */

extern void *oss_pmalloc (size_t sz);
#define PMALLOC(osdev, sz) oss_pmalloc(sz)

/*
 * Timer macros
 *
 * These macros are obsolete and should not be used in any new code.
 * Use the timeout mechanism (see the timeout(9F) Solaris man page).
 */
#define DEFINE_TIMER(name, proc)	static timeout_id_t name = 0
#define REMOVE_TIMER(name, proc)	{if (name != 0) oss_untimeout(name);}
#define INIT_TIMER(name,proc)
typedef void (*timeout_func_t) (void *);
#define ACTIVATE_TIMER(name, proc, time) \
	name=oss_timeout((timeout_func_t)proc, (void*)&name, time)

#endif

#define OSS_OS "Linux"
#define OSS_OS_LONGNAME "Linux"

#undef DMA_TRY_PSEUDOINIT

int get_dma_residue (int chn);
void disable_dma (int chn);
void enable_dma (int chn);

typedef void (*softintr_func_t) (int);

struct oss_softintr
{
  int id;
  softintr_func_t func;
  volatile int armed, running;
};

#define MUTEX_INIT(osdev, mutex, hier) mutex=oss_mutex_init()
#define MUTEX_CLEANUP(mutex) {oss_mutex_cleanup(mutex);mutex=NULL;}
#define MUTEX_ENTER_IRQDISABLE(mutex, flags) oss_spin_lock_irqsave(mutex, &flags)
#define MUTEX_EXIT_IRQRESTORE(mutex, flags) oss_spin_unlock_irqrestore(mutex, flags)
#define MUTEX_ENTER(mutex, flags) oss_spin_lock(mutex)
#define MUTEX_EXIT(mutex, flags) oss_spin_unlock(mutex)

extern int detect_trace;
#define DDB(x) if (detect_trace) x

#define MAP_PCI_IOADDR(osdev, nr, io) (oss_native_word)io
#define MAP_PCI_MEM(osdev, ix, phaddr, size) 	oss_map_pci_mem(osdev, size, phaddr)
#define UNMAP_PCI_MEM(osdev, ph, virt, size)	oss_unmap_pci_mem(virt)

#define GET_PROCESS_PID(x)  oss_get_pid()

#define GET_PROCESS_NAME(x) oss_get_procname()

#define pci_read_config_irq oss_pci_read_config_irq
#define pci_read_config_byte oss_pci_read_config_byte
#define pci_read_config_word oss_pci_read_config_word
#define pci_read_config_dword oss_pci_read_config_dword
#define pci_write_config_byte oss_pci_write_config_byte
#define pci_write_config_word oss_pci_write_config_word
#define pci_write_config_dword oss_pci_write_config_dword

#define VM_READ         0x1
#define VM_WRITE        0x2

#define FP_SUPPORT

#ifdef FP_SUPPORT
typedef short fp_env_t[512];
typedef unsigned int fp_flags_t[4];
extern int oss_fp_check (void);
extern void oss_fp_save (short *envbuf, fp_flags_t flags);
extern void oss_fp_restore (short *envbuf, fp_flags_t flags);
#   define FP_SAVE(envbuf, flags)		oss_fp_save(envbuf, flags)
#   define FP_RESTORE(envbuf, flags)		oss_fp_restore(envbuf, flags)
#endif

#include "oss_pci.h"