#include <iostream>
#include <mutex>
#include <thread>

#include "Semaphore.h"
using namespace std;

mutex mu;
Semaphore full(0);
Semaphore Empty(15);

char buffer[15];

// Producer Theard function
void producer(string s) {
    cout << "Starting Producer\n";
    int index = 0;
    for (char c : s) {
        // wait on semaphores
        Empty.wait();
        mu.lock();

        // add character to buffer
        buffer[index] = c;

        // release semaphores
        mu.unlock();
        full.notify();
        // increment index
        index++;
        // go back to start for circular buffer
        if (index >= 15) {
            index = 0;
        }
    }

    Empty.wait();
    mu.lock();

    buffer[index] = '\0';

    mu.unlock();
    full.notify();
}

// Consumer Threead function
void consumer() {
    cout << "Starting Consumer\n";
    int index = 0;
    bool endoffile = false;
    while (true) {
        // wait on semaphores
        full.wait();
        mu.lock();
        // print waht is in buffer
        cout << buffer[index];
        // detect end of buffer
        if (buffer[index] == '\0') {
            endoffile = true;
        }
        // release semaphores
        mu.unlock();
        Empty.notify();
        // increase read index
        index++;
        // break if end of buffer
        if (endoffile) {
            cout << endl;
            break;
        }
        // go back to start for circular buffer
        if (index >= 15) {
            index = 0;
        }
    }
}

int main() {
    // input for producer
    string s = "abcdefghijklmnopqrstovwxyz";

    // creates threads
    thread pro(producer, s);
    thread con(consumer);

    // waits on threads
    pro.join();
    con.join();

    cout << "Finshed" << endl;
}