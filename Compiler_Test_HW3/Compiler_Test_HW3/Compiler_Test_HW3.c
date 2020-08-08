#include <stdio.h>

void main()
{
	int a = 0;
	int b = 1;
	b += 3;

	printf("%d\n", !a);
	printf("%d\n", !b);
	printf("%d\n", b);

	int one = 2 * (5 - 3) / 4;
	int i = -1;
	int led = 26;
	while (++i <= 1)
	{
		int j = 0;
		int led = 26;
		do
		{
			if (i == 0 && j == 0)
			{
				led = 26;
			}
			else
			{
				if (i == 0 && j == 1)
				{
					led = 27;
				}
				else
				{
					if (i == 1 && j == 0)
					{
						led = 28;
					}
					else
					{
						led = 29;
					}
				}
			}

			//digitalWrite(led, 1);
			//delay(one * 1000);
		} while (++j <= 1);
	}

	do
	{
		//digitalWrite(led, 0);
		led = led + one;
	} while (led <= 29);

	//delay(one * 1000);
}
