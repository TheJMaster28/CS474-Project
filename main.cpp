// Libraries
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "Airport.h"

using namespace std;

// mutal exclusion semaphore
mutex mu;
// semaphores for having takeoff and landing threads alternate
mutex land;
mutex takeoff;

void take_off(Airport &a) {
    bool exit = false;
    while (true) {
        // Have planes takeoff after a plane has landed
        takeoff.lock();
        // mutual exclusion of crit section
        mu.lock();

        // crit section
        // check if a plne is in Hanger
        if (a.checkAnyPlanesInHanger()) {
            // take off first plane in Hanger queue
            a.airplaneTakingOff();
            cout << endl
                 << endl
                 << "~~~Airplane " << a.runWay.getAirplaneID() << " is taking off~~~" << endl
                 << endl
                 << endl;
            // have thread wait in milliseconds for plane takeing off
            chrono::seconds timespan(a.runWay.getRunwayTime());
            this_thread::sleep_for(timespan);
            // print status of Airport
            a.printStatus();
        }

        // if there are no more planes in hanger or planes in the air, exit loop
        if (!a.checkAnyPlanesInHanger() && !a.checkAnyPlanesInAir()) {
            exit = true;
        }
        // mutual exclusion of crit section
        mu.unlock();
        // let airplanes land
        land.unlock();

        // exit loop to terminate thread
        if (exit) {
            break;
        }
    }
}

void landing(Airport &a) {
    bool exit = false;
    while (true) {
        // Have planes land after a plane has taken off
        land.lock();
        // mutual exclusion of crit section
        mu.lock();

        // sleep on flying time
        cout << endl
             << endl
             << "~~~Airplane " << a.Flying.front().getAirplaneID() << " is flying~~~" << endl;
        chrono::seconds timespan(a.Flying.front().getFlyingTime());
        this_thread::sleep_for(timespan);

        // crit section
        //checks if there is a plane in the air
        if (a.checkAnyPlanesInAir()) {
            a.airplaneLanding();
            // Indicating which plane landed
            cout << endl
                 << endl
                 << "~~~Airplane " << a.runWay.getAirplaneID() << " is landing~~~" << endl
                 << endl
                 << endl;
            // Runway time
            chrono::seconds timespan(a.runWay.getRunwayTime());
            this_thread::sleep_for(timespan);
            // print status of Airport
            a.printStatus();
        }

        // checking planes in air and in hanger
        if (!a.checkAnyPlanesInHanger() && !a.checkAnyPlanesInAir()) {
            exit = true;
        }

        // mutual exclusion of crit section
        mu.unlock();
        // let planes takeoff after landing
        takeoff.unlock();

        // exit loop to terminate thread
        if (exit) {
            break;
        }
    }
}

int main() {
    // make global object airport for threads to share
    static Airport airport1;
    // populate Airport
    airport1.populateAirplanes(5);
    airport1.printStatus();
    // set mutex to have landing go first
    takeoff.lock();

    // create threads with the shared object airport
    thread take_off_thread(take_off, ref(airport1));
    thread landing_thread(landing, ref(airport1));

    // wait for threads to be done
    take_off_thread.join();
    landing_thread.join();

    cout << "Done With Airport" << endl;
}
