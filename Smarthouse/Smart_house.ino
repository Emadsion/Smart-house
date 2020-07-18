//Shift register
#define SER 7
#define LATCH 8
#define CLK 6
//7-segment
#define D1 10
#define D2 11
#define D3 12
#define D4 13
int v1,v2,v3,v4;
byte seg[]={B11111100,B01100000,B11011010,B11110010,B01100110,B10110110,B10111110,B11100000,B11111110,B11100110};
//LIGHT SYSTEM
#define LDR A0
#define relay 5

#define motor 9
#define encoder 2
#define buz 4
#define LM35 A1

#define lock 3
int x=0;
char loc,start;
int r,rpm, L,temp=0;
volatile int count=0;
unsigned long _time=0;
float volt=0;

void setup() {
  //pinmode of shift registers
  pinMode(SER,OUTPUT);
  pinMode(LATCH,OUTPUT);
  pinMode(CLK,OUTPUT);
  
//pinmode of 7-segment
   pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  
  //pinmode of air conditionning (encoder,fan/motor,buzzer and LM35)
 pinMode(encoder,INPUT_PULLUP);
 pinMode(motor,OUTPUT);
  pinMode(buz,OUTPUT);
  pinMode(LM35,INPUT);
  
 //Pinmode of ligh system(LDR,relay)
   pinMode(relay,OUTPUT);
     pinMode(LDR,INPUT);
     
     //pinmode of lock button
      pinMode(lock,INPUT);
      
      attachInterrupt(digitalPinToInterrupt(encoder),ticks,FALLING);
  Serial.begin(9600);
  digitalWrite(LATCH,LOW);
}

void loop() {
  
if (Serial.read()=='1')
x=1;
if(x==1)
  {
    
     volt=analogRead(LM35);
     volt=(5.0/1023)* volt;
     temp= volt/0.01;
     
     L = analogRead(LDR);
  
  
//LIGHTS
    if(L > 600)
    {
      digitalWrite(relay,LOW);
    }
    else if (L < 400)
    {
      digitalWrite(relay,HIGH);
    }
    
//Tempreture
    if(temp <15)
    { 
      analogWrite(motor,LOW);
    }
else if (temp>=15 && temp<25)
{
analogWrite(motor,20);
  }
  else if(temp>=25 && temp<35)
  {  
    analogWrite(motor,40);
  }
  else if (temp>=35 && temp<45)
  {
    digitalWrite(buz,LOW);
    analogWrite(motor,60);
  }
  else if (temp>=45)
 {
  digitalWrite(buz,HIGH);
 analogWrite(motor,60);
 }
 //ENCODER
  if (millis()-_time>=1000)
  {
rpm=(count*60)/24;
count=0;
 _time=millis();
}

//Shiftregister&7segment
v1=rpm/1000;
v2=(rpm/100)%10;
v3=(rpm/10)%10;
v4=rpm%10;



 shiftOut(SER,CLK,LSBFIRST,seg[v1]);
 digitalWrite(D1,LOW);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,HIGH);
  store();
 

 

 shiftOut(SER,CLK,LSBFIRST,seg[v3]);
 digitalWrite(D1,HIGH);
  digitalWrite(D2,LOW);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,HIGH);
   store();

shiftOut(SER,CLK,LSBFIRST,seg[v4]);
 digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,LOW);
  digitalWrite(D4,HIGH);
 
 store();


 shiftOut(SER,CLK,LSBFIRST,seg[v2]);
  digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,LOW);
 store();
 
  }

loc=digitalRead(lock);
if(loc==0)
{
Serial.print('0');
x=0;
low();
delay(300);
}
}

void low()
{
 digitalWrite(D1,HIGH);
 digitalWrite(D2,HIGH);
 digitalWrite(D3,HIGH);
 digitalWrite(D4,HIGH);
 shiftOut(SER,CLK,LSBFIRST,B00000000);
  digitalWrite(relay,LOW);
   digitalWrite(buz,LOW);
  digitalWrite(motor,LOW);
  
  
}
void ticks()
{
  count++;
}
void store() {
  digitalWrite(LATCH,HIGH);
  delayMicroseconds(10);
  digitalWrite(LATCH,LOW);
   delayMicroseconds(10);
}
