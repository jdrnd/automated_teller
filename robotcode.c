#include "accountdata.c"

const int NUMACCOUNTS = 10;

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

int getCardSwipe(Account * accounts)
{
	//Get card color data from sensor
	//return cardnum;
	string cardnum;
	return doesExist(cardnum, accounts);
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
                displayString(0, "Enter PIN: %c%c%c%c",pin[0],pin[1],pin[2]);
                displayString(1, "           %c%c%c%c",pointer[0],pointer[1],pointer[2]);

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
        pinvalue+=pin[0];
        pinvalue+=pin[1];
        pinvalue+=pin[2];
        pinvalue+=pin[3];
        return comparePin(pinvalue, accountList);
}






//Russell Wong
//Tested
void billsToOutput(int amount, BillsToOutput & bills)
{
	int denominations[5] = {1, 5, 10, 20, 100};
	for (int i = 4; i >= 0; i--)
	{
		bills.number[i] = amount / denominations[i];
		amount -= denominations[i]*bills.number[i];
	}
}


bool output()
{}

float getBalance()
{}



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

int getBill()
{
	while //Pulls in bill, reads color value, and returns value of bill
	return 0;
}

int doDeposit()
{
	int ammounttodeposit;

	while (!getButtonPress(buttonEnter))
	{
		ammounttodeposit +=getBill();
	}
	return ammounttodeposit;

}

//Russell Wong
void doOutput(int bill, int number, BillsToOutput & bills)
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
		for (int j = 0; j < bills.number[i]; j++)
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
		SensorType[S1] = sensorTouch;
		SensorType[S2] = sensorColorNxtFULL;

		struct Account accountList[NUMACCOUNTS];
		initAccounts(accountList, NUMACCOUNTS);

		string account;
		string pin;
		int accountindex;
		bool pinCorrect = false;

		while (getBatteryCurrent() > 0.02)
		{
			do
			{
				displayString(0,"Swipe Card to Begin");
				while (SensorValue[S1] == 0)
				{}

			accountindex = getCardSwipe(accountList);

			}while (accountindex == -1);

			while (pinCorrect == false)
			{
				pinCorrect = checkPin(accountList);
			}

			//Selection Menu
			eraseDisplay();
			DisplayString(0,"Press Left to Deposit, Right to Withdraw");
			DisplayString(3,"Deposit                       Withdraw");

			waitforButtonPress();

	    if (getButtonPress(buttonLeft) == 1)
	    {
	            accountList[accountindex].balance += doDeposit();
	    }
	    else if (getButtonPress(buttonRight) ==1)
	    {
	            int amount = doWithdraw(accountList[accountindex])
	            if (amount != -1)
	            {
	            	accountList[accountindex].balance -= doWithdraw(accountList[accountindex]);
	            }
	    }


		}
}
