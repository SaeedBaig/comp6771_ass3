#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>

//create an iterator and
//change the content of 2 to three

struct Node {

	Node (std::string node_name) {
		node_name_=std::make_shared<std::string>(node_name);
	}

	void replaceNodeName(std::string node_name) {
		node_name_.reset();
		node_name_=std::make_shared<std::string>(node_name);
	}

	std::string getNodeName() {
		return *node_name_;
	}

	std::shared_ptr<std::string> node_name_;
};


int main() {
	std::vector<std::shared_ptr<std::string>> list;

	auto test_node = std::make_shared<Node>("new");
	std::cout << test_node->getNodeName() << std::endl;
	test_node->replaceNodeName("test");
	std::cout << test_node->getNodeName() << std::endl;


	std::vector<std::shared_ptr<Node>> nodelist;
	nodelist.push_back(std::make_shared<Node>("11"));
	nodelist.push_back(std::make_shared<Node>("22"));

	for(auto item:nodelist) {
		std::cout << item->getNodeName() << std::endl;
	}

	std::string search_content = "11";

	auto search_iter = std::find_if(nodelist.begin(), nodelist.end(), [&search_content](std::shared_ptr<Node> n) {
		return n->getNodeName() == search_content;
	});

	//iteartor can access element by *(iter)->method()
	std::cout << "------------------------------" << std::endl;
	if(search_iter != nodelist.end()) {
		std::cout << search_iter->get()->getNodeName() << std::endl;
		search_iter->get()->replaceNodeName("new");
	}
	std::cout << "------------------------------" << std::endl;

	for(auto item:nodelist) {
		std::cout << item->getNodeName() << std::endl;
	}

	return 0;
}

