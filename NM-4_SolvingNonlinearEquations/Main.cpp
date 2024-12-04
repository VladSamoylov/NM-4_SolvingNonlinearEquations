#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>

#define ANSI_COLOR_BLUE "\033[34m"
#define ANSI_COLOR_RESET "\033[0m"
#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_RED "\033[31m"

using namespace std;

/**
 * @brief Функція знаходження дійсного корення нелінійного рівняння методом половинного розподілу
 * @param f Нелінійне рівняння
 * @param a Початкова границя
 * @param b Кінцева границя
 * @param error Погрішність знаходження кореня
 */
void HalfDivitionMethod(function<double(double)> f, double a, double b, const double& error) {

	if (f(a) * f(b) >= 0) throw "Error: <Function have similar signs at a and b>";

	double X_mid = 0.0;
	double X = 0.0;
	int iterator = 0;
	cout << setw(4) << "n" << setw(10) << "a" << setw(10) << "b" << setw(10) << "Xmid" << setw(12) << "f(a)" << setw(12) << "f(b)" << setw(12) << "f(Xmid)" << endl;
	do {
		X_mid = (a + b) / 2;
		cout << setw(4) << iterator << setw(10) << a << setw(10) << b << setw(10) << X_mid << setw(12) << f(a) << setw(12) << f(b) << setw(12) << f(X_mid) << endl;
		if (f(X_mid) == 0) {
			X = X_mid;
			break;
		}
		if (f(a) * f(X_mid) < 0) b = X_mid;
		else a = X_mid;
		iterator++;
	} while (abs(a-b) > error);
	if (f(X_mid) != 0) X = (a + b) / 2;
	cout << setw(4) << iterator << setw(10) << a << setw(10) << b << setw(10) << X << setw(12) << f(a) << setw(12) << f(b) << setw(12) << f(X) << endl;
	cout << "\nX = " << ANSI_COLOR_GREEN << X << ANSI_COLOR_RESET << " f(X) = " << ANSI_COLOR_RED << f(X) << ANSI_COLOR_RESET << endl;
}

/**
 * @brief Функція знаходження дійсного корення нелінійного рівняння методом хорд
 * @param f Нелінійне рівняння
 * @param f_sderiv Друга похідна нелінійного рівняння
 * @param a Початкова границя
 * @param b Кінцева границя
 * @param error Погрішність знаходження кореня
 */
void ChordMethod(function<double(double)> f, function<double(double)> f_sderiv, const double& a, const double& b, const double& error) {

	if (f(a) * f(b) >= 0) throw "Error: <Function have similar signs at a and b>";

	double X, X_new;
	int iterat = 0;

	if (f(a) * f_sderiv(a) > 0) {
		cout << "f(a) * f_deriv(a) = " << f(a) * f_sderiv(a) << " > 0" << endl;
		cout << "Fix left point (a) as interval boundary" << endl;
		X = b;
		X_new = X;
		cout << setw(4) << "n" << setw(15) << "a" << setw(15) << "b" << setw(15) << "f(a)" << setw(15) << "f(b)" << endl;
		do {
			X = X_new;
			cout << setw(4) << iterat << setw(15) << a << setw(15) << X << setw(15) << f(a) << setw(15) << f(X) << endl;
			X_new = X - (f(X) * (X - a)) / (f(X) - f(a));
			iterat++;
		} while (abs(X_new - X) > error);
		cout << setw(4) << iterat << setw(15) << a << setw(15) << X_new << setw(15) << f(a) << setw(15) << f(X_new) << endl;
		cout << "\nX = " << ANSI_COLOR_GREEN << X_new << ANSI_COLOR_RESET << " f(X) = " << ANSI_COLOR_RED << f(X_new) << ANSI_COLOR_RESET << endl;
	}
	else {
		cout << "f(a) * f_deriv(a) = " << f(a) * f_sderiv(a) << " < 0" << endl;
		cout << "Fix right point (b) as interval boundary" << endl;
		X = a;
		X_new = X;
		cout << setw(4) << "n" << setw(15) << "a" << setw(15) << "b" << setw(15) << "f(a)" << setw(15) << "f(b)" << endl;
		do {
			X = X_new;
			cout << setw(4) << iterat << setw(15) << X << setw(15) << b << setw(15) << f(X) << setw(15) << f(b) << endl;
			X_new = X - (f(X) * (X - b)) / (f(X) - f(b));
			iterat++;
		} while (abs(X_new - X) > error);
		cout << setw(4) << iterat << setw(15) << X_new << setw(15) << b << setw(15) << f(X_new) << setw(15) << f(b) << endl;
		cout << "\nX = " << ANSI_COLOR_GREEN << X_new << ANSI_COLOR_RESET << " f(X) = " << ANSI_COLOR_RED << f(X_new) << ANSI_COLOR_RESET << endl;
	}
}

