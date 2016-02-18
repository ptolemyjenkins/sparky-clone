#include <iostream>
static int find(std::string text, std::string phrase, int first) {
	text = text.substr(first);
	int i = text.find(phrase);
	return i + first;
}


int main() {
	std::cout << find("0123456789012345678901234567890123456789", "01" ,10) << std::endl;
	system("PAUSE");
}