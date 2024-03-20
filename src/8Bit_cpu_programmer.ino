

//Note: we are usuing version 2.3 of the library to keep this simple.
#include <IRremote.h>    
int RECV_PIN = 13;
int LED_PIN = A0;
int CLOCK_PIN = 12;
int RI_PIN = 11;
int MI_PIN = 10;
int EEPROM1_PIN = A1; 
int EEPROM2_PIN = A2;

// We declare the range of the bus signals
int BUS_PIN1 = 2;
int BUS_PIN2 = 9;

IRrecv irrecv(RECV_PIN);
decode_results results;

int memoryValue = 0;
int ramValue = 0;
bool captureMemory = false;
int memoryCounter = 0;
bool captureRam = false;
int ramCounter = 0;

// Load sample programs into the onboard arduino
byte program1[] = {
   0b01010001, 0b00101111,0b11100000,0b01100001,0,0,0,0,0,0,0,0,0,0,0,0b00000001,
};

byte program2[] = {
   0b01010010, 0b01001111,0b00111111,0b11100000,0b01100010,0,0,0,0,0,0,0,0,0,0,0,
};


//Load program
void loadProgram(int program) {

  if (program == 1) {
    for(int x = 0; x < sizeof(program1); x++) {
      saveDataToMemory(x);
      saveDataToRam(program1[x]);
      flashLED();
     }
  }

   if (program == 2){
    for(int x = 0; x < sizeof(program2); x++) {
      saveDataToMemory(x);
      saveDataToRam(program2[x]);
      flashLED(); 
    }
  }
}

void startArduino() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(RI_PIN, OUTPUT);
  pinMode(MI_PIN, OUTPUT);

  for (int pin = BUS_PIN1; pin <= BUS_PIN2; pin++) {
    pinMode(pin, OUTPUT);
  }
  
  digitalWrite(EEPROM1_PIN, HIGH);
  digitalWrite(EEPROM2_PIN, HIGH);

}

