#pragma config(Sensor, S1,     touchCalibrate, sensorEV3_Touch)
#pragma config(Sensor, S2,     touchReader,    sensorEV3_Touch)
#pragma config(Sensor, S3,     colorBill,      sensorColorNxtFULL)
#pragma config(Sensor, S4,     colorReader,    sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorA,          traySlide,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          billReader,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          armWeight,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          billOut,       tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "accountdata.c"

const int NUMACCOUNTS = 10;

int const START_NUM_BILLS = 50;
//-----------------{1 ,5 ,10,20,100}
int numOfBills[] = {START_NUM_BILLS,START_NUM_BILLS,START_NUM_BILLS,START_NUM_BILLS,START_NUM_BILLS};

/*
Bills:
1 - White
5 - Blue
10 - Yellow
20 - Green
100 - Red
*/


struct BillsToOutput
{
	int number[5];
};


int doesExist(string cardvalue, Account * account)
{
	for (int i = 0; i<NUMACCOUNTS; i++)
	{
		if (account[i].cardNum == cardvalue)
			return i;
	}
	return -1;
}

int getCardSwipe()
{
	char values[4];

	//Waits for card to be inserted
	while (getTouchValue(touchReader) == false)
	{}


	//Waits until moved off black
	while (SensorValue[S4] == 1  || SensorValue[S4] == 1)
	{
		wait1Msec(100);
	}



	//Detects and records new color when change is detected
	for (int i = 0; i<4; i++)
	{
		values[i] = SensorValue[S4];
		while (SensorValue[S4] == values[i])
		{}
		wait1Msec(200);
	}

	eraseDisplay();
	displayString(0,"%i",values[0]*1000+values[1]*100+values[2]*10+values[3]);
	wait1Msec(3000);

	return (values[0]*1000+values[1]*100+values[2]*10+values[3]);

}


bool comparePin(string pin, Account * accountList)
{
	for (int i = 0; i<NUMACCOUNTS; i++)
	{
		if (accountList[i].pin == pin)
			return true;
	}
	return false;
}

bool checkPin(Account * accountList)
{
        char pin[4] = {'0','0','0','0'};
        int i = 0;

        while (!getButtonPress(buttonEnter))
        {
                char pointer[4] = {' ',' ',' ',' '};
                pointer[i] = '^';
                displayString(1, "Enter PIN: %c%c%c%c",pin[0],pin[1],pin[2],pin[3]);
                displayString(2, "           %c%c%c%c",pointer[0],pointer[1],pointer[2],pointer[3]);

                while (getButtonPress(buttonAny) == 0)
              	{}

                //React to button Presses
               	while (getButtonPress(buttonAny) == 1)
                {
                        if (getButtonPress(buttonLeft) == 1)
                        {
                                i--;
                        }
                        else if (getButtonPress(buttonRight) ==1 )
                        {
                                i++;
                        }
                        else if (getButtonPress(buttonUp) ==1)
                        {
                                pin[i]++;
                        }
                        else if (getButtonPress(buttonDown) ==1)
                        {
                                pin[i]--;
                        }
                        else
                        {
                                break;
                        }

                        if (i<0)
                                i++;
                        else if (i>3)
                                i--;

                        if (pin[i] >= ':')
                        		pin[i]--;
                        else if (pin[i] <= '/')
                        		pin[i]++;

                        wait1Msec(250);
                        eraseDisplay();


                }


        }
        eraseDisplay();
        string pinvalue = "";
        for (int i = 0; i<4; i++)
        {
        	pinvalue+=pin[i];
        }

        return comparePin(pinvalue, accountList);
}


//Russell Wong
//Tested
//Changed to use pointers (should re-test)
void billsToOutput(int amount, int * bills)
{
	int denominations[5] = {1, 5, 10, 20, 100};
	for (int i = 4; i >= 0; i--)
	{
		bills[i] = amount / denominations[i];
		amount -= denominations[i]*bills[i];
	}
}



//Joel Ruhland
//Fully Tested
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
               	while (getButtonPress(buttonAny) == 1)
                {
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
                        else
                        {
                                break;
                        }

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

//Russell Wong
//Tested
int getBill()
{
	//Pulls in until color change is detected, then continues for 1/5
	motor[billReader] = 50;
	int billVal = 0;
	int numEachColor[5] = {0, 0, 0, 0, 0};
	int max = 0;
	//while (getButtonPress(buttonEnter) != 1)
	//{
			while (SensorValue[colorBill] == 1)
				wait1Msec(200);
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
			else			 				 //red
				billVal = 100;
		  displayString(2, "%d", max);
		  wait1Msec(1000);
	//}


	return billVal;


}

int doDeposit()
{
	int ammounttodeposit;
	eraseDisplay();
	displayString(0, "Press center button to exit");
	while (getButtonPress(buttonEnter) != 1)
	{
		ammounttodeposit +=getBill();
		eraseDisplay();
		displayString(0, "Press center button to exit");
		displayString(1,"%d", ammounttodeposit);
	}
	return ammounttodeposit;
	eraseDisplay();

}

//Russell Wong
void doOutput(int * numBills)
{
	//Move to location and output number of bills
	motor[traySlide] = -50;

	const float TRAY_DIST = 8.1 * 180 / PI ;
	int colors[5] = {6, 2, 4, 3, 5}; //White Blue Yellow Green Red


	while (SensorValue[touchCalibrate] == 1) //move tray to the very end
  {}

	motor[billReader] = -50;
	motor[billOut] = 50;
	for (int i = 0; i < 4; i++)
	{
		motor[armWeight] = 20;
		wait1Msec(2000);

	  motor[billOut] = 50;
		for (int j = 0; j < numBills[i]; j++)
		{
			//may need to do debouncing
			while (SensorValue[colorBill] != colors[i])
			{}
			numOfBills[i]--;
			delay(300);
		}

		motor[armWeight] = -20;
		wait1Msec(2000);

		motor[motorA] = 50;
		nMotorEncoder[motorA] = 0;
		while (nMotorEncoder[motorA] < TRAY_DIST)
		{}
	}
}

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

task main()
{


		struct Account accountList[NUMACCOUNTS];
		initAccounts(accountList, NUMACCOUNTS);

		string account;
		string cardnum;
		string pin;
		int accountindex;
		bool pinCorrect;

		while (getBatteryCurrent() > 0.02)
		{
			/*
			displayString(0,"Swipe card to Begin");
			do
			{
				cardnum = getCardSwipe();
				accountindex = doesExist(cardnum, accountList);
				displayString(0,"ERROR Card Not Found!!");
			}while (accountindex == -1);
			eraseDisplay();
			do
			{
				pinCorrect = checkPin(accountList);
				displayString(0,"ERROR Incorrect PIN");
			}while (pinCorrect == false);
			wait1Msec(100);
			eraseDisplay();
			wait1Msec(500);*/

			//Selection Menu
			//while (getButtonPress(buttonEnter) != 1)
			//{
					eraseDisplay();
					displayString(2,"<----                   ---->");
					displayString(3,"Deposit             Withdraw");

					waitForButtonPress();

			    if (getButtonPress(buttonLeft) == 1)
			    {
			    		int amount = doDeposit();
			        accountList[accountindex].balance += amount;
							eraseDisplay();
			        displayString(0,"%d", amount);
			    }
			    else if (getButtonPress(buttonRight) ==1)
			    {
			            int amount = doWithdraw(accountList[accountindex]);
			            if (amount != -1)
			            {
			            	accountList[accountindex].balance -= doWithdraw(accountList[accountindex]);
			            }
			    }
		  //}

	    wait1Msec(5000);


		}
}
