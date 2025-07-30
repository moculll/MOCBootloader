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

        return;
    }

    currentCoroutine = next;
    currentCoroutine->state = Coroutine::State::RUNNING;

    if(prevCoroutine) {

        MOCoroutineSwitchImpl(&prevCoroutine->context, &currentCoroutine->context);
    }
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
        co->context.init(stackPtr->stackTop(), reinterpret_cast<void *>(entryFunc), reinterpret_cast<void *>(co), reinterpret_cast<void *>(exit));
    
    }, co->stack);

}

void Scheduler::exitEntry()
{
    if (currentCoroutine) {
        currentCoroutine->state = Coroutine::State::FINISHED;

        currentCoroutine = nullptr;
        yield();


    }

    MOCoroutineRestoreContextImpl(&mainContext);

}

} /* MOCoroutine */