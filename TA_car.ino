const int leftNearinfrared = A4;
const int rightNearinfrared = A3;
const int leftBlackmark = A2;
const int rightBlackmark = A0;
#define leftMotorPWM  5
#define leftMotorGND  6
#define rightMotorPWM  9
#define rightMotorGND  10

#define left 0
#define right 1

void nearinfraredInit();
boolean leftNearInfraredTest();
boolean rightNearInfraredTest();
boolean nearInfraredTest(char dir);

void blackmarkInit();
boolean leftblackmarkTest();
boolean rightblackmarkTest();
boolean blackmarkTest(char dir);

void motorInit();
void leftMotorRun(int leftspeed);
void rightMotorRun(int rightspeed);
void motorRun(int leftspeed,int rightspeed);

void followBlackBelt();

void setup() {
  // put your setup code here, to run once:
  motorInit();
  nearinfraredInit();
  blackmarkInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  //TTL型  非触发为高电平，触发为低电平
//  motorRun(-150,150);//100的速度较慢

if(nearInfraredTest(left) && nearInfraredTest(right)){//both 
  motorRun(0,0);
}
else if((!nearInfraredTest(left)) && nearInfraredTest(right)){//left no trig and right trig,turn left
   motorRun(-100,180);
}
else if(nearInfraredTest(left) && (!nearInfraredTest(right))){//left trig and right no trig,turn right
  motorRun(180,-100);
}
else if((!nearInfraredTest(left)) && (!nearInfraredTest(right))){
  followBlackBelt();
}
else{
  motorRun(0,0);
}


//followBlackBelt();


//  if(nearInfraredTest(left)){
//     motorRun(150,0);
//  }
//  else{
//    motorRun(0,150);
//  }
  
//  digitalWrite(led,HIGH);//LED亮
//  delay(500);
//  digitalWrite(led,LOW);
//  delay(500);
}
//-------------------------近红外------------------------
void nearinfraredInit(){
  pinMode(leftNearinfrared,INPUT);
  pinMode(rightNearinfrared,INPUT);
}

boolean leftNearInfraredTest(){
  if(digitalRead(leftNearinfrared) == LOW)//如果检测到遮挡
  {
    return true;
    }
  if(digitalRead(leftNearinfrared) == HIGH)
   {
    return false;
    }
}

boolean rightNearInfraredTest(){
  if(digitalRead(rightNearinfrared) == LOW)//如果检测到遮挡
  {
    return true;
    }
  if(digitalRead(rightNearinfrared) == HIGH)
   {
    return false;
    }
}

boolean nearInfraredTest(char dir){
  if(dir == left)
  return leftNearInfraredTest();
  if(dir == right)
  return rightNearInfraredTest();
}

//-------------黑标-----------------------------------------
void blackmarkInit(){
  pinMode(leftBlackmark,INPUT);
  pinMode(rightBlackmark,INPUT);
}

boolean leftblackmarkTest(){
  if(digitalRead(leftBlackmark) == LOW)//如果检测到褐色
  {
    return true;
    }
  if(digitalRead(leftBlackmark) == HIGH)
   {
    return false;
    }
}

boolean rightblackmarkTest(){
  if(digitalRead(rightBlackmark) == LOW)//如果检测到褐色
  {
    return true;
    }
  if(digitalRead(rightBlackmark) == HIGH)
   {
    return false;
    }
}

boolean blackmarkTest(char dir){
  if(dir == left)
  return leftblackmarkTest();
  if(dir == right)
  return rightblackmarkTest();
}

//--------------------------电机-------------------------
void motorInit(){
  pinMode(leftMotorPWM,OUTPUT);
  pinMode(leftMotorGND,OUTPUT);
  pinMode(rightMotorPWM,OUTPUT);
  pinMode(rightMotorGND,OUTPUT);

  analogWrite(leftMotorPWM,0);
  analogWrite(leftMotorGND,0);

  analogWrite(rightMotorPWM,0);
  analogWrite(rightMotorGND,0);
}

void leftMotorRun(int leftspeed)
{
  if(leftspeed>=0)
  {
    analogWrite(leftMotorPWM,leftspeed);
    analogWrite(leftMotorGND,0);
  }
  else
  {
    leftspeed = abs(leftspeed);
    analogWrite(leftMotorGND,leftspeed);
    analogWrite(leftMotorPWM,0);
  }
}

void rightMotorRun(int rightspeed)
{
  if(rightspeed>=0)
  {
    analogWrite(rightMotorPWM,rightspeed);
    analogWrite(rightMotorGND,0);
  }
  else
  {
    rightspeed = abs(rightspeed);
    analogWrite(rightMotorGND,rightspeed);
    analogWrite(rightMotorPWM,0);
  }
}

void motorRun(int leftspeed,int rightspeed){
  leftMotorRun(leftspeed);
  rightMotorRun(rightspeed);
}

//----------------------follow black belt----------------------------
void followBlackBelt(){
    if(blackmarkTest(left)&&(!blackmarkTest(right))){//左边黑标触发--往右偏
    motorRun(-220,220);//v_left<v_right
  }
  else if(blackmarkTest(right)&&(!blackmarkTest(left))){//右边黑标触发--往左偏
    motorRun(220,-220);//v_left>v_right
  }
  else if((!blackmarkTest(left))&&(!blackmarkTest(right))){//都没出发则直线行驶
    motorRun(220,220);
  }
  else{
    motorRun(100,100);
  }
}

