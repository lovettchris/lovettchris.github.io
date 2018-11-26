#include <stdint.h>

#define SIGNAL_PIN 12
#define POWER_PIN 3

#define TOGGLE_ON HIGH
#define TOGGLE_OFF LOW

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Arduino Leonardo is ready!");   // send an initial string

  // initialize digital pin SIGNAL_PIN as an output.
  pinMode(SIGNAL_PIN, OUTPUT);
  pinMode(POWER_PIN, OUTPUT);
}

void writePreamble(int len, float scale)
{
  for (int i = 0; i < len ; i++)
  {
    digitalWrite(SIGNAL_PIN, HIGH);
    delayMicroseconds((int)(200.0 * scale));
    digitalWrite(SIGNAL_PIN, LOW); 
    delayMicroseconds((int)(200.0 * scale));
  }
}

void writeBits(uint16_t signal, float scale)
{
  for (int i = 0; i < 16 ; i++)
  {
    int bit = (signal & 0x8000);
    digitalWrite(SIGNAL_PIN, HIGH);
    if (bit) {      
      delayMicroseconds((int)(610.0 * scale));
    } else {
      delayMicroseconds((int)(200.0 * scale));
      digitalWrite(SIGNAL_PIN, LOW); 
      delayMicroseconds((int)(410.0 * scale));
    }
    digitalWrite(SIGNAL_PIN, LOW);
    delayMicroseconds((int)(210.0 * scale));
    signal <<= 1; 
  }
}

uint16_t makeSignal(bool on, uint8_t addr)
{
   uint16_t signal = 0x68;
   signal <<= 4;
   if (on) {
    signal += 0x2;
   }
   else {
     signal += 0x1;
   }   
   signal <<= 4;
   signal += (0xF & addr);
   return signal;
}

void sendSignal(uint16_t signal, float scale)
{
  writePreamble(48, scale);
  delay(4);
  for (int i = 0; i < 4; i++) {
    writeBits(signal, scale);
    delay((int)(4.0 * scale));
  } 
}

void turnOn(uint8_t addr, float scale)
{
  digitalWrite(POWER_PIN, TOGGLE_ON);
  delay(1); // allow some settle time
  uint16_t onSignal = makeSignal(true, addr);
  sendSignal(onSignal, scale);
  digitalWrite(POWER_PIN, TOGGLE_OFF);
}

void turnOff(uint8_t addr, float scale)
{
  digitalWrite(POWER_PIN, TOGGLE_ON);
  delay(1); 
  uint16_t offSignal = makeSignal(false, addr);
  sendSignal(offSignal, scale);
  digitalWrite(POWER_PIN, TOGGLE_OFF);
}

char buffer[1000];
int length = 0;

void loop() {
  float scale = 2.77; // old remote is slower.
  
  //float scale = 1; 
  //uint8_t addr = 0x0; // new switch

  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    
    int ch = Serial.read();
    if (ch == '\r')
    {
      buffer[length] = '\0';
      Serial.println(buffer);
      if (strncmp(buffer, "on:", 3) == 0)
      {    
        int id = atoi(&buffer[3]);
        sprintf(buffer, "Turning on lights id: %d", id);
        Serial.println(buffer);
        turnOn(id, scale);
      }
      else if (strncmp(buffer, "off:", 4) == 0)
      {
        int id = atoi(&buffer[4]);
        sprintf(buffer, "Turning off lights id: %d", id);
        Serial.println(buffer);
        turnOff(id, scale);
      }
      else {
        Serial.print("Remote Light Controller:");
        Serial.print(buffer);
        Serial.println();
      }
      length = 0;
    }
    else 
    {      
      char temp[2];
      temp[0] = ch;
      temp[1] = 0;
      Serial.print(temp);
      buffer[length++] = ch;
      if (length == 1000)
      {
        length = 0;      
      }
    }
  }
}
