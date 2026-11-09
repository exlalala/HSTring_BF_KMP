#pragma once
#include <iostream>
using namespace std;
#define MAX_n 1000

typedef int ElemType;

typedef struct CLNode {
	int i, j;
	ElemType e;
	struct CLNode* right, * down;
}CLNode, * CLink;

typedef struct {
	CLink* rhead, * chead;
	int m, n, t;
} Crosslist;

typedef struct {
	int i, j, e;
}Triple;

void CreateMatrix(Crosslist& C, int m, int n, int t, Triple data[]) {
	C.m = m;
	C.n = n;
	C.t = t;

	C.chead = new CLink[n + 1]();
	C.rhead = new CLink[m + 1]();
	if (C.chead == nullptr || C.rhead == nullptr)	return;

	for (int k = 0;k < t;k++) {
		int row = data[k].i;
		int col = data[k].j;
		int val = data[k].e;

		CLink p = new CLNode;
		p->i = row;	p->j = col;	p->e = val;
		p->down = nullptr;	p->right = nullptr;
		if (C.rhead[row] == nullptr || C.rhead[row]->j > col) {
			p->right = C.rhead[row];
			C.rhead[row] = p;
		}
		else {
			CLink q = C.rhead[row];
			for (;q->right && q->right->j < col;q = q->right);
			p->right = q->right;
			C.rhead[row]->right = p;
		}

		if (C.chead[col] == nullptr || C.chead[col]->i > row) {
			p->down = C.chead[col];
			C.chead[col] = p;
		}
		else {
			CLink q = C.chead[col];
			for (;q->down && q->down->i < row;q = q->down);
			p->down = q->down;
			C.chead[col]->down = p;
		}
	}
}

void PrintMatrix(Crosslist C) {
	for (int i = 1;i <= C.m;i++) {
		CLink p = C.rhead[i];
		for (int j = 1;j <= C.n;j++) {
			if (p != nullptr && p->j == j) {
				cout << p->e << "\t";
				p = p->right;
			}
			else {
				cout << "0\t";
			}
		}
		cout << endl;
	}
}

void AddMatrix(Crosslist& A, Crosslist B) {
	int i, j;
	CLink p, pa, pb, pre, hl[MAX_n + 1];
	if (A.m != B.m || A.n != B.n)	return;
	if (B.t == 0)	return;
	for (j = 1;j <= A.n;j++)	hl[j] = A.chead[j];
	for (i = 1;i <= A.m;i++) {
		pa = A.rhead[i];
		pb = B.rhead[i];
		pre = nullptr;

		while (pb) {
			if (pa == nullptr || pa->j > pb->j) {
				p = new CLNode;
				if (!pre)	A.rhead[i] = p;
				else  pre->right = p;
				p->right = pa;
				p->i = i;
				p->j = pb->j;
				p->e = pb->e;

				if (A.chead[p->j] == nullptr || A.chead[p->j]->i > p->i) {
					p->down = A.chead[p->j];
					A.chead[p->j] = p;
				}
				else {
					while (hl[p->j]->down && hl[p->j]->i < p->i) {
						hl[p->j] = hl[p->j]->down;
					}
					p->down = hl[p->j]->down;
					hl[p->j]->down = p;
				}
				hl[p->j] = p;
				pb = pb->right;
				A.t++;
			}

			else if (pa->j < pb->j) {
				pre = pa;
				pa = pa->right;
			}

			else if (pa->e + pb->j != 0) {
				pa->e += pb->e;
				pre = pa;
				pa = pa->right;
				pb = pb->right;
			}

			else {
				if (pre == nullptr)	A.rhead[i] = pa->right;
				else  pre->right = pa->right;

				p = pa;
				pa = pa->right;
				pb = pb->right;

				if (A.chead[p->j] == p)	A.chead[p->j] = p->down;
				else  hl[p->j]->down = p->down;

				free(p);
				A.t--;
			}
		}
	}
}

void DestroyMatrix(Crosslist& A) {
	for (int i = 1;i <= A.m;i++) {
		CLink p = A.rhead[i];
		while (p != NULL) {
			CLink temp = p;
			p = p->right;
			delete temp;
		}
		A.rhead[i] = nullptr;
	}
	delete[] A.rhead;
	delete[] A.chead;

	A.rhead = nullptr;
	A.chead = nullptr;
	A.m = A.n = A.t = 0;
}