#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "Airport.h"
#include "Semaphore.h"
using namespace std;

mutex mu;
mutex land;
mutex takeoff;
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
        // need to have where a planes lands, a plane takes off
        takeoff.lock();
        mu.lock();

        // critical section
        // check if a plne is in Hanger queue and check if plane in the air is not going to land while plane is taking off
        if (a.checkAnyPlanesInHanger()) {
            // take off first plane in Hanger queue
            a.airplaneTakingOff();
            cout << endl
                 << endl
                 << "~~~Airplane " << a.runWay.getAirplaneID() << " is taking off~~~" << endl
                 << endl;
            // have thread wait in milliseconds for plane takeing off
            chrono::milliseconds timespan(a.runWay.getTakeoffTime());
            this_thread::sleep_for(timespan);
            a.printStatus();
        }

        // if there are no more planes in hanger or planes in the air, exit loop
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
