# 41443106

作業二

## 解題說明

1. 實作 Polynomial 類別及其抽象資料型別。
2. 寫出 C++ 函數，用於輸入和輸出多項式。這些函數應重載 `<<` 和 `>>` 運算子。

### 解題策略

1. 要先寫出一個類別，包含coef跟exp，和存取這個的陣列termArray。
2. 寫出一個函數，可以動態的調整termArray來存取更多的值。
3. 在寫出需要的功能，像是Add、Mult等等。

## 程式實作

以下為主要程式碼：

```cpp
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
```

## 效能分析

**時間複雜度**：

1. Term: $O(1)$ 不包含任何演算法或迴圈，僅在被建立時配置記憶體。
2. Polynomial(): $O(1)$ 固定配置初始容量為2的動態陣列。
3. newTerm(const float theCoef, const int theExp): 平均情況： $O(1)$ 當陣列容量足夠時直接放入;最差情況： $O(n)$ 當陣列空間滿了需要擴容時，需透過 copy() 將舊陣列的n個元素複製到新陣列中。
4. Add(const Polynomial &b): $O(n + m)$ 使用雙指標（aPos 和 bPos）同步掃描多項式 A 與 B。因為每個項次最多被訪問一次，所以時間與兩多項式的項數總和成正比。
5. Mult(const Polynomial &b): $O(n*m+(總項數)^2)$  雙層迴圈分別走訪n項與m項產生n x m個暫時項，每次呼叫 Add 進行合併時，會隨著多項式項數增加而進行額外的陣列搬移。
6. Eval(double x): $O(n)$ 使用單層迴圈走訪多項式的 $n$ 個非零項，每次迴圈進行一次 pow() 運算與乘加。
7. show(): $O(n)$ 需要完整走訪多項式的 $n$ 個非零項並逐一輸出。
8. main: $O(numA + numB + 操作次數*對應運算複雜度)$ 主要取決於使用者輸入的項數，以及在 while 迴圈中選擇執行 Add、Mult 或 Eval 的次數。
   
