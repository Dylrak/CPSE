#include <stdio.h>
#include <iostream>
#include "ADT.hpp"

int main(int argc, char **argv)
{
	set<int, 8> ar;
	std::cout << ar.contains (1);
	ar.add(1);
	std::cout << ar.contains (1);
	std::cout << ar.contains (2);
	ar.add(2);
	ar.remove(1);
	std::cout << ar.contains (1);
	std::cout << ar.contains (2);
	std::string input;
	std::cin >> input;
}
