# Arduino Multi-Port Communication System

A C++ Arduino project developed as part of my Computer Science degree at Aberystwyth 
University in 2024. The project uses the Aberystwyth Software Serial Protocol (ASSP) to communicate 
with devices across multiple serial ports, identify connected devices, measure response times and display 
binary data using LEDs.

**Result: 80%**

## Features

- **Device detection:** Checks whether devices respond to ping messages across different serial ports.
- **Port identification:** Determines which port each device is connected to.
- **Response-time measurement:** Measures device response times and calculates the average response
- time for connected devices.
- **LED display:** Converts letters into binary representations and displays them using a five-LED array.
- **Device categorisation:** Groups devices according to their connected port and identifies devices that do not respond.

## Technologies Used

- C++
- Arduino
- Arduino IDE
- Serial communication
- ASSP (Aberystwyth Software Serial Protocol)
- Digital input/output
- Bitwise operations
- Timing and response measurement using `millis()`

## Project Structure

| File | Description |
|---|---|
| `IntroProgramming.ino` | Main Arduino sketch containing the tasks and program logic. |
| `ASSP.cpp` | Implements the software serial communication protocol. |
| `ASSP.h` | Header file defining the ASSP class and communication functions. |
| `names.h` | Contains the list of device names used by the program. |

## Tasks Implemented

### Task 1 — Device Detection
Checks a selected port for responses from a predefined list of 26 devices.

### Task 2 — Response-Time Measurement
Measures the time taken for devices connected to port 3 to respond and calculates the average response time for
responding devices.

### Task 3 — Binary LED Display
Checks devices connected to port 4 and displays their corresponding letters as five-bit binary values using LEDs.

### Task 4 — Port Identification
Checks the available ports and categorises devices according to their connection, identifying devices that cannot 
be reached.

## Skills Demonstrated

This project helped me develop practical experience in embedded programming, serial communication, debugging, bitwise
operations and working with hardware. It also involved implementing repeated communication attempts, 
validating incoming messages and measuring program execution time.

## Running the Project

1. Install the Arduino IDE.
2. Open `IntroProgramming.ino` in the IDE.
3. Ensure the required ASSP library and compatible hardware are available.
4. Connect the Arduino and associated communication hardware.
5. Upload the sketch and open the Serial Monitor at **57600 baud**.

**Note:** Task 1 is enabled by default in the main loop. Tasks 2, 3 and 4 can be enabled by modifying the loop.

## Project Details

- **Completed:** 2024
- **Academic result:** 80%
- **Language:** C++
- **Platform:** Arduino
- **Institution:** Aberystwyth University
