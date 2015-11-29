/*
Joel Ruhland, George Cowan, Russell Wong, Justin Pezzak


****NOTE****
The code below is written for the EV3. RobotC has different functions and
syntax for different fuctionalities between the NXT platform and the EV3
platform. This code reflects that. Most native function names are self-explanatory,
but some may require lookup in the RobotC documentation.
***

*/

//RobotC's syntax to automatically initialise and set aliases for motors and sensors
//Initialises sensors and sets a 'friendly' name
#pragma config(Sensor, S1,     touchCalibrate, sensorEV3_Touch)
#pragma config(Sensor, S2,     touchReader,    sensorEV3_Touch)
#pragma config(Sensor, S3,     colorBill,      sensorColorNxtFULL)
#pragma config(Sensor, S4,     colorReader,    sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorA,          traySlide,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          billReader,    tmotorNXT, PIDControl, encoder)

//Motors not used in the final buidld
#pragma config(Motor,  motorC,          armWeight,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          billOut,       tmotorEV3_Medium, PIDControl, encoder)


#include "accountdata.c"

//Max number of accounts. Can be increased with no issues.
const int NUMACCOUNTS = 10;

int const START_NUM_BILLS = 20;

//-   Denominations:1 ,5 ,10,20,100}
int numOfBills[] = {START_NUM_BILLS,START_NUM_BILLS,START_NUM_BILLS,START_NUM_BILLS,START_NUM_BILLS};
const float TRAY_DIST = 8.2 * 180 / PI ;
const float BILL_THICKNESS = 0.011;

/*Withdraw code, not used
const float ARM_DIST = 180 / (0.85 * PI);
const float ARM_HEIGHT = 5.5;
*/


/*
Bills:     Common Index:
1 - White - 0
5 - Blue - 1	
10 - Yellow - 2	
20 - Green - 3
100 - Red - 4
*/

//Checks if account read from card exists
int doesExist(string cardvalue, Account * account)
{
	for (int i = 0; i<NUMACCOUNTS; i++)
	{
		if (account[i].cardNum == cardvalue)
			return i;
	}
	return -1;
}

//Gets card number from the swipe of card
int getCardSwipe()
{
	int values[4];

	//Waits for card to be inserted
	while (getTouchValue(touchReader) == false)
	{}

	//Waits until moved off black
	while (SensorValue[colorReader] == 1)
	{
		wait1Msec(100);
	}

	//Detects and records new color when change is detected
	for (int i = 0; i<4; i++)
	{
		values[i] = SensorValue[colorReader];
		while (SensorValue[colorReader] == values[i])
		{}
		wait1Msec(200);
	}

	eraseDisplay();
	
	//Displays read card number on screen
	displayString(0,"%d",values[0]*1000+values[1]*100+values[2]*10+values[3]);
	wait1Msec(2000);

	return (values[0]*1000+values[1]*100+values[2]*10+values[3]);

}

//Checks if pin matches the account's pin
bool comparePin(string pin, Account * accountList)
{
	for (int i = 0; i<NUMACCOUNTS; i++)
	{
		if (accountList[i].pin == pin)
			return true;
	}
	return false;
}

//User interface to get pin from user
bool checkPin(Account * accountList)
{
	char pin[4] = {'0','0','0','0'};
	
	//Initial position of pointer
	int i = 0;

	while (!getButtonPress(buttonEnter))
	{	
		//Redeclares pointer array and pointer value
		char pointer[4] = {' ',' ',' ',' '};
		pointer[i] = '^';
		
		//Redraws menu
		displayString(1, "Enter PIN: %c%c%c%c",pin[0],pin[1],pin[2],pin[3]);
		displayString(2, "           %c%c%c%c",pointer[0],pointer[1],pointer[2],pointer[3]);

		while (!getButtonPress(buttonAny))
		{}

		//React to button presses
		while (getButtonPress(buttonAny) && !getButtonPress(buttonEnter))
		{
			//Changes selected digit
			if (getButtonPress(buttonLeft))
			{
				i--;
			}
			else if (getButtonPress(buttonRight))
			{
				i++;
			}
			
			//Increment or decrement if up/down pressed
			else if (getButtonPress(buttonUp))
			{
				pin[i]++;
			}
			else if (getButtonPress(buttonDown))
			{
				pin[i]--;
			}
			
			//Normalises array index to stay within bounds
			if (i<0)
				i++;
			else if (i>3)
				i--;
			
			//Normalises character values to stay in the integers
			if (pin[i] >= ':')
				pin[i]--;
			else if (pin[i] <= '/')
				pin[i]++;

			wait1Msec(250);
			eraseDisplay();
		}


	}
	eraseDisplay();
	
	//Combines pin chars into a string
	string pinvalue = "";
	for (int i = 0; i<4; i++)
	{
		pinvalue+=pin[i];
	}
	
	//Returns if pin is correct
	return comparePin(pinvalue, accountList);
}


