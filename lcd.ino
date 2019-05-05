// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int serial = 13;
int clk = 12;
int reset = 11;
int disable = 10;

int delayTime = 400;
int index = 1;

bool lcdEnable = true;
bool lcdCommandRegister = true; // Selects register for lcd
int lcdData = 0;

void resetRegister() {
  digitalWrite(reset, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(reset, LOW);
  delayMicroseconds(delayTime);
  digitalWrite(reset, HIGH);
  delayMicroseconds(delayTime);
}

void writeBit(boolean b) {
  digitalWrite(clk, LOW);
  delayMicroseconds(delayTime);
  digitalWrite(serial, b ? HIGH : LOW);
  delayMicroseconds(delayTime);
  digitalWrite(clk, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(clk, LOW);
  delayMicroseconds(delayTime);
}


void writeByte(int b) {
  resetRegister();
  digitalWrite(disable, HIGH);
  for (int i = 0;i < 24;i++) {
    switch(i) {
      case 0:
        writeBit(lcdEnable);
        break;
      case 1:
        writeBit(lcdCommandRegister);
        break;
      case 2:
      case 3:
      case 4:
      case 5:
        writeBit((lcdData >> (i - 2)) & 1);
        break;
      default:
        writeBit((b >> i) & 1);
        break;
    }
  }
  digitalWrite(disable, LOW);
}

void writeLcd(int b1, bool commandRegister = false, bool singleNibble = false, int b2 = 0) {
  lcdEnable = true;
  lcdCommandRegister = commandRegister;
  lcdData = b1;
  writeByte(0);
  lcdEnable = false;
  if (!singleNibble) {
    lcdData = b2;
    writeByte(0);
  }
}

void initLcd() {
  writeLcd(2, true, true);
  writeLcd(2, true, false, 8);
  writeLcd(0, true, false, 15);
  writeLcd(0, true, false, 6);
}

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(serial, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(reset, OUTPUT);
  pinMode(disable, OUTPUT);
  
  digitalWrite(disable, LOW);
  digitalWrite(clk, LOW);
  resetRegister();
  writeByte(1);
  initLcd();
  writeLcd(4, false, false, 8);
  writeLcd(4, false, false, 9);
}

int upState = 0;

// the loop routine runs over and over again forever:
void loop() {
  
}
