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

void take_off(Airport &a) {
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
            chrono::seconds timespan(a.runWay.getRunwayTime());
            this_thread::sleep_for(timespan);
            a.printStatus();
        }

        // if there are no more planes in hanger or planes in the air, exit loop
        if (!a.checkAnyPlanesInHanger() && !a.checkAnyPlanesInAir()) {
            exit = true;
        }
        mu.unlock();
        land.unlock();

        if (exit) {
            break;
        }
    }
}

void landing(Airport &a) {
    bool exit = false;
    while (true) {
        // locking landing
        land.lock();
        mu.lock();

        // crit section
        //checks if there is a plane in the air
        if (a.checkAnyPlanesInAir()) {
            a.airplaneLanding();
            // Indicating which plane landed
            cout << endl
                 << endl
                 << "~~~Airplane " << a.runWay.getAirplaneID() << " is landing~~~" << endl
                 << endl;
            // Runway time
            chrono::seconds timespan(a.runWay.getRunwayTime());
            this_thread::sleep_for(timespan);
            a.printStatus();
        }

        // checking planes in air and in hanges
        if (!a.checkAnyPlanesInHanger() && !a.checkAnyPlanesInAir()) {
            exit = true;
        }

        mu.unlock();
        takeoff.unlock();

        if (exit) {
            break;
        }
    }
}

int main() {
    Airport airport1;
    // airport1.populateHanger(4);
    // airport1.populateFlying(2);
    airport1.populateAirplanes(3);
    airport1.printStatus();

    thread take_off_thread(take_off, ref(airport1));
    thread landing_thread(landing, ref(airport1));

    take_off_thread.join();
    landing_thread.join();

    cout << "Finshed" << endl;
}
