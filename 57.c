#pragma config(Sensor, S1,     ColourLeft,     sensorEV3_Color)
#pragma config(Sensor, S2,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     ColourRight,    sensorEV3_Color)
#pragma config(Motor,  motorA,          motorLeft,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          motorRight,    tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//



#pragma DebuggerWindows("debugStream")


// the array of degree space of turning the robot
int myTurn[4] = { 600, 700, 800, 900};
int myArray[4] = { 5, 8, 12, 15};
//// Array for random delay of next new speed differ of both motors.
int myTime[4] = { 10, 20, 30, 40};

//// diretion of the robot, 0 means left and 1 means right
int dir = 0;

//// count the escapled time of the speed differ
int counter = 0;

//// the delay time util the update of speed differ
int latency = 20;

int currentDistance = 0;
short currentColourLeft;
short currentColourRight;
int turningSpeed = 70;
int robotSpeed = 15;

int tinyTimer = 10;
int smallTimer = 300;
int mediumTimer = 450;
int largeTimer = 900;
int randomCoolDown = 0;


int left = 15;
int right = 15;
/*
	status:
	Wandering:0
	lineFolowing: 1
	objectDeteted: 2
*/
int status = 0;


void playSound() {
	playTone(400, 20);
	while(bSoundActive)
		sleep(1);
  writeDebugStreamLine("XXXXXXXXXXXXXXXXXXX");
}

void turnLeft(int theTime){
		setMotorSpeed(motorLeft, 0);
		setMotorSpeed(motorRight, 60);
		sleep(100);

}

void turnRight(int theTime){
		setMotorSpeed(motorLeft, 60);
		setMotorSpeed(motorRight, 0);
		sleep(100);
}

void randomTurn(){
	int temp = random(2);
	if(temp == 0){
		turnLeft(mediumTimer);
	}else {
		turnRight(mediumTimer);
	}
}

void sonarSensorTesting() {
	// Distance to maintain to the target (30 cm)
	const int distanceToMaintain = 30;

		// Read the sensor
		currentDistance = SensorValue[sonarSensor];
		displayCenteredBigTextLine(4, "Dist: %3d cm", currentDistance);

		// We're too far away, move forward
		if ((distanceToMaintain - currentDistance) < -2)
		{
			motor[motorLeft] = 30;
			motor[motorRight] = 30;
		}
		// We're too close, move backwards
		else if ((distanceToMaintain - currentDistance) > 2)
		{
			motor[motorLeft] = -30;
			motor[motorRight] = -30;
		}
		// We're good, don't go anywhere
		else
		{
			motor[motorLeft] = 0;
			motor[motorRight] = 0;
		}

		//Loop to monitor value in Sensor debugger window
		sleep(50);
}


void resetRandomTurn(){
			randomCoolDown = 0;
			setLEDColor(ledGreen);
}

void turnOffRandomTurn(){
			randomCoolDown = 1;
			setLEDColor(ledRed);
}

void checkRandomCoolDown() {
	if(randomCoolDown == 0 ) {
			turnOffRandomTurn();
	}
}





/*
    Main function
    Ifiniti while loop
*/
task main()
{
	writeDebugStreamLine("Here we go XXXXXXXXXXXXXXXXXXX");
	while (true)
	{
		//counter++;

		currentColourLeft = SensorValue[ColourLeft];

		currentColourRight = SensorValue[ColourRight];
						//sonarSensorTesting();
		currentDistance = SensorValue[sonarSensor];

		// if(currentDistance <=92) {
			// status  = 2;
		// } else {
			// status =0;
			// robotSpeed = 15;
		// }



		if(status == 0 &&(currentColourLeft < 10 || currentColourRight < 10 )){ // for both sensors sensing black
				status = 1;
				resetRandomTurn();
		}


		if (currentDistance > 6 &&currentDistance <=92) {
				//robotSpeed = 0;



				while(currentDistance > 5 &&currentDistance <=92) {
			  	//int speed = 50;

			  	displayCenteredBigTextLine(6, " %d", currentDistance);

	  			setMotorSpeed(motorLeft, currentDistance);
					setMotorSpeed(motorRight,currentDistance);
					//sleep(100);

			  	currentDistance = SensorValue[sonarSensor];
			  }

			  	setMotorSpeed(motorLeft, 50);
				setMotorSpeed(motorRight, -50);
				sleep(700);
				
				status =0;
			}
			else if(status == 0) {
				displayCenteredBigTextLine(4, "Wandering");
				counter++;
				// If the counter is less than latency
				// it is time to update the speed of each motor
				if(counter > latency){
						// if it is going right
						// just reset the left motor to default value 50
						// then add a random value to 50 as the new speed of
						// right motor to make it turn left
						if(dir == 1 ){
								right = robotSpeed;
								left += myArray[random(3)];
								//writeDebugStreamLine("Right  %d",myArray[random(3)] );
								dir = 0;
						} else {// if it is going left
								// just reset the right motor to default value 50
								// then add a random value to 50 as the new speed of
								// left motor to make it turn right
								left = robotSpeed;
								right += myArray[random(3)];
								//writeDebugStreamLine("Left	%d",myArray[random(3)]);
								dir = 1;
						}

						// reset the counter and update the latency
						counter =0;
						latency = myTime[random(3)];
				}
				// For debugging
				//writeDebugStreamLine("The left speed is %d and the right is %d ", left, right);

				//update each speed od the motor
				setMotorSpeed(motorLeft, left);
				setMotorSpeed(motorRight, right);

				// delay for 0.005 second
				sleep(50);



			} else if(status == 1) {
				//sonarSensorTesting();
				//currentDistance = SensorValue[sonar3];
				//displayCenteredBigTextLine(4, "Dist: %3d cm", currentDistance);

				//if(currentDistance <=5) {
				//	robotSpeed = 0;
				// }
	  		displayCenteredBigTextLine(4, "Line following");




				//currentColourLeft = SensorValue[ColourLeft];
				//currentColourRight = SensorValue[ColourRight];

				if(currentColourLeft < 10 && currentColourRight < 10 ){ // for both sensors sensing black
						setMotorSpeed(motorLeft, robotSpeed);
						setMotorSpeed(motorRight, robotSpeed);
						//sleep(300);
				} else if(currentColourLeft < 10){ // for left sensor sensing black
						turnLeft(tinyTimer);
				} else if(currentColourRight < 10){ // for right sensor sensing black
						turnRight(tinyTimer);
				} else {
						status = 0;
						int temp = random(2);
						if(temp == 0){
							setMotorSpeed(motorLeft, 0);
							setMotorSpeed(motorRight, 80);
							sleep(300);
						}else {
							setMotorSpeed(motorLeft, 80);
							setMotorSpeed(motorRight, 0);
							sleep(300);
						}
						//resetRandomTurn();
				}
		}


	}
}
