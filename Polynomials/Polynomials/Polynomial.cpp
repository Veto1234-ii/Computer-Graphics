#include "Polynomial.h"

Monom::Monom(double c, int x, int y, int z) {
	this->c = c;

	if (x < 0) x = 10 + x * (-1);
	if (y < 0) y = 10 + y * (-1);
	if (z < 0) z = 10 + z * (-1);

	s = x + y * p + z * p * p;
}

int Monom::getX() {
	int t = s % p;
	if (t > 10) t = 10 - t;

	return t;
}

int Monom::getY() {

	int t = (s / p) % p;
	if (t > 10) t = 10 - t;


	return t;
}

int Monom::getZ() {

	int t = (s / (p * p)) % p;
	if (t > 10) t = 10 - t;

	return t;
}

double Monom::calc_value_monom(int x, int y, int z) {

	double res = 1.0;
	res *= c;

	int vx = getX();
	int vy = getY();
	int vz = getZ();

	if (vx < 0) res = res / pow(x, (-1) * vx);
	else res = res * pow(x, vx);

	if (vy < 0) res = res / pow(y, (-1) * vy);
	else res = res * pow(y, vy);

	if (vz < 0) res = res / pow(z, (-1) * vz);
	else res = res * pow(z, vz);

	return res;
}