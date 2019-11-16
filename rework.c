#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>


float in_suf;

double f(float angle);

double f(float angle) {
	double caliber_caculation = 0.203;
	double surface = 3.14 * (caliber_caculation / 2)*(caliber_caculation / 2);
	double Coefficient =  0.337 * surface / (155*2);
	
	double cw_2 = 100 + 1000 / 3 * 0.001*203;
	double vx = 0;
	double vy = 0;
	double T;
	double P;
	double rho;




	vx = 920 * cos(angle*0.01*3.14 / 180.0);
	vy = 920 * sin(angle*0.01*3.14 / 180.0);
	double t = 0;
	double x = 0;
	double y = 0;
	do {
		x = x + 0.01 * vx;
		y = y + 0.01 * vy;

		T = 288 - 0.0065 * y;
		P = 101325 * pow((1 - 0.0065 * y / 288), (9.81 * 0.0289644 / (8.31447*0.0065)));
		rho = P * 0.0289644 / (8.31447*T);

		vx = vx - 0.01 * Coefficient*rho*rho*(1*pow(vx, 2) + cw_2 * vx);

		vy = vy - 0.01 * 9.81 - 0.01 *rho* Coefficient*(1*pow(vy, 2) + cw_2 * fabs(vy))*signbit(vy);

		t = t + 0.01;

	}while (y > 0);
	return x-19000;
	//return x;
}

void regula(float *x, float x0, float x1, float fx0, float fx1, int *itr)
{
	*x = x0 - ((x1 - x0) / (fx1 - fx0))*fx0;
	++(*itr);
	printf("Iteration no. %3d X = %7.5f \n", *itr, *x);
}

float falsi() {
	int itr = 0, maxmitr;
	float x0, x1, x2, x3, allerr;
	//printf("\nEnter the values of x0, x1, allowed error and maximum iterations:\n");
	//scanf_s("%f %f %f %d", &x0, &x1, &allerr, &maxmitr);
	x0 = 0.0;
	x1 = 4500;
	allerr = 100;
	maxmitr = 20;
	regula(&x2, x0, x1, f(x0), f(x1), &itr);
	do
	{
		if (f(x0)*f(x2) < 0)
			x1 = x2;
		else
			x0 = x2;
		regula(&x3, x0, x1, f(x0), f(x1), &itr);
		if (fabs(x3 - x2) < allerr)
		{
			printf("After %d iterations, root = %6.4f\n", itr, x3);
			
			return x3;
			break;
		}
		x2 = x3;
	} while (itr < maxmitr);
	printf("Solution does not converge or iterations not sufficient:\n");
	return 0;
	
	
}

void insufficient() {
	for (float i = 0; i < 4501; i++) {
		if (fabs(f(i)) < 100) {
			in_suf = i;
			printf("%f. Durchlauf\n", i);
			break;
			//return i;
		}
		//return i;
	}
}
int main() {
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	printf("Result with Regula-Falsi: %f\n", falsi());
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time passed:%lf\n", cpu_time_used);
	start = clock();
	insufficient();
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Result with insufficient method: %i\n", in_suf);
	printf("Time passed:%lf\n", cpu_time_used);
	system("pause");
	return 0;


}
