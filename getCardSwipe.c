
task main()
{
	SensorType[S4] = sensorColorNxtFULL;
	SensorType[S3] = sensorTouch;

	string hue;

for (int i = 0; i< 20000; i++)
	{
		displayString(0, "%i", SensorRaw[S4]);
		wait1Msec(100);
	}

}
