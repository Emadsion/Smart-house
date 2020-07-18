
#include<LiquidCrystal.h>
#define  led 8
#include <Servo.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
Servo myservo; 

int c1 = 10, c2 = 11, c3 = 12;
int r1 = A0, r2 = A1, r3 = A2, r4 = A3;
char Storepass[]="123";
int i=0,j,count=0, del = 600;
int number=sizeof(Storepass)-1;
char pass[sizeof(Storepass)-1];
char key;
int p=0;


void setup() {
 Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Enter Password  ");
  delay(1000);
  lcd.setCursor(0, 1);

 pinMode(led,OUTPUT);
  pinMode(c1, INPUT_PULLUP);
  pinMode(c2, INPUT_PULLUP);
  pinMode(c3, INPUT_PULLUP);
  
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);
  
 myservo.attach(9);
 myservo.write(0);
  
}

void loop() {
  
 // if (p==1)
 // Serial.print('1');
  
 key='l';
 
  row1();
  
  row2();
  
  row3();
  
  row4();
  


  
if (key!='l' && key != '#')
{
 
  pass[i]=key;
   lcd.print('*');
  i++;
}
else if (key == '#')
{
  if (i == number)
  {
    for (int j=0;j<number;j++)
    {
      if(pass[j]==Storepass[j])
      count++;
    }
    if (count==number)
   { bravo();}
    else 
    {no();}
  }
   else no();
}
else if (key ='l')
{
  
}
if(Serial.available())
{
  
  if (Serial.read()=='0')
  startover();
}
}




void row1() {
  
  digitalWrite(r1, LOW);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, HIGH);
  digitalWrite(r4, HIGH);

 
  if (digitalRead(c1) == LOW) {
    key='1';
    
    delay(del);
  }
  else if (digitalRead(c2) == LOW) {
    key='2';
     
    delay(del);
  }
  else if (digitalRead(c3) == LOW) {
    key='3';
     
    delay(del);
  }

}

void row2() {
  digitalWrite(r1, HIGH);
  digitalWrite(r2, LOW);
  digitalWrite(r3, HIGH);
  digitalWrite(r4, HIGH);

  if (digitalRead(c1) == LOW) {
    key='4';
     
    delay(del);
  }
  else if (digitalRead(c2) == LOW) {
    key='5';
     
    delay(del);
  }
  else if (digitalRead(c3) == LOW) {
     key='6';
     
     delay(del);
  }
}

void row3() {
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, LOW);
  digitalWrite(r4, HIGH);

  if (digitalRead(c1) == LOW) {
     key='7';
     
     delay(del);
  }
  else if (digitalRead(c2) == LOW) {
     key='8';
     
     delay(del);
  }
  else if (digitalRead(c3) == LOW) {
     key='9';
     delay(del);
  }
}
void row4() {
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, HIGH);
  digitalWrite(r4, LOW);

  if (digitalRead(c1) == LOW) {
    key='*';
    delay(del);
  }
  else if (digitalRead(c2) == LOW) {
    key='0';
      
    delay(del);
  }
  else if (digitalRead(c3) == LOW) {
    key='#';
      
    delay(del);
  }
}


void bravo()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome Maged   ");
  delay(500);
  digitalWrite(led, HIGH);
   myservo.write(90);
   Serial.print('1');
   
 
   
  
}
void no() 
{
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Wrong password  ");
  delay(2000);
  i=0;
  count=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter password: ");
  lcd.setCursor(0,1);
}

void startover()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter password  ");
   i=0;
  count=0;
  p=0;
  delay(300);
  myservo.write(0);
  digitalWrite(led,LOW);
  lcd.setCursor(0,1);
  Serial.write("mamamia");
}