//Withdraw specific function
/*
void billsToOutput(int amount, int * bills)
{
	int denominations[5] = {1, 5, 10, 20, 100};
	for (int i = 4; i >= 0; i--)
	{
		bills[i] = amount / denominations[i];
		amount -= denominations[i]*bills[i];
	}
}
*/


//Withdraw Only
//Gets amount of money to withdraw from user using buttons
/*
int getAmount()
{
	char amount[3] = {'0','0','0'};
	int i = 0;

	while (!getButtonPress(buttonEnter))
	{
		char pointer[3] = {' ',' ',' '};
		pointer[i] = '^';
		displayString(0, "Enter Amount: %c%c%c",amount[0],amount[1],amount[2]);
		displayString(1, "              %c%c%c",pointer[0],pointer[1],pointer[2]);

		while (getButtonPress(buttonAny) == 0)
		{}
		//React to button Presses
		while (getButtonPress(buttonAny) == 1 && !getButtonPress(buttonEnter))
		{
			//Changes index or value when buttons are pressed
			if (getButtonPress(buttonLeft) == 1)
			{
				i--;
			}
			else if (getButtonPress(buttonRight) ==1)
			{
				i++;
			}
			else if (getButtonPress(buttonUp) ==1)
			{
				amount[i]++;
			}
			else if (getButtonPress(buttonDown) ==1)
			{
				amount[i]--;
			}

			//Normalisation
			if (i<0)
				i++;
			else if (i>2)
				i--;

			if (amount[i] >= ':')
				amount[i]--;
			else if (amount[i] <= '/')
				amount[i]++;

			wait1Msec(250);
			eraseDisplay();


		}


	}
	int a0 = amount[0] - '0';
	int a1 = amount[1] - '0';
	int a2 = amount[2] - '0';
	eraseDisplay();
	return (a0*100+a1*10+a2);
}
*/

//Moves tray to location to deposit a bill of specific color
void moveTrayDeposit(int colorIndex)
{
	int direction = colorIndex - 2;
	nMotorEncoder[traySlide] = 0;
	eraseDisplay();
	displayString(0, "Please wait. . .");
	
	//Moves tray to deposit position
	if (direction > 0)
	{
		motor[traySlide] = 30;
		while (nMotorEncoder[traySlide] < TRAY_DIST * direction)
		{}
	}
	else
	{
		motor[traySlide] = -30;
		while (nMotorEncoder[traySlide] > TRAY_DIST * direction)
		{}
	}

	motor[traySlide] = 0;

	//Moves the bill into the tray
	motor[billReader] = 50;
	wait1Msec(3000);
	
	//Test code for withdrawals
	/*
	motor[armWeight] = 20;
	wait1Msec(2000);
	motor[armWeight] = -20;
	wait1Msec(2000);
	motor[armWeight] = 20;
	wait1Msec(2000);
	motor[armWeight] = -20;
	wait1Msec(2000);
	motor[billReader] = 0;
	*/


	nMotorEncoder[traySlide] = 0;

	//Move back to original position
	if (direction > 0)
	{
		motor[traySlide] = -30;
		while (nMotorEncoder[traySlide] > TRAY_DIST * -direction)
		{}
	}
	else
	{
		motor[traySlide] = 30;
		while (nMotorEncoder[traySlide] < TRAY_DIST * -direction)
		{}
	}
	motor[traySlide] = 0;
}

