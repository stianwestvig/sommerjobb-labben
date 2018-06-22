#include <Arduino.h>
#include <MKRGSM.h>
#include <config.h>
#include <DHT.h>


//arduino pin-setup
const int echoPin = 8;
const int triggerPin = 7;
const int DHT11_PIN = 5; 


// APN data
const char GPRS_APN[]      = "com4";
const char GPRS_LOGIN[]    = "";
const char GPRS_PASSWORD[] = "";


// URL, path and port 
char server[] ="ec2-54-229-221-128.eu-west-1.compute.amazonaws.com";
char path[] = "/";
int port = 80; // port 80 is the default for HTTP


GSMClient client;
GPRS gprs;
GSM gsmAccess;
DHT dht; 


void post(float distance, float temp, float humidity) {

  String json = String("{\"distance\":" + String(distance) + ", \"temp\":" + String(temp) + ", \"humidity\":" + String(humidity)+"}");
  Serial.println(json);

  if (client.connected()){
    client.println("POST / HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(json.length());

    client.println();
    client.println(json);
    } else {
      client.connect(server, port);
    }
}


void setup() {

  // initialize serial communications and wait for port to open:
 Serial.begin(9600);
  while (!Serial) {
      ; 
  }

  // PIN setup
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  dht.setup(5);
  Serial.println("Starting Arduino web client.");
  digitalWrite(LED_BUILTIN, HIGH);
  
  
  //connect to GSM
  boolean connected = false;
  while (!connected) {
      if ((gsmAccess.begin(PIN, true, true) == GSM_READY) &&
          (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD) == GPRS_READY)) {
      connected = true;
      } else {
        Serial.println("Not connected");
        delay(1000);
      }
  }
  Serial.println("Connected to GSM");
  digitalWrite(LED_BUILTIN, LOW);

  //connecting to server
  client.connect(server, port);
}




void loop() {
  //temp and humidity sensor
  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  // Distance sensor
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.00017;

  //Post data to server
  post(distance, temperature, humidity);
  delay(5000);

}
