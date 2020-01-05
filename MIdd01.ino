/* serial and usb midi to C64 user port parallel adaptor
 *  
 */


#define B0    2
#define B1    3
#define B2    4
#define B3    5
#define B4    6
#define B5    7
#define B6    8
#define B7    9

#define _PC2  16
#define FLAG  10


int period = 1000;
unsigned long time_now = 0;


void send_byte(uint8_t in) {
  digitalWrite(FLAG, HIGH);

  digitalWrite(B0, in & (1<<0));
  digitalWrite(B1, in & (1<<1));
  digitalWrite(B2, in & (1<<2));
  digitalWrite(B3, in & (1<<3));
  digitalWrite(B4, in & (1<<4));
  digitalWrite(B5, in & (1<<5));
  digitalWrite(B6, in & (1<<6));
  digitalWrite(B7, in & (1<<7));

  digitalWrite(FLAG, LOW);
  delayMicroseconds(10);
  digitalWrite(FLAG, HIGH);
  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(B0, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(B3, OUTPUT);
  pinMode(B4, OUTPUT);
  pinMode(B5, OUTPUT);
  pinMode(B6, OUTPUT);
  pinMode(B7, OUTPUT);

  pinMode(FLAG, OUTPUT);
  pinMode(_PC2, INPUT);

// Serial1 is hardware uart and opto midi input
  Serial1.begin(31250);

// USB serial to PC
  Serial.begin(115200);
}

char test_msg[] = "HELLO THERE TEST MSG\n";

char noprintf[128];

void loop() {
  // put your main code here, to run repeatedly:
  if ( Serial1.available() ) {
    time_now = millis();
    uint8_t in = Serial1.read();
    sprintf (noprintf, "%02x ", in);
    Serial.print(noprintf);
    send_byte(in);
  }
  
  if(millis() - time_now > 1000){
    time_now = millis();
    Serial.println("\n90 3c 3f");
    send_byte(0x90);
    delay(20);
    send_byte(0x3c);
    delay(20);
    send_byte(0x3f);
    delay(20);
/*
    for (int i=0; i<strlen(test_msg); i++) {
      Serial.write(test_msg[i]);
      send_byte(test_msg[i]);
      delayMicroseconds(300);
    }
    */
  }
}
