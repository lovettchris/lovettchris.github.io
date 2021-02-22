#include <stdint.h>

#define SIGNAL_PIN 12
#define POWER_PIN 3

#define TOGGLE_ON HIGH
#define TOGGLE_OFF LOW

char buffer[1000];
int length = 0;
float frequency = 1;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Remote Light Controller");   // send an initial string

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
    delayMicroseconds((int)(200.0 * scale));
    if (bit) {      
      delayMicroseconds((int)(410.0 * scale));
    } else {
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
  for (int i = 0; i < 5; i++) {
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

struct Command
{
    bool on; 
    bool off;
    uint8_t addr; // switch id
    float frequency; // 1 or 2.7
};

struct Command parse(char* buffer)
{
    Command cmd;
    cmd.on = false;
    cmd.off = false;
    cmd.addr = 0;
    cmd.frequency = 1;

    // serialization format is "on:4,freq:2.7"
    char* part2 = strchr(buffer, ',');
    if (part2 != nullptr)
    {
      *part2 = 0;
      part2++;
      if (strncmp(part2, "freq:", 4) == 0)
      {
        cmd.frequency = (float)atof(&part2[5]);
      }
    }
    
    if (strncmp(buffer, "on:", 3) == 0)
    {
      cmd.on = true;
      cmd.addr = atoi(&buffer[3]);
    }
    else if (strncmp(buffer, "off:", 4) == 0)
    {
      cmd.off = true;
      cmd.addr = atoi(&buffer[4]);
    }
    return cmd;
}

void processCommand(struct Command cmd)
{
  // for some unknown reason sprintf with %f is not working.
  int x = (int)cmd.frequency;
  int y = (int)(cmd.frequency * 10) - (10*x);
  if (cmd.on)
  {
    sprintf(buffer, "Turning on lights id: %d with frequency %d.%d ", cmd.addr, x, y);
    Serial.println(buffer);
    turnOn(cmd.addr, cmd.frequency);
  }
  else if (cmd.off)
  {
    sprintf(buffer, "Turning off lights id: %d with frequency %d.%d ", cmd.addr, x, y);
    Serial.println(buffer);
    turnOff(cmd.addr, cmd.frequency);
  }
  else
  {
        Serial.println("Remote Light Controller");
  }
}

void loop() {

  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    
    int ch = Serial.read();
    
    // echo char so you can control this interactivly over serial port.
    char temp[2];
    temp[0] = ch;
    temp[1] = 0;
    Serial.print(temp);
    
    if (ch == '\r')
    {
      temp[0] = '\n';
      Serial.print(temp);
      
      buffer[length] = '\0';

      struct Command cmd = parse(buffer);
      processCommand(cmd);
      
      length = 0;
      buffer[length] = '\0';
    }
    else if (ch != '\n')
    {
      buffer[length++] = ch;
      if (length == 1000)
      {
        length = 0;      
      }
    }
  }
}
