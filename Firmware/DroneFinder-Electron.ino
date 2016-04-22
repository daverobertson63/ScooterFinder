/*----------------------------------------------

4-20-2016: Code for Particle Electron to connect Ada Fruit GPS device
for polling altitude, speed, location from HTML web browser


----------------------------------------------*/

#include "TinyGPS.h"


TinyGPS gps;

double gpsAltitude;
double gpsLat;
double gpsLon;
double gpsSpeed;


// Every 5 minutes if necessary
int sleep = 5 * 60 * 1000;
bool isValidGPS = false;

void setup(){
    Serial1.begin(9600);

    Particle.variable("gpsAltitude", &gpsAltitude,DOUBLE);
    Particle.variable("gpsSpeed", &gpsSpeed,DOUBLE);
    Particle.variable("gpsLat", &gpsLat, DOUBLE);
    Particle.variable("gpsLon", &gpsLon, DOUBLE);


}

void loop(){
    isValidGPS = false;

    for (unsigned long start = millis(); millis() - start < 1000;){
        // Check GPS data is available
        while (Serial1.available()){
            char c = Serial1.read();

            // parse GPS data
            if (gps.encode(c))
                isValidGPS = true;
        }
    }

    // If we have a valid GPS location then publish it
    if (isValidGPS){
        float lat, lon;
        unsigned long age;

        //update GPS position variables; Latitude and Longitude
        gps.f_get_position(&lat, &lon, &age);

        //Update Particle Variables from GPS functions
        gpsAltitude = (double)gps.f_altitude();
        gpsSpeed = (double)gps.f_speed_mph();
        gpsLat = (double)lat;
        gpsLon = (double)lon;


    }
    else{
      //do something for error if you want

    }


    // Sleep for some time
    //delay(sleep);
}
