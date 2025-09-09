🚀 CanSat GNSS Module Setup & Flight State Machine

This project demonstrates how to set up a Quectel L89HA GNSS Module with an Arduino for a CanSat mission. The code configures the GNSS to output only the required NMEA sentences, parses GPS data using the TinyGPS++ library, and implements a state machine based on altitude to track the CanSat’s flight profile.

⸻

📜 Problem Statement

Objective:
Write Arduino code to set up a Quectel L89HA GNSS Module for our CanSat to:
	1.	Receive and parse GPS data.
	2.	Print time, latitude, longitude, and MSL altitude onto the Serial Monitor in a clean format.
	3.	Configure the GNSS to only output GNRMC & GNGGA NMEA sentences (to reduce unnecessary data).
	4.	Implement a simple altitude-based state machine with the following states:

	•	IDLE: CanSat is stationary on the ground.
	•	ASCENT: CanSat is ascending.
	•	APOGEE: CanSat has reached peak altitude.
	•	DESCENT: CanSat is descending without payload deployed.
	•	PAYLOAD DEPLOYED: Payload is deployed at 75% of peak altitude during descent.
	•	LANDED: CanSat has landed near the ground (altitude ≤ 5 m).

Assumption: The CanSat has a normal flight path — it ascends, reaches peak altitude (apogee), then descends and lands. The initial state is IDLE.

⸻

⚡ Features
	•	Uses TinyGPS++ library for easy parsing of NMEA sentences.
	•	Sends UBX configuration command to enable only GNRMC & GNGGA output.
	•	Implements a state machine that transitions based on altitude changes.
	•	Prints both GNSS data and current flight state to the Serial Monitor.
	•	Includes a simulation option to test logic without live GNSS hardware.

⸻

🔧 Hardware Setup
	•	Arduino Uno / Nano / Mega
	•	Quectel L89HA GNSS Module
	•	Wiring (SoftwareSerial pins):
	•	Arduino Pin 4 → GNSS TX
	•	Arduino Pin 3 → GNSS RX

🚀 Flight State Machine Logic
	•	IDLE → ASCENT: When altitude > 1 m.
	•	ASCENT → APOGEE: When altitude stops increasing and starts decreasing.
	•	APOGEE → DESCENT: Transition immediately after peak altitude.
	•	DESCENT → PAYLOAD DEPLOYED: When descending and altitude ≤ 75% of peak altitude.
	•	DESCENT / PAYLOAD DEPLOYED → LANDED: When altitude ≤ 5 m.

⸻
