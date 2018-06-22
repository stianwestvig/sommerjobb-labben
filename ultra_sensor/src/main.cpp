#include <Arduino.h>
#include <MKRGSM.h>

const int id = 1;

const int echoPin = 8;
const int triggerPin = 7;


// APN data
const char GPRS_APN[]      = "com4";
const char GPRS_LOGIN[]    = "";
const char GPRS_PASSWORD[] = "";
const char PIN[] = "0579";


// URL, path and port (for example: arduino.cc)
char server[] ="ec2-54-229-221-128.eu-west-1.compute.amazonaws.com";
char path[] = "/";
int port = 80; // port 80 is the default for HTTP

// initialize the library instance
GSMClient client;
GPRS gprs;
GSM gsmAccess;



void post(float val) {
  String json = String("{\"value\":" + String(val) + "}");
  if (client.connect(server, port)){
      Serial.println("connected");
    client.println("POST / HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    //client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(json.length());

    client.println();
    client.println(json);
    } else {
      //client.connect(server, port);
      //Serial.println("connection to server failed");
    }

}




void setup() {
  // initialize serial communications and wait for port to open:
 Serial.begin(9600);
  while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
  }
  // PIN setup
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Starting Arduino web client.");
  digitalWrite(LED_BUILTIN, HIGH);
  // connection state
  boolean connected = false;
    // After starting the modem with GSM.begin()
  // attach the shield to the GPRS network with the APN, login and password
  while (!connected) {
      Serial.println(".");
      if ((gsmAccess.begin(PIN, true, true) == GSM_READY) &&
          (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD) == GPRS_READY)) {
      connected = true;
      } else {
      Serial.println("Not connected");
      delay(1000);
      }
  }
  digitalWrite(LED_BUILTIN, LOW);

  // connect to server
//  client.connect(server, port);
//  Serial.println("Connected to GSM");

}






void loop() {

  // Gjør ekkokallet
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(triggerPin, LOW);
  // Mål hvor lang tid det tar før ekkoet kommer tilbake
  long duration = pulseIn(echoPin, HIGH);
  // Regn ut avstanden
  float distance = duration * 0.00017;
  post(distance);
  delay(5000);

    // if there are incoming bytes available
  // from the server, read them and print them:
//  if (client.available()) {
  //  char c = client.read();
    //Serial.print(c);
//  }

  // if the server's disconnected, stop the client:
//  if (!client.available() && !client.connected()) {
    //Serial.println();
    //Serial.println("disconnecting.");
  //  client.stop();

    // do nothing forevermore:
  //  for (;;)
    //  ;
  //}
}
