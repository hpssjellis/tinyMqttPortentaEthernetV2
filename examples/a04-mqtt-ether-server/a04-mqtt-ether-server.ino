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
// typical standards for most local networks
//IPAddress myIp(192, 168, 1, 177);
//IPAddress myDns(192, 168, 1, 1);
//IPAddress myGateway(192, 168, 1, 1);
//IPAddress mySubnet(255, 255, 255, 0);


#define TINY_MQTT_DEBUG
#define PORT 1883
EthernetServer server(PORT);

MqttBroker broker(&server);

void setup() 
{
  // initialize the Ethernet device
  //Ethernet.begin(myIp, myDns, myGateway, mySubnet);  / only if you know them
  Ethernet.begin();  // Will be auto set
  
  pinMode(LED_BUILTIN, OUTPUT);      // set the LED default green pin
  pinMode(LEDB, OUTPUT);             // set the LED blue pin
  digitalWrite(LEDB, LOW);           // LED Blue on (on board LED low is on) 

  // Non-blocking wait for serial port
  Serial.begin(115200);
  delay(5000);
  Serial.println("Wait a bit to connect serial monitor");
  delay(5000);
  Serial.println("Wait a bit");
  delay(5000);
  Serial.println("Wait a bit");
  

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
