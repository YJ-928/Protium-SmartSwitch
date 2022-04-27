#include<stdio.h>
// Analog Input
const int ldrpin     = A0 ; // LDR Sensor ip A0
// Digital Inputs
const int firepin    = 23 ; // Fire/Flame Sensor ip
const int switch4    = 37 ; // IR Switch 4 FAN ip
const int switch3    = 35 ; // IR Switch 3 LED3 ip
const int switch2    = 25 ; // IR Switch 2 LED2 ip
const int switch1    = 39 ; // IR Switch 1 LED1 ip

// Digital Outputs to Switch Buzzers and Leds
const int buzz       = 41 ; // Buzzer Output
const int redledbuzz = 43 ; // RedLED plus BOTH Buzzers OP
const int greenled   = 45 ; // GREENLED OP
const int blueled    = 47 ; // BLUELED OP
const int yellowled  = 49 ; // YELLOW OP

// Digital Outputs to Transistors
const int trans1     = 27 ; // Op to Transistor 1
const int trans2     = 29 ; // Op to Transistor 2
const int trans3     = 31 ; // Op to Transistor 3
const int trans4     = 33 ; // Op to Transistor 4

// Communication pins
const int c_led1          = 38 ; //MQTT connection to control LED1 D1
const int c_led2          = 40 ; //MQTT connection to control LED2 D2
const int c_led3          = 42 ; //MQTT connection to control LED3 D3
const int c_fan           = 44 ; //MQTT connection to control FAN D4
const int c_net_connected = 46 ; //To check if BLYNK/IFFFT is connected D5
const int c_web_active    = 48 ; //To check if MQTT website is connected D6

// Temp Variable for Storing values
int c_l1 = 1 , c_l2 = 1, c_l3= 1, c_f= 1 , c_n1 , c_n2, c_tl1 ,c_tl2 ,c_tl3 ,c_tf;

// Essential variables
int val1,val2,val3,val4,val5,val6 ,val7;
int led1=1 , led2=1, led3 =1, fan =1;

//Global Variable For Enabling BLYNK
int web_Access = 0;
//Global Variable for Automate and Reset
int automate = 0, R1 = 0, R2 =0;


// Function that beeps the buzzer for 1 second
void firealarm(void)
{
  digitalWrite(redledbuzz , HIGH);
  delay(300);
  digitalWrite(buzz , HIGH);
  digitalWrite(redledbuzz , LOW);
  delay(300);
  digitalWrite(buzz , LOW);
}

void Automate(int mode)
{
  if(mode == 1)
  {
    digitalWrite(trans1,HIGH);
    digitalWrite(trans2,HIGH);
    digitalWrite(trans3,HIGH);
  }
  if(mode == 0){
    digitalWrite(trans1,LOW);
    digitalWrite(trans2,LOW);
    digitalWrite(trans3,LOW);
  }
}

void Reset()
{   if(R1!=R2){
    digitalWrite(trans1,LOW);
    digitalWrite(trans2,LOW);
    digitalWrite(trans3,LOW);
    R2 = R1 ;
    }
    
}

// Function to change led state and update led variable
void change_state(int n)
{
  switch(n)
  {
   case 1:
       if(led1 == LOW){
          digitalWrite(trans1 , HIGH);
          led1 = HIGH;}
        else{
          digitalWrite(trans1 , LOW);
          led1 = LOW;}
         Serial.println(led1); 
    break;
    case 2:
       if(led2 == 0){
          digitalWrite(trans2 , HIGH);
          led2 = 1;}
        else{
          digitalWrite(trans2 , LOW);
          led2 = 0;}
    break;
    case 3:
       if(led3 == 0){
          digitalWrite(trans3 , HIGH);
          led3 = 1;}
        else{
          digitalWrite(trans3 , LOW);
          led3 = 0;}
    break;
    case 4:
       if(fan == 0){
          digitalWrite(trans4 , HIGH);
          fan = 1;}
        else{
          digitalWrite(trans4 , LOW);
          fan = 0;}
    break;

    default:
    Serial.println(">>[change_state()] INVALID INPUT ! ");
  }
}

void setup()
{
  Serial.begin(115200);
  
  pinMode(redledbuzz, OUTPUT);  // for fire alarm
  pinMode(buzz, OUTPUT);
  pinMode(greenled, OUTPUT);    // When Smart Switch is connected to Device(Room)
  pinMode(blueled, OUTPUT);     // For MQTT connection success
  pinMode(yellowled, OUTPUT);   // For BLYNK connection success
  pinMode(trans1, OUTPUT);
  pinMode(trans2, OUTPUT);
  pinMode(trans3, OUTPUT);
  pinMode(trans4, OUTPUT);

  pinMode(firepin,INPUT);
  pinMode(ldrpin, INPUT);
  pinMode(switch1,INPUT);
  pinMode(switch2,INPUT);
  pinMode(switch3,INPUT);
  pinMode(switch4,INPUT);

  pinMode(c_led1,INPUT);
  pinMode(c_led2,INPUT);
  pinMode(c_led3,INPUT);
  pinMode(c_fan,INPUT);
  pinMode(c_net_connected,INPUT);
  pinMode(c_web_active,INPUT);
  

  //Serial.println("Initializing NODEMCU Pins");
  c_tl1 = digitalRead(c_led1);
  //Serial.println(c_tl1);
  c_tl2 = digitalRead(c_led2);
  //Serial.println(c_tl2);
  c_tl3 = digitalRead(c_led3);
  //Serial.println(c_tl3);
  c_tf  = digitalRead(c_fan);
  //Serial.println(c_tf);

  digitalWrite(yellowled , HIGH);
  delay(1000);
  digitalWrite(blueled , HIGH);
  delay(1000);
  digitalWrite(greenled , HIGH);
  delay(1000);
  digitalWrite(redledbuzz , HIGH);
  delay(300);
  digitalWrite(buzz , HIGH);
  delay(300);
  
  digitalWrite(yellowled , LOW);
  digitalWrite(blueled , LOW);
  digitalWrite(greenled , LOW);
  digitalWrite(redledbuzz , LOW);
  digitalWrite(buzz , LOW);

  delay(1000);
  digitalWrite(yellowled , HIGH);
}

