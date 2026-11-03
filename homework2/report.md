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

| 測試案例 | 輸入參數 $n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $n = 0$      | 0        | 0        |
| 測試二   | $n = 1$      | 1        | 1        |
| 測試三   | $n = 3$      | 6        | 6        |
| 測試四   | $n = 5$      | 15       | 15       |
| 測試五   | $n = -1$     | 異常拋出 | 異常拋出 |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o sigma sigma.cpp
$ ./sigma
6
```

### 結論

1. 程式能正確計算 $n$ 到 $1$ 的連加總和。  
2. 在 $n < 0$ 的情況下，程式會成功拋出異常，符合設計預期。  
3. 測試案例涵蓋了多種邊界情況（$n = 0$、$n = 1$、$n > 1$、$n < 0$），驗證程式的正確性。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程式邏輯簡單直觀**  
   遞迴的寫法能夠清楚表達「將問題拆解為更小的子問題」的核心概念。  
   例如，計算 $\Sigma(n)$ 的過程可分解為：  

   $$
   \Sigma(n) = n + \Sigma(n-1)
   $$

   當 $n$ 等於 1 或 0 時，直接返回結果，結束遞迴。

2. **易於理解與實現**  
   遞迴的程式碼更接近數學公式的表示方式，特別適合新手學習遞迴的基本概念。  
   以本程式為例：  

   ```cpp
   int sigma(int n) {
       if (n < 0)
           throw "n < 0";
       else if (n <= 1)
           return n;
       return n + sigma(n - 1);
   }
   ```

3. **遞迴的語意清楚**  
   在程式中，每次遞迴呼叫都代表一個「子問題的解」，而最終遞迴的返回結果會逐層相加，完成整體問題的求解。  
   這種設計簡化了邏輯，不需要額外變數來維護中間狀態。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。
