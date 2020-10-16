/**
 * Threads that waste CPU cycles
 */
#include <thread>
#include <chrono>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

using namespace std;

// a simple function that wastes CPU cycles "forever"
void cpu_waster() {
    cout << "CPU Waster Process ID: " << getpid() << endl;
    cout << "CPU Waster Thread ID : " << std::this_thread::get_id() << endl;
    while(true) continue;
}

int main() {
    cout << "Main Process ID      : " <<  getpid() << endl;
    cout << "Main Thread ID       : " << std::this_thread::get_id() << endl;
    std::thread thread1(cpu_waster);
    std::thread thread2(cpu_waster); 

    while(true) { // keep the main thread alive "forever"
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
