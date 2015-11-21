/*
All card data here
Could not get file input working so static arrays are used here instead
All data is NON-PERSISTANT, ie machine resets itself after each run
If questions on why this approach was taken/why we couldn't use files
please ask us or Prof. Hulls
*/

struct Account
{
 	string cardNum;
	string pin;
  float balance;
};

void initAccounts(Account * accounts, int num)
{
		accounts[0].cardNum = 4625;
		accounts[0].pin = 6969;
		accounts[0].balance = 120;

		/*accounts[0].cardNum =
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

		accounts[0].cardNum =
		accounts[0].pin =
		accounts[0].balance =
		*/
}
