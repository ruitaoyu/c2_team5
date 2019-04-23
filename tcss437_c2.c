#pragma config(Sensor, S3,     sonar3,         sensorEV3_Ultrasonic)
#pragma config(Sensor, S1,     ColourLeft,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     ColourRight,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorA,          motorLeft,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          motorRight,    tmotorEV3_Large, PIDControl, encoder)
#pragma DebuggerWindows("debugStream")

/*
    TCSS 437 Mobile Robotic
    Challenge 1
    Arjun Prajapati, Ruitao Yu
    This is the program of a robot that can accomplish these following behaviour:
        1. Wandering behavior: Robot randomly go left and right, but will still keep
            going forward.
        2. Robot will wander on a table with bounds and obsticles, and it cannot
            get stuck in 4 minutes.
*/

// the array of degree space of turning the robot
//int myTurn[4] = { 600, 700, 800, 900};

/*
    Function to controll the robot go backward.
*/
//void moveBack(){
//    // set the LED to read when hit
//	setLEDColor(ledRed);

//	// get both motor the negative value to go backward
//	setMotorSpeed(motorLeft, -50);
//	setMotorSpeed(motorRight, -50);

//	// go backward for 1 second
//	sleep(1000);
//}

/*
    Function to controll the robot go backward when double-bumper-hit occured.
*/
//void moveBackPlaySound(){
//    // set the LED to read when hit
//	setLEDColor(ledRed);

//	// set sound value play the sound of double-bumper-hit
//	setSoundVolume(75);
//	playSoundFile("Backing alert");

//	// get both motor the negative value to go backward
//	setMotorSpeed(motorLeft, -50);
//	setMotorSpeed(motorRight, -50);

//	// go backward for 1.5 second
//	sleep(1500);
//}

/*
    Function to move robot come back and move right after left bumper hit is
    detected
*/
//void moveLeft(){
//    // show the text on the robot screan when left bumper is hited
//	displayCenteredBigTextLine(4, "left is press!");

//	// only run the right motor to right
//	setMotorSpeed(motorLeft, 0);
//	setMotorSpeed(motorRight, 50);

//	// set a random turning time
//	sleep(myTurn[random(3)]);
//}

/*
    Function to move robot come back and move left after right bumper hit is
    detected
*/
//void moveRight(){
//    // show the text on the robot screan when right bumper is hited
//	displayCenteredBigTextLine(4, "right is pressed!");

//	// only run the left motor to left
//	setMotorSpeed(motorLeft, 50);
//	setMotorSpeed(motorRight, 0);

//	// set a random turning time
//	sleep(myTurn[random(3)]);
//}

// Array for random speed differential of two motors
//int myArray[4] = { 5, 8, 10, 12};

//// Array for random delay of next new speed differ of both motors.
//int myTime[4] = { 10, 20, 30, 40};

//// diretion of the robot, 0 means left and 1 means right
//int dir = 0;

//// count the escapled time of the speed differ
//int counter = 0;

//// the speed of each motor
//int left = 50;
//int right = 50;

//// the delay time util the update of speed differ
//int latency = 20;
int currentDistance = 0;
short currentColourLeft;
short currentColourRight;
/*
    Main function
    Ifiniti while loop
*/
task main()
{
	while (true)
	{

		currentDistance = SensorValue[sonar3];
		displayCenteredBigTextLine(4, "Dist: %3d cm", currentDistance);

		if(currentDistance <=5) {
			setMotorSpeed(motorLeft, 0);
	  	setMotorSpeed(motorRight, 0);
			sleep(100);
	  }

		setMotorSpeed(motorLeft, 30);
	  setMotorSpeed(motorRight, 30);
		sleep(100);

		currentColourLeft = SensorValue[ColourLeft];
		currentColourRight = SensorValue[ColourRight];

		switch(currentColourRight)
		{
			case 0:  displayCenteredBigTextLine(12, "none"); break;
			case 1:  displayCenteredBigTextLine(12, "black"); break;
			case 2:	 displayCenteredBigTextLine(12, "blue"); break;
			case 3:	 displayCenteredBigTextLine(12, "green"); break;
			case 4:	 displayCenteredBigTextLine(12, "yellow"); break;
			case 5:	 displayCenteredBigTextLine(12, "red"); break;
			case 6:	 displayCenteredBigTextLine(12, "white"); break;
			case 7:	 displayCenteredBigTextLine(12, "brown"); break;
			default: displayCenteredBigTextLine(12, "unknown");
		}

				switch(currentColourLeft)
		{
			case 0:  displayCenteredBigTextLine(8, "none"); break;
			case 1:  displayCenteredBigTextLine(8, "black"); break;
			case 2:	 displayCenteredBigTextLine(8, "blue"); break;
			case 3:	 displayCenteredBigTextLine(8, "green"); break;
			case 4:	 displayCenteredBigTextLine(8, "yellow"); break;
			case 5:	 displayCenteredBigTextLine(8, "red"); break;
			case 6:	 displayCenteredBigTextLine(8, "white"); break;
			case 7:	 displayCenteredBigTextLine(8, "brown"); break;
			default: displayCenteredBigTextLine(8, "unknown");
		}

		// Wait 20 ms to get 50 readings per second
		sleep(20);


        // Update the counter by 1
		//counter++;

  //      // If the counter is less than latency
  //      // it is time to update the speed of each motor
		//if(counter > latency){
		//    // if it is going right
		//    // just reset the left motor to default value 50
		//    // then add a random value to 50 as the new speed of
		//    // right motor to make it turn left
		//	if(dir == 1 ){
		//		right = 50;
		//		left += myArray[random(3)];
		//		writeDebugStreamLine("Right  %d",myArray[random(3)] );
		//		dir = 0;
		//	} else {// if it is going left
		//    // just reset the right motor to default value 50
		//    // then add a random value to 50 as the new speed of
		//    // left motor to make it turn right
		//		left = 50;
		//	    right += myArray[random(3)];
		//		writeDebugStreamLine("Left	%d",myArray[random(3)]);
		//		dir = 1;
		//	}

		//	// reset the counter and update the latency
		//	counter =0;
		//	latency = myTime[random(3)];
	 // }
	 //   // For debugging
		//writeDebugStreamLine("The left speed is %d and the right is %d ", left, right);

		////update each speed od the motor
		//setMotorSpeed(motorLeft, left);
		//setMotorSpeed(motorRight, right);

		//// delay for 0.005 second
		//sleep(50);

        // If it is double-bumper-hit
	//	if(SensorValue[Touch1] && SensorValue[Touch4]){
	//		// To play sound
	//		moveBackPlaySound();

 //           // stop both motor for 2 seconds


	//		// set a random direction
	//		int randomDirection = random(1);

 //           //condition to move robot either left or right
	//		if(randomDirection == 1){
	//			moveLeft();
	//		}else{
	//			moveRight();
	//	    }
	//	}else if (SensorValue[Touch4]){//condition to move robot to right
	//		moveBack();
	//		moveRight();
	//	}else if(SensorValue[Touch1]){ //condition to move robot to left
	//		moveBack();
	//		moveLeft();

 //   	}
	//	// If it's in a released state, turn the LED green
	//	else{
	//		displayCenteredBigTextLine(4, "Not Pressed!");
	//		setLEDColor(ledGreen);
	//	}
	}
}