/**
 * @brief Функція знаходження дійсного корення нелінійного рівняння методом дотичних (Ньютона)
 * @param f Нелінійне рівняння
 * @param df Перша похідна нелінійного рівняння
 * @param f_sderiv Друга похідна нелінійного рівняння
 * @param a Початкова границя
 * @param b Кінцева границя
 * @param error Погрішність знаходження кореня
 */
void TangentMethod(function<double(double)> f, function<double(double)> df, function<double(double)> f_sderiv, const double& a, const double& b, const double& error) {
	
	if (f(a) * f(b) >= 0) throw "Error: <Function have similar signs at a and b>";

	double X, X_new;
	int iterat = 0;

	if (f(a) * f_sderiv(a) > 0) {
		cout << "f(a) * f_deriv(a) = " << f(a) * f_sderiv(a) << " > 0" << endl;
		cout << "Left point (a) as X" << endl;
		X = a;
	}
	else {
		cout << "f(a) * f_deriv(a) = " << f(a) * f_sderiv(a) << " < 0" << endl;
		cout << "Left point (b) as X" << endl;
		X = b;
		X_new = X;
	}
	cout << setw(4) << "n" << setw(15) << "a" << setw(15) << "f(X)" << setw(15) << "f'(X)" << endl;
	do {
		X = X_new;
		cout << setw(4) << iterat << setw(15) << X << setw(15) << f(X) << setw(15) << df(X) << endl;
		X_new = X - (f(X) / df(X));
		iterat++;
	} while (abs(X_new - X) > error);
	cout << setw(4) << iterat << setw(15) << X_new << setw(15) << f(X) << setw(15) << df(X_new) << endl;
	cout << "\nX = " << ANSI_COLOR_GREEN << X_new << ANSI_COLOR_RESET << " f(X) = " << ANSI_COLOR_RED << f(X_new) << ANSI_COLOR_RESET << endl;
}

int main() {

	double a_test = 1.3, b_test = 1.4;
	auto f_test = [](double x) {return x + 4 * pow(x, 3) - 12; };
	auto fSDeriv_test = [](double x) {return 24 * x; };
	auto dfx_test = [](double x) {return 1 + 12 * pow(x, 2); };

	double a1 = 0, b1 = 2, error = 0.0001;
	auto f1 = [](double x) {return 3 * pow(x, 4) + 8 * pow(x, 3) + 6 * pow(x, 2) - 11; };
	auto dfx1 = [](double x) {return 12 * pow(x, 3) + 24 * pow(x, 2) + 12 * x; };
	auto dsfx1 = [](double x) {return 36 * pow(x, 2) + 48 + 12; };

	try {
		cout << "---------HalfDivitionMethod---------" << endl;
		//HalfDivitionMethod(f_test, a_test, b_test, 0.0001);
		HalfDivitionMethod(f1, a1, b1, error);
	}
	catch (const char* err) {
		cerr << err << endl;
	}
	try {
		cout << "---------Welcome to ChordMethod---------" << endl;
		//ChordMethod(f_test, fSDeriv_test, 1, 2, 0.001);
		ChordMethod(f1, dsfx1, a1, b1, error);
	}
	catch (const char* err) {
		cerr << err << endl;
	}
	try {
		cout << "---------Welcome to TangentMethod---------" << endl;
		//TangentMethod(f_test, dfx_test, fSDeriv_test, 1, 2, 0.001);
		TangentMethod(f1, dfx1, dsfx1, a1, b1, error);
	}
	catch (const char* err) {
		cerr << err << endl;
	}
	cout << "\n____________Task 2____________\n\n";
	double a2 = 0, b2 = 1;
	auto f2 = [](double x) {return 3 - exp(x) - pow(5, x); };
	auto dfx2 = [](double x) {return -exp(x) - log(5) * pow(5, x); };
	auto dsfx2 = [](double x) {return -exp(x) - pow(log(5), 2) * pow(5, x); };
	try {
		cout << "---------HalfDivitionMethod---------" << endl;
		HalfDivitionMethod(f2, a2, b2, error);
	}
	catch (const char* err) {
		cerr << err << endl;
	}
	try {
		cout << "---------Welcome to ChordMethod---------" << endl;
		ChordMethod(f2, dsfx2, a2, b2, error);
	}
	catch (const char* err) {
		cerr << err << endl;
	}
	try {
		cout << "---------Welcome to TangentMethod---------" << endl;
		TangentMethod(f2, dfx2, dsfx2, a2, b2, error);
	}
	catch (const char* err) {
		cerr << err << endl;
	}

	return 0;
}