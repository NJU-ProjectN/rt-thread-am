/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-21     Meco Man     The first version
 * 2021-12-25     Meco Man     Handle newlib 2.2.0 or lower version
 */

/*
 * Newlib's <sys/types.h> includes <sys/select.h> before it defines clock_t.
 * If this wrapper is picked up at that point, including RT-Thread's
 * <sys/time.h> below pulls in <time.h> too early and newlib sees an undefined
 * clock_t.  In that specific in-progress newlib include, keep using newlib's
 * own select definitions first.
 */
#if defined(__GNUC__) && !defined(__ARMCC_VERSION) && defined(_SYS_TYPES_H) && \
    !defined(__clock_t_defined) && !defined(_CLOCK_T_DECLARED)
#include_next <sys/select.h>
#else

#ifndef __SYS_SELECT_H__
#define __SYS_SELECT_H__

#include <rtconfig.h>
#include <sys/types.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef  FD_SETSIZE
#define  FD_SETSIZE  32
#endif

#ifdef SAL_USING_POSIX
#ifdef FD_SETSIZE
#undef FD_SETSIZE
#endif
#define FD_SETSIZE      DFS_FD_MAX
#endif /* SAL_USING_POSIX */

typedef long    fd_mask;

#ifndef _SYS_TYPES_FD_SET /* Newlib 2.2.0 or lower version */
#define   NBBY    8       /* number of bits in a byte */
#define   NFDBITS (sizeof (fd_mask) * NBBY)   /* bits per mask */
#ifndef   howmany
#define   howmany(x,y)    (((x)+((y)-1))/(y))
#endif /* howmany */

typedef struct _types_fd_set {
    fd_mask fds_bits[howmany(FD_SETSIZE, NFDBITS)];
} _types_fd_set;
#define fd_set _types_fd_set

#define FD_SET(n, p)    ((p)->fds_bits[(n)/NFDBITS] |= (1L << ((n) % NFDBITS)))
#define FD_CLR(n, p)    ((p)->fds_bits[(n)/NFDBITS] &= ~(1L << ((n) % NFDBITS)))
#define FD_ISSET(n, p)  ((p)->fds_bits[(n)/NFDBITS] & (1L << ((n) % NFDBITS)))
#define FD_ZERO(p)      rt_memset((void*)(p), 0, sizeof(*(p)))
#endif /* _SYS_TYPES_FD_SET */

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

#ifdef __cplusplus
}
#endif

#endif /* __SYS_SELECT_H__ */

#endif
