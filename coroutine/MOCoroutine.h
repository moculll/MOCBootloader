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

/* aarch64 register */
struct Context {
    /* x18 */
    uint64_t pr;
    /* x19-x28 */
    uint64_t callee[10];
    /* x29 */
    uint64_t fp;
    /* x30 */
    uint64_t lr;
    uint64_t sp;
    uint64_t jump_to;
    uint64_t reg;
    /* d8-d15 */
    uint64_t fpu[8];

    void print(const std::string &tag) {
        printf("=== %s ===\n", tag.c_str());
        
        printf("x18:  0x%016lx\n", pr);
        for (int i = 0; i < static_cast<int>(sizeof(callee) / sizeof(callee[0])); ++i) {
            printf("x%d:  0x%016lx\n", 19 + i, callee[i]);
        }
        
        printf("fp(x29): 0x%016lx\n", fp);
        printf("lr(x30): 0x%016lx\n", lr);
        printf("sp:     0x%016lx\n", sp);
        printf("jump_to:0x%016lx\n", jump_to);
        printf("reg:0x%016lx\n", reg);
        for (int i = 0; i < 8; ++i) {
            printf("d%d:    0x%016lx\n", 8 + i, fpu[i]);
        }
        
        printf("=========================\n");
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

    uint64_t stackTop()
    {
        return reinterpret_cast<uint64_t>(stack + size);
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
    
    
    Context context;

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
    Scheduler() : currentCoroutine(nullptr), lastScheduled(nullptr) {}

    Coroutine* findNextRunnable();
    Coroutine *currentCoroutine;
    /* std::vector<Coroutine *> coroutines; */
    std::forward_list<Coroutine *> coroutines;
    std::forward_list<Coroutine *>::iterator lastScheduled;
    Context mainContext;
};



} /* MOCoroutine */