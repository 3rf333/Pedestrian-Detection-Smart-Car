# Pedestrian Detection Smart Car (ENGR 478)

This project demonstrates a **smart RC car** that detects motion in front of it and **automatically stops to prevent collisions**. The system is inspired by real-world autonomous vehicle safety features and was developed as a final project for ENGR 478.
Using an **STM32 microcontroller**, a **PIR motion sensor**, and a **motor driver**, the car continuously monitors its path while driving forward. When motion is detected, the system immediately disables the motors, activates a visual LED indicator, waits briefly, and then resumes movement once the area is clear.
<img width="727" height="547" alt="Screenshot 2025-12-22 at 9 47 04 PM" src="https://github.com/user-attachments/assets/ea1acdcf-4cc0-41ea-b943-19d0474a16af" />
## How the System Works

The smart car follows a simple control logic implemented on the STM32 NUCLEO-L476RG microcontroller. The system continuously monitors a PIR motion sensor while the car is driving forward.

- The user presses the onboard button to activate the system  
- The motors are enabled and the car begins moving forward  
- The PIR motion sensor monitors movement in front of the vehicle  
- When motion is detected:
  - The microcontroller disables the L298N motor driver
  - The car comes to a complete stop
  - An LED indicator turns on to signal detection
- After the PIR sensor’s default delay of approximately 3 seconds:
  - The LED turns off
  - The motors are re-enabled
  - The car resumes forward motion  

This control loop repeats continuously, allowing the car to respond quickly to motion and prevent collisions.

## Project Demonstration Video

The video below demonstrates the smart car driving forward, detecting motion in front of it, stopping the motors, activating the LED indicator, and then resuming motion after the delay, as described in the project design and implementation.

src="https://www.youtube.com/embed/nRQBuy-paVU"
title="Pedestrian Detection Smart Car Demo"
frameborder="0"
allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
allowfullscreen></iframe>

## Hardware Components

The smart car system is built using a combination of low-cost embedded hardware components that work together to provide motion detection and motor control.

- **STM32 NUCLEO-L476RG Microcontroller**  
  Acts as the main controller for the system. It reads the PIR motion sensor input, controls the motor driver outputs, and manages timing and LED status indications.

- **L298N Dual H-Bridge Motor Driver**  
  Used to control the DC motors of the RC car. The motor driver receives control signals from the microcontroller and supplies sufficient current to drive the front and rear motors.
<img width="294" height="187" alt="Screenshot 2025-12-22 at 9 43 20 PM" src="https://github.com/user-attachments/assets/d80187af-c9e4-4d80-a815-4397d8f408aa" />

- **AM312 PIR Motion Sensor**  
  Detects motion in front of the vehicle. When motion is detected, the sensor outputs a signal to the microcontroller, triggering the car to stop.
<img width="265" height="199" alt="Screenshot 2025-12-22 at 9 51 03 PM" src="https://github.com/user-attachments/assets/ded1ea65-8538-4aa7-b801-6f48a3adbdd7" />

- **4WD Smart Car DC Motors**  
  Provides the mechanical platform for the project. The front and rear motors are wired in series to ensure synchronized movement.
<img width="337" height="329" alt="Screenshot 2025-12-22 at 9 53 04 PM" src="https://github.com/user-attachments/assets/c0f31cd8-f90c-4743-bd7a-11c4a79fc6d7" />

- **LED and Current-Limiting Resistor**  
  Used as a visual indicator to show when motion has been detected and the car has stopped.
<img width="191" height="163" alt="Screenshot 2025-12-22 at 9 59 23 PM" src="https://github.com/user-attachments/assets/fccd6491-edda-41af-b71e-428143ef0836" />

- **Battery Power Supply**  
  Supplies power 6v to the motor driver and the overall system. A common ground is shared between the motor driver and microcontroller to ensure stable operation.
## Design Explanation
The STM32 microcontroller sends control signals to the L298N motor driver to manage the front and rear DC motors. The motors are powered by an external battery connected to the motor driver, while the microcontroller provides only the logic-level control signals.

