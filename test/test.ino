#include <Wire.h> 
#include <Keypad.h>
#include <virtuabotixRTC.h>
#include <LiquidCrystal_I2C.h>

#define door_contact   2
#define motor          A0
#define fan            A1
#define uv_light       A2
#define cab_light      A3


LiquidCrystal_I2C lcd(0x27,16,2);

const byte ROWS = 4; 
const byte COLS = 4; 

int i1,i2,i3,i4;
int N_year,N_month,N_day,N_hour,N_minutes,N_seconds;
int S_hour,S_minutes,S_seconds;

char c1,c2,c3,c4;
char keypressed;

char hexaKeys[ROWS][COLS]= 
{
  {'1', '2', '3', 'A'}, 
  {'4', '5', '6', 'B'}, 
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {10, 9, 8, 7}; 
byte colPins[COLS] = {6, 5, 4, 3}; 

bool Auto = false;

virtuabotixRTC myRTC(13, 12, 11); // CLK,DAT,RST

Keypad myKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void Door()
{
  return;
  }
void setup() {
  Serial.begin(9600);
  
  pinMode(motor, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(uv_light, OUTPUT);
  pinMode(cab_light, OUTPUT);
  pinMode(door_contact, INPUT);
  
  digitalWrite(motor,LOW);
  digitalWrite(fan,LOW);
  digitalWrite(uv_light,LOW);
  digitalWrite(cab_light,LOW);
   
  attachInterrupt (digitalPinToInterrupt(0), Door, HIGH);//interrupt ---D2
  lcd.init();
  lcd.backlight();
  lcd.home ();
  delay(100);
  Set_time();
  Set_Scheduled_time();
}

void loop() {

  
  while(keypressed == NO_KEY){
  keypressed = myKeypad.getKey();
  lcd.clear();
  myRTC.updateTime();
  lcd.setCursor(0,0);
  lcd.print(myRTC.dayofmonth);
  lcd.print("/");
  lcd.print(myRTC.month);
  lcd.print("/");
  lcd.print(myRTC.year);
  lcd.setCursor(0,1);
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  lcd.print(":");
  lcd.print(myRTC.seconds);
  delay(100);
  }
  if(digitalRead(door_contact) == HIGH)
  {
    digitalWrite(cab_light,LOW);
     /*********** 模式A 自动模式*******************/
     if (keypressed == 'A')
     {
        lcd.clear();
        lcd.print("Mode  A");
        delay(100);
        if(myKeypad.waitForKey() == '#')
        {
          Auto = true;
          }
        keypressed == NO_KEY;
      }
     /*********** 模式B 设置排定时间*******************/
     if (keypressed == 'B')
     {
        lcd.clear();
        lcd.print("Mode  B");
        delay(100);
        if(myKeypad.waitForKey() == '#')
        {
          Auto = false;
          Set_Scheduled_time();
          }
        keypressed == NO_KEY;
      }
     /*********** 模式C 手动模式*******************/
     if (keypressed == 'C')
     {
        lcd.clear();
        lcd.print("Mode  C");
        delay(100);
        if(myKeypad.waitForKey() == '#')
        {
          Auto = false;
          function();  
          }
        keypressed == NO_KEY;
      }
     /*********** 模式D 设置时间*******************/
     if (keypressed == 'D')
     {
        lcd.clear();
        lcd.print("Mode  D");
        delay(100);
        if(myKeypad.waitForKey() == '#')
        {
          Auto = false;
          Set_time();
          }
        keypressed == NO_KEY;
      }

   if(Auto == true)
   {
    if((S_hour - myRTC.hours) == 0)
    {
      if((S_minutes - myRTC.minutes) == 0)
      {
        if((S_seconds - myRTC.seconds) == 0)
        {
          function();
          }
        }
      }
    }
  }
  else
  {
    digitalWrite(cab_light,HIGH);
  }
}
void function()
{
  digitalWrite(motor,HIGH);
  delay(60000);
  digitalWrite(motor,LOW);
  delay(60000);
  digitalWrite(fan,HIGH);
  delay(60000);
  digitalWrite(fan,LOW);
  delay(60000);
  digitalWrite(uv_light,HIGH);
  delay(300000);
  digitalWrite(uv_light,LOW);
  }
void Set_time()
{
  /***********************设置时间***********************/
    lcd.clear();
    lcd.print("     Setup");
    delay(1000);
    lcd.clear();
    lcd.print("Setup year");
    char keypressed2 = myKeypad.waitForKey();  
      if (keypressed2 != NO_KEY && keypressed2 !='*' && keypressed2 !='#' && keypressed2 !='A' && keypressed2 !='B' && keypressed2 !='C' && keypressed2 !='D' )
      {
         c1 = keypressed2;
         lcd.setCursor(0, 1);
         lcd.print(c1);
       }
    char keypressed3 = myKeypad.waitForKey();
      if (keypressed3 != NO_KEY && keypressed3 !='*' && keypressed3 !='#' && keypressed3 !='A' && keypressed3 !='B' && keypressed3 !='C' && keypressed3 !='D' )
      {
         c2 = keypressed3;
         lcd.setCursor(1, 1);
         lcd.print(c2);
       }
     char keypressed4 = myKeypad.waitForKey();
       if (keypressed4 != NO_KEY && keypressed4 !='*' && keypressed4 !='#' && keypressed4 !='A' && keypressed4 !='B' && keypressed4 !='C' && keypressed4 !='D' )
      {
         c3 = keypressed4;
         lcd.setCursor(2, 1);
         lcd.print(c3);
       }
     char keypressed5 = myKeypad.waitForKey();
      if (keypressed5 != NO_KEY && keypressed5 !='*' && keypressed5 !='#' && keypressed5 !='A' && keypressed5 !='B' && keypressed5 !='C' && keypressed5 !='D' )
      {  
         c4 = keypressed5;
         lcd.setCursor(3, 1);
         lcd.print(c4);
       }

       i1=(c1-48)*1000;
       i2=(c2-48)*100;
       i3=(c3-48)*10;
       i4=c4-48;
       N_year=i1+i2+i3+i4;
       delay(500);
       lcd.clear();
       lcd.print("Setup month");

       char keypressed6 = myKeypad.waitForKey();  
        if (keypressed6 != NO_KEY && keypressed6 !='*' && keypressed6 !='#' && keypressed6 !='A' && keypressed6 !='B' && keypressed6 !='C' && keypressed6 !='D' )
        {
           c1 = keypressed6;
           lcd.setCursor(0, 1);
           lcd.print(c1);
         }
      char   keypressed7 = myKeypad.waitForKey();
       if (keypressed7 != NO_KEY && keypressed7 !='*' && keypressed7 !='#' && keypressed7 !='A' && keypressed7 !='B' && keypressed7 !='C' && keypressed7 !='D' )
      {
         c2 = keypressed7;
         lcd.setCursor(1, 1);
         lcd.print(c2);
       }


       i1=(c1-48)*10;
       i2=c2-48;
       N_month=i1+i2;
       delay(500);

       lcd.clear();
       lcd.print("Setup Day");
                   
       char keypressed8 = myKeypad.waitForKey();
        if (keypressed8 != NO_KEY && keypressed8 !='*' && keypressed8 !='#' && keypressed8 !='A' && keypressed8 !='B' && keypressed8 !='C' && keypressed8 !='D' )
        {
           c1 = keypressed8;
           lcd.setCursor(0, 1);
           lcd.print(c1);
         }
       char keypressed9 = myKeypad.waitForKey();
        if (keypressed9 != NO_KEY && keypressed9 !='*' && keypressed9 !='#' && keypressed9 !='A' && keypressed9 !='B' && keypressed9 !='C' && keypressed9 !='D' )
        {
           c2 = keypressed9;
           lcd.setCursor(1, 1);
           lcd.print(c2);
         }


       i1=(c1-48)*10;
       i2=c2-48;
       N_day=i1+i2;
       delay(500);
       lcd.clear();
       lcd.print("Setup hour");                    
       char keypressed10 = myKeypad.waitForKey();
       if (keypressed10 != NO_KEY && keypressed10 !='*' && keypressed10 !='#' && keypressed10 !='A' && keypressed10 !='B' && keypressed10 !='C' && keypressed10 !='D' )
        {
         c1 = keypressed10;
         lcd.setCursor(0, 1);
         lcd.print(c1);
         }
      char   keypressed11 = myKeypad.waitForKey();
      if (keypressed11 != NO_KEY && keypressed11 !='*' && keypressed11 !='#' && keypressed11 !='A' && keypressed11 !='B' && keypressed11 !='C' && keypressed11 !='D' )
        {
          c2 = keypressed11;
         lcd.setCursor(1, 1);
         lcd.print(c2);
         }
       i1=(c1-48)*10;
       i2=c2-48;
        N_hour=i1+i2;
        delay(500);
       lcd.clear();
       lcd.print("Setup minutes");
      char keypressed12 = myKeypad.waitForKey();
      if (keypressed12 != NO_KEY && keypressed12 !='*' && keypressed12 !='#' && keypressed12 !='A' && keypressed12 !='B' && keypressed12 !='C' && keypressed12 !='D' )
        {
           c1 = keypressed12;
           lcd.setCursor(0, 1);
           lcd.print(c1);
         }
     char keypressed13 = myKeypad.waitForKey();
      if (keypressed13 != NO_KEY && keypressed13 !='*' && keypressed13 !='#' && keypressed13 !='A' && keypressed13 !='B' && keypressed13 !='C' && keypressed13 !='D' )
        {
           c2 = keypressed13;
           lcd.setCursor(1, 1);
           lcd.print(c2);
         }
       i1=(c1-48)*10;
       i2=c2-48;
        N_minutes=i1+i2;
        delay(500);
       lcd.clear();
       lcd.print("Setup seconds");
      char keypressed14 = myKeypad.waitForKey();
       if (keypressed14 != NO_KEY && keypressed14 !='*' && keypressed14 !='#' && keypressed14 !='A' && keypressed14 !='B' && keypressed14 !='C' && keypressed14 !='D' )
        {
          c1 = keypressed14;
          lcd.setCursor(0, 1);
          lcd.print(c1);
         }
      char keypressed15 = myKeypad.waitForKey();
       if (keypressed15 != NO_KEY && keypressed15 !='*' && keypressed15 !='#' && keypressed15 !='A' && keypressed15 !='B' && keypressed15 !='C' && keypressed15 !='D' )
        {
           c2 = keypressed15;
           lcd.setCursor(1, 1);
           lcd.print(c2);
         }
       i1=(c1-48)*10;
       i2=c2-48;
       N_seconds=i1+i2;
       delay(500);
       lcd.clear();


  }
void Set_Scheduled_time()
{
  /***********************设定排定时间***********************/
       lcd.clear();
       lcd.print("Scheduled hou");                    
       char keypressed16 = myKeypad.waitForKey();
       if (keypressed16 != NO_KEY && keypressed16 !='*' && keypressed16 !='#' && keypressed16 !='A' && keypressed16 !='B' && keypressed16 !='C' && keypressed16 !='D' )
        {
         c1 = keypressed16;
         lcd.setCursor(0, 1);
         lcd.print(c1);
         }
      char   keypressed17 = myKeypad.waitForKey();
      if (keypressed17 != NO_KEY && keypressed17 !='*' && keypressed17 !='#' && keypressed17 !='A' && keypressed17 !='B' && keypressed17 !='C' && keypressed17 !='D' )
        {
          c2 = keypressed17;
         lcd.setCursor(1, 1);
         lcd.print(c2);
         }
        i1=(c1-48)*10;
        i2=c2-48;
        S_hour=i1+i2;
        delay(500);
        lcd.clear();
        lcd.print("Scheduled min");
      char keypressed18 = myKeypad.waitForKey();
      if (keypressed18 != NO_KEY && keypressed18 !='*' && keypressed18 !='#' && keypressed18 !='A' && keypressed18 !='B' && keypressed18 !='C' && keypressed18 !='D' )
        {
           c1 = keypressed18;
           lcd.setCursor(0, 1);
           lcd.print(c1);
         }
     char keypressed19 = myKeypad.waitForKey();
      if (keypressed19 != NO_KEY && keypressed19 !='*' && keypressed19 !='#' && keypressed19 !='A' && keypressed19 !='B' && keypressed19 !='C' && keypressed19 !='D' )
        {
           c2 = keypressed19;
           lcd.setCursor(1, 1);
           lcd.print(c2);
         }
       i1=(c1-48)*10;
       i2=c2-48;
       S_minutes=i1+i2;
       delay(500);
       lcd.clear();
       lcd.print("Scheduled sec");
      char keypressed20 = myKeypad.waitForKey();
       if (keypressed20 != NO_KEY && keypressed20 !='*' && keypressed20 !='#' && keypressed20 !='A' && keypressed20 !='B' && keypressed20 !='C' && keypressed20 !='D' )
        {
          c1 = keypressed20;
          lcd.setCursor(0, 1);
          lcd.print(c1);
         }
      char keypressed21 = myKeypad.waitForKey();
       if (keypressed21 != NO_KEY && keypressed21 !='*' && keypressed21 !='#' && keypressed21 !='A' && keypressed21 !='B' && keypressed21 !='C' && keypressed21 !='D' )
        {
           c2 = keypressed21;
           lcd.setCursor(1, 1);
           lcd.print(c2);
         }
       i1=(c1-48)*10;
       i2=c2-48;
       S_seconds=i1+i2;
       delay(500);
       lcd.clear();
  }
