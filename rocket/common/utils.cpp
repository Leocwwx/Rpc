#include "utils.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

namespace rocket{

static int g_pid = 0;
static thread_local int g_threadId = 0;
    pid_t getPid()
    {
        if(g_pid != 0)
        {
            return g_pid;
        }
        return getpid();
    }

    pid_t getThreadId()
    {
        if(g_threadId != 0)
        {
            return g_threadId;
        }
        return syscall(SYS_gettid);
    }
}