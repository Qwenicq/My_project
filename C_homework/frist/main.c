#include<stdio.h>
int main()
{
	float w, h;
	int t;
	printf("Please enter h,w:\n");
	scanf_s("%f,%f", &h, &w);
	t = (int)(w / (h * h));
	if (t < 18)
	{
		printf("Lower weight!\n");
	}
	else if (t >= 18 && t < 25)
	{
		printf("Standard weight!\n");
	}
	else if (t >= 25 && t < 27)
	{
		printf("Higher weight!\n");
	}
	else
	{
		printf("Too fat!\n");
	}
	return 0;
}
