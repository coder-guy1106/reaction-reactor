
byte seven_seg_digits_dot[10] = { B11111101,  // = 0
                              B01100001,  // = 1
                              B11011011,  // = 2
                              B11110011,  // = 3
                              B01100111,  // = 4
                              B10110111,  // = 5
                              B10111111,  // = 6
                              B11100001,  // = 7
                              B11111111,  // = 8
                              B11100111   // = 9
                             };


byte seven_seg_digits[10] = { B11111100,  // = 0
                              B01100000,  // = 1
                              B11011010,  // = 2
                              B11110010,  // = 3
                              B01100110,  // = 4
                              B10110110,  // = 5
                              B10111110,  // = 6
                              B11100000,  // = 7
                              B11111110,  // = 8
                              B11100110   // = 9
                             };
int latchPin = 7;
int clockPin = 8;
int dataPin = 6;
 
int one=9;
int two=11;
int three=10;
int four=12;

int red = 4;
int yellow = 3;
int green = 2;
int button = 5;
int buffer[4];

void setNumber(int value){
  buffer[0]=(value/1000) % 10;
  buffer[1]=(value/100) % 10;
  buffer[2]=(value/10) % 10;
  buffer[3]=value % 10;
}

void setup() {
  // Set latchPin, clockPin, dataPin as output
  Serial.begin(9600);
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);     
  pinMode(green,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(one,OUTPUT);
  pinMode(two,OUTPUT);
  pinMode(three,OUTPUT);
  pinMode(four,OUTPUT);
  digitalWrite(red,HIGH);
  digitalWrite(one, HIGH);
  digitalWrite(two, HIGH);
  digitalWrite(three, HIGH);
  digitalWrite(four, HIGH);
}
void alloff(){
  digitalWrite(one, HIGH);
  digitalWrite(two, HIGH);
  digitalWrite(three, HIGH);
  digitalWrite(four, HIGH);

}
// display a number on the digital segment display
void sevenSegWriteDot(byte digit) {
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);
     
  // the original data (bit pattern)
  shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits_dot[digit]);  
 
  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);
}
void sevenSegWrite(byte digit) {
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);
     
  // the original data (bit pattern)
  shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]);  
 
  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);
}
void refreshDisplay(){

  alloff();
  sevenSegWriteDot(buffer[0]);
  digitalWrite(one, LOW);
  delayMicroseconds(1000);
  digitalWrite(one, HIGH);


  alloff();
  sevenSegWrite(buffer[1]);
  digitalWrite(two, LOW);
  delayMicroseconds(1000);
  digitalWrite(two, HIGH);


  alloff();  
  sevenSegWrite(buffer[2]);
  digitalWrite(three, LOW);
  delayMicroseconds(1000);
  digitalWrite(three, HIGH);


  alloff();
  sevenSegWrite(buffer[3]);
  digitalWrite(four, LOW);
  delayMicroseconds(1000);
  digitalWrite(four, HIGH);
}
void stopwatch(){
  unsigned long start = millis();
  unsigned long lastUpdate =start;
  int state=digitalRead(button);
  while((millis()-start<10000)&&(state==HIGH)){

    refreshDisplay();
    unsigned long now = millis();

    if(now-lastUpdate>=10){
      lastUpdate+=10;
      setNumber(now-start);
      state=digitalRead(button);
    }

    
  }

  Serial.println(millis()-start);
  digitalWrite(green,LOW);
  for(int a=0;a<4;a++){
    for(int i=0;i<300;i++){
      refreshDisplay();
    }
    delay(700);
  }

}

void loop() {      
  int state = digitalRead(button);



  if (state==LOW){
    while(state==LOW){
      state = digitalRead(button);
    }
    

    digitalWrite(red,LOW);  
    digitalWrite(yellow,HIGH);
    delay(100);
    int waitTime=1000*random(2,11);


    do {
      state = digitalRead(button);
      delay(50);
      waitTime-=50;
      
    } while(waitTime>0 && state==HIGH);


    if (state==LOW){
      for (int i=0;i<5;i++){
        digitalWrite(yellow,HIGH);
        delay(500);
  
        digitalWrite(yellow,LOW);
        delay(500);
      }

    } else {
      digitalWrite(green,HIGH);
      digitalWrite(yellow,LOW);
      stopwatch();
      digitalWrite(red,HIGH);

    } 
  }  
}