**空間複雜度**：
1. Term: $O(1)$ 固定佔用 8 個位元組（32位元指標架構下，float 佔 4 bytes、int 佔 4 bytes，不考慮記憶體對齊）。
2. Polynomial(): $O(1)$ 固定配置微小的初始記憶體空間。
3. newTerm(const float theCoef, const int theExp): 平均情況： $O(1)$ ;最差情況： $O(n)$ 擴容時會暫時配置兩倍大小的新記憶體。
4. Add(const Polynomial &b): $O(n + m)$ 需要建立一個新的多項式物件c來儲存結果，其最多可能包含n + m個非零項。
5. Mult(const Polynomial &b): $O(n * m)$ 需要額外空間來儲存相乘展開後的各個暫時項以及最終結果多項式。
6. Eval(double x): $O(1)$ 僅使用常數級別的額外變數(如f)來累積計算結果。
7. show(): $O(1)$ 僅作串流輸出，無額外資料結構開銷。
8. main: $O(n + m)$ 主程式中主要宣告了多項式物件 A、B、C、D，其記憶體開銷取決於多項式儲存的項數大小。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入多項式A | 輸入多項式B | 顯示A、B | A + B | A * B | 計算 A(x)| 計算 B(x)|結束程式|
|---------|------------|------------|----------|-------|-------|----------|---------|--------|
| 測試一 | 3 3 2 2 1 1 0 | 2 3 3 2 1 | A=3x^2+2x+1 B=3x^3+2x | A + B =3x^3+3x^2+4x+1 | A * B =9x^5+6x^4+9x^3+4x^2+2x | 輸入x:3 A(3)=34 | 輸入x:4 A(4)=200 | 結束 |
| 測試二 | 4 4 4 3 2 8 1 3 0 | 2 9 4 7 1 | A=4x^4+3x^2+8x+3 B=9x^4+7x | A + B =13x^4+3x^2+15x+3 | A * B =36x^8+27x^6+100x^5+27x^4+21x^3+56x^2+21x| 輸入x:3 A(3)=378 | 輸入x:6 A(6)=11706 | 結束 |
| 測試三 | 2 3 5 9 4 | 3 4 8 9 5 6 4    | A=3x^5+9x^4 B=4x^8+9x^5+6x^4 | A + B =4x^8+12x^5+15x^4 | A * B =12x^13+36x^12+27x^10+99x^9+54x^8 | 輸入x:6 A(6)=34992 | 輸入x:4 A(4)=272896 | 結束 |
| 測試四 | 3 6 2 8 1 4 0 | 3 2 6 1 8 0 4 | A=6x^2+8x+4 B=2x^6+1x^8 | A + B =2x^6+1x^8+6x^2+8x+4 | A * B =6x^10+8x^9+16x^8+16x^7+8x^6 | 輸入x:2 A(2)=44 | 輸入x:4 A(4)=73728 | 結束 |
| 測試五 | 3 3 2 2 1 1 0 | 3 1 0 2 1 3 2 | A=3x^2+2x+1 B=1+2x+3x^2 | A + B =3x^2+2x+2+2x+3x^2 | A * B =9x^4+12x^3+10x^2+4x+1 | 輸入x:5 A(5)=86 | 輸入x:4 A(4)=57|   結束|

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o polynomial polynomial.cpp
$ ./polynomial
輸入格式:項數 係數 指數 係數 指數..
ex: 3x^2 + 2x + 1: 3 3 2 2 1 1 0
輸入A多項式: 3 3 2 2 1 1 0
輸入B多項式: 2 3 3 2 1
============ Polynomial 選單 ============
1. 顯示A、B
2. A + B
3. A * B
4. 計算 A(x)
5. 計算 B(x)
0. 結束程式
選擇:1
A =3x^2+2x+1
B =3x^3+2x
============ Polynomial 選單 ============
1. 顯示A、B
2. A + B
3. A * B
4. 計算 A(x)
5. 計算 B(x)
0. 結束程式
選擇:2
A + B =3x^3+3x^2+4x+1
============ Polynomial 選單 ============
1. 顯示A、B
2. A + B
3. A * B
4. 計算 A(x)
5. 計算 B(x)
0. 結束程式
選擇:3
A * B =9x^5+6x^4+9x^3+4x^2+2x
============ Polynomial 選單 ============
1. 顯示A、B
2. A + B
3. A * B
4. 計算 A(x)
5. 計算 B(x)
0. 結束程式
選擇:4
輸入x:3
A(3) =34
============ Polynomial 選單 ============
1. 顯示A、B
2. A + B
3. A * B
4. 計算 A(x)
5. 計算 B(x)
0. 結束程式
選擇:5
輸入x:4
A(4) =200
============ Polynomial 選單 ============
1. 顯示A、B
2. A + B
3. A * B
4. 計算 A(x)
5. 計算 B(x)
0. 結束程式
選擇:0
結束程式
```

### 結論

1. 程式能顯示A和B跟算出A和B的加、乘和計算x帶進去的數。  
2. 在A、B多項式都是降冪的情況下，程式會成功的算出值;但是是升冪，就沒辦粉順利執行Add。  
3. 測試案例涵蓋了多種情況(升冪與降冪)，驗證程式還是有些問題。

## 申論及開發報告
1. 空間的最佳化利用：採用多項式動態陣列儲存結構，僅記錄非零項，有效解決了陣列在面對高次方且項數稀疏時造成的記憶體浪費問題。
2. 雙指標多項式加法：陣列雙指標走訪演算法，在 $O(n+m)$ 時間內完成多項式合併與自動排序，將原本需要兩層迴圈的暴力解法，降為單層迴圈。
3. 乘法運算：基於分配律，透過雙層迴圈將各項相乘，並藉由重複利用Add實現多項式相乘。
   
