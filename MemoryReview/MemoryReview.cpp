#include <iostream>
using namespace std;
struct Person
{
	char name[32];
	int id;
};

//Function to square a value
void Square(int& num)
{
	num = num * num;
}

//Function to double a value using a pointer
void Double(int* ptr)
{
	if (ptr != nullptr) {
		*ptr = *ptr * 2;
	}
}

int main()
{
	// ** REFERENCE **
	//
	// declare an int variable and set the value to some number (less than 10)
	int num = 5;

	// declare a int reference and set it to the int variable above
	int& numRef = num;

	// output the int variable
	cout << "Original value: " << num << endl;
	
	// set the int reference to some number
	numRef = 7;

	// output the int variable
	cout << "After reference change: " << num << endl;

	// what happened to the int variable when the reference was changed? (insert answer)
	// Answer: The original variable's value changed because the reference is an alias to it.
	
	// output the address of the int variable
	cout << "Address of num: " << &num << endl;

	// output the address of the int reference
	cout << "Address of numRef: " << &numRef << endl;

	// are the addresses the same or different? (insert answer)
	// Answer: The addresses are the same because a reference is an alias to the original variable.
	// ** REFERENCE PARAMETER **
	//
	// create a function above main() called Square that takes in an int parameter
	Square(num);

	// in the function, multiply the int parameter by itself and assign it back to the parameter(i = i * i)
	// call the Square function with the int variable created in the REFERENCE section
	// output the int variable to the console
	cout << "After Square function: " << num << endl;

	// !! notice how the variable has not changed, this is because we only passed the value to the function !!
	// change the Square function to take a int reference
	// !! notice how the calling variable has now changed, this is because we 'passed by reference' !!
	// !! when a function takes a reference parameter, any changes to the parameter changes the calling variable ""
	// ** POINTER VARIABLE **
	//
	// declare an int pointer, set it to nullptr (it points to nothing)
	int* ptr = nullptr;

	// set the int pointer to the address of the int variable created in the REFERENCE section
	ptr = &num;

	// output the value of the pointer
	cout << "Pointer value (address): " << ptr << endl;
	// what is this address that the pointer is pointing to? (insert answer)
	// Answer: It's pointing to the address of the 'num' variable.
	// output the value of the object the pointer is pointing to (dereference the pointer
	cout << "Value pointed to by pointer: " << *ptr << endl;

	// ** POINTER PARAMETER **
	//
	// create a function above main() called Double that takes in an int pointer parameter
	// in the function, multiply the int pointer parameter by 2 and assign it back to the parameter(i = i * 2)
	// !! make sure to dereference the pointer to set the value and not set the address !!
	// call the Double function with the pointer created in the POINTER VARIABLE section
	Double(ptr);

	// output the dereference pointer
	cout << "After Double function (pointer): " << *ptr << endl;


	// output the int variable created in the REFERENCE section
	cout << "After Double function (original variable): " << num << endl;


	// did the int variable's value change when using the pointer?
	// Answer: Yes, the original variable's value changed because we modified it through the pointer.
}
