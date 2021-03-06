#pragma config(Sensor, S1,     BillReader,     sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorA,          MotorA,        tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{

	motor[MotorA] = 25;
  //SensorType[S1] = sensorColorNxtFULL;
	for (int i = 0; i < 20; i++)
	{
    delay(300);
		while (getColorName(BillReader) == colorNone)
	  {
	  	displayString(i, "/");
	  }
		delay(300);

/*		int billColor = SensorValue[S1];
		if (billColor == 2)
			displayString(i, "BLUE");
		else if (billColor == 3)
			displayString(i, "GREEN");
	  else if (billColor == 4)
	  	displayString(i, "YELLOW");
	  else if (billColor == 5)
  	  displayString(i, "RED");
  	else
  		displayString(i, "NONE");
		*/
		TLegoColors colorName = getColorName(BillReader);
		int colorHue = getColorHue(BillReader);
	  if (colorName == colorBlue)
	  {
	  	displayString(i, "BLUE");
	  }
	  else if (colorName == colorGreen)
	  {
	  	displayString(i, "GREEN");
	  }
	  else if (colorName == colorWhite)
	  {
	  	displayString(i, "WHITE");
	  }
	  else if (colorName == colorRed)
	  {
	  	displayString(i, "RED");
	  }
	  else if (colorName == colorBrown)
	  {
	  	displayString(i, "YELLOW");
	  }
	  else
	  {
	  	displayString(i, "%d", colorHue);
	  }
	  delay(400);
	  while (getColorName(BillReader) == colorName)
	  {}
	  delay(400);
	}
	delay(1000);
	motor[MotorA] = 0;
}
