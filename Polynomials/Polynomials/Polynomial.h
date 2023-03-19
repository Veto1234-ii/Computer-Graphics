#pragma once

#pragma once
#include <string>
#include <iostream>
#include <istream>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;

const int p = 21;

struct Monom {

	double c;
	int s;



	Monom(double c = 1.0, int x = 0, int y = 0, int z = 0);


	int getX();


	int getY();


	int getZ();

	double calc_value_monom(int x, int y, int z);

	Monom multipl_monomials(Monom& monom) {

		double c_res = c * monom.c;

		int x_res = getX() + monom.getX();
		int y_res = getY() + monom.getY();
		int z_res = getZ() + monom.getZ();

		return Monom(c_res, x_res, y_res, z_res);
	}

	friend ostream& operator<<(ostream& out, Monom& m) {

		int t;

		if (m.c > 0.0) out << "+ ";

		out << m.c;

		t = m.getX();

		if (t != 0) out << "x^" << t;


		t = m.getY();

		if (t != 0) out << "y^" << t;


		t = m.getZ();

		if (t != 0) out << "z^" << t;


		return out;
	}
	friend istream& operator>>(istream& in, Monom& monom) {


		string input;
		in >> input;

		string p = "xyz";
		string op = "+-";
		string tmp = "";

		monom.c = 1.0;
		monom.s = 0;


		int k;
		int l;
		int y;

		double coef;
		int s = 0;
		int fl = 0;

		for (int i = 0; i < input.size(); i++) {
			char c = input[i];
			k = p.find(c);

			if (k >= 0) {

				if (fl == 0) {

					if ((tmp == "") || (tmp == "-") || (tmp == "+")) {
						coef = 1.0;
					}
					else coef = stof(tmp);

					tmp = "";
					fl = 1;
				}

				switch (c) {

				case 'x':
					if ((i == input.size() - 1) || (input[i + 1] != '^')) {
						s += 1;
					}

					if (input[i + 1] == '^') {
						string m;

						l = op.find(input[i + 2]);

						if (l >= 0) {
							m += input[i + 2];

							if (input[i + 3] >= '0' && input[i + 3] <= '9') m += input[i + 3];

							if (i + 4 < input.size())

								if (input[i + 4] >= '0' && input[i + 4] <= '9') m += input[i + 4];

							y = atoi(m.c_str());

							if (y < 0) y = 10 + y * (-1);

							s += y;
						}
						else {
							if (input[i + 2] >= '0' && input[i + 2] <= '9') m += input[i + 2];

							if (i + 3 < input.size())

								if (input[i + 3] >= '0' && input[i + 3] <= '9') m += input[i + 3];

							y = atoi(m.c_str());

							if (y < 0) y = 10 + y * (-1);

							s += y;
						}

					}

					break;


				case 'y':
					if ((i == input.size() - 1) || (input[i + 1] != '^')) {
						s += 21;
					}

					if (input[i + 1] == '^') {
						string m;
						l = op.find(input[i + 2]);

						if (l >= 0) {

							m += input[i + 2];

							if (input[i + 3] >= '0' && input[i + 3] <= '9') m += input[i + 3];

							if (i + 4 < input.size()) {
								if (input[i + 4] >= '0' && input[i + 4] <= '9') m += input[i + 4];
							}

							y = atoi(m.c_str());

							if (y < 0) y = 10 + y * (-1);

							y *= 21;
							s += y;
						}
						else {
							if (input[i + 2] >= '0' && input[i + 2] <= '9') m += input[i + 2];

							if (i + 3 < input.size())

								if (input[i + 3] >= '0' && input[i + 3] <= '9') m += input[i + 3];

							y = atoi(m.c_str());

							if (y < 0) y = 10 + y * (-1);

							y *= 21;
							s += y;
						}

					}


					break;

				case 'z':
					if ((i == input.size() - 1) || (input[i + 1] != '^')) {
						s += 21 * 21;
					}

					if (input[i + 1] == '^') {
						string m;

						l = op.find(input[i + 2]);

						if (l >= 0) {
							m += input[i + 2];

							if (input[i + 3] >= '0' && input[i + 3] <= '9') m += input[i + 3];

							if (i + 4 < input.size())

								if (input[i + 4] >= '0' && input[i + 4] <= '9') m += input[i + 4];

							y = atoi(m.c_str());

							if (y < 0) y = 10 + y * (-1);

							y *= 21 * 21;
							s += y;
						}
						else {
							if (input[i + 2] >= '0' && input[i + 2] <= '9') m += input[i + 2];

							if (i + 3 < input.size())

								if (input[i + 3] >= '0' && input[i + 3] <= '9') m += input[i + 3];

							y = atoi(m.c_str());

							if (y < 0) y = 10 + y * (-1);

							y *= 21 * 21;
							s += y;
						}

					}

					break;

				}


			}

			tmp += c;
		}

		if (fl == 0) {
			s = 0;
			coef = stof(input);
		}


		monom.c = coef;
		monom.s = s;

		return in;
	}
};

