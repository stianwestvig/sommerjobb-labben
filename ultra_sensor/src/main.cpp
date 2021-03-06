#include <Arduino.h>
#include <MKRGSM.h>
#include <config.h>
#include <DHT.h>


//arduino pin-setup
const int echoPin = 8;
const int triggerPin = 7;
const int DHT11_PIN = 5; 
const int vibPin = 4; 


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
int counter = 0; 

void post(float distance, float temp, float humidity, int vib) {
  counter ++; 

  String json = String("{\"distance\":" + String(distance) + ", \"temp\":" + String(temp) + ", \"humidity\":" + String(humidity) + ", \"vib\": "+ String(vib) +", \"no\": " + String(counter) + "}");
  Serial.println(json);

  if (client.connect(server, port)){
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
      Serial.println("Reconnecting");
      client.connect(server, port);
    }
    client.stop();
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
  dht.setup(DHT11_PIN);
  pinMode(vibPin,INPUT);//set pin2 as INPUT
  digitalWrite(vibPin, HIGH);//set pin2 as HIGH
  digitalWrite(LED_BUILTIN, HIGH);


  Serial.println("Starting Arduino web client.");
  
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

}




void loop() {
  //temp and humidity sensor
  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  Serial.println(humidity);

  // Distance sensor
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.00017;

  //vibration sensor 
  int digitalVib = digitalRead(vibPin);//Read the value of pin2


  //Post data to server
  post(distance, temperature, humidity, digitalVib);
}


 