void stopArduino() {

  captureRam = false;
  captureMemory = false;
  memoryCounter = 0;
  ramCounter = 0;

  pinMode(LED_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(RI_PIN, INPUT);
  pinMode(MI_PIN, INPUT);
  
  pinMode(EEPROM1_PIN, OUTPUT);
  pinMode(EEPROM2_PIN, OUTPUT);
  digitalWrite(EEPROM1_PIN, LOW);
  digitalWrite(EEPROM2_PIN, LOW);

  for (int pin = BUS_PIN1; pin <= BUS_PIN2; pin++)   {
    pinMode(pin, INPUT);
  }
  
  Serial.println("Arduino is stopped");
  delay(50);
}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(LED_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(RI_PIN, INPUT);
  pinMode(MI_PIN, INPUT);
  pinMode(EEPROM1_PIN, OUTPUT);
  pinMode(EEPROM2_PIN, OUTPUT);
  digitalWrite(EEPROM1_PIN,LOW);
  digitalWrite(EEPROM2_PIN,LOW);

  for (int pin = BUS_PIN1; pin <= BUS_PIN2; pin++)  {
    pinMode(pin, INPUT);
  }
  Serial.println("Arduino is setup complete");
}

//Fire off a single clock pulse to load the circuit.
bool clockPulse() {
  digitalWrite(CLOCK_PIN, HIGH);
  delay(50);
  digitalWrite(CLOCK_PIN, LOW);
}

//This function will be called when we want to write a piece of data to ram. This will assume that the memory address has been set properly.
//This will open up the bus and write with a clock pulse.
bool saveDataToRam(int ramValue) {
 
  digitalWrite(RI_PIN, HIGH);

  for (int pincount = BUS_PIN1; pincount <= BUS_PIN2; pincount ++) {
    int value = ramValue & 0x01;   
    Serial.println(ramValue,BIN);
    Serial.println(value,BIN);
    
    if (value == 1) {
      Serial.print("output ");
      Serial.print(pincount);
      Serial.println(" HIGH \n");
      digitalWrite(pincount, HIGH);
    }
    else {
      Serial.print("output ");
      Serial.print(pincount);
      Serial.println(" LOW \n");
      digitalWrite(pincount, LOW);
    }

     ramValue = ramValue >> 1;
  }

  delay(100);
  clockPulse();
  delay(100);
  digitalWrite(RI_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
   
   for (int pin = BUS_PIN1; pin <= BUS_PIN2; pin++) {
    digitalWrite(pin, LOW);
  }

}

bool saveDataToMemory(int memoryValue) {

  digitalWrite(MI_PIN, HIGH);

  for (int pincount = BUS_PIN1; pincount <= BUS_PIN2; pincount ++) {
    int value = memoryValue & 0x01;

    if (value == 1) {
      Serial.print("output ");
      Serial.print(pincount);
      Serial.println(" HIGH \n");
      digitalWrite(pincount, HIGH);
    }
    else {
      Serial.print("output ");
      Serial.print(pincount);
      Serial.println(" LOW \n");
      digitalWrite(pincount, LOW);
    }
    memoryValue = memoryValue >> 1;
  }

  delay(100);
  clockPulse();
  delay(50);
  digitalWrite(MI_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  for (int pin = BUS_PIN1; pin <= BUS_PIN2; pin++)  {
    digitalWrite(pin, LOW);
  }
}

void flashLED() {
  digitalWrite(LED_PIN, HIGH);
  delay(80);
  digitalWrite(LED_PIN, LOW);
}

void loop()
{
  //We will want to increment the counters as we capture values reliably.

  if (irrecv.decode(&results)) { // Returns 0 if no data ready, 1 if data ready.
  
    Serial.println(results.value,HEX);
    switch (results.value) {
      //Capture signals recieved by the IR remote
      case 0xFF30CF:
        if (captureMemory == true && memoryCounter < 4) {
          memoryCounter++;
          memoryValue =  (memoryValue << 1) + 1;
          Serial.println("Adding binary 1");
          flashLED();
        }
        if (captureRam == true && ramCounter < 8) {
          ramCounter++;
          ramValue = (ramValue << 1) + 1;
          Serial.println("Adding binary 1");
          flashLED();
        }
        break;
      case 0xFF6897:
        if (captureMemory == true && memoryCounter < 4) {
          memoryCounter++;
          memoryValue = (memoryValue << 1) + 0;
          Serial.println("Adding binary 0");
          flashLED();
        }

        if (captureRam == true && ramCounter < 8) {
          ramCounter++;
          ramValue = (ramValue << 1) + 0;
          Serial.println("Adding binary 0");
          flashLED();
        }
        break;
      case 0xFFC23D:
        Serial.println("you pressed the Save button");
        Serial.println("\n");

        if (captureMemory) {
          saveDataToMemory(memoryValue);
          captureMemory = false;
          memoryCounter = 0;
          memoryValue = 0;

        }
        else if (captureRam) {
          saveDataToRam(ramValue);
          ramCounter = 0;
          captureRam = false;
          ramValue = 0;
        }
        break;
      case 0xFFE21D:
        Serial.println("you pressed the Memory button");
        Serial.println("\n");
        captureMemory = true;
        captureRam = false;
        memoryValue = 0;
        memoryCounter = 0;
        flashLED();
        digitalWrite(LED_PIN, LOW);
        break;
      case 0xFF629D:
        Serial.println("you pressed the Ram button");
        Serial.println("\n");
        captureRam = true;
        captureMemory = false;
        ramCounter = 0;
        ramValue = 0;
        flashLED();
        digitalWrite(LED_PIN, LOW);
        break;
      case 0xFF22DD:
        Serial.println("STOP ARDUINO CONTROL");
        stopArduino();
        break;

      case 0xFF02FD:
        Serial.println("START ARDUINO CONTROL");
        startArduino();
        break;
      case 0xFF52AD:
        Serial.println("Load Program 0");
        loadProgram(1);
        break;
      case 0xFF4AB5:
        Serial.println("Load Program 1"); 
        loadProgram(2);
        break;
      case 0xFFA857:
        Serial.println("Up Memory");   
        break;        
    }

    if (captureRam == true && ramCounter == 8) {
      digitalWrite(LED_PIN, HIGH);
    }

    if (captureMemory == true && memoryCounter == 4) {
      digitalWrite(LED_PIN, HIGH);
    }
    
    irrecv.resume(); // Restart the ISR state machine and Receive the next value
  }
}
