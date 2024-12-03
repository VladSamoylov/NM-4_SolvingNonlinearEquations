#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>

using namespace std;

double Function(const double& x) {

	return x + 4 * pow(x, 3) - 12;
}

void HalfDivitionMethod(double& a, double& b, const double& error) {

	if (Function(a) * Function(b) >= 0) throw "Error: <Function have similar signs at a and b>";

	double X_mid = 0.0;
	double X = 0.0;
	int iterator = 0;
	do {
		X_mid = (a + b) / 2;
		if (Function(X_mid) == 0) {
			X = X_mid;
			break;
		}
		if (Function(a) * Function(X_mid) < 0) b = X_mid;
		else a = X_mid;
		iterator++;
	} while (abs(a-b) > error);
	if (Function(X_mid) != 0) X = (a + b) / 2;

	cout << "X: " << X << " n - " << iterator << endl;
}

void ChordMethod(function<double(double)> f, function<double(double)> f_sderiv, const double& a, const double& b, const double& error) {

	if (f(a) * f(b) >= 0) throw "Error: <Function have similar signs at a and b>";

	double X, X_new;
	int iterat = 0;

	if (f(a) * f_sderiv(a) > 0) {
		cout << "f(a) * f_deriv(a) = " << f(a) * f_sderiv(a) << " > 0" << endl;
		cout << "Fix left point (a) as interval boundary" << endl;
		X = b;
		X_new = X;
		cout << setw(4) << "n" << setw(10) << "a" << setw(10) << "b" << setw(10) << "f(a)" << setw(10) << "f(b)" << endl;
		do {
			X = X_new;
			cout << setw(4) << iterat << setw(10) << a << setw(10) << X << setw(10) << f(a) << setw(10) << f(X) << endl;
			X_new = X - (f(X) * (X - a)) / (f(X) - f(a));
			iterat++;
		} while (abs(X_new - X) > error);
		cout << setw(4) << iterat << setw(10) << a << setw(10) << X_new << setw(10) << f(a) << setw(10) << f(X_new) << endl;
		
	}
	else {
		cout << "f(a) * f_deriv(a) = " << f(a) * f_sderiv(a) << " < 0" << endl;
		cout << "Fix right point (b) as interval boundary" << endl;
		X = a;
		X_new = X;
		cout << setw(4) << "n" << setw(10) << "a" << setw(10) << "b" << setw(10) << "f(a)" << setw(10) << "f(b)" << endl;
		do {
			X = X_new;
			cout << setw(4) << iterat << setw(10) << X << setw(10) << b << setw(10) << f(X) << setw(10) << f(b) << endl;
			X_new = X - (f(X) * (X - b)) / (f(X) - f(b));
			iterat++;
		} while (abs(X_new - X) > error);
	}

}

int main() {
	double a = 1.3, b = 1.4;
	auto f_test = [](double x) {return x + 4 * pow(x, 3) - 12; };
	auto fSDeriv_test = [](double x) {return 24 * x; };
	cout << "Hello w" << endl;
	try {
		//HalfDivitionMethod(a, b, 0.0001);
	}
	catch (const char* err) {
		cerr << err << endl;
	}
	try {
		ChordMethod(f_test, fSDeriv_test, 1, 2, 0.001);
	}
	catch (const char* err) {
		cerr << err << endl;
	}

	return 0;
}