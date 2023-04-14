#include <iostream>
#include <algorithm>
using namespace std;

void bubble_sort(double* ar, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (ar[j] > ar[j + 1]) // swap ar[j], ar[j+1]
			{
				const int tmp = ar[j + 1];
				ar[j + 1] = ar[j];
				ar[j] = tmp;
			}
		}
	}
}

void insertion_sort(double* ar, int n)
{
	for (int i = 1; i < n; i++)
	{
		int op = ar[i];
		int j = i - 1;
		while (op < ar[j] && j >= 0)
		{ar[j + 1] = ar[j]; j--;}
		ar[j + 1] = op;
	}
}

void select_sort(double* ar, int n)
{
	int m_ind;
	for (int i = 0; i < n-1; i++)
	{
		m_ind = i;
		for (int j = i+1; j < n; j++) { if (ar[j] < ar[m_ind]) { m_ind = j; } }
		swap(ar[m_ind], ar[i]);
	}
}


void std_sort(double* ar, int n)
{
	sort(ar, ar + n);
}


int op(double* a, int start, int end)
{
	double opora = a[end];
	int i = start - 1;
	for (int j = start; j < end; j++)
	{
		if (a[j] <= opora) { i++; swap(a[i], a[j]); }
	}
	swap(a[i + 1], a[end]);
	return (i + 1);
}

void qk_sort(double* a, int start, int end)
{
	if (start < end)
	{
		int el = op(a, start, end);
		qk_sort(a, start, el - 1);
		qk_sort(a, el + 1, end);
	}
}

void quick_sort(double* ar, int n) { qk_sort(ar, 0, n); }

void line_merge(double* ar, int start, int mid, int end)
{
	int i, j, k;
	double* c = new double[end-start];
	i = start;
	//k = start;
	j = mid;
	for (int l = 0; l < end - start; l++)
	{
		if (i < mid && j < end)
		{
			if (ar[i] < ar[j])
			{
				c[l] = ar[i++];
			}
			else { c[l] = ar[j++]; }
		}
		else
		{
			if (i == mid) { c[l] = ar[j++]; }
			else { c[l] = ar[i++]; }
		}
	}
	for (int m = start; m < end; m++) { ar[m] = c[m - start]; }
	delete[]c;
}
void mrg_srt(double* ar, int start, int end)
{
	int mid;
	if (start + 1 >= end) {return;}
	mid = (start + end) / 2;
	mrg_srt(ar, start, mid);
	mrg_srt(ar, mid, end);
	line_merge(ar, start, mid, end);
}

void merge_sort(double* ar, int n) 
{
	mrg_srt(ar, 0, n);
}

void combinated_sort()
{

}

void copy_ar(double* ar, double* copy, int n)
{
	for (int i = 0; i < n; i++) { copy[i] = ar[i]; }
}

bool check(double* ar, int n)
{
	for (int i = 1; i < n; i++) { if (ar[i - 1] > ar[i]) { return false; break; } }
	return true;
}

int get_str_len(const char* a)
{
	int count = 0;
	while (a[count] != '\0')
	{
		count++;
	}
	return count;
}

bool eq_str(const char* a, const char* b)
{
	int l1 = get_str_len(a);
	int l2 = get_str_len(b);
	if (l1 != l2) return false;
	for (int i = 0; i < l1; i++)
		if (a[i] != b[i]) return false;
	return true;
}

void create_ar(double* ar, int n)
{
	for (int i = 0; i < n; i++)
	{
		double x;
		x = (double)(-1000 + rand() % 2001) / 10;
		//cout << x << " ";
		ar[i] = x;
	}
}

void (*my_sort) (double*, int);

int main(int argc, char** argv)
{
	string name_of_sort[5] = {"insertion_sort", "select_sort", "std_sort", "quick_sort", "merge_sort"};
	int num;
	setlocale(LC_ALL, "Russian");
	if (argc == 1)
	{
		my_sort = bubble_sort;
		printf("bubble_sort\n");
	}
	else if (argc == 2)
	{
		for (int i = 0; i < 6; i++) { if (argv[1] == name_of_sort[i]) { num = i; } }
		switch (num)
		{
		case 0:
			my_sort = insertion_sort; break;
		case 1:
			my_sort = select_sort; break;
		case 2:
			my_sort = std_sort; break;
		case 3:
			my_sort = quick_sort; break;
		case 4:
			my_sort = merge_sort; break;
		default:
			cout << "bad sort"; return -1;
		}
		/*
		if (eq_str(argv[1], "std_sort"))
		{
			my_sort = std_sort;
			printf("std_sort");
		}
		else if (eq_str(argv[1], "merge_sort")) {my_sort = merge_sort; }
		else
		{
			printf("bad sort");
			return -1;
		}*/
		
		
	}
    const int n = 100000; 
	double* ar=new double[n];
	srand(time(NULL));
	for (int i = 1000* 10; i <= n; i += 10000)
	{
		create_ar(ar, i);
		int t1 = clock();
		my_sort(ar, i);
		t1 = clock() - t1;
		//if (check(ar, i)) { cout << "+"; }
		//cout << endl;
		//for (int j = 0; j < i; j++) { cout << ar[j] << " "; }
		cout << t1 << "; ";
	}
}