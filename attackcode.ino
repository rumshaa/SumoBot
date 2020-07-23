//Variables
#define LA 11    //Motor
#define LB 10    //Apply on ` pins 
#define RA 8    //Only those can do PWM
#define RB 9
#define Echo 12  //Ultrasonic Sensor
#define Trig 13
#define color A0 //Color detect

unsigned long time_1;
unsigned long time_2;
int c;
long duration;
int distance;
int len;
int counter;
bool found;

//Functions
void Forward(){
    analogWrite(LA,255);  //Remeber analogWrite can go to 255
    analogWrite(LB,0);
    analogWrite(RA,255);
    analogWrite(RB,0);
    Serial.println("going forward");
  }//Makes it go forward

void Backwards(){
    analogWrite(LA,0);
    analogWrite(LB,255);
    analogWrite(RA,0);
    analogWrite(RB,255);
    Serial.println("Turing backwards");
  }//Makes it go backwards

void turnRevR(){
  analogWrite(LA,0);
  analogWrite(LB,255);
  analogWrite(RA,255);
  analogWrite(RB,0);
  Serial.println("Turing right");
}//Makes it go backwards and to the right

void turnRevL(){
  analogWrite(LA,255);
  analogWrite(LB,0);
  analogWrite(RA,0);
  analogWrite(RB,255);
  Serial.println("Turing left");
}//Makes it go backwards and to the right

int Distance(){
    digitalWrite(Trig,LOW);
    delayMicroseconds(2);
    digitalWrite(Trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig,LOW);
    duration = pulseIn(Echo, HIGH);
    distance = duration*0.034/2;
    return distance;
  }//Finds the distance of empty space

void detectEnemy(){
    len = Distance();
    found=false;
    c = analogRead(color);
    
    while (c<200){
      c = analogRead(color);
      Backwards();
      delay(50);  //Placeholder values 50
      turnRevR;
      delay(50); 
      
    }
    
    if(len<10){
        Forward();
      }
    else{
      
        time_1 = millis();
        turnRevR();

        while(millis() - time_1 < 1000){ //if u find it lunge
          len = Distance();
          if(len<10){
              Forward();
              found=true;
              return;
       
          }
        }
      //  if (found==true){
        //  return;
       // }
        time_1 = millis();
        turnRevL();
        while(millis() - time_1 < 2000){
          len = Distance();
          if(len<10){
              Forward();
              return;
            
        }
      }
    }
  }//Continues to rotate until the enemy is found

void detectLine(){
    c = analogRead(color);
    if(c<200){
      Backwards();
      delay(50);  //Placeholder values 50
      turnRevR;
      delay(50);  //Change to make better 50
      //Forward();
    }
    //else{
      //detectEnemy();
    //}
  }//detects the line and gets out of danger

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  //counter = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(Distance());
  //Forward();
  //detectLine();
  //detectEnemy();
  //detectEnemy();
  //Serial.println(analogRead(color));
  Forward();
  //turnRevR();
}
