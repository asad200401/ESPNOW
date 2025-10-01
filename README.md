# ESPNOW
ESP-NOW Communication

This repository provides a simple implementation of ESP-NOW communication between two ESP32 devices. The sender transmits a custom data structure (string, integer, float, boolean) to the receiver, which displays the data via the Serial Monitor.

**Usage**

Upload sender.ino to one ESP32 and receiver.ino to another after updating the receiverAddress in sender.ino with the receiver's MAC address (found in the receiver's Serial Monitor). Connect both boards to the Arduino IDE, set the baud rate to 115200, and monitor the sender's status and receiver's data output every 5 seconds.
