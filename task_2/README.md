Arduino Live Data Plot with Web Serial API

This project demonstrates how to read real-time data from an Arduino using the Web Serial API and plot it live in the browser using Plotly.js.

It features:
	•	A 2D line graph for sensor readings.
	•	A 3D scatter plot for visualizing latitude, longitude, and altitude data.
	•	A simulation mode if you don’t have hardware connected.

⸻

🚀 Features
	•	Connect directly to your Arduino via USB from a supported browser.
	•	Real-time plotting with Plotly.js.
	•	Simulation button to test the visualization without hardware.
	•	Works with sensor data in the format: `sensor_value,latitude,longitude,altitude`

 🔧 Setup Instructions

1. Arduino Setup

Upload code to your Arduino that sends sensor data over the serial port in the expected format.
For example:
```
Serial.print(sensorVal);
Serial.print(",");
Serial.print(latitude);
Serial.print(",");
Serial.print(longitude);
Serial.print(",");
Serial.println(altitude);
```

2. Run the Website
- Clone this repository:
```
git clone https://github.com/your-username/arduino-live-plot.git
```
- install live serve extension on VS code
- host on live server (required!)

🌐 Browser Support

The Web Serial API is supported in:
	•	✅ Google Chrome (v89+)
	•	✅ Microsoft Edge (v89+)
	•	❌ Firefox & Safari (not supported yet)

⸻

🖼️ Demo Screenshots

(Optional: add screenshots of your 2D and 3D plots here)

⸻

▶️ Usage
	1.	Open the webpage.
	2.	Click “Connect to Arduino” and select the correct serial port.
	3.	Watch the live sensor data update on the graphs.
	4.	If you don’t have hardware, click “Simulate Data” to see demo plots.

⸻

⚡ Example Output
	•	2D Graph: Sensor values vs Time.
	•	3D Graph: Latitude, Longitude, Altitude trajectory.

