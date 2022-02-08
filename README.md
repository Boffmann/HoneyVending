# Honey Vending
`Honey Vending` is a vending machine for honey I am building. This repository contains all assets regarding software and hardware.

## Components
The honey vending machine consists of multiple components and a software program.

* Customers can insert money via a programmable coin acceptor like [this one](https://www.sparkfun.com/products/11636).
* The currently insterted amount is shown via a [TM1637 Display Module](https://www.amazon.com/DEVMO-Digital-Display-Module-Arduino/dp/B07R64BC38/ref=sr_1_1_sspa?keywords=tm1637&qid=1644671514&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExVEc0TVhXVzVPQVNMJmVuY3J5cHRlZElkPUEwMDExODY5MjVIRVJISzI5SlFRTCZlbmNyeXB0ZWRBZElkPUEwMTgzMTM3M0JCWDJUNTJPTUNSJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==).
* All products are behind individually addressable doors that are controled by 12V electromagnetic locks like [this](https://www.amazon.com/uxcell-Electromagnetic-Solenoid-Assembly-Electirc/dp/B07TMWY94C/ref=sr_1_6?keywords=12v+door+lock&qid=1644671675&sr=8-6).
* Each door is linked to a button on a customly designed button rack.

The entire machine is managed by a ESP32 microcontroller that runs a custom program and links all parts.

## Structure
The project is structured as follows:

* **CADs**: Contains CAD files for all individual components and PCBs that are featured in this project
* **src**: The source files for the software programm controling the vending machines workflow

## Deploy
TODO

## Run tests
The unittests feature an independent build workflow using CMake. They cover all code that does not directly interact with the ESP hardware.

To compile and run unittests make sure to have `CMake` installed and perform following commands:

```
mkdir build && cd build
cmake ..
make
./unittest
```
