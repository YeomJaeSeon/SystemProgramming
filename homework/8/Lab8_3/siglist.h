#ifndef SIGLIST_H_INCLUDED
#define SIGLIST_H_INCLUDED

#include <signal.h>

struct siginfo {
    int code;
    char *name;
    char *description;
};

const struct siginfo siglist[] = {
#ifdef SIGABRT
    {SIGABRT  , "SIGABRT"  , "Abort signal"},
#endif
#ifdef SIGALRM
    {SIGALRM  , "SIGALRM"  , "Timer signal"},
#endif
#ifdef SIGBUS
    {SIGBUS   , "SIGBUS"   , "Bus error (bad memory access)"},
#endif
#ifdef SIGCHLD
    {SIGCHLD  , "SIGCHLD"  , "Child stopped or terminated"},
#endif
#ifdef SIGCLD
    {SIGCLD   , "SIGCLD"   , "Child stopped or terminated"},
#endif
#ifdef SIGCONT
    {SIGCONT  , "SIGCONT"  , "Continue if stopped"},
#endif
#ifdef SIGEMT
    {SIGEMT   , "SIGEMT"   , "Emulator trap"},
#endif
#ifdef SIGFPE
    {SIGFPE   , "SIGFPE"   , "Floating-point exception"},
#endif
#ifdef SIGHUP
    {SIGHUP   , "SIGHUP"   , "Hangup detected on controlling terminal or death of controlling process"},
#endif
#ifdef SIGILL
    {SIGILL   , "SIGILL"   , "Illegal Instruction"},
#endif
#ifdef SIGINFO
    {SIGINFO  , "SIGINFO"  , "Power failure"},
#endif
#ifdef SIGINT
    {SIGINT   , "SIGINT"   , "Interrupt from keyboard"},
#endif
#ifdef SIGIO
    {SIGIO    , "SIGIO"    , "I/O now possible"},
#endif
#ifdef SIGIOT
    {SIGIOT   , "SIGIOT"   , "IOT trap: Abort signal"},
#endif
#ifdef SIGKILL
    {SIGKILL  , "SIGKILL"  , "Kill signal"},
#endif
#ifdef SIGLOST
    {SIGLOST  , "SIGLOST"  , "File lock lost "},
#endif
#ifdef SIGPIPE
    {SIGPIPE  , "SIGPIPE"  , "Broken pipe: write to pipe with no readers"},
#endif
#ifdef SIGPOLL
    {SIGPOLL  , "SIGPOLL"  , "Pollable event: I/O now possible"},
#endif
#ifdef SIGPROF
    {SIGPROF  , "SIGPROF"  , "Profiling timer expired"},
#endif
#ifdef SIGPWR
    {SIGPWR   , "SIGPWR"   , "Power failure"},
#endif
#ifdef SIGQUIT
    {SIGQUIT  , "SIGQUIT"  , "Quit from keyboard"},
#endif
#ifdef SIGSEGV
    {SIGSEGV  , "SIGSEGV"  , "Invalid memory reference"},
#endif
#ifdef SIGSTKFLT
    {SIGSTKFLT, "SIGSTKFLT", "Stack fault on coprocessor"},
#endif
#ifdef SIGSTOP
    {SIGSTOP  , "SIGSTOP"  , "Stop process"},
#endif
#ifdef SIGTSTP
    {SIGTSTP  , "SIGTSTP"  , "Stop typed at terminal"},
#endif
#ifdef SIGSYS
    {SIGSYS   , "SIGSYS"   , "Bad system call "},
#endif
#ifdef SIGTERM
    {SIGTERM  , "SIGTERM"  , "Termination signal"},
#endif
#ifdef SIGTRAP
    {SIGTRAP  , "SIGTRAP"  , "Trace/breakpoint trap"},
#endif
#ifdef SIGTTIN
    {SIGTTIN  , "SIGTTIN"  , "Terminal input for background process"},
#endif
#ifdef SIGTTOU
    {SIGTTOU  , "SIGTTOU"  , "Terminal output for background process"},
#endif
#ifdef SIGUNUSED
    {SIGUNUSED, "SIGUNUSED", "Bad system call "},
#endif
#ifdef SIGURG
    {SIGURG   , "SIGURG"   , "Urgent condition on socket "},
#endif
#ifdef SIGUSR1
    {SIGUSR1  , "SIGUSR1"  , "User-defined signal 1"},
#endif
#ifdef SIGUSR2
    {SIGUSR2  , "SIGUSR2"  , "User-defined signal 2"},
#endif
#ifdef SIGVTALRM
    {SIGVTALRM, "SIGVTALRM", "Virtual alarm clock "},
#endif
#ifdef SIGXCPU
    {SIGXCPU  , "SIGXCPU"  , "CPU time limit exceeded "},
#endif
#ifdef SIGXFSZ
    {SIGXFSZ  , "SIGXFSZ"  , "File size limit exceeded"},
#endif
#ifdef SIGWINCH
    {SIGWINCH , "SIGWINCH" , "Window resize signal"},
#endif
};

const size_t SIGLIST_LENGTH = sizeof(siglist)/sizeof(siglist[0]);

#endif // SIGLIST_H_INCLUDED
