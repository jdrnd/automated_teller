struct Account 
{
 	string cardNum;
	string pin;
  float balance;
} ;

/*
0 = $1
1 = $5
2 = $10
3 = $20
4 = $100
*/
struct BillsToOutput
{
	int number[5];
};

//Russel Wong
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


bool intake ()
{
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


int accountExists(int cardvalue, Account & account)
{

}

task main()
{				
		BillsToOutput bills;
		Account account[10];
		wait1Msec(4000);
}
