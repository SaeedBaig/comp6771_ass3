/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

*/

#include "assignments/dg/graph.h"
#include "catch.h"


SCENARIO("Default constructor test") {
	WHEN("Default constructor is called") {
			gdwg::Graph<int, int> a;
			gdwg::Graph<int, int> b {};
			THEN("There should be no segmentation fault") {
			}
	}
}


SCENARIO("Constructor with 2 iterators") {
	WHEN("Default constructor is called") {
		std::vector<std::string> v{"Hello", "how", "are", "you"};
		gdwg::Graph<std::string, double> graph{v.begin(),v.end()};
		/*
		auto list = graph.getList();
		for(auto l:list) {
			std::cout << *l << std::endl;
		}
		*/
		THEN("There should be no segmentation fault") {
				REQUIRE(graph.IsNode("Hello")==true);
				REQUIRE(graph.IsNode("how")==true);
				REQUIRE(graph.IsNode("are")==true);
				REQUIRE(graph.IsNode("you")==true);
				REQUIRE(graph.IsNode("null")==false);
				REQUIRE(graph.IsNode("HELLO")==false);
			}
	}
}

SCENARIO("Itearate over tuple constructor test") {
	WHEN("Creating a list to test") {
		std::string s1{"Hello"};
		std::string s2{"how"};
		std::string s3{"are"};
		auto e1 = std::make_tuple(s1, s2, 5.4);
		auto e2 = std::make_tuple(s2, s3, 7.6);
		auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
		Graph<std::string, double> graph{e.begin(), e.end()};

		THEN("There should be no segmentation fault") {
			REQUIRE(graph.IsNode("Hello")==true);
			REQUIRE(graph.IsNode("how")==true);
			REQUIRE(graph.IsNode("are")==true);
			REQUIRE(graph.IsNode("HELLO")==false);
		}
	}
}

SCENARIO("Constructor with initialization list") {
	WHEN("Creating a list to test") {
		Graph<char, std::string> graph{'a', 'b', 'x', 'y'};
		THEN("There should be no segmentation fault") {
			REQUIRE(graph.IsNode('a')==true);
			REQUIRE(graph.IsNode('b')==true);
			REQUIRE(graph.IsNode('x')==true);
			REQUIRE(graph.IsNode('y')==true);
			REQUIRE(graph.IsNode('k')==false);
		}
	}
}

SCENARIO("Copy constructor test") {
	WHEN("Creating a list to test") {
		std::vector<std::string> v{"Hello", "how", "are", "you"};
		gdwg::Graph<std::string, double> graph{v.begin(),v.end()};
		gdwg::Graph<std::string, double> copy{graph};
		THEN("There should be no segmentation fault") {
			//property 1 holds
			REQUIRE(graph.IsNode("Hello")==true);
			REQUIRE(graph.IsNode("how")==true);
			REQUIRE(graph.IsNode("are")==true);
			REQUIRE(graph.IsNode("you")==true);
			REQUIRE(graph.IsNode("null")==false);
			REQUIRE(graph.IsNode("HELLO")==false);

			//property 2 also holds
			REQUIRE(copy.IsNode("Hello")==true);
			REQUIRE(copy.IsNode("how")==true);
			REQUIRE(copy.IsNode("are")==true);
			REQUIRE(copy.IsNode("you")==true);
			REQUIRE(copy.IsNode("null")==false);
			REQUIRE(copy.IsNode("HELLO")==false);
		}
	}
}

SCENARIO("Move constructor test") {
	WHEN("Creating a list to test") {
		std::vector<std::string> v{"Hello", "how", "are", "you"};
		gdwg::Graph<std::string, double> graph{v.begin(),v.end()};
		gdwg::Graph<std::string, double> aMove{std::move(graph)};
		THEN("There should be no segmentation fault") {

			REQUIRE(graph.IsNode("Hello")==false);
			REQUIRE(graph.IsNode("how")==false);
			REQUIRE(graph.IsNode("are")==false);
			REQUIRE(graph.IsNode("you")==false);
			REQUIRE(graph.IsNode("null")==false);


			REQUIRE(aMove.IsNode("Hello")==true);
			REQUIRE(aMove.IsNode("how")==true);
			REQUIRE(aMove.IsNode("are")==true);
			REQUIRE(aMove.IsNode("you")==true);
			REQUIRE(aMove.IsNode("null")==false);
		}
	}
}

SCENARIO("Copy operator test") {
	WHEN("Creating a list to test") {
		std::vector<std::string> v{"Hello", "how", "are", "you"};
		gdwg::Graph<std::string, double> graph{v.begin(),v.end()};
		gdwg::Graph<std::string, double> empty;
		empty=graph;
		THEN("There should be no segmentation fault") {
			//property 1 holds
			REQUIRE(graph.IsNode("Hello")==true);
			REQUIRE(graph.IsNode("how")==true);
			REQUIRE(graph.IsNode("are")==true);
			REQUIRE(graph.IsNode("you")==true);
			REQUIRE(graph.IsNode("null")==false);
			REQUIRE(graph.IsNode("HELLO")==false);


			REQUIRE(empty.IsNode("Hello")==true);
			REQUIRE(empty.IsNode("how")==true);
			REQUIRE(empty.IsNode("are")==true);
			REQUIRE(empty.IsNode("you")==true);
			REQUIRE(empty.IsNode("null")==false);
			REQUIRE(empty.IsNode("HELLO")==false);

		}
	}
}


SCENARIO("Move operator test") {
	WHEN("Creating a list to test") {
		std::vector<std::string> v{"Hello", "how", "are", "you"};
		gdwg::Graph<std::string, double> graph{v.begin(),v.end()};
		gdwg::Graph<std::string, double> empty;
		empty= std::move(graph);;
		THEN("There should be no segmentation fault") {

			REQUIRE(graph.IsNode("Hello")==false);
			REQUIRE(graph.IsNode("how")==false);
			REQUIRE(graph.IsNode("are")==false);
			REQUIRE(graph.IsNode("you")==false);
			REQUIRE(graph.IsNode("null")==false);


			REQUIRE(empty.IsNode("Hello")==true);
			REQUIRE(empty.IsNode("how")==true);
			REQUIRE(empty.IsNode("are")==true);
			REQUIRE(empty.IsNode("you")==true);
			REQUIRE(empty.IsNode("null")==false);

		}
	}
}

SCENARIO("Insert edge test") {

	std::string s1{"Hello"};
	std::string s2{"how"};
	std::string s3{"are"};
	auto e1 = std::make_tuple(s1, s2, 5.4);
	auto e2 = std::make_tuple(s2, s3, 7.6);
	auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
	Graph<std::string, double> graph{e.begin(), e.end()};

	WHEN("Creating an new edge to the existing graph") {
		//inserting an new edge to the existing graph
		std::string u{"c"};
		graph.InsertEdge("a",u,1);

		THEN("The new edge should be inserted") {
			REQUIRE(graph.IsNode("Hello")==true);
			REQUIRE(graph.IsNode("how")==true);
			REQUIRE(graph.IsNode("are")==true);
			REQUIRE(graph.IsNode("a")==true);
			REQUIRE(graph.IsNode("c")==true);
			REQUIRE(graph.InsertEdge("a",u,1)==false);
		}
	}
}