struct Link {
	Monom m;
	Link* next;

	Link(Monom _m, Link* _n = nullptr) :m(_m), next(_n) {}
};
// упорядоченная вставка

class List {
	Link* start;
	Link* end;
public:
	List() {
		Monom m(0, 0, 0, 0);
		Link* p = new Link(m);

		p->next = p;

		start = p;
		end = p;
	}

	void addLast(Monom a) {


		Link* p = new Link(a, start);

		end->next = p;

		end = end->next;

	}

	List(const List& l) {

		Monom m(0, 0, 0, 0);

		start = new Link(m);
		start->next = start;

		end = start;

		Link* t = l.start->next;

		while (t != l.start) {

			addLast(t->m);
			t = t->next;
		}

	}
	bool IsEmpty() { return start->next == start; }

	List& operator=(List list) {

		if (this == &list) return list;

		if (list.IsEmpty()) {

			Monom m(0, 0, 0, 0);

			Link* p = new Link(m);

			p->next = p;

			start = p;
			end = p;

			return *this;
		}

		clean();

		Monom m(0, 0, 0, 0);

		Link* p = new Link(m);

		p->next = p;

		start = p;
		end = p;

		Link* t = list.start->next;

		Link* tmp = start->next;

		while (t != list.start) {

			add(t->m);
			t = t->next;

		}

		return *this;

	}

	void add(Monom a) {
		Link* tmp;
		tmp = start;



		while (tmp->next != start) {

			if (tmp->next->m.s > a.s) {

				Link* b = new Link(a, tmp->next);
				tmp->next = b;
				return;
			}


			tmp = tmp->next;

		}
		Link* c = new Link(a, start);

		tmp->next = c;

	}

	friend ostream& operator<<(ostream& out, List& list) {
		Link* tmp = list.start->next;

		while (tmp != list.start) {
			out << tmp->m << " ";
			tmp = tmp->next;
		}

		cout << endl;
		return out;
	}

	void del_first() {

		Link* tmp;
		if (start->next == start) throw - 1;

		tmp = start->next;
		start->next = tmp->next;
		delete tmp;

		if (start->next == start) end = start;

	}

	void clean() {

		while (start->next != start)
			del_first();

	}


	friend istream& operator>>(istream& in, List& p) {

		string str;
		in >> str;

		string t;

		p.clean();

		str += " ";

		for (int i = 0; i < str.size(); i++) {
			char c = str[i];

			if (((c == ' ') || (c == '+') || (c == '-')) && (str[i - 1] != '^')) {

				if (t.size() > 0) {
					istringstream ss(t);
					Monom m;
					ss >> m;
					p.add(m);
				}

				t = "";

				if (c == '-') {
					t += "-";
				}

			}
			else {
				t += c;
			}
		}
		return in;
	}

	~List() {

		clean();
		delete start;
	}

