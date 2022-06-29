#include "DHT.h"
#include "secrets.h"
#include <WiFiNINA.h>
#include <SPI.h>
#include <UbidotsUnoWifi.h>

// Section to define PINS
#define DHTPIN 4
#define DHTTYPE DHT11

// Define the loop delay - currently 5 seconds
#define DELAY 5000

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

//Initizalize Ubidots client
Ubidots client(TOKEN);

char ssid[] = SSID;   // your network SSID (name)
char pass[] = PASSWORD;   // your network password (use for WPA, or use as key for WEP)

void setup() {
    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    dht.begin();

    client.wifiConnect(ssid, pass);
}

void loop() {
    // Get sensor data
    float temperature = getTemp();
    float humidity = getHumidity();
    float heatIndex = getHeatIndex(temperature, humidity, false);
    
    // Print data collected from the sensor to serial
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("% ");

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C ");

    Serial.print("Heat index: ");
    Serial.print(heatIndex);
    Serial.println("°C ");

    // Collect data to be sent to ubidots
    client.add(TEMP_LABEL, temperature);
    client.add(HUM_LABEL, humidity);
    client.add(HEAT_LABEL, heatIndex);

    bool bufferSent = false;
    // Send data to Ubidots
    bufferSent = client.sendAll();

    if (bufferSent) {
        // Print success if values were sent properly
        Serial.println("Values sent by the device");
    } else {
        // Else print out an error message
        Serial.println("An error occurred");
    }
    
    delay(DELAY); // Put the device to sleep for 5s 
}

// Function to get the DHT temperature from the sensor
float getTemp()
{
    // Get the temperature from the DHT sensor
    float temp = dht.readTemperature();
    // Check if the temperature is valid
    if (isnan(temp))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return 1;
    }
    
    return temp;
}

// Function to get the DHT humidity from the sensor
float getHumidity()
{
    // Get the humidity from the DHT sensor
    float hum = dht.readHumidity();
    // Check if the humidity is valid
    if (isnan(hum))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return 1;
    }
    
    return hum;
}

// Function to calculate the DHT heat index
float getHeatIndex(float temp, float hum, bool isFahreheit)
{
    // Calculate the heat index with the formula from the DHT sensor
    float heatIndex = dht.computeHeatIndex(temp, hum, isFahreheit);
    
    return heatIndex;
}