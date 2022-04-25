int	main(void)
{
	char	timer;
	
	timer = 50;
	while (1)
	{
		gpio2 = readPin(gpio3);
		delay(1);
		if (!--timer)
		{
			resetPin(gpio1);
			setPin(gpio1);
			timer = 50;
		}
	}
}

