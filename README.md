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
|Arduino UNO Wifi Rev2| <img src=https://user-images.githubusercontent.com/71549844/177054583-417527e5-d058-40b6-8e98-cf395c58d3ec.jpg width=200>| Microcontroller with built-in WiFi module | [€45](https://www.amazon.com/Arduino-UNO-WiFi-REV2-ABX00021/dp/B07MK598QV/) |
|KEYESTUDIO Upgraded 37 in 1 sensor module V3.0| <img src=https://user-images.githubusercontent.com/71549844/177054724-11f7f145-b5a3-479a-a7ec-41b44f145175.png width=200>| Sensor set including DHT |[€40](https://www.amazon.de/-/en/KEYESTUDIO-Upgraded-compatible-instructions-electronics/dp/B0834KMKNH/)|
|Elegoo Jumper Wire Set| <img src=https://user-images.githubusercontent.com/71549844/177054775-b0f07b71-fcd7-4b50-9779-20c350cd9da6.jpg width=200>| Used to connect sensors to microcontroller | [€7](https://www.amazon.de/-/en/Elegoo-Jumper-Bridges-Arduino-Raspberry/dp/B01EV70C78/) |

**NOTE:** You don't have to use these exact list of materials. Realistically, you only need 1 DHT sensor, or less wires than included in the set but I would strongly recommend them if you are new to the IoT world as I believe it will encourage you to continue exploring and building.

## Computer Setup

1. Since we are working with Arduino Uno WiFi 2, for this project you should install Arduino IDE by following [this guide](https://www.arduino.cc/en/Guide).
2. Install the core for the board (megaAVR) by following [this article](https://docs.arduino.cc/software/ide-v1/tutorials/getting-started/cores/arduino-megaavr). Make sure you select Arduino Uno WiFi Rev2.
3. Install the required libraries. For a general guide [click here](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries).
    - DHT, WiFiNINA and SPI libraries can be installed directly through the Library Manager.
    - [UbidotsUnoWifi](https://github.com/suhail-jr/Ubidots_Uno_Wifi/) library must be imported as a .zip file. Download it by [clicking here](https://github.com/suhail-jr/Ubidots_Uno_Wifi/archive/refs/heads/main.zip).
4. Open [arduino.ino](https://github.com/erdemhalil/1DT305-IoT/blob/main/arduino/arduino.ino) file with Arduino IDE and [upload the sketch](https://support.arduino.cc/hc/en-us/articles/4733418441116-Upload-a-sketch-in-Arduino-IDE). 

## Putting everything together

The circuit diagram for the project can be seen below:

<img src=https://user-images.githubusercontent.com/71549844/177055107-939a6961-32a0-4418-8bc4-650b851604c7.jpg height=500>

Connect 5V power (RED) and ground (BLACK) from the board to the sensor. Then, connect the last pin of the sensor to PIN number 4 of the Arduino board

Since the project is fairly simple, I didn't feel the need to overcomplicate things by using a breadboard but if you are planning on expanding on this, it might be a good idea to use one.

## Platform

For this project, the chosen platfrom was [Ubidots](https://ubidots.com/) which is an IoT Platform that offers a REST API that allows you to read and write data to the resources available. It was my first choice to explore since I had previous experience with HTTP requests and RESTful designs. After a bit of digging, I also found a nice [Arduino library](https://github.com/suhail-jr/Ubidots_Uno_Wifi) that supports my board and HTTP requests to Ubidots. Frankly, this made my choice final.

## The Code

The source code is located in [./arduino folder](https://github.com/erdemhalil/1DT305-IoT/tree/main/arduino)

The code is simple as it makes use of a few libraries. DHT library lets us collect sensor data easily, whereas WiFiNINA, SPI and UbidotsUnoWifi libraries help ease the process of connecting to the network and sending data to Ubidots. 

Firstly, the board activates the sensor and connects to a WiFi network in the setup block:
```cpp
dht.begin();
client.wifiConnect(ssid, pass);
```

Then, it continuously reads the sensor data, adds it to the Ubidot client by associating it with an existing variable ID and sends the data through HTTP.  
**NOTE:** Example is with temperature only!
```cpp
float temperature = getTemp();
client.add(TEMP_LABEL, temperature);

bool bufferSent = false;
// Send data to Ubidots
bufferSent = client.sendAll();
```

To make the code work for your case, you would need to change the macros (#define) in ["secrets.h"](https://github.com/erdemhalil/1DT305-IoT/blob/main/arduino/secrets.h). 

```c
// WiFi Network's SSID
#define SSID "PLACEHOLDER"
// WiFi Network's Password
#define PASSWORD "PLACEHOLDER"
// Ubidots TOKEN
#define TOKEN "PLACEHOLDER"

// Ubidots variables that will be updated
#define TEMP_LABEL "PLACEHOLDER"
#define HUM_LABEL "PLACEHOLDER" 
#define HEAT_LABEL "PLACEHOLDER" 
```

Currently I have macros for WiFi SSID, WiFI Password, Ubidots token and 3 Ubidots label IDs to store 3 sets of data (temperature, humidity and heat index). You can find more information on how to create an Ubidots account, dashboard, variables and retrieve their IDs [here](https://hackmd.io/@lnu-iot/Hkpudaxq9).

## Transmitting the data / connectivity

The wireless protocol I have chosen is WiFi as the project is intended for home use and I assumed that I would have a decent internet connection at all times. 

Currently, data is collected and sent every 5 seconds. This can be modified by changing the value of DELAY macro in [./arduino/arduino.ino](https://github.com/erdemhalil/1DT305-IoT/blob/bc7235a3c66abe77b92dc26bf737d16705c95ebf/arduino/arduino.ino#L12). 
```cpp
#define DELAY 5000
```
It's measured in milliseconds so, for instance, if you'd like to collect data every minute, you may change the value to 60000.

Data transmission relies entirely on HTTP since Ubidots provides a neat RESTful API to handle those requests and, unlike MQTT, there is no need to spend more effort on creating a broker. 

## Presenting the data

![dashboard](https://user-images.githubusercontent.com/71549844/177054501-1f5aaae7-18e8-4e35-952c-e85381027170.png)

The Ubidots dashboard I have created provides three graphs for the three types of data we receive and one thermometer which shows the last recorded temperature in °C. Data is saved and the graphs are updated as soon as Ubidots API receives your POST requests. Graphs are pretty responsive and you can see what the variable value was at a certain point in time.

**NOTE:** Feel free to explore what Ubidots dashboard offers as you might be able to create cool things like setting up an alarm that would go off only if one of the variables reaches a certain threshold. 

## Finalizing the desing

<img src=https://user-images.githubusercontent.com/71549844/177054465-f750357f-d5b8-4d34-87f5-23de2211fe02.jpg width=800>

The project is very simple with only one type of sensor being used. As previously discussed, it can be easily extended or modified for your needs. A few more sensors that collect different type of data can be added which will enable you to gather more insight. You can also combine it with another IoT project to make the most out it, e.g. triggering IoT device if the temperature is below/above certain point.
