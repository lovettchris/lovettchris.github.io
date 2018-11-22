#include <stdint.h>

#define CONTROL_PIN LED_BUILTIN

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin CONTROL_PIN as an output.
  pinMode(CONTROL_PIN, OUTPUT);
}

void writePreamble(int len, float scale)
{
  for (int i = 0; i < len ; i++)
  {
    digitalWrite(CONTROL_PIN, HIGH);
    delayMicroseconds((int)(200.0 * scale));
    digitalWrite(CONTROL_PIN, LOW); 
    delayMicroseconds((int)(200.0 * scale));
  }
}

void writeBits(uint16_t signal, float scale)
{
  for (int i = 0; i < 16 ; i++)
  {
    int bit = (signal & 0x8000);
    digitalWrite(CONTROL_PIN, HIGH);
    if (bit) {      
      delayMicroseconds((int)(610.0 * scale));
    } else {
      delayMicroseconds((int)(200.0 * scale));
      digitalWrite(CONTROL_PIN, LOW); 
      delayMicroseconds((int)(410.0 * scale));
    }
    digitalWrite(CONTROL_PIN, LOW);
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
  uint16_t onSignal = makeSignal(true, addr);
  sendSignal(onSignal, scale);
}

void turnOff(uint8_t addr, float scale)
{
  uint16_t offSignal = makeSignal(false, addr);
  sendSignal(offSignal, scale);
}

void loop() {
  //float scale = 2.77; // old remote is slower.
  //uint8_t addr = 0x4; // south lights
  //uint8_t addr = 0xC; // north lights

  float scale = 1; 
  uint8_t addr = 0x0; // new switch
  
  turnOn(addr, scale);
  delay(1000);  

  turnOff(addr, scale);
  delay(1000);
}
