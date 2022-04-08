

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 4
#define RST_PIN 3
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
const int ena = 20;
const int dir = 19;
const int pul = 18;





const int interval = 9100;   // increase to reduce speed

//const int STEPS_PER_REV = 2;
//const int interval= 700 ;   //intervalo entre as
//olean puls = LOW; //estado do pulso
//int timespan = 0;



boolean pulse_state = LOW;
int timespan = 0;
//const byte interruptPin = 2;
//volatile bool blade_state = 0;
//volatile bool proximity_sensor1_state =0 ;

void setup()
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(ena, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(pul, OUTPUT);//  pinMode(interruptPin, INPUT);
  digitalWrite(ena, LOW);// LOW to enable
  digitalWrite(dir, HIGH);
  digitalWrite(pul, HIGH);
//  attachInterrupt(digitalPinToInterrupt(interruptPin), blade_state_interrupt, RISING);//trigger when the pin goes from low to high,
  // proximity_sensor1 =  digitalRead(interruptPin);

}
void loop()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  //if (content.substring(1) == "48 01 AF 89" || "83 OB 34 03" || "89 5B A2 99") //change here the UID of the card/cards that you want to give access
  
  if (content.substring(1) == "89 5B A2 99") //change here the UID of the card/cards that you want to give access
  {

    Serial.println("Authorized access");
    runMotor() ;
    delay(1000);
  }

  else   {
    Serial.println(" Access denied");
    delay(3000);
  }
}

void runMotor() 
{
  for (timespan = 0; timespan <= 133 ; timespan++) {
    dispense();
  }

  delay(3000);  //break btwn dispensation
}
  
  void dispense() {
    pulse_state = !pulse_state;
    digitalWrite(pul, pulse_state);
    delayMicroseconds(interval);
  }
