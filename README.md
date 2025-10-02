# Agri-Rover: Autonomous Farming Robot Simulation

## Project Overview

The Agri-Rover is an autonomous farming robot designed to monitor key environmental conditions within a simulated agricultural plot. Developed in Tinkercad Circuits, this project demonstrates fundamental robotics, sensor integration, and data acquisition concepts. The rover's primary function is to periodically stop, deploy a soil moisture sensor, collect data (soil moisture, temperature, and light), display it locally, and then proceed to the next analysis point.

## Features

-   **Autonomous Navigation:** Controls 4 DC motors via an L293D motor driver for forward movement.
-   **Intelligent Soil Moisture Sensing:** A servo motor precisely lowers and retracts the soil moisture sensor, ensuring accurate in-ground readings.
-   **Environmental Data Collection:**
    -   **Soil Moisture:** Measures the water content in the soil.
    -   **Temperature:** Utilizes a TMP36 sensor for ambient temperature readings.
    -   **Light Intensity:** Employs a photoresistor (LDR) to gauge light levels.
-   **Real-time Feedback:** A 16x2 I2C LCD displays current sensor readings directly on the rover.
-   **Detailed Logging:** All sensor data and operational status are streamed to the Serial Monitor for detailed analysis.

## Components Used (Tinkercad)

-   Arduino Uno R3
-   16x2 LCD Display (I2C)
-   Micro Servo (for soil sensor deployment)
-   Soil Moisture Sensor
-   TMP36 Temperature Sensor
-   Photoresistor (LDR)
-   L293D Motor Driver IC
-   4 x DC Motors
-   9V Battery (for Arduino/Logic power, regulated to 5V by onboard regulator or external 7805)
-   6V Battery Pack (e.g., 4xAA) (for Motor power)
-   Breadboard
-   10kΩ Resistor (for LDR voltage divider)
-   Optional: L7805 Voltage Regulator (if using external regulation to 5V instead of Arduino's VIN)

## Circuit Diagram

(Include a link to your Tinkercad simulation here once it's finalized, or embed the final schematic image)

For a detailed view of the wiring, please refer to the Tinkercad project: [Link to your Tinkercad Project Here]

## Code

The `AgriRover_Main.ino` file contains the complete Arduino sketch.

### Key Libraries:
-   `Wire.h`: For I2C communication with the LCD.
-   `LiquidCrystal_I2C.h`: For controlling the I2C LCD.
-   `Servo.h`: For controlling the servo motor.

## How It Works

1.  **Initialization:** Upon startup, the LCD displays a welcome message, and the servo ensures the soil sensor is in the 'up' position. All motor control pins are configured.
2.  **Analyze Phase:**
    -   The rover stops.
    -   The servo lowers the soil moisture sensor into the ground.
    -   After a brief stabilization period, readings are taken from the soil moisture, TMP36, and LDR sensors.
    -   Sensor data is displayed on the LCD and printed to the Serial Monitor.
    -   The servo lifts the soil moisture sensor.
3.  **Movement Phase:**
    -   The rover moves forward for a set duration.
    -   The `totalMovementTime` variable is updated to track cumulative motor run time.
4.  **Loop:** The rover continuously cycles between the "Analyze" and "Movement" phases.

## Future Enhancements

-   **PCB Design:** Develop a custom Printed Circuit Board to eliminate messy wiring, improve reliability, and create a more compact, professional design.
-   **IoT Integration (ESP32 Upgrade):** Replace the Arduino Uno with an ESP32 microcontroller to enable Wi-Fi connectivity for:
    -   Cloud data logging (e.g., to ThingSpeak, Adafruit IO, Google Cloud).
    -   Remote monitoring and control via a web interface or mobile app.
    -   Advanced data analytics and trend visualization.
-   **Obstacle Avoidance:** Integrate ultrasonic sensors (HC-SR04) to detect obstacles and implement basic navigation logic.
-   **Automated Watering System:** Add a small pump or solenoid valve (simulated with an LED) to automatically water plants when soil moisture falls below a threshold.
-   **Solar Charging:** Integrate a small solar panel and charge controller for sustainable power.

## Contribution

Suggestions and improvements are always welcome! Feel free to fork this repository, open issues, or submit pull requests.
