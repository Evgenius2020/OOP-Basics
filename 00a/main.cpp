#include "module1.h"
#include "module2.h"
#include "module3.h"
#include <iostream>

using namespace std; // If you want use 'cout' without 'std::'

int main(int argc, char** argv)
{
	cout <<  "Hello world!" << "\n";
	
	cout << Module1::getMyName() << "\n";
	cout << Module2::getMyName() << "\n";

	using namespace Module1;
	cout << getMyName() << "\n"; // (A) - Prints 'John'
	cout << Module2::getMyName() << "\n";

	//using namespace Module2; // (B)
	//std::cout << getMyName() << "\n"; // COMPILATION ERROR (C) - because of name conflict ('getMyName()' method)

	// You can make it compilable by renaming method, or call it like at next strings:

	using Module2::getMyName;
	cout << getMyName() << "\n"; // (D) - Prints 'James'

	//using Module3::getMyName;
	//cout << getMyName() << "\n"; // Prints 'Peter'
	cout << Module3::getMyName() << "\n";
}
