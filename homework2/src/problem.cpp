#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

class Polynomial;

class Term {
	friend Polynomial;
	private:
		float coef;
		int exp;
};

class Polynomial {
	private:
		Term* termArray;
		int capacity;
		int terms;
	public:
		Polynomial() :capacity(2), terms(0) {
			termArray = new Term[capacity];
		}
		void newTerm(const float theCoef, const int theExp);
		Polynomial Add(const Polynomial &b);
		Polynomial Mult(const Polynomial &b);
		double Eval(double x);
		void show();
};

void Polynomial::newTerm(const float theCoef, const int theExp) {
	if (theCoef == 0) return;
	if (terms == capacity) {
		capacity *= 2;
		Term* temp = new Term[capacity];
		copy(termArray, termArray + terms, temp);
		delete []termArray;
		termArray = temp;
	}
	termArray[terms].coef = theCoef;
	termArray[terms++].exp = theExp;
}

Polynomial Polynomial::Add(const Polynomial &b) {
	Polynomial c;
	int aPos = 0, bPos = 0;
	while ((aPos < terms) && (bPos < b.terms)) {
		if (termArray[aPos].exp == b.termArray[bPos].exp) {
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t) c.newTerm(t,termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp) {
			c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else {
			c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	}
	for (; aPos < terms; aPos++)
		c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.terms; bPos++)
		c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c;
}

Polynomial Polynomial::Mult(const Polynomial &b) {
	Polynomial c; 
	for (int i = 0; i < b.terms; i++) {
		Polynomial temp; 
		for (int j = 0; j < terms; j++) {
			float newCoef = termArray[j].coef * b.termArray[i].coef;
			int newExp = termArray[j].exp + b.termArray[i].exp;
			temp.newTerm(newCoef, newExp); 
		}
		c = c.Add(temp);
	}

	return c;
}

double Polynomial::Eval(double x) {
	double f=0.0;
	for (int i = 0; i < terms; i++) {
		f += termArray[i].coef * pow(x, termArray[i].exp);
	}
	return f;
}

void Polynomial::show() {
	if (terms == 0) {
		cout << "0" << endl;
		return;
	}
	for (int i = 0; i < terms; i++) {
		if (i > 0 && termArray[i].coef > 0) { cout << "+" ; }
		else if (termArray[i].coef < 0) { cout << " "; }

		cout << termArray[i].coef;
		if (termArray[i].exp) {
			cout << "x";
			if (termArray[i].exp > 1) { cout << "^" << termArray[i].exp; }
		}
	}
	cout << endl;
}

int main() {
	Polynomial A, B, C, D;
	int choise=1;
	double x = 0, y = 0, a = 0, b = 0;

	cout << "輸入格式:項數 係數 指數 係數 指數.."<<endl;
	cout << "ex: 3x^2 + 2x + 1: 3 3 2 2 1 1 0" << endl;

	cout << "輸入A多項式: ";
	int numA;
	if (cin >> numA) {
		for (int i = 0; i < numA; i++) {
			float c;
			int e;
			cin >> c >> e;
			A.newTerm(c, e);
		}
	}

	cout << "輸入B多項式: ";
	int numB;
	if (cin >> numB) {
		for (int i = 0; i < numB; i++) {
			float c;
			int e;
			cin >> c >> e;
			B.newTerm(c, e);
		}
	}

	while (choise != 0) {
		cout << "============ Polynomial 選單 ============" << endl;
		cout << "1. 顯示A、B" << endl;
		cout << "2. A + B" << endl;
		cout << "3. A * B" << endl;
		cout << "4. 計算 A(x)" << endl;
		cout << "5. 計算 B(x)" << endl;
		cout << "0. 結束程式" << endl;
		cout << "選擇:";
		cin >> choise;
		switch (choise) {
		case 1:
			cout << "A ="; A.show();
			cout << "B ="; B.show();
			break;
		case 2:
			C = A.Add(B);
			cout << "A + B ="; C.show();
			break;
		case 3:
			D = A.Mult(B);
			cout << "A * B ="; D.show();
			break;
		case 4:

			cout << "輸入x:";
			cin >> x;
			a=A.Eval(x);
			cout << "A(" << x << ") =" << a << endl;
			break;
		case 5:

			cout << "輸入x:";
			cin >> y;
			b = B.Eval(y);
			cout << "A(" << y << ") =" << b << endl;
			break;
		case 0:
			cout << "結束程式" << endl;
			break;
		}
	}
	return 0;
}