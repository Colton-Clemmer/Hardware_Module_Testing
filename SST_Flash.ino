int flash_output_enable = 12;
int flash_write_enable = 11;

int latch_pin_data = 10;
int clock_pin_data = 9;
int data_pin_data = 8;

int latch_pin_addr_msb = 7;
int clock_pin_addr_msb = 6;
int data_pin_addr_msb = 5;

int latch_pin_addr_lsb = 4;
int clock_pin_addr_lsb = 3;
int data_pin_addr_lsb = 2;

void ReadFlash(int addr)
{
    digitalWrite(flash_output_enable, HIGH);
    digitalWrite(flash_write_enable, HIGH);
    SetShift(addr, 0);
    digitalWrite(flash_output_enable, LOW);
    delay(100);
}

void WriteFlash(int addr, int data)
{
    digitalWrite(flash_output_enable, HIGH);
    WriteSequencePart(0x5555, 0xAA);
    WriteSequencePart(0x2AAA, 0x55);
    WriteSequencePart(0x5555, 0xA0);
    WriteSequencePart(addr, data);
}

void WriteSequencePart(int addr, int data)
{
    digitalWrite(flash_write_enable, HIGH);
    SetShift(addr, data);
    digitalWrite(flash_write_enable, LOW);
    delay(100);
    digitalWrite(flash_write_enable, HIGH);
    delay(100);
}

void SetShift(int addr,int data)
{
    int addr_msb = addr >> 8;  
    int addr_lsb = addr - addr_msb;
    digitalWrite(latch_pin_addr_lsb, LOW);
    digitalWrite(latch_pin_addr_msb, LOW);
    digitalWrite(latch_pin_data, LOW);
    
    shiftOut(data_pin_addr_lsb, clock_pin_addr_lsb, MSBFIRST, addr_lsb);
    shiftOut(data_pin_addr_msb, clock_pin_addr_msb, MSBFIRST, addr_msb);
    shiftOut(data_pin_data, clock_pin_data, MSBFIRST, data);
    
    digitalWrite(latch_pin_addr_lsb, HIGH);
    digitalWrite(latch_pin_addr_msb, HIGH);
    digitalWrite(latch_pin_data, HIGH);
    delay(100);
}

void setup()
{
    pinMode(latch_pin_addr_lsb, OUTPUT);
    pinMode(clock_pin_addr_lsb, OUTPUT);
    pinMode(data_pin_addr_lsb, OUTPUT);
    pinMode(latch_pin_addr_msb, OUTPUT);
    pinMode(clock_pin_addr_msb, OUTPUT);
    pinMode(data_pin_addr_msb, OUTPUT);
    pinMode(flash_output_enable, OUTPUT);
    pinMode(flash_write_enable, OUTPUT);
    //WriteFlash(0x000A, 43);
    //ReadFlash(0x000F);
    Serial.begin(9600);
    Serial.setTimeout(10000);
    Serial.print("Cmd> ");
}

/*
state:
0: reading command
1: reading address
2: writing address
3: writing data
*/

boolean state = 0;

void loop()
{
    if (Serial.available() == 0) return;
    int input = Serial.read();
    if (input == 10) return; // new line character
    if (input == 114 && state == 0) // Read cmd "r"
    {
        state = 1;
        Serial.print("Read: 0x");
        return;
    }
    if (input == 119 && state == 0) // Write cmd "w"
    {
        state = 2;
        Serial.print("Write: 0x");
        return;
    }
    if (state == 1)
    {
        
    }

//    if (
//        
//        Serial.println("Read");
//        int r = Serial.read();
//        Serial.print(Serial.available());
//        // ReadFlash();
//    }
//    if (input == 119) // Write "w"
//    {
//        Serial.print("Write: 0x");
//    }
}
