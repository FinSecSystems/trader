
#include "targetver.h"

#include "defines.h"

#if defined(_DEBUG)
#define TASK_SCHEDULER_DEBUG 1
#else
#define TASK_SCHEDULER_DEBUG 0
#endif // defined(_DEBUG)
#define TASK_SCHEDULER_ASSERT 1
#define TASK_SCHEDULER_PROFILER TASK_SCHEDULER_PROFILER_ITT