void loop()
{  
  // If fire detected, the device will stop operating and all the lights will be static
  val6 = digitalRead(firepin);
  while(val6 == LOW){
    firealarm();
    digitalWrite(greenled ,LOW);
    digitalWrite(blueled , LOW);
    digitalWrite(yellowled,LOW);
    digitalWrite(trans1 , LOW);
    digitalWrite(trans2 , LOW);
    digitalWrite(trans3 , LOW);
    digitalWrite(trans4 , LOW);
    val6 = digitalRead(firepin);
  }
  digitalWrite(yellowled,HIGH);
  val7 = analogRead(ldrpin);
  if (automate == 1){
    if(val7>500)
    Automate(1);
    else{
    Automate(0);
    if(R1 == 1)
    R1 =0;
    else
    R1 =1;
    }
  }
  //Serial.println(val7);
  //Serial.println("Read IR sensors");
  val1 = digitalRead(switch1);
  //Serial.println(val1);
  val2 = digitalRead(switch2);
  //Serial.println(val2);
  val3 = digitalRead(switch3);
  //Serial.println(val3);
  val4 = digitalRead(switch4);
  //Serial.println(val4);

  // Read analog value when asked for automation
  
  // Code for ldr controls

  // Operatings trans using IR sensors
  if (val1 == LOW){
    change_state(1);
    Serial.println(">>[Arduino] LED1 State is Toggled.");
    while(val1 == LOW){
      val1 = digitalRead(switch1);
      //Serial.print(val1);
    }
      
  }
  if (val2 == LOW){
    change_state(2);
    Serial.println(">>[Arduino] LED2 State is Toggled.");
    while(val2 == LOW)
      {
      val2 = digitalRead(switch2);
      //Serial.print(val2);
    }
  }
  if (val3 == LOW){
    change_state(3);
    Serial.println(">>[Arduino] LED3 State is Toggled.");
    while(val3 == LOW)
      {
      val3 = digitalRead(switch3);
     // Serial.print(val3);
    }
  }
  if (val4 == LOW){
    change_state(4);
    Serial.println(">>[Arduino] FAN State is Toggled.");
    while(val4 == LOW)
      {
      val4 = digitalRead(switch4);
      // Serial.print(val4);
    }
  }

  // Listen to communication pins and alter variables
  // Turn on blue led if mqtt connection to net is successful

  // Reading NODEMCU_Values
  //Serial.println("Initializing NODEMCU Pins");
  c_tl1 = digitalRead(c_led1);
  //Serial.println(c_tl1);
  c_tl2 = digitalRead(c_led2);
  //Serial.println(c_tl2);
  c_tl3 = digitalRead(c_led3);
  //Serial.println(c_tl3);
  c_tf  = digitalRead(c_fan);
  //Serial.println(c_tf);


  c_n1 = digitalRead(c_net_connected);
  c_n2 = digitalRead(c_web_active);
  //Serial.println(c_n1);
  if (c_n1 == HIGH){
    digitalWrite(greenled, HIGH);
    web_Access = 1;
    //Serial.println("BLYNK CONNECTED ");
    }
  else{
    digitalWrite(greenled, LOW);
    web_Access = 0;
    }
  if (web_Access == 1)
    {
      // Turn on green led if someone has opened the website
      if(c_n2 == HIGH){
        automate = 1;
        digitalWrite(blueled,HIGH);}
      else{
        automate = 0;
        digitalWrite(blueled, LOW);
        }
    
      // If communication pin is toggled, operate the trans
      if (c_tl1 != c_l1){
        c_l1 = c_tl1;
        //Serial.println(c_l1);
        change_state(1);
        Serial.println(">>[NodeMCU] LED1 state is Toggled.");
      }
      if (c_tl2 != c_l2){
        c_l2 = c_tl2;
        //Serial.println(c_l2);
        change_state(2);
        Serial.println(">>[NodeMCU] LED2 state is Toggled.");
      }
      if (c_tl3 != c_l3){
        c_l3 = c_tl3;
        //Serial.println(c_l3);
        change_state(3);
        Serial.println(">>[NodeMCU] LED3 state is Toggled.");
      }
      if (c_tf != c_f){
        c_f = c_tf;
        //Serial.println(c_tf);
        change_state(4);
        Serial.println(">>[NodeMCU] FAN state is Toggled.");
      }
    }
}
