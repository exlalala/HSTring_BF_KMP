#include "head.h"

int main() {
	char s[] = { "abc12abcd123efdk1123" };
	char t1[] = { "abc" };
	char t2[] = { "12" };

	HStr* S1 = InitHStr(s);
	HStr* S2 = InitHStr(s);
	HStr* T1 = InitHStr(t1);
	HStr* T2 = InitHStr(t2);

	cout << "S='";
	Output(S1);
	cout << "'" << endl << "T1='";
	Output(T1);
	cout << "'" << endl << "T2='";
	Output(T2);
	cout << "'" << endl;

	BF_Index_Delete(S1, T1, 0);

	cout << "BF法删除T1后：S='";
	Output(S1);
	cout << "'" << endl;

	KMP_Index_Delete(S2, T2, 0);

	cout << "KMP法删除T2后：S='";
	Output(S2);
	cout << "'" << endl;

	return 0;
}