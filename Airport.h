// Airport.h
// This file holds the airfield and aircraft classes
#include <queue>
#include <string>

using namespace std;

class Airplane{
        public:
        int ID;
        int takeoffTime;
        int landingTime;
        int timesTillDone;


    Airplane();

    Airplane(int x, int y, int z){
        ID = x;
        takeoffTime = y;
        landingTime = z;
    }

    int getAirplaneID(){
        return ID;
    }

    int getTakeoffTime(){
        return takeoffTime;
    }
    
    int getLandingTime(){
        return landingTime;
    }

    int getTimesLanded(){
        return timesTillDone;
    }

    string toString(){
        string output = "Temp";
        return output;
    }
};

class Airport{

    public:
        queue<Airplane> Hanger;
        queue<Airplane> Flying;
        Airplane runWay;

    Airport(
        
    );

    // Add 'n' number of aircraft to the Hanger queue
    void populateHanger(int n){
        for ( int i = 1; i <= n; i++){
            Hanger.push(Airplane(i + Flying.size()));
        }
    }

    // Add 'n' number of aircraft to the Flying queue
    void populateFlying(int n){
        for ( int i = 1; i <= n; i++){
            Flying.push(Airplane(i + Hanger.size()));
        }
    }

    // Airplane landing method
    // Removes the top airplane of the flying queue and adds it to the end of the Flying queue
    void airplaneLanding(){
        runWay = Flying.front();
        Flying.pop();
        Hanger.push(runWay);
    }

    // Airplane takingOff method
    // Removes the top airplane of the Hanger queue and adds it to the end of the Flying queue
    void airplaneTakingOff(){
        runWay = Hanger.front();
        Hanger.pop();
        Flying.push(runWay);
    }
    


}; // end class airport