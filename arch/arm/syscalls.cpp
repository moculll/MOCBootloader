
#include <errno.h>
#include <unistd.h>

#include <stddef.h>
#include <driver/Uart.h>

extern char __HeapLimit;
extern char _heap_start;
extern char _stack_top;
static char *heap_ptr = &_heap_start;

extern "C" void __sync_synchronize() {}

extern "C"
void* _sbrk(ptrdiff_t incr) {
    char *prev = heap_ptr;

    if (heap_ptr + incr > &__HeapLimit) {
        errno = ENOMEM;
        return (void*)-1;
    }

    heap_ptr += incr;
    return (void*)prev;
}

extern "C"
int _write(int fd, char* ptr, int len) {
    if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
        MOCBootloader::Driver::Uart::instance().write(0, ptr, len);
        return len;
    }
    errno = EBADF;
    return -1;
}

extern "C"
int _read(int file, char* ptr, int len) {

    return 0;
}



extern "C"
int _fstat(int file, struct stat* st) {

    return 0;
}

extern "C"
int _isatty(int file) {
    return 1;
}

extern "C"
int _lseek(int file, int ptr, int dir) {
    return 0;
}

extern "C"
int _close(int file) {
    return -1;
}

extern "C"
int _kill(int pid, int sig) {
    errno = EINVAL;
    return -1;
}

extern "C"
int _getpid(void) {
    return 1;
}

extern "C"
void _exit(int status) {
    while (1);
}
