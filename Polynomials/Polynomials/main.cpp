
#include "Polynomial.h"

int main() {

	ifstream f;

	f.open("Pol.txt");

	List p1, p2;
	f >> p1;
	f >> p2;

	cout << p1;
	cout << endl;

	cout << p2;
	cout << endl;

	List res;
	res = p1.add_polynomials(p2);

	//res = p1.sub_polynomials(p2);

	//res = p1.multipl_polynomials(p2);

	//cout<<p2.calculate_value(1, 1, 2)<<endl;
	cout << res;


	//string m = "-12.5x^2y^-3";
	//string polinom = "12.5x^-10z^5-2.6x^2y^5+10";


	//Monom m(1.5, 2, -3, 4);
	//cout << m.calc_value_monom(1, 1, 2) << endl;

	//istringstream m_in(m);

	//m_in >> m;
	//cout << m << endl;

	//List p;


	//istringstream p_in(polinom);
	//p_in >> p;
	//cout << p << endl;

	return 0;
}