The PIR motion sensor is connected to a GPIO input pin and outputs a digital signal when motion is detected in front of the vehicle. An LED indicator is connected to a separate GPIO output pin through a current-limiting resistor to provide visual feedback when motion is detected.

A common ground is shared between the microcontroller, motor driver, and sensor to ensure reliable signal reference and stable system operation.

## System Schematic and Design
The STM32 microcontroller sends control signals to the L298N motor driver to manage the front and rear DC motors. The motors are powered by an external battery connected to the motor driver, while the microcontroller provides only the logic-level control signals.

The PIR motion sensor is connected to a GPIO input pin and outputs a digital signal when motion is detected in front of the vehicle. An LED indicator is connected to a separate GPIO output pin through a current-limiting resistor to provide visual feedback when motion is detected.

A common ground is shared between the microcontroller, motor driver, and sensor to ensure reliable signal reference and stable system operation.
<img width="822" height="499" alt="Screenshot 2025-12-18 at 12 36 38 PM" src="https://github.com/user-attachments/assets/4bd06c9f-8145-47ff-9eea-e2fb9cc606e8" />
## Experimental Results and AD2 Measurements

**Normal Operation (No Motion Detected)**
<img width="536" height="289" alt="Screenshot 2025-12-22 at 11 05 31 PM" src="https://github.com/user-attachments/assets/7d37e011-e156-42ce-9e7f-8b30b96f0cfd" />

This waveform shows the system operating under normal conditions when no motion is detected by the PIR sensor. The motor control signal remains at a steady voltage level, allowing the DC motors to continue driving the car forward. The LED output remains low, indicating that no object or motion is present in front of the vehicle.

**Motion Detected (Motors Stopped)**

<img width="510" height="387" alt="Screenshot 2025-12-22 at 11 12 43 PM" src="https://github.com/user-attachments/assets/8e10271e-5e74-49ab-a8b1-c577b654cb37" />

This waveform captures the system response when motion is detected by the PIR sensor. The sensor output transitions high, and the microcontroller immediately disables the motor driver, causing the motor control voltage to drop and the car to stop. At the same time, the LED output rises, indicating that motion has been detected and the system has entered its stop state.

**Motor Re-Activation After Sensor Delay**
<img width="426" height="329" alt="Screenshot 2025-12-22 at 11 14 59 PM" src="https://github.com/user-attachments/assets/5f8280ba-617f-4ae3-86e2-ba48bcfdb714" />


This waveform shows the system behavior after the PIR sensor delay has elapsed. The LED output returns low and the motor control voltage rises again, re-enabling the motors and allowing the car to resume forward motion. A brief voltage overshoot is observed during motor startup, which is expected due to motor load and wiring effects.

### Challenges

One of the main challenges encountered during this project was maintaining stable wiring and a reliable common ground between the microcontroller, motor driver, and sensors. Loose connections occasionally caused unpredictable behavior, such as motors stopping unexpectedly or signals not being detected correctly. Additionally, configuring and debugging the L298N motor driver required careful attention, as incorrect wiring of the motor channels could result in motors spinning in the wrong direction or not operating at all.

Another challenge involved sensor selection. The project initially used an ultrasonic distance sensor; however, inconsistent readings at varying distances made reliable detection difficult. Due to time constraints and the need for consistent behavior, the ultrasonic sensor was replaced with a PIR motion sensor, which provided more stable and predictable detection for this application.

### Future Improvements

There are several ways the project could be improved in the future. Adding multiple sensors around the car would allow detection from different directions and improve overall safety. Incorporating distance-based sensors could enable the car to slow down gradually instead of stopping abruptly when an object is detected. Additionally, implementing motor speed control using PWM would allow smoother motion and more realistic behavior, bringing the system closer to real-world autonomous vehicle operation.

## AI Use Statement

Artificial intelligence tools (ChatGPT) were used to assist with debugging and understanding code during the development of this project. All system design, testing, and results were completed by the project team.

Documentation: https://docs.google.com/document/d/1qVt2LgvRY7-j_iaigUQTmMgnjjfXFBuBFuLY0SI5S8E/edit?tab=t.0#heading=h.lgktv86arj0
