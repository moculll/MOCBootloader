#include <stdio.h>
#include <driver/Uart.h>
#include <string.h>

#include <MOCoroutine.h>
int main(int argc, char *argv[])
{
    
    MOCBootloader::Driver::Uart::UartConfig config;
    MOCBootloader::Driver::Uart::instance().init(0, config);

    printf("Welcome to MOCBootloader!\r\n");


    auto stack = std::make_unique<MOCoroutine::Stack>(2048);
    
    auto stack1 = std::make_unique<MOCoroutine::Stack>(2048);
    auto stack2 = std::make_unique<MOCoroutine::Stack>(2048);
    auto stack3 = std::make_unique<MOCoroutine::Stack>(2048);
    auto stack4 = std::make_unique<MOCoroutine::Stack>(2048);
    MOCoroutine::Scheduler &scheduler = MOCoroutine::Scheduler::instance();
    
    MOCoroutine::Coroutine coro("coro", std::move(stack), [&scheduler] () {
        int coroId = 0;
        for(int i = 0; i < 5; i++) {
            printf("coro id: %d\r\n", coroId++);
            scheduler.yield();
        }
        
        
    });

    
    MOCoroutine::Coroutine coroShared("coroShared", std::move(stack1), [&scheduler] () {
        int coroSharedId = 10;
        for(int i = 0; i < 5; i++) {
            printf("coroShared id: %d\r\n", coroSharedId++);
            scheduler.yield();
        }
        
        
    });

    
    MOCoroutine::Coroutine coroShared1("coroShared1", std::move(stack2), [&scheduler] () {
        int coroSharedId1 = 20;
        for(int i = 0; i < 5; i++) {
            printf("coroShared1 id: %d\r\n", coroSharedId1++);
            scheduler.yield();
        }
        
       
    });

    
    MOCoroutine::Coroutine coroShared2("coroShared2", std::move(stack3), [&scheduler] () {
        int coroSharedId2 = 30;
        for(int i = 0; i < 5; i++) {
            printf("coroShared2 id: %d\r\n", coroSharedId2++);
            scheduler.yield();
        }
        
       
    });

    
    MOCoroutine::Coroutine coroShared3("coroShared3", std::move(stack4), [&scheduler] () {
        int coroSharedId3 = 0;
        for(int i = 0; i < 30; i++) {
            printf("coroShared3 id: %d\r\n", coroSharedId3++);
            scheduler.yield();
        }
        
       
    });

    scheduler.add(&coro);
    scheduler.add(&coroShared);
    scheduler.add(&coroShared1);
    scheduler.add(&coroShared2);
    scheduler.add(&coroShared3);

    scheduler.run();
    
    printf("minimalTest exit.\r\n");
    return 0;
}