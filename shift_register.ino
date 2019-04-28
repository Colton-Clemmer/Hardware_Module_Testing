// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int serial = 0;
int clk = 1;
int reset = 2;

int btnUp = 7;
int btnReset = 6;

int btnUpLed = 9;

double delayTime = .001;
int index = 1;

void resetRegister() {
  digitalWrite(reset, HIGH);
  delay(delayTime);
  digitalWrite(reset, LOW);
  delay(delayTime);
  digitalWrite(reset, HIGH);
  delay(delayTime);
}

void writeBit(boolean b) {
  digitalWrite(clk, LOW);
  delay(delayTime);
  digitalWrite(serial, b ? HIGH : LOW);
  delay(delayTime);
  digitalWrite(clk, HIGH);
  delay(delayTime);
  digitalWrite(clk, LOW);
  delay(delayTime);
}


void writeByte(int b) {
  resetRegister();
  for (int i = 0;i < 16;i++) {
    writeBit((b >> i) & 1);
  }
}


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(serial, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(reset, OUTPUT);
  
  pinMode(btnUpLed, OUTPUT);
  
  pinMode(btnUp, INPUT);
  pinMode(btnReset, INPUT);
 
  digitalWrite(clk, LOW);
  resetRegister();
  writeByte(index);
}

int upState = 0;

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(btnUpLed, digitalRead(btnUp));
  int oldUpState = upState;
  upState = digitalRead(btnUp);
  if (oldUpState != upState && upState == LOW) {
    index++;
    writeByte(index);
  }
  if (digitalRead(btnReset) == HIGH) {
    index = 1;
    resetRegister();
    writeByte(1);
  }
  index++;
  writeByte(index);
  delay(1);
  if (index > 62000) {
    resetRegister();
    index = 1;
  }
}
