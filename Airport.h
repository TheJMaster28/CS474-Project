// Airport.h
// This file holds the airfield and aircraft classes

// Libraries
#include <time.h>

#include <cstdlib>
#include <queue>
#include <random>
#include <string>
#include <vector>

using namespace std;

// Class Airplane
class Airplane {
    // Public variables
   public:
    int ID;
    int runwayTime;
    int flyingTime;
    int timesTillDone;

    // Default constructor
    Airplane(){};

    // Parameterized constructor
    Airplane(int x, int y, int z, int a) {
        ID = x;
        runwayTime = y;
        flyingTime = z;
        timesTillDone = a;
    }

    int getAirplaneID() {
        return ID;
    }

    int getRunwayTime() {
        return runwayTime;
    }

    int getFlyingTime() {
        return flyingTime;
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
        srand(time(NULL));
        int landNum = rand() % 5 + 1;

        // Airplane object initialization
        for (int i = 1; i <= n; i++) {
            Hanger.push(Airplane(i, 5, i + 20, landNum));
        }
    }

    // Add 'n' number of aircrafts to the Flying queue
    void populateFlying(int n) {
        //variable randomization for landings
        srand(time(NULL));
        int landNum = rand() % 5 + 1;

        // Airplane object initialization
        for (int i = 1; i <= n; i++) {
            Flying.push(Airplane(i, 5, i + 40, landNum));
        }
    }

    void populateAirplanes(int n) {
        // Randomizaiton Seed
        srand(time(NULL));

        // have vector to keep track of used IDs
        // vector<Airplane> AirplaneIDs;

        for (int i = 1; i <= n; i++) {
            // randomize number of times a plane can land
            int landNum = rand() % 5 + 1;
            // randomize planes flying time
            int airtime = rand() % 15 + 1;
            // randomize plane to go into FLying or Hanger
            int HangerOrFlying = rand() % 100 + 1;
            // HangerOrFlying = HangerOrFlying % 2;
            Airplane a = Airplane(i, 5, airtime, landNum);
            if (HangerOrFlying <= 50) {
                Hanger.push(a);
            } else {
                Flying.push(a);
            }
        }
    }

    // Airplane landing method
    // Removes the top airplane of the flying queue and adds it to the end of the Flying queue
    void airplaneLanding() {
        runWay = Flying.front();
        Flying.pop();
        runWay.timesTillDone--;
        if (runWay.timesTillDone != 0) {
            Hanger.push(runWay);
        } else {
            cout << endl
                 << endl
                 << "Airplane " << runWay.getAirplaneID() << " is grounded" << endl
                 << endl;
            ;
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
        if (planeInAir.getFlyingTime() <= planeAboutToTakeOff.getRunwayTime()) {
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
        // cout << "Airplanes inside the Hanger: " << tempHanger.size() << "             "
        //      << "Airplanes in the Air: " << tempFlying.size() << "\n\n";

        printf("Airplanes inside Hanger : %-5d Airplanes in the Air : %-5d\n\n", (int)tempHanger.size(), (int)tempFlying.size());
        while (!tempHanger.empty() || !tempFlying.empty()) {
            planeInfoH = tempHanger.front();
            planeInfoF = tempFlying.front();

            // If both queues are not empty
            if (!tempHanger.empty() && !tempFlying.empty()) {
                printf("Airplane ID             : %-5d Airplane ID          : %-5d\n", planeInfoH.ID, planeInfoF.ID);
                printf("Airplane Runway Time    : %-5d Airplane Runway Time : %-5d\n", planeInfoH.runwayTime, planeInfoF.runwayTime);
                printf("Airplane Flying Time    : %-5d Airplane Flying Time : %-5d\n", planeInfoH.flyingTime, planeInfoF.flyingTime);
                printf("Airplane Rounds Left    : %-5d Airplane Rounds Left : %-5d\n", planeInfoH.timesTillDone, planeInfoF.timesTillDone);
                cout << "-----------------------------------------------------------------"
                     << endl;
                // // cout << "Airplane ID: " << planeInfoH.ID << "\t"
                // //      << "Airplane ID: " << planeInfoF.ID << "\n";
                // cout << "Airplane Runway Time: " << planeInfoH.runwayTime << "\t"
                //      << "Airplane Runway Time: " << planeInfoF.runwayTime << "\n";
                // cout << "Airplane Flying Time: " << planeInfoH.flyingTime << "\t"
                //      << "Airplane Flying Time: " << planeInfoF.flyingTime << "\n";
                // cout << "Airplane Rounds Left: " << planeInfoH.timesTillDone << "\t"
                //      << "Airplane Rounds Left: " << planeInfoF.timesTillDone << "\n";
            }
            // If the hanger queue is empty
            else if (tempHanger.empty()) {
                printf("                                Airplane ID          : %-5d\n", planeInfoF.ID);
                printf("                                Airplane Runway Time : %-5d\n", planeInfoF.runwayTime);
                printf("                                Airplane Flying Time : %-5d\n", planeInfoF.flyingTime);
                printf("                                Airplane Rounds Left : %-5d\n", planeInfoF.timesTillDone);
                cout << "-----------------------------------------------------------------"
                     << endl;
                // cout << "\t"
                //      << "Airplane ID: " << planeInfoF.ID << "\n";
                // cout << "\t"
                //      << "Airplane Runway Time: " << planeInfoF.runwayTime << "\n";
                // cout << "\t"
                //      << "Airplane Flying Time: " << planeInfoF.flyingTime << "\n";
                // cout << "\t"
                //      << "Airplane Rounds Left: " << planeInfoF.timesTillDone << "\n";
            }
            // If flying queue is empty
            else {
                // cout << "Airplane ID: " << planeInfoH.ID << "\n";
                // cout << "Airplane Runway Time: " << planeInfoH.runwayTime << "\n";
                // cout << "Airplane Flying Time: " << planeInfoH.flyingTime << "\n";
                // cout << "Airplane Rounds Left: " << planeInfoH.timesTillDone << "\n";

                printf("Airplane ID             : %-5d\n", planeInfoH.ID);
                printf("Airplane Runway Time    : %-5d\n", planeInfoH.runwayTime);
                printf("Airplane Flying Time    : %-5d\n", planeInfoH.flyingTime);
                printf("Airplane Rounds Left    : %-5d\n", planeInfoH.timesTillDone);
                cout << "-----------------------------------------------------------------"
                     << endl;
            }

            if (!tempHanger.empty()) tempHanger.pop();
            if (!tempFlying.empty()) tempFlying.pop();
        }
    }

};  // end class Airport
