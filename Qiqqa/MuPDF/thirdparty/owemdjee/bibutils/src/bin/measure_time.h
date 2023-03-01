#ifndef __MEASURE_TIME_H__
#define __MEASURE_TIME_H__

#include "cross_platform_porting.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef int (*work_fn)(const char *title, void * closure);
typedef int (*report_fn)(double msecs, const char *title, void* closure);

extern int measure(work_fn work, report_fn report, const char *title, void* closure);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


