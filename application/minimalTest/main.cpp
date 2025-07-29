#include <stdio.h>
#include <driver/Uart.h>
#include <string.h>
#include <iostream>
#include <MOCoroutine.h>
int main(int argc, char *argv[])
{
    
    MOCBootloader::Driver::Uart::UartConfig config;
    MOCBootloader::Driver::Uart::instance()->init(0, config);

    printf("[C] Welcome to MOCBootloader!\r\n");
    std::cout << "[C++] Welcome to MOCBootloader!" << std::endl;

    const char* msg = "Hello";
    printf("msg addr = %p\n", msg);

    auto stack = std::make_unique<MOCoroutine::Stack>(2048);
    auto stack1 = std::make_unique<MOCoroutine::Stack>(2048);
    auto stack2 = std::make_unique<MOCoroutine::Stack>(2048);
    auto stack3 = std::make_unique<MOCoroutine::Stack>(2048);
    auto stack4 = std::make_unique<MOCoroutine::Stack>(2048);
    MOCoroutine::Scheduler &scheduler = MOCoroutine::Scheduler::instance();
    int coroId = 0;
    MOCoroutine::Coroutine coro("coro", std::move(stack), [&coroId, &scheduler] () {
        for(int i = 0; i < 50; i++) {
            printf("id: %d\r\n", coroId++);
            scheduler.yield();
        }
        
        
    });

    int coroSharedId = 10;
    MOCoroutine::Coroutine coroShared("coroShared", std::move(stack1), [&coroSharedId, &scheduler] () {

        for(int i = 0; i < 5; i++) {
            printf("id: %d\r\n", coroSharedId++);
            scheduler.yield();
        }
        
        
    });

    int coroSharedId1 = 20;
    MOCoroutine::Coroutine coroShared1("coroShared1", std::move(stack2), [&coroSharedId1, &scheduler] () {
        for(int i = 0; i < 50; i++) {
            printf("id: %d\r\n", coroSharedId1++);
            scheduler.yield();
        }
        
       
    });

    int coroSharedId2 = 30;
    MOCoroutine::Coroutine coroShared2("coroShared2", std::move(stack3), [&coroSharedId2, &scheduler] () {
        for(int i = 0; i < 50; i++) {
            printf("id: %d\r\n", coroSharedId2++);
            scheduler.yield();
        }
        
       
    });

    int coroSharedId3 = 40;
    MOCoroutine::Coroutine coroShared3("coroShared3", std::move(stack4), [&coroSharedId3, &scheduler] () {

        for(int i = 0; i < 50; i++) {
            printf("id: %d\r\n", coroSharedId3++);
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