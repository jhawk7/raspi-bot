#include <iostream>
#include <wiringPi.h>
#include "libSonar.h"
#include "L298N.h"

using namespace std;

//set trigger pin and echo pin
int trigger = 1;
int echo = 0;

Sonar sonar;
sonar.init(trigger, echo);

//min distance of object detection
int MIN_DISTANCE = 5;

// setup motor pins
int enga; 
int in1;
int in2; 
int in3; 
int in4; 
int engb;

//init motor bridge
L298N motor(enga,in1,in2,in3,in4,engb);

//set LED pin
LED = 1;

//set led pin to receive digital output
pinMode(LED, OUTPUT);


int main() {
	if (wiringPiSetup() == -1) {
		return -1;
	}

	for (;;) {

		if (objectDetected()) {
			motor.full_stop(500);
			digitalWrite(LED, HIGH); 
			recover();
			digitalWrite(LED, LOW);
		}

		motor.forward(10,500);
	}

	return 0;
}

void hardwareTest() {
	motor.forward(10,500);
	delay(500)
	for (int i=0; i<10; i++) {
		cout << "Distance is " << sonar.distance(30000) << " cm." << endl; // 30000 is a timeout in microseconds
		delay(1000);
	}
}

bool objectDetected() {
	if (sonar.distance(30000) <= MIN_DISTANCE) {
		return true;
	} else {
		return false;
	}
}

void recover() {
	motor.backward(5,500);
	motor.turn_right(5,500);
}

