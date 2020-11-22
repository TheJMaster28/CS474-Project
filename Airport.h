// Airport.h
// This file holds the airfield and aircraft classes

// Libraries
#include <queue>
#include <random>
#include <string>
#include <time.h>
#include <cstdlib>



using namespace std;

// Class Airplane
class Airplane {
    // Public variables
   public:
    int ID;
    int runwayTime;
    int landingTime;
    int timesTillDone;

    // Default constructor
    Airplane(){};

    // Parameterized constructor
    Airplane(int x, int y, int z, int a) {
        ID = x;
        runwayTime = y;
        landingTime = z;
        timesTillDone = a;
    }

    int getAirplaneID() {
        return ID;
    }

    int getRunwayTime() {
        return runwayTime;
    }

    int getLandingTime() {
        return landingTime;
    }

    int getTimesLanded() {
        return timesTillDone;
    }

    string toString() {
        string output = "Temp";
        return output;
    }

};  // end class Airplane

// Class Airport
class Airport {
    // Public variables
   public:
    queue<Airplane> Hanger;
    queue<Airplane> Flying;
    queue<Airplane> tempHanger;
    queue<Airplane> tempFlying;
    Airplane runWay;
    Airplane planeInfoH;
    Airplane planeInfoF;

    // Default constructor
    Airport(){};

    // Add 'n' number of aircrafts to the Hanger queue
    void populateHanger(int n) {
        //variable randomization for landings
        srand (time(NULL));
        int landNum = rand() % 5 + 1;

        // Airplane object initialization
        for (int i = 1; i <= n; i++) {
            Hanger.push(Airplane(i, 5, i + 20, landNum));
        }
    }

    // Add 'n' number of aircrafts to the Flying queue
    void populateFlying(int n) {
        //variable randomization for landings
        srand (time(NULL));
        int landNum = rand() % 5 + 1;

        // Airplane object initialization
        for (int i = 1; i <= n; i++) {
            Flying.push(Airplane(i, 5, i + 40, landNum));
        }
    }

    void populateAirplanes(int n) {
        // Randomizaiton Seed
        srand(time(NULL));

    }

    // Airplane landing method
    // Removes the top airplane of the flying queue and adds it to the end of the Flying queue
    void airplaneLanding() {
        runWay = Flying.front();
        Flying.pop();
        runWay.timesTillDone--;
        if (runWay.timesTillDone != 0) {
            Hanger.push(runWay);
        }
    }

    // Airplane takingOff method
    // Removes the top airplane of the Hanger queue and adds it to the end of the Flying queue
    void airplaneTakingOff() {
        runWay = Hanger.front();
        Hanger.pop();
        Flying.push(runWay);
    }

    // Method to check if there are any planes in the Hanger
    bool checkAnyPlanesInHanger() {
        if (Hanger.empty()) {
            return false;
        }
        return true;
    }

    // Method to check if there are any planes Flying
    bool checkAnyPlanesInAir() {
        if (Flying.empty()) {
            return false;
        }
        return true;
    }

    // Method to see if a plane in the air will be landing will land before a plane in the hanger will take off
    bool checkIfPlaneInAirIsLanding() {
        Airplane planeInAir = Flying.front();
        Airplane planeAboutToTakeOff = Hanger.front();
        if (planeInAir.getLandingTime() <= planeAboutToTakeOff.getRunwayTime()) {
            return true;
        }
        return false;
    }

    // printStatus method
    // Prints all of the information for each airplane in the Hanger anf Flying queue
    void printStatus() {
        //Copying over the queues
        tempHanger = Hanger;
        tempFlying = Flying;

        // Printing how many airplanes are in the hanger and flying
        cout << "Airplanes inside the Hanger: " << tempHanger.size() << "             "
             << "Airplanes in the Air: " << tempFlying.size() << "\n\n";
        while (!tempHanger.empty() || !tempFlying.empty()) {
            planeInfoH = tempHanger.front();
            planeInfoF = tempFlying.front();

            // If both queues are not empty
            if (!tempHanger.empty() && !tempFlying.empty()) {
                cout << "Airplane ID: " << planeInfoH.ID << "                             "
                     << "Airplane ID: " << planeInfoF.ID << "\n";
                cout << "Airplane Takeoff Time: " << planeInfoH.runwayTime << "                  "
                     << "Airplane Takeoff Time: " << planeInfoF.runwayTime << "\n";
                cout << "Airplane Landing Time: " << planeInfoH.landingTime << "                  "
                     << "Airplane Landing Time: " << planeInfoF.landingTime << "\n";
                cout << "Airplane Rounds Left: " << planeInfoH.timesTillDone << "                    "
                     << "Airplane Rounds Left: " << planeInfoF.timesTillDone << "\n";
                cout << "----------------------------------------------------------------------------------------------------------------------------------------"
                     << "\n";
            }
            // If the hanger queue is empty
            else if (tempHanger.empty()) {
                cout << "                                           "
                     << "Airplane ID: " << planeInfoF.ID << "\n";
                cout << "                                           "
                     << "Airplane Takeoff Time: " << planeInfoF.runwayTime << "\n";
                cout << "                                           "
                     << "Airplane Landing Time: " << planeInfoF.landingTime << "\n";
                cout << "                                           "
                     << "Airplane Rounds Left: " << planeInfoF.timesTillDone << "\n";
                cout << "----------------------------------------------------------------------------------------------------------------------------------------"
                     << "\n";
            }
            // If flying queue is empty
            else {
                cout << "Airplane ID: " << planeInfoH.ID << "\n";
                cout << "Airplane Takeoff Time: " << planeInfoH.runwayTime << "\n";
                cout << "Airplane Landing Time: " << planeInfoH.landingTime << "\n";
                cout << "Airplane Rounds Left: " << planeInfoH.timesTillDone << "\n";
                cout << "----------------------------------------------------------------------------------------------------------------------------------------"
                     << "\n";
            }

            if (!tempHanger.empty()) tempHanger.pop();
            if (!tempFlying.empty()) tempFlying.pop();
        }
    }

};  // end class Airport
