#include <Servo.h>

#define linearity 120
int i = 0;
int servoPositionR,servoPositionL,servoPositionRotation;
int pinStatus;
int mode;
int pin1,pin2;
Servo servoR; 
Servo servoL; 
Servo servoRotation;

void setup() 
{ 
    pinMode(7, INPUT);
    pinMode(8, INPUT);
    servoRotation.attach(11);
    servoR.attach(12);
    servoL.attach(13);
} 

void loop() 
{
//    demo_mode();
    check_pin_status();
    mode = decide_behavior(pinStatus);

    switch(mode){
        case 0:
            delay(1000);
            initialize();
            break;
        case 1:
            push_out_mode();
            break;
        case 2:
            swype_mode();
            break;
    }
}
void demo_mode(){

    initialize();
    delay(3000);
    action1();
    delay(3000);
    action2();
    delay(3000);
    action3();
    for(int j = 0; j < 5; j++){
        actionSwype();
    }
    action1();
    delay(3000);
    action2();
    delay(3000);
}

void push_out_mode(){
    action1();
    do{
        check_pin_status();
        decide_behavior(pinStatus);
        delay(1000);
    }while(mode == 1);
    action2();
}

void swype_mode(){
    action3();
do{
    actionSwype();
    check_pin_status();
    decide_behavior(pinStatus);
}while(mode == 2);

if(mode == 3){
    push_out_mode();
}
}

int check_pin_status(){

    pin1 = digitalRead(7);
    pin2 = digitalRead(8);

    if(pin1 == 0 && pin2 == 0){
        pinStatus = 0;
    }else if(pin1 == 1 && pin2 == 0){
        pinStatus = 1;
    }else if(pin1 == 0 && pin2 == 1){
        pinStatus = 2;
    }else{
        pinStatus = 3;
    }
    return pinStatus;
}

int decide_behavior(int ps){

    switch(ps){
        case 0:
            mode = 0;
            break;
        case 1:
            mode = 1;
            break;
        case 2:
            mode = 2;
            break;
    }
    return mode;
}

void initialize(){
    if(servoPositionR > 0){
        int temp;
        temp = servoPositionR;
        while(temp > 0){
            temp--;
            orderServoR(temp);
            delay(50);
        }
    }
    if(servoPositionL > 0){
        int temp;
        temp = servoPositionL;
        while(temp <100){
            temp++;
            orderServoL(temp);
            delay(50);
        }
    }
    if(servoPositionRotation > 0){
        int temp;
        temp = servoPositionRotation;
        while(temp > 0){
            temp--;
            orderServoRotation(temp);
            delay(50);
        }
    }
}

// iの初期値をPositonにしてみたらどうでしょうか
void action1(){
    for(i = servoPositionR; i < 80; i++){
        orderServoR(i);
        orderServoL(100-i);
        orderServoRotation(i);
        delay(linearity);
    }
    for(i = 81;i < 100; i++){
        orderServoR(i);
        orderServoL(100-i);
        delay(linearity);
    }
}

void action2(){
    for(i = 99; i > 80; i--){
        orderServoR(i);
        orderServoL(100-i);
        delay(linearity);
    }
    for(i= 81; i > 0; i--){
        orderServoR(i);
        orderServoL(100-i);
        orderServoRotation(i);
        delay(linearity);
    }
}

void action3(){
    for(i = 0; i < 60; i++){
        orderServoR(i);
        orderServoL(100-i);
        delay(linearity);
    }
}

void actionSwype(){
    for(i = 10; i < 30; i++){
        orderServoRotation(i);
        delay(160);
    }
    for(i = 30; i > 10; i--){
        orderServoRotation(i);
        delay(160);
    }
}

int orderServoR(int ang){
    servoR.write(ang);
    servoPositionR = ang;

    return servoPositionR;
}

int orderServoL(int ang){
    servoL.write(ang);
    servoPositionL = ang;

    return servoPositionL;
}

int orderServoRotation(int ang){
    servoRotation.write(ang);
    servoPositionRotation = ang;

    return servoPositionRotation;
}

