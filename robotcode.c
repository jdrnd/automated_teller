#pragma config(Sensor, S1,     touchCalibrate, sensorEV3_Touch)
#pragma config(Sensor, S2,     touchReader,    sensorEV3_Touch)
#pragma config(Sensor, S3,     colorBill,      sensorColorNxtFULL)
#pragma config(Sensor, S4,     colorReader,    sensorEV3_Color, modeEV3Color_Color)
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
void billsToOutput(int amount, BillsToOutput bills)
{
	int denominations[5] = {1, 5, 10, 20, 100};
	for (int i = 4; i >= 0; i--)
	{
		bills.number[i] = amount / denominations[i];
		amount -= denominations[i]*bills.number[i];
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
int getBill()
{
	//Pulls in until color change is detectted, then continues for 1/5
	motor[motorA] = 30;
	while (SensorValue[colorBill] == 1)
	{}
	wait1Msec(200);

	//Stops motor, waits, and takes color reading
	motor[motorA] = 0;
	wait1Msec(500);
	int curr_bill = SensorValue[S3];

	//convert colour to bill value
	if (curr_bill == 6) //white
		curr_bill = 1;
	else if (curr_bill == 2) //blue
		curr_bill = 5;
	else if (curr_bill == 4) //yellow
		curr_bill = 10;
	else if (curr_bill == 3) //green
		curr_bill = 20;
	else			 //red
		curr_bill = 100;

	return curr_bill;
}

int doDeposit()
{
	int ammounttodeposit;
	eraseDisplay();
	displayString(0, "Press center button to exit");
	while (!getButtonPress(buttonEnter))
	{
		ammounttodeposit +=getBill();
		eraseDisplay();
		displayString(0,"%s", ammounttodeposit);
	}
	return ammounttodeposit;
	eraseDisplay();

}

//Russell Wong
void doOutput(int position, int numbills)
{
	//Move to location and output number of bills
	motor[motorA] = 50; //tray motor
	motor[motorB] = -50;  //bill dispenser motor
	motor[motorC] = 50; //bottom wheel motor

	const float TRAY_DIST = 6.0325 * 180 / (PI * 1.5);


	int colors[5] = {6, 2, 4, 3, 5}; //White Blue Yellow Green Red


	delay(3000); //move tray to the very end
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < numbills; j++)
		{
			while (SensorValue[S1] != colors[i]) //for a colour sensor attached to S1
			{}
			delay(300);
		}
		motor[motorA] = -50;
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
	BillsToOutput bills;
	billsToOutput(amounttowithdraw, bills);

	for (int i = 0; i < 4; i++)
	{
		doOutput(i,bills.number[i]);
	}

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
		bool pinCorrect = false;

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
			}while (pinCorrect == false);*/

			//Selection Menu
			eraseDisplay();
			displayString(2,"<----                   ---->");
			displayString(3,"Deposit             Withdraw");

			waitForButtonPress();

	    if (getButtonPress(buttonLeft) == 1)
	    {
	    		int amount = doDeposit();
	        accountList[accountindex].balance += amount;
					eraseDisplay();
	        displayString(0,"%i", amount);
	    }
	    else if (getButtonPress(buttonRight) ==1)
	    {
	            int amount = doWithdraw(accountList[accountindex]);
	            if (amount != -1)
	            {
	            	accountList[accountindex].balance -= doWithdraw(accountList[accountindex]);
	            }
	    }

	    wait1Msec(5000);


		}
}
