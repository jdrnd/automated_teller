/*
All card data here
Could not get file input working so static arrays are used here instead
All data is NON-PERSISTANT, ie machine resets itself after each run
If questions on why this approach was taken/why we couldn't use files
please ask us or Prof. Hulls.
*/

struct Account
{
 	string cardNum;
	string pin;
  int balance;
};

void initAccounts(Account * accounts, int num)
{
		accounts[0].cardNum = 3572;
		accounts[0].pin = 4321;
		accounts[0].balance = 120;

		accounts[1].cardNum = 5757;
		accounts[1].pin = 1234;
		accounts[1].balance = 500;
		/*
		accounts[0].cardNum =
		accounts[0].pin =
		accounts[0].balance =
		accounts[0].cardNum =
		accounts[0].pin =
		accounts[0].balance =
		accounts[0].cardNum =
		accounts[0].pin =
		accounts[0].balance =
		accounts[0].cardNum =
		accounts[0].pin =
		accounts[0].balance =
		accounts[0].cardNum =
		accounts[0].pin =
		accounts[0].balance =
		accounts[0].cardNum =
		accounts[0].pin =
		accounts[0].balance =
		accounts[0].cardNum =
		accounts[0].pin =
		accounts[0].balance =
		accounts[0].cardNum =
		accounts[0].pin =
		accounts[0].balance =
		*/
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
