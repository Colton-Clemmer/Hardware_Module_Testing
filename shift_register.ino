// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int serial = 13;
int clk = 12;
int reset = 11;
int disable = 10;

int delayTime = 400;
int index = 1;

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
    writeBit((b >> i) & 1);
  }
  digitalWrite(disable, LOW);
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
}

int upState = 0;

// the loop routine runs over and over again forever:
void loop() {
  index++;
  writeByte(index);
  delay(20);
  if (index > 255) {
    resetRegister();
    index = 1;
  }
}