	double calculate_value(int x, int y, int z) {

		double res = 0;

		Link* tmp;

		tmp = start->next;

		while (tmp != start) {

			res += tmp->m.calc_value_monom(x, y, z);

			tmp = tmp->next;

		}

		return res;
	}

	List add_polynomials(List& list) {

		Link* tmp1;
		Link* tmp2;

		tmp1 = start->next;
		tmp2 = list.start->next;

		List res;

		while ((tmp1 != start) && (tmp2 != list.start)) {

			if (tmp1->m.s < tmp2->m.s) {
				res.addLast(tmp1->m);
				tmp1 = tmp1->next;
			}
			else if (tmp2->m.s < tmp1->m.s) {
				res.addLast(tmp2->m);
				tmp2 = tmp2->next;
			}
			else {
				if (tmp1->m.c + tmp2->m.c != 0) {
					Monom m(tmp1->m.c + tmp2->m.c, tmp1->m.getX(), tmp1->m.getY(), tmp1->m.getZ());

					res.addLast(m);
				}


				tmp1 = tmp1->next;
				tmp2 = tmp2->next;

			}
		}

		while (tmp1 != start) {
			res.addLast(tmp1->m);
			tmp1 = tmp1->next;
		}

		while (tmp2 != list.start) {
			res.addLast(tmp2->m);
			tmp2 = tmp2->next;
		}

		return res;
	}

	List sub_polynomials(List& list) {

		Link* tmp1;
		Link* tmp2;

		tmp1 = start->next;
		tmp2 = list.start->next;

		List res;

		while ((tmp1 != start) && (tmp2 != list.start)) {

			if (tmp1->m.s < tmp2->m.s) {
				res.addLast(tmp1->m);
				tmp1 = tmp1->next;
			}
			else if (tmp2->m.s < tmp1->m.s) {

				Monom m((-1) * tmp2->m.c, tmp2->m.getX(), tmp2->m.getY(), tmp2->m.getZ());

				res.addLast(m);
				tmp2 = tmp2->next;
			}
			else {
				if (tmp1->m.c - tmp2->m.c != 0) {

					Monom m(tmp1->m.c - tmp2->m.c, tmp1->m.getX(), tmp1->m.getY(), tmp1->m.getZ());

					res.addLast(m);
				}


				tmp1 = tmp1->next;
				tmp2 = tmp2->next;

			}
		}

		while (tmp1 != start) {
			res.addLast(tmp1->m);
			tmp1 = tmp1->next;
		}

		while (tmp2 != list.start) {
			Monom m((-1) * tmp2->m.c, tmp2->m.getX(), tmp2->m.getY(), tmp2->m.getZ());

			res.addLast(m);
			tmp2 = tmp2->next;
		}

		return res;
	}

	List multipl_polynomials(List& list) {

		List l;
		List res;


		Link* tmp1;
		Link* tmp2;

		tmp1 = start->next;
		tmp2 = list.start->next;


		while (tmp1 != start) {

			while (tmp2 != list.start) {

				Monom mn = tmp1->m.multipl_monomials(tmp2->m);

				l.add(mn);

				tmp2 = tmp2->next;

			}

			tmp2 = list.start->next;

			tmp1 = tmp1->next;

		}


		tmp1 = l.start->next;
		tmp2 = tmp1->next;

		int fl = 0;



		while (tmp1 != l.start) {
			double sm = 0.0;


			while ((tmp2 != l.start)) {

				if (tmp1->m.s == tmp2->m.s) {

					sm += tmp2->m.c;
					fl++;
				}

				tmp2 = tmp2->next;
			}

			if (fl > 0) {

				sm += tmp1->m.c;

				Monom mn(sm, tmp1->m.getX(), tmp1->m.getY(), tmp1->m.getZ());

				res.add(mn);

				fl++;

				while (fl != 0) {
					tmp1 = tmp1->next;
					fl--;
				}

			}
			else {
				res.add(tmp1->m);
				tmp1 = tmp1->next;

			}
			fl = 0;


			tmp2 = tmp1->next;
		}


		return res;
	}

};






