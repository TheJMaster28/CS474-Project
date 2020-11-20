#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "Airport.h"
#include "Semaphore.h"
using namespace std;

mutex mu;
// Semaphore full(0);
// Semaphore Empty(15);

// char buffer[15];

// // Producer Theard function
// void producer(string s) {
//     cout << "Starting Producer\n";
//     int index = 0;
//     for (char c : s) {
//         // wait on semaphores
//         Empty.wait();
//         mu.lock();

//         // add character to buffer
//         buffer[index] = c;

//         // release semaphores
//         mu.unlock();
//         full.notify();
//         // increment index
//         index++;
//         // go back to start for circular buffer
//         if (index >= 15) {
//             index = 0;
//         }
//     }

//     Empty.wait();
//     mu.lock();

//     buffer[index] = '\0';

//     mu.unlock();
//     full.notify();
// }

// // Consumer Threead function
// void consumer() {
//     cout << "Starting Consumer\n";
//     int index = 0;
//     bool endoffile = false;
//     while (true) {
//         // wait on semaphores
//         full.wait();
//         mu.lock();
//         // print waht is in buffer
//         cout << buffer[index];
//         // detect end of buffer
//         if (buffer[index] == '\0') {
//             endoffile = true;
//         }
//         // release semaphores
//         mu.unlock();
//         Empty.notify();
//         // increase read index
//         index++;
//         // break if end of buffer
//         if (endoffile) {
//             cout << endl;
//             break;
//         }
//         // go back to start for circular buffer
//         if (index >= 15) {
//             index = 0;
//         }
//     }
// }

void take_off(Airport a) {
    bool exit = false;
    while (true) {
        mu.lock();

        // critical section
        if (a.checkAnyPlanesInHanger()) {
            a.airplaneTakingOff();
            cout << endl
                 << endl
                 << "~~~Airplane " << a.runWay.getAirplaneID() << " is taking off~~~" << endl
                 << endl;
            chrono::milliseconds timespan(a.runWay.getTakeoffTime());
            this_thread::sleep_for(timespan);
            a.printStatus();
        }

        if (!a.checkAnyPlanesInHanger() && !a.checkAnyPlanesInAir()) {
            exit = true;
        }
        mu.unlock();

        if (exit) {
            break;
        }
    }
}

int main() {
    // // input for producer
    // string s = "abcdefghijklmnopqrstovwxyz";

    // // creates threads
    // thread pro(producer, s);
    // thread con(consumer);

    // // waits on threads
    // pro.join();
    // con.join();

    // cout << "Finshed" << endl;

    Airport airport1;
    airport1.populateHanger(4);
    airport1.populateFlying(2);
    airport1.printStatus();

    thread take_off_thread(take_off, airport1);

    take_off_thread.join();

    cout << "Finshed" << endl;
}