//Pulls bill into reader and gets its color
int getBill()
{
	//Pulls in until color change is detected, then continues for 0.2 s
	motor[billReader] = 30;
	int billVal = 0;
	int numEachColor[5] = {0, 0, 0, 0, 0};
	int max = 0;
	while (SensorValue[colorBill] == 1)
	{
		if(getButtonPress(buttonEnter) == 1)
			return 0;
		wait1Msec(50);
	}
	
	wait1Msec(200);
	motor[billReader] = 0;

	//find the color that occurs the most
	for (int i = 0; i < 10; i++)
	{
		int currentColor = SensorValue[colorBill];
		int currentIndex = -1;
		if(currentColor == 6)
			currentIndex = 0;
		else if (currentColor == 2)
			currentIndex = 1;
		else if (currentColor == 4)
			currentIndex = 2;
		else if (currentColor == 3)
			currentIndex = 3;
		else if (currentColor == 5)
			currentIndex = 4;

		if (currentIndex > -1)
		{
			numEachColor[currentIndex]++;
			numOfBills[currentIndex]++;
			if (numEachColor[currentIndex] > numEachColor[max])
				max = currentIndex;
		}
		wait1Msec(100);
	}
	
	if (max == 0) //white
		billVal = 1;
	else if (max == 1) //blue
		billVal = 5;
	else if (max == 2) //yellow
		billVal = 10;
	else if (max == 3) //green
		billVal = 20;
	else			 //red
		billVal = 100;
	displayString(2, "%d", max);
	wait1Msec(1000);

	moveTrayDeposit(max);


	return billVal;


}

//Main deposit function, calls getBill and returns total amount brought in
int doDeposit()
{
	int amounttodeposit = 0;
	eraseDisplay();
	displayString(0, "Hold center button to exit");
	while (getButtonPress(buttonEnter) != 1)
	{
		int billVal = getBill();
		if (billVal == 0)
		{
			motor[billReader] = 0;
			return amounttodeposit;
		}
		amounttodeposit += billVal;
		eraseDisplay();
		displayString(0, "Hold center button to exit");
		displayString(1,"%d", amounttodeposit);
	}
	eraseDisplay();
	motor[billReader] = 0;
	return amounttodeposit;

}

//Withdrawl specific code
//Outputs the specifc amount of each bill as pre-determined
/*
void doOutput(int * numBills)
{
	//Move to location and output number of bills
	motor[traySlide] = -30;

	int colors[5] = {6, 2, 4, 3, 5}; //White Blue Yellow Green Red

	//Assume start position in the centre
	nMotorEncoder[traySlide] = 0;
	while(nMotorEncoder[traySlide] > TRAY_DIST * -2)
	{}
	motor[traySlide] = 0;

	motor[billReader] = -30;
	motor[billOut] = 50;
	for (int i = 0; i < 4; i++)
	{
		int numEachColor[5] = {0, 0, 0, 0, 0};
		int max = 0;
		motor[billOut] = 50;
		for (int j = 0; j < numBills[i]; j++)
		{
			//wait until a bill is detected
			while (SensorValue[colorBill] != colors[i])
			{
				motor[motorC] = 20;
				nMotorEncoder[motorC] = 0;
				while (nMotorEncoder[motorC] < (ARM_HEIGHT-numOfBills[i]*BILL_THICKNESS) * ARM_DIST)
				{}
				motor[motorC] = 0;
				wait1Msec(500);

				nMotorEncoder[motorC] = 0;
				motor[motorC] = -20;
				while (nMotorEncoder[motorC] > (ARM_HEIGHT-numOfBills[i]*BILL_THICKNESS) * -ARM_DIST)
				{}
				motor[motorC] = 0;
				wait1Msec(500);

			}

			//wait until bill passes through
			int billVal = colors[i];
			while (billVal == colors[i])
			{
				//find the color that occurs the most
				for (int k = 0; k < 10; k++)
				{
					int currentColor = SensorValue[colorBill];
					int currentIndex = -1;
					if(currentColor == 6)
						currentIndex = 0;
					else if (currentColor == 2)
						currentIndex = 1;
					else if (currentColor == 4)
						currentIndex = 2;
					else if (currentColor == 3)
						currentIndex = 3;
					else if (currentColor == 5)
						currentIndex = 4;

					if (currentIndex > -1)
					{
						numEachColor[currentIndex]++;
						numOfBills[currentIndex]++;
						if (numEachColor[currentIndex] > numEachColor[max])
							max = currentIndex;
					}
					wait1Msec(50);
				}
				if (max == 0) //white
					billVal = 1;
				else if (max == 1) //blue
					billVal = 5;
				else if (max == 2) //yellow
					billVal = 10;
				else if (max == 3) //green
					billVal = 20;
				else			 				 //red
					billVal = 100;

			}
			numOfBills[i]--;
			wait1Msec(300);
		}


		//move arm up
		motor[armWeight] = -20;
		wait1Msec(2000);

		//move tray to next slot
		motor[traySlide] = 30;
		nMotorEncoder[traySlide] = 0;
		while (nMotorEncoder[traySlide] < TRAY_DIST)
		{}
		motor[traySlide] = 0;
	}

	//move back to starting position (centre)
	motor[traySlide] = -30;
	nMotorEncoder[traySlide] = 0;
	while (nMotorEncoder[traySlide] > TRAY_DIST * -2)
	{}
	motor[traySlide] = 0;
}*/


