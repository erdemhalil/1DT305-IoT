# 1DT305 - Introduction to Applied IoT

## Tutorial on how to build a smart temperature monitoring system using Arduino and Ubidots

#### *Developed by [Erdem Halil](https://github.com/erdemhalil) (eh224rw)*

This tutorial provides a step-by-step guide on how to set up a smart temperature monitoring system for your needs via WiFi and Ubidots. 

Provided that you have beginner-to-intermediate knowledge about application of Internet of Things, building your own system by following this tutorial should take you no more than a couple of hours.

## Objective 

Imagine that you are outside in the scorching summer sun. You get home as soon as possible to cool off only to find that it's no colder inside. You rush to turn the AC on and the room takes a good half an hour to reach the wanted temperature. Wouldn't you have wanted to know the room temperature beforehand and turn the AC on remotely based on that so you arrive in a perfect environment? 

Well, this project was built with the goal to tackle the first problem - collect temperature, humidity and heat index data of the room and make it available on the Internet.

Furtherly, this project can be extended to facilitate operating another IoT device, for instance, an AC, so you can turn it on no matter how far away you are. 

## Material

| Product | Product Image | Description | Price and Where to Buy |
|  :---:  |     :---:     |    :---:    |         :---:          |
|Arduino UNO Wifi Rev2| **PLACEHOLDER** | Microcontroller with built-in WiFi module | [€45](https://www.amazon.com/Arduino-UNO-WiFi-REV2-ABX00021/dp/B07MK598QV/) |
|KEYESTUDIO Upgraded 37 in 1 sensor module V3.0| **PLACEHOLDER** | Sensor set including DHT |[€40](https://www.amazon.de/-/en/KEYESTUDIO-Upgraded-compatible-instructions-electronics/dp/B0834KMKNH/)|
|Elegoo Jumper Wire Set| **PLACEHOLDER** | Used to connect sensors to microcontroller | [€7](https://www.amazon.de/-/en/Elegoo-Jumper-Bridges-Arduino-Raspberry/dp/B01EV70C78/) |

**NOTE:** You don't have to use these exact list of materials. Realistically, you only need 1 DHT sensor, or less wires than included in the set but I would strongly recommend them if you are new to the IoT world as I believe it will encourage you to continue exploring and building.

## Computer Setup

Since we are working with Arduino UNO Wifi 2, for this project you should install Arduino IDE by following [this guide](https://www.arduino.cc/en/Guide).

TBC...

## Putting everything together

The circuit diagram for the project can be seen below:

**PLACEHOLDER**

Connect 5V power (RED) and ground (BLACK) from the board to the sensor. Then, connect the last pin of the sensor to PIN number 4 of the Arduino board

Since the project is fairly simple, I didn't feel the need to overcomplicate things by using a breadboard but if you are planning on expanding on this, it might be a good idea to use one.

## Platform

For this project, the chosen platfrom was [Ubidots](https://ubidots.com/) which is an IoT Platform that offers a REST API that allows you to read and write data to the resources available. It was my first choice to explore since I had previous experience with HTTP requests and RESTful designs. After a bit of digging, I also found a nice [Arduino library](https://github.com/suhail-jr/Ubidots_Uno_Wifi) that supports my board and Ubidots and this made my choice final.

## The Code

The source code is located in [./arduino folder](https://github.com/erdemhalil/1DT305-IoT/tree/main/arduino)

The code is simple as it makes use of a few libraries explained above. The board is first connected to a WiFi network, then, it continuously reads the sensor data, adds it to the Ubidot client by associating it with an existing variable ID and then sends the data through HTTP.

To make the code work for your case, you would need to change the macros (#define) in ["secrets.h"](https://github.com/erdemhalil/1DT305-IoT/blob/main/arduino/secrets.h). Currently I have macros for WiFi SSID, WiFI Password, Ubidots token and 3 Ubidots label IDs to store 3 sets of data (temperature, humidity and heat index). You can find more information on how to create an Ubidots account, dashboard, variables [here](https://hackmd.io/@lnu-iot/Hkpudaxq9).

## Transmitting the data / connectivity

The wireless protocol I have chosen is WiFi as the project is intended for home use and I assumed that I would have a decent internet connection at all times. 

Currently, data is collected and sent every 5 seconds. This can be modified by changing the value of DELAY macro in [./arduino/arduino.ino](https://github.com/erdemhalil/1DT305-IoT/blob/bc7235a3c66abe77b92dc26bf737d16705c95ebf/arduino/arduino.ino#L12). It's measured in milliseconds so, for instance, if you'd like to collect data every minute, you may change the value to 60000.

Data transmission relies entirely on HTTP since Ubidots provides a neat RESTful API to handle those requests and, unlike MQTT, there is no need to spend more effort on creating a broker. 

## Presenting the data

**PLACEHOLDER**

The Ubidots dashboard I have created provides three graphs for the three types of data we receive and one thermometer which shows the last recorded temperature in °C. Data is saved and the graphs are updated as soon as Ubidots API receives your POST requests. Graphs are pretty responsive and you can see what the variable value was at a certain point in time.

**NOTE:** Feel free to explore what Ubidots dashboard offers as you might be able to create cool things like setting up an alarm that would go off only if one of the variables reaches a certain threshold. 

## Finalizing the desing

**PLACEHOLDER**

The project is very simple with only one type of sensor being used. As previously discussed, it can be easily extended or modified for your needs. A few more sensors that collect different type of data can be added which will enable you to have more insight. You can also combine this project with another IoT project to make the most out it, e.g. triggering IoT device if the temperature is below/above certain point.
