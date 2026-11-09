#pragma once
#include <iostream>
using namespace std;
#define OK 1
#define ERROR -1

typedef struct {
	char* sv;
	int len;
	int size;
} HStr;


HStr* InitHStr(char* a) {
	int i;
	HStr* T;
	for (i = 0; a[i] != '\0'; i++);
	if (!i) return nullptr;
	else {
		T = (HStr*)malloc(sizeof(*T));
		if (!T || !(T->sv=(char*)malloc(sizeof(char) * (i + 1))))	return nullptr;
		T->len = i;
		T->size = i + 1;
		for (int j = 0; j < i; j++) {
			T->sv[j] = a[j];
		}
		T->sv[i] = '\0';
	}
	return T;
}

void StrDelete(HStr* s, int k, int len) {
	if (!s || !s->sv || k<0 || k + len > s->len || len <= 0) return;
	int i;
	for (i = k; i + len < s->len; i++) {
		s->sv[i] = s->sv[i + len];
	}
	s->len = i;
	s->sv[i] = '\0';
}

int BF_Index_Delete(HStr* s, HStr* t, int pos) {
	if (!s || !t || pos<0 || pos>s->len)	return ERROR;
	int i = pos, j = 0;
	while (i < s->len && j < t->len) {
		if (s->sv[i] == t->sv[j]) {
			i++; j++;
		}
		else {
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == t->len) {
		int startIndex= i - t->len;
		StrDelete(s, startIndex, t->len);
		return BF_Index_Delete(s, t, startIndex);
	}
	else {
		return ERROR;
	}
}

void Output(HStr* s) {
	for (int i = 0;i < s->len;i++) {
		cout << s->sv[i];
	}
}

void Get_next(HStr* t, int* next) {
	int i = 0, j = -1;
	next[0] = -1;
	while (i < t->len-1){
		if (j == -1 || t->sv[i] == t->sv[j])
		{
			i++;
			j++;
			if (j==0 || t->sv[i] != t->sv[j])	next[i] = j;
			else   next[i] = next[j];
		}
		else j = next[j];
	}
}


int Index_KMP(HStr* s, HStr* t, int pos, int next[]) {
	if (!s || !t || t->len <= 0 || pos<0 || pos>s->len) return ERROR;
	int i = pos, j = 0;
	while (i < s->len && j < t->len) 
		if (j == -1 || s->sv[i] == t->sv[j]) {
			++i;   ++j; 
		} 
		else j = next[j]; 
	if (j == t->len) return  i - t->len;
	else return ERROR;
}

void KMP_Index_Delete(HStr* s, HStr* t, int pos) {
	int* next = new int[t->len];
	Get_next(t, next);
	int k = Index_KMP(s, t, pos, next);
	while (k !=ERROR) {
		StrDelete(s, k, t->len);
		pos = k;
		k = Index_KMP(s, t, pos, next);
	}
	delete[] next;
}