#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <random>

int main(int argc, char const *argv[])
{
	int n, t;
	scanf("%d %d", &n, &t);
	double a[n][n], pi[n], l[n][n], u[n][n];

	for(int i = 0; i < n; i++)
	{
		pi[i] = i;
	}

	for(int k = 0; k < n; k++)
	{
		int k_1;
		double temp;
		double max = 0.0;

		//Finding the pivot.
		for(int i = k; i < n; i++)
		{
			if(max < abs(a[i][k]))
			{
				max = abs(a[i][k])
				k_1 = i;
			}
		}

		//Singular Matrix handling.
		if(max == 0)
		{
			printf("Error: Singluar Matrix.\n");
			return 0;
		}

		//Swapping pi[k] and pi[k prime]
		temp = pi[k];
		pi[k] = pi[k_1];
		pi[k_1] = temp;

		

	}

	return 0;
}