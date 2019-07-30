#include <iostream>
#include "graph.h"
#include <string>
//using namespace gdwg;

int main() {
	gdwg::Graph<std::string, int> g;
	{
	    std::string s1{"Hello"};
	    g.InsertNode(s1);
	}
	std::cout << g.IsNode("Hello") << "\n";
	return 0;
}
