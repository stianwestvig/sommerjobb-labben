#include <Arduino.h>
#include <MKRGSM.h>

// initialize the library instance
GSM gsmAccess;
GSM_SMS sms;

// iteration in loop
bool smsSent = false;

/*
  Read input serial
 */
int readSerial(char result[]) {
  int i = 0;
  while (1) {
    while (Serial.available() > 0) {
      char inChar = Serial.read();
      if (inChar == '\n') {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if (inChar != '\r') {
        result[i] = inChar;
        i++;
      }
    }
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // get pin from user
  Serial.print("Enter PIN: ");
  char pin[5];  // telephone number to send sms
  readSerial(pin);
  Serial.println();

  // set status to not connected
  int status = 0;

  // Start GSM shield
  while (status != GSM_READY) {
    Serial.println("Trying to connect");
    status = gsmAccess.begin(pin, true, true);
    if (status != GSM_READY) {
      Serial.print("Failed to connect, status: ");
      Serial.println(status);
      delay(1000);
    }
  }

  Serial.println("Connected");
}

void loop() {
  // only continue the first iteration of the loop
  if (smsSent) {
    return;
  }

  // number
  Serial.print("Enter a mobile number: ");
  char remoteNum[20];  // telephone number to send sms
  readSerial(remoteNum);
  Serial.println(remoteNum);

  // sms text
  Serial.print("Now, enter SMS content: ");
  char txtMsg[200];
  readSerial(txtMsg);
  Serial.println(txtMsg);

  // send the message
  sms.beginSMS(remoteNum);
  sms.print(txtMsg);
  sms.endSMS();
  smsSent = true;
  Serial.println("Sent.");
}

