struct account {
 	string cardNum;
	string pin;
  float balance;
} ;


bool intake ()
{
}

bool output()
{}

float getBalance()
{}

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
        return (a0*100+a1*10+a2);
}


task main()
{				int amount = getAmount();
				eraseDisplay();
        displayString(0,"%i", amount);
        wait1Msec(2000);
}
