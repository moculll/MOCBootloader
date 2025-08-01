#pragma once
#include <stdint.h>
#include <functional>
#include <memory>
#include <variant>
#include <string.h>
#include <forward_list>
#include <stdio.h>
#include <string>
namespace MOCoroutine {

extern "C" void MOCoroutineSwitchImpl(void *from, void *to) __attribute__((noinline));
extern "C" void MOCoroutineSaveContextImpl(void *save) __attribute__((noinline));
extern "C" void MOCoroutineRestoreContextImpl(void *restore) __attribute__((noinline));

enum class ArchType {
    AARCH64,
    ARM,
};

/* aarch64 register */
template<ArchType>
struct Context;

template<>
struct Context<ArchType::AARCH64> {
    /* x18 */
    void *pr;
    /* x19-x28 */
    void *callee[10];
    /* x29 */
    void *fp;
    /* x30 */
    void *lr;
    void *sp;
    void *entry;
    void *reg;
    /* d8-d15 */
    void *fpu[8];

    void init(void *stackTop, void *entryFunc, void *entryArg, void *exitFunc)
    {
        uint8_t *bp = reinterpret_cast<uint8_t *>(stackTop);
        bp -= (uintptr_t)bp % 16;
        sp = bp - 16;
        fp = stackTop;
        lr = exitFunc;
        entry = entryFunc;
        reg = entryArg;
    }


    Context()
    {
        clear();
    }

    void clear()
    {
        memset(this, 0, sizeof(*this));
    }

};

template<>
struct Context<ArchType::ARM> {
    /* r4-r11 */
    void *callee[8];
    /* s16-s31 */
    void * fpu[16];

    void *sp;
    void *lr;
    void *pc;
    
    void *entry;
    void *reg;

    void init(void *stackTop, void *entryFunc, void *entryArg, void *exitFunc)
    {
        uint8_t *bp = reinterpret_cast<uint8_t *>(stackTop);
        bp -= (uintptr_t)bp % 8;
        this->sp = bp - 8;
        this->pc = entryFunc;
        this->lr = exitFunc;
        this->entry = entryFunc;
        this->reg = entryArg;
        /* printf("registered entry: %p, arg: %p\r\n", entry, reg); */
    }

    void print(const std::string &tag) {
        /* printf("sp: %p, lr: %p, pc: %p, entry: %p, reg: %p\r\n", sp, lr, pc, entry, reg); */
    }

    Context()
    {
        clear();
    }

    void clear()
    {
        memset(this, 0, sizeof(*this));
    }

};

class Stack {
public:

    Stack(uint64_t stackSize) : size(stackSize)
    {
        stack = new uint8_t[stackSize];
        memset(stack, 0, size);
    }

    Stack(uint8_t *stk, uint64_t stackSize) : stack(stk), size(stackSize) {}

    ~Stack()
    {
        delete stack;
    }

    void *stackTop()
    {
        return reinterpret_cast<void *>(stack + size);
    }
private:

    uint8_t *stack;
    uint64_t size;
};




class Coroutine {
    friend class Scheduler;
public:
    enum class State { READY, RUNNING, SUSPENDED, FINISHED };

    template<typename F, typename... Args>
    Coroutine(const std::string &initTag, std::unique_ptr<Stack> stk, F&& func, Args&&... args) : tag(initTag), stack(std::move(stk)) 
    {
        callback = [=] {
            func(args...);
        };
        
    }

    template<typename F, typename... Args>
    Coroutine(const std::string &initTag, std::shared_ptr<Stack> stk, F&& func, Args&&... args) : tag(initTag), stack(stk) 
    {
        callback = [=] {
            func(args...);
        };
        
    }

    std::function<void()> callback;

    void yield()
    {

    }

    void resume()
    {

    }

    void start()
    {

    }
    
private:
    Coroutine() = delete;
    const std::string &tag;
    State state = State::READY;
    
#if __AARCH64
    Context<ArchType::AARCH64> context;
#elif __ARM
    Context<ArchType::ARM> context;
#endif


    using StackPtr = std::variant<
        std::unique_ptr<Stack>,
        std::shared_ptr<Stack>
    >;

    StackPtr stack;

};



class Scheduler {
public:

    void entry(Coroutine* co) {
        co->callback();
    }

    void init(Coroutine* co);

    void add(Coroutine *co)
    {
        init(co);
        coroutines.emplace_front(co);
    }

    void exitEntry();
    
    void run();

    void yield();

    static Scheduler &instance()
    {
        static Scheduler instance;

        return instance;
    }
private:
    Scheduler() : currentCoroutine(nullptr), lastScheduled(coroutines.end()) {}

    Coroutine* findNextRunnable();
    Coroutine *currentCoroutine;
    /* std::vector<Coroutine *> coroutines; */
    std::forward_list<Coroutine *> coroutines;
    std::forward_list<Coroutine *>::iterator lastScheduled;

#if __AARCH64
    Context<ArchType::AARCH64> mainContext;
#elif __ARM
    Context<ArchType::ARM> mainContext;
#endif
};



} /* MOCoroutine */