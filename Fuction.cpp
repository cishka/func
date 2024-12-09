#include <stdio.h>
#include <math.h>
#define M_PI 3.1415926535897923846


double choosen_number = 0.0;
int accuracy = 0;
int amount_number = 0;
int amount_experim = 0;
int mode = 0;
int global_mode = 0;


double rounding(double num, int exactness) {
	double factor = pow(10, exactness);
	return round(num * factor) / factor;
}

long long Factoiral(int a) {
	if (a == 0) {
		return 0;
	}
	double result = 1;
	for (int i = 1; i <= a; ++i) {
		result *= i;
	}
	return result;
}


double sine_taylor(double x, int terms, int accuracy) {
	double sin_x = 0.0;
	x = fmod(x, 2 * M_PI);
	for (int i = 0; i < terms; ++i) {
		double term = pow(-1, i) * pow(x, 2 * i + 1) / (double)Factoiral(2 * i + 1);
		sin_x += term;
	}
	return rounding(sin_x, accuracy);
}


double cos_taylor(double x, int terms, int accuracy) {
	double cos_x = 0.0;
	x = fmod(x, 2 * M_PI);
	for (int i = 0; i < terms; ++i) {
		double term = pow(-1, i) * pow(x, 2 * i) / Factoiral(2 * i);
		cos_x += term;
	}
	return rounding(cos_x,accuracy);
}


double exp_taylor(double x, int terms, int accuracy) {
	double exp_x = 0.0;
	x = fmod(x, 2 * M_PI);
	for (int i = 0; i < terms; ++i) {
		double term = pow(x, i) / Factoiral(i);
		exp_x += term;
	}
	return rounding(exp_x,accuracy);
}


double csc_taylor(double x, int terms, int accuracy) {
	if (x == 0) {
		return NAN;
	}
	double sin_x = x;
	double csc_x = 1 / sin_x;
	x = fmod(x, 2 * M_PI);
	for (int n = 1; n <= terms; ++n) {
		double term = pow(-1, n) * pow(x, 2 * n + 1) / Factoiral(2 * n + 1);
		sin_x += term;
	}
	csc_x = 1 / sin_x;
	return rounding(csc_x, accuracy);
}

void Vvod_Parametrov() {
	printf("Select number for function\nNumber:");
	scanf_s("%lf", &choosen_number);
	printf("Select the accuracy\nAccuracy:");
	scanf_s("%d", &accuracy);
	printf("Select amount number in Taylor\nAmount:");
	scanf_s("%d", &amount_number);
}


void print_result(double benchmark, double calculated, double difference, int amount_number){
	printf("Benchmark result: %.10f\n", benchmark);
	printf("Calculacted result: %.10f\n", calculated);
	printf("Difference between bencmark and calculated: %lf\n", difference);
	printf("Amount of number in Taylor: %d\n", amount_number);
	}


double (*function[4])(double, int, int) = { sine_taylor, cos_taylor, exp_taylor, csc_taylor };


void print_result_experiment(double (*func)(double, int, int), double x, int amount_of_number, int accuracy) {
	double taylor_value = 0.0;
	double term = 0.0;

	printf("Taylor series iterations:\n");
	for (int i = 0; i < amount_of_number; ++i) {
		if (func == sine_taylor) {
			term = (i % 2 == 0 ? 1 : -1) * pow(x, 2 * i + 1) / Factoiral(2 * i + 2);
		}
		else if (func == cos_taylor) {
			term = (i % 2 == 0 ? 1 : -1) * pow(x, 2 * i) / Factoiral(2 * i + 1);
		}
		else if (func == exp_taylor) {
			term = pow(x, i) / Factoiral(i + 1);
		}
		else if (func == csc_taylor) {
			term = 1 / ((i % 2 == 0 ? 1 : -1) * pow(x, 2 * i + 1) / Factoiral(2 * i + 2));
		}

		taylor_value += term;
		printf("Iteration %d: %.10f\n", i + 1, rounding(taylor_value, accuracy));

		printf("\n");
		double benchmark_result = 0.0;
		if (func == sine_taylor) benchmark_result = sin(x);
		else if (func == cos_taylor) benchmark_result = cos(x);
		else if (func == exp_taylor) benchmark_result = exp(x);
		else if (func == csc_taylor) benchmark_result = cosh(x);
		printf("\nFinal result: %.10f\n", rounding(taylor_value, accuracy));
		printf("Benchmark result: %.10f\n", rounding(benchmark_result, accuracy));
		printf("Difference: %.10f\n\n", fabs(taylor_value - benchmark_result));
	}
}

int main() {
	printf("Select mode:\n");
	printf("1- One calcuted\n");
	printf("2- Experiment series\n");

	scanf_s("%d", &global_mode);

	if (global_mode == 1) {
		do {
			printf("Choose operatng:\n");
			printf("1-Calculating a sinus\n");
			printf("2-Calculating a cosinus\n");
			printf("3-Calculating a exp\n");
			printf("4-Calculating a csc\n");
			printf("0-finish programm\n");
			scanf_s("%d", &mode);

			Vvod_Parametrov();

			double calculated = function[mode - 1](choosen_number, amount_number, accuracy);
			double benchmark = 0.0;
			if (mode == 1) {
				benchmark = sin(choosen_number);
			}
			if (mode == 2) {
				benchmark = cos(choosen_number);
			}
			if (mode == 3) {
				benchmark = exp(choosen_number);
			}
			if (mode == 4) {
				benchmark = 1/(sin(choosen_number));
			}
			double difference = fabs(calculated - benchmark);
			print_result(benchmark, calculated, calculated, amount_number);
		} while (mode != 0);
	}
	else if (global_mode == 2) {

		printf("Choose operatng:\n");
		printf("1-Calculating a sinus\n");
		printf("2-Calculating a cosinus\n");
		printf("3-Calculating a exp\n");
		printf("4-Calculating a csc\n");
		printf("0-finish programm");
		scanf_s("%d", &mode);
		printf("Amount of calculation:");
		scanf_s("%d", &amount_experim);

		Vvod_Parametrov();

		for (int i = 1; i <= amount_experim; ++i) {
			double calculated = 0.0;
			double bencmark = 0.0;
			double difference = 0.0;
			 
			calculated = function[mode - 1](choosen_number, amount_number, accuracy);

			if (mode == 1) {
				bencmark = sin(choosen_number);
			}
			if (mode == 2) {
				bencmark = cos(choosen_number);
			}
			if (mode == 3) {
				bencmark = exp(choosen_number);
			}
			if (mode == 4) {
				bencmark = 1/(sin(choosen_number));
			}

			difference = fabs(calculated - bencmark);
			print_result_experiment(function[mode-1],choosen_number, amount_number, accuracy);
		}
	}
	return 0;

}