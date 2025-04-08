#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <map>

using namespace std;

// Function declarations
void week();
void numbers();
void fruts();
void stock();

int main()
{
	// Call the function to display the days of the week
	cout << "--- Week Days ---" << endl;
	week();

	// Call the function to display and modify a vector of numbers
	cout << "\n--- Numbers ---" << endl;
	numbers();

	// Call the function to display and modify a list of fruits
	cout << "\n--- Fruits ---" << endl;
	fruts();

	// Call the function to display and modify a map of stock quantities
	cout << "\n--- Stock ---" << endl;
	stock();

	return 0;
}

void week()
{
	// Initialize a string array with a size of 7 containing the days of the week
	array<string, 7> days = { "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY" };

	// Print the number of elements in the array
	cout << "Number of days: " << days.size() << endl;

	// Loop through the array and print each day separately
	for (const string& day : days)
	{
		cout << day << endl;
	}
}

void numbers()
{
	// Initialize a vector of int with 5 numbers
	vector<int> numbers = { 1, 2, 3, 4, 5 };

	// Add number 6 to the vector
	numbers.push_back(6);

	// Add number 7 to the vector
	numbers.push_back(7);

	// Remove the last number, in this case the number 7
	numbers.pop_back();

	// Loop through the vector and print each number separately
	for (const int& number : numbers)
	{
		cout << number << endl;
	}
}

void fruts()
{
	// Initialize a list of strings with 3 fruit names
	list<string> fruits = { "APPLE", "MANGO", "TUNA" };

	// Add a fruit to the front of the list
	fruits.push_front("DRAGONFRUIT");

	// Add a fruit to the back of the list
	fruits.push_back("PINEAPPLE");

	// Remove a specific fruit from the list
	fruits.remove("TUNA");

	// Loop through the list using an iterator and print each fruit
	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		cout << *it << endl;
	}
}

void stock()
{
	// Initialize a map with two grocery items and their quantities
	map<string, int> stocks = {
		{"APPLES", 5},
		{"MANGOS", 10},
		{"BANANAS", 8}
	};

	// Update the quantity of APPLES
	stocks["APPLES"] = 7;

	// Loop through the map and print each product and its quantity
	for (const auto& item : stocks)
	{
		cout << item.first << ": " << item.second << endl;
	}
}
