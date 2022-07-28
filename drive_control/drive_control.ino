#if (ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include <WProgram.h>
#endif

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <AFMotor.h>


// for center ultrasonic sernsor
#define trig 49
#define echo 48

ros::NodeHandle nh;

AF_DCMotor RF_Motor(3);
AF_DCMotor RB_Motor(2);
AF_DCMotor LF_Motor(4);
AF_DCMotor LB_Motor(1);

void mes_forward(const std_msgs::String& toggle_msg)
{
  forward();
}

void mes_backward(const std_msgs::String& toggle_msg)
{
  backward();
}

void mes_right(const std_msgs::String& toggle_msg)
{
  rightward();
}

void mes_left(const std_msgs::String& toggle_msg)
{
  leftward();
}

void mes_stop(const std_msgs::String& toggle_msg)
{
  stopping();
}

// ---------------------------- subscriber message for motors -------------------------------------
ros::Subscriber<std_msgs::String> motor_forward("motor_forward", &mes_forward);
ros::Subscriber<std_msgs::String> motor_backward("motor_backward", &mes_backward);
ros::Subscriber<std_msgs::String> motor_right("motor_right", &mes_right);
ros::Subscriber<std_msgs::String> motor_left("motor_left", &mes_left);
ros::Subscriber<std_msgs::String> motor_stop("motor_stop", &mes_stop);

// ------------------------ publisher message for ultrasonic sensor ------------------------------
std_msgs::Int16 int_msg;
ros::Publisher ultra("ultra", &int_msg);

void setup()
{

  nh.initNode();

  // ------ motor subscriber --------------
  nh.subscribe(motor_forward);
  nh.subscribe(motor_backward);
  nh.subscribe(motor_right);
  nh.subscribe(motor_left);
  nh.subscribe(motor_stop);

  // ------ ultrasonic publisher -----------
  nh.advertise(ultra);
  
  // ---- ultrasonic sensor pin description ------------
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  
}

void loop()
{
  long duration;
  int distance;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = (duration/2) / 29.1;
  int_msg.data = distance;
  ultra.publish(&int_msg);

  nh.spinOnce();
  delay(10);
  
}

void forward()
{
  RF_Motor.setSpeed(255);
  RF_Motor.run(FORWARD);

  LF_Motor.setSpeed(255);
  LF_Motor.run(FORWARD);

  RB_Motor.setSpeed(255);
  RB_Motor.run(FORWARD);

  LB_Motor.setSpeed(255);
  LB_Motor.run(FORWARD);
}

void backward()
{
  RF_Motor.setSpeed(255);
  RF_Motor.run(BACKWARD);

  LF_Motor.setSpeed(255);
  LF_Motor.run(BACKWARD);

  RB_Motor.setSpeed(255);
  RB_Motor.run(BACKWARD);

  LB_Motor.setSpeed(255);
  LB_Motor.run(BACKWARD);
}

void rightward()
{
  RF_Motor.setSpeed(255);
  RF_Motor.run(BACKWARD);

  LF_Motor.setSpeed(255);
  LF_Motor.run(FORWARD);

  RB_Motor.setSpeed(255);
  RB_Motor.run(BACKWARD);

  LB_Motor.setSpeed(255);
  LB_Motor.run(FORWARD);
}

void leftward()
{
  RF_Motor.setSpeed(255);
  RF_Motor.run(FORWARD);

  LF_Motor.setSpeed(255);
  LF_Motor.run(BACKWARD);

  RB_Motor.setSpeed(255);
  RB_Motor.run(FORWARD);

  LB_Motor.setSpeed(255);
  LB_Motor.run(BACKWARD);
}

void stopping()
{
  RF_Motor.setSpeed(255);
  RF_Motor.run(RELEASE);

  LF_Motor.setSpeed(255);
  LF_Motor.run(RELEASE);

  RB_Motor.setSpeed(255);
  RB_Motor.run(RELEASE);

  LB_Motor.setSpeed(255);
  LB_Motor.run(RELEASE);
}
