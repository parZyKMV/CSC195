#include <iostream>

void func1(int* p)
{
	if (p) *p = 5;
}

void Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
	int i1 = 5;
	int i2 = 20;
	int* p1 = &i1;
	p1 = nullptr;
	func1(p1);

	int& r1 = i1;
	r1 = 10;

	std::cout << "i1: " << i1 << " i2: " << i2 << std::endl;
	Swap(&i1, &i2);
	std::cout << "i1: " << i1 << " i2: " << i2 << std::endl;
	Swap(i1, i2);
	std::cout << "i1: " << i1 << " i2: " << i2 << std::endl;

	std::cout << i1 << std::endl;
}

