# Magic-Seasoning

a general sketch of what it will look like highlighting physical features
one slide for the "sensor" device, with a more detailed sketch of this device and a few sentences describing how it works
one slide for the "display" device, with a more detailed sketch of this device and a few sentences describing how it works 
One slide with a figure to show how the devices communicate with each other and a detailed diagram that explains how it will work (2 figures/charts on this slide in total).

Introduction
The Smart Cooking System integrates a mobile app with smart seasoning jars that feature built-in scales to simplify cooking. Users manually input the weight of ingredients into the app, which calculates the required seasoning amounts. The jars guide users by lighting up and dispensing precise quantities. Progress is updated on the app and synced with the jars, ensuring an intuitive and seamless cooking experience.

## Features
1. Mobile App as a Control Hub:
  1. Choose recipes and input ingredient weights manually.
  2. View progress updates as you cook.

2. Smart Seasoning Jars:
  1. Integrated scales for precise seasoning measurement.
  2. LED indicators to guide usage.
  3. Wireless communication with the app.

3. Bidirectional Communication:
   1. The app sends calculated seasoning requirements to the jars.
   2. The jars update the app once dispensing is complete.

General Look:

# System Design
Smart Seasoning Jar
Each jar is designed to weigh and dispense seasoning while communicating progress to the app.

Key Features:

Integrated scale for measuring seasoning output.
LED light for guidance.
Wireless communication (e.g., Bluetooth/Wi-Fi).
Sketch:

# Workflow
User Input:
1. Select a recipe in the app.
2. Manually input the weight of the main ingredients.
Calculation:
1. The app calculates the required seasoning for each jar.
Guidance:
1. Jars light up to indicate which seasoning to use and how much to dispense.
Progress Update:
1. Jars notify the app after each step is completed.

# System Communication
Communication Workflow
App to Jar: Recipe details and calculated seasoning amounts are sent to the jars.
Jar to App: Jars update the app with dispensing progress in real time.
Diagram:

Detailed Data Flow
Step 1: User selects a recipe in the app and inputs the weight of the ingredients.
Step 2: The app calculates seasoning proportions and sends the instructions to the jars.
Step 3: Jars guide the user by lighting up and dispensing seasoning. Dispensing progress is sent back to the app.
Diagram:

# Sensors and Hardware Components
Sensors
Load Cell (Weight Sensor):

Used to measure the weight of the dispensed seasoning.
Communicates data to the internal microcontroller.
Example: HX711 ADC module for weight data precision.
Datasheet: HX711 Datasheet

LED Indicators:

Provides visual feedback to users on which jar to use and how much to dispense.
Example: WS2812 RGB LED.
Datasheet: WS2812 LED Datasheet

Wireless Communication Module:

Ensures communication between jars and the mobile app.
Example: ESP32 or ESP8266 for Bluetooth/Wi-Fi connectivity.
Datasheet: ESP32 Datasheet

Power Management:

Powers the jars and sensors.
Example: Rechargeable Li-Po battery with charging module (e.g., TP4056).
Datasheet: TP4056 Datasheet
