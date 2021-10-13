#include <PortentaEthernet.h>
#include <Ethernet.h>
#include <tinyMqttPortentaEthernetV2.h>   // https://github.com/hsaturn/TinyMqtt



/** Basic Mqtt Broker
  *
  *  +-----------------------------+
  *  | ESP                         |
  *  |       +--------+            | 
  *  |       | broker |            | 1883 <--- External client/s
  *  |       +--------+            |
  *  |                             |
  *  +-----------------------------+
  *
  *  Your ESP will become a MqttBroker.
	*  You can test it with any client such as mqtt-spy for example
	*  
  */

// Only importent if you know the values you need
IPAddress ip(192, 168, 1, 177);
IPAddress myDns(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

#define TINY_MQTT_DEBUG
#define PORT 1883
EthernetServer server(PORT);

MqttBroker broker(&server);

void setup() 
{
  // initialize the Ethernet device
  //Ethernet.begin(ip, myDns, gateway, subnet);  / only if you know them
  Ethernet.begin();

  // Open serial communications and wait for port to open:
  Serial.begin(115200);
    delay(5000);
  Serial.println("Wait a bit to connect serial monitor");
  delay(5000);
  Serial.println("Wait a bit");
  delay(5000);
  Serial.println("Wait a bit");
  
  pinMode(LED_BUILTIN, OUTPUT);      // set the LED pin mode
  pinMode(LEDB, OUTPUT);      // set the LED pin mode
  digitalWrite(LEDB, LOW);  

 // while (!Serial) {
  //  ; // wait for serial port to connect. Needed for native USB port only
  //}

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  Serial.print("MQTT Broker address:");
  Serial.println(Ethernet.localIP());

  broker.begin();
}

void loop()
{
  broker.loop();
}