//Withdraw Specific
//Checks if sufficint balance, and calls output function
/*
int doWithdraw(Account accountList)
{
	int amounttowithdraw = getAmount();

	if (accountList.balance < amounttowithdraw)
	{
		eraseDisplay();
		displayString(0,"Error, Insufficient Balance");
		return -1;
	}
	int bills[5] = {0, 0, 0, 0, 0};
	billsToOutput(amounttowithdraw, bills);

	doOutput(bills);

	return amounttowithdraw;
}
*/


task main()
{
	struct Account accountList[NUMACCOUNTS];
	initAccounts(accountList, NUMACCOUNTS);

	string account, cardnum, pin;
	int accountindex = -1;
	bool pinCorrect = false;

	//Keeps ATM running while battery is still alive
	while (getBatteryCurrent() > 0.02)
	{

		do
		{
		wait1Msec(1000);
		
		//Checks if swiped card account exists
		displayString(0,"Swipe card to Begin");
		cardnum = getCardSwipe();
		accountindex = doesExist(cardnum, accountList);
		displayString(0,"ERROR Card Not Found!!");
		}while (accountindex == -1);
		
		eraseDisplay();
		
		//Confirms correct pin was entered
		do
		{
		pinCorrect = checkPin(accountList);
		displayString(0,"ERROR Incorrect PIN");
		}while (pinCorrect == false);

		eraseDisplay();
		wait1Msec(500);

		//Selection Menu
		bool transaction = true;
		while (transaction)
		{
			//Withdrawal code
			/*
			else if (getButtonPress(buttonRight) ==1)
			{
				int amount = doWithdraw(accountList[accountindex]);
				if (amount != -1)
				{
					accountList[accountindex].balance -= amount;
				}
			}*/
			
			//Displays menu
			eraseDisplay();
			displayString(0,"Balance: %d", accountList[accountindex].balance);
			displayString(1,"Would you like a transaction?");
			displayString(2,"<----                   ---->");
			displayString(3,"Yes                       No");
			
			
			waitForButtonPress();
			
			//Calls deposit when left button pressed
			if (getButtonPress(buttonLeft) == 1)
			{
				int amount = doDeposit();
				accountList[accountindex].balance += amount;
				eraseDisplay();
			}
			
			//Exits when right button pressed
			if (getButtonPress(buttonRight) == 1)
			{
				eraseDisplay();
				transaction = false;
			}
			
			//Limits screen withdrawing to 5 times per second
			wait1Msec(200);
		}
	}
}
