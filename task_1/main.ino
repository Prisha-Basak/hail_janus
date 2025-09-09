#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Defining software serial pins 
#define RX_PIN 4
#define TX_PIN 3

SoftwareSerial gpsSerial(RX_PIN, TX_PIN); // RX, TX

TinyGPSPlus gps; // Creating TinyGPS++ object

// Variables for altitude-based state machine
double lastAltitude = 0;
double peakAltitude = 0;
bool payloadDeployed = false;

// Flight states
enum FlightState {IDLE, ASCENT, APOGEE, DESCENT, PAYLOAD_DEPLOYED, LANDED};
FlightState currentState = IDLE;

// Function to send UBX command to GNSS module
void sendUBX(byte *cmd, int len){
  for(int i = 0; i < len; i++){
    gpsSerial.write(cmd[i]);
  }
}

// UBX command to enable only GNRMC & GNGGA sentences
byte setNMEAOnlyRMC_GGA[] = {
  0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x00, 0x01, 0x00, 0xF0, 0x01, 0x01, 0xFA
};

void setup() {
  Serial.begin(115200);      // Serial monitor
  gpsSerial.begin(9600);     // GNSS serial
  delay(1000);

  Serial.println("Initializing Quectel L89HA GNSS...");

  // Configure GNSS to output only GNRMC & GNGGA
  sendUBX(setNMEAOnlyRMC_GGA, sizeof(setNMEAOnlyRMC_GGA));
}

void loop() {
  // Read from GNSS
  /* nwhile (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  } */

  // Replace while(gpsSerial.available()) with this for simulation:
  const char* simulatedNMEA[] = {
    "$GNRMC,120000.00,A,28.6139,N,77.2090,E,0.0,0.0,090925,,,A*68",
    "$GNGGA,120000.00,28.6139,N,77.2090,E,1,08,1.0,200.0,M,0.0,M,,*5C"
  };
   for(int i=0; i<2; i++){
    gps.encode(simulatedNMEA[i][0]);
  }


  if (gps.location.isUpdated()) {
    double altitude = gps.altitude.meters();
    double latitude = gps.location.lat();
    double longitude = gps.location.lng();
    int hour = gps.time.hour();
    int minute = gps.time.minute();
    int second = gps.time.second();

    // Update flight state machine
    if(currentState == IDLE && altitude > 1){
      currentState = ASCENT;
    }
    else if(currentState == ASCENT){
      if(altitude > peakAltitude) peakAltitude = altitude;
      if(altitude < peakAltitude) currentState = APOGEE;
    }
    else if(currentState == APOGEE){
      currentState = DESCENT;
    }
    else if(currentState == DESCENT && !payloadDeployed && altitude <= 0.25 * peakAltitude){
      payloadDeployed = true;
      currentState = PAYLOAD_DEPLOYED;
    }
    else if((currentState == DESCENT || currentState == PAYLOAD_DEPLOYED) && altitude <= 5){
      currentState = LANDED;
    }

    // Print data
    Serial.print("Time: "); Serial.print(hour); Serial.print(":"); Serial.print(minute); Serial.print(":"); Serial.println(second);
    Serial.print("Latitude: "); Serial.println(latitude, 6);
    Serial.print("Longitude: "); Serial.println(longitude, 6);
    Serial.print("MSL Altitude: "); Serial.println(altitude);

    // Print flight state
    Serial.print("State: ");
    switch(currentState){
      case IDLE: Serial.println("IDLE"); break;
      case ASCENT: Serial.println("ASCENT"); break;
      case APOGEE: Serial.println("APOGEE"); break;
      case DESCENT: Serial.println("DESCENT"); break;
      case PAYLOAD_DEPLOYED: Serial.println("PAYLOAD DEPLOYED"); break;
      case LANDED: Serial.println("LANDED"); break;
    }

    Serial.println("-----------------------------");
    delay(1000); // Slow down serial printing
  }
}

