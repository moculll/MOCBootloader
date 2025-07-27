#include <MOCoroutine.h>

namespace MOCoroutine {

Coroutine* Scheduler::findNextRunnable()
{
    if (coroutines.empty()) return nullptr;
    
    auto it = lastScheduled;
    if (it == coroutines.end()) {
        
        it = coroutines.begin();
    }
    
    auto start = it;
    
    do {

        ++it;
        if (it == coroutines.end()) {
            it = coroutines.begin();
        }
        
        if (*it != currentCoroutine && ((*it)->state == Coroutine::State::READY || (*it)->state == Coroutine::State::SUSPENDED)) {
            lastScheduled = it;
            return *it;
        }
    } while (it != start);
    
    return nullptr;
}

void Scheduler::yield()
{
    Coroutine* prevCoroutine = nullptr;
    if (currentCoroutine) {
        currentCoroutine->state = Coroutine::State::SUSPENDED;
        prevCoroutine = currentCoroutine;
    }

    Coroutine* next = findNextRunnable();
    if (!next) {
        printf("no coroutine to yield.\r\n");
        return;
    }

    currentCoroutine = next;
    currentCoroutine->state = Coroutine::State::RUNNING;

    if(prevCoroutine)
        MOCoroutineSwitchImpl(&prevCoroutine->context, &currentCoroutine->context);
    else {
        MOCoroutineRestoreContextImpl(&currentCoroutine->context);

    }
}

void Scheduler::run()
{

    Coroutine* next = *coroutines.begin();
    if(next) {

        currentCoroutine = next;
        currentCoroutine->state = Coroutine::State::RUNNING;

        MOCoroutineSwitchImpl(&mainContext, &currentCoroutine->context);

        
    }
}

void Scheduler::init(Coroutine* co) {
    std::visit([this, co](auto &stackPtr) {
        auto *exit = +[](){
            Scheduler::instance().exitEntry();
        };
        
        auto *entryFunc = +[](Coroutine* co){
            Scheduler::instance().entry(co);
        };

        uint8_t *bp = reinterpret_cast<uint8_t *>(stackPtr->stackTop());
        bp -= (uint64_t)bp % 16;
        co->context.sp = (uint64_t)(void*)(bp - 16);
        co->context.fp = co->context.sp;
        co->context.lr = (uint64_t)(void*)(exit);
        co->context.jump_to = (uint64_t)(void*)(entryFunc);
        co->context.reg = reinterpret_cast<uint64_t>(co);
    }, co->stack);

}

void Scheduler::exitEntry()
{
    if (currentCoroutine) {
        currentCoroutine->state = Coroutine::State::FINISHED;
        printf("%s finished, remove coroutine.\r\n", currentCoroutine->tag.c_str());
        coroutines.remove(currentCoroutine);
        currentCoroutine = nullptr;
        yield();

    }

    MOCoroutineRestoreContextImpl(&mainContext);

}

} /* MOCoroutine */