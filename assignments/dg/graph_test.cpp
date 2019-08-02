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
		gdwg::Graph<std::string, double> graph{e.begin(), e.end()};

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
		gdwg::Graph<char, std::string> graph{'a', 'b', 'x', 'y'};
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

SCENARIO("Copy assignment test") {
	WHEN("Creating a list to test") {
		std::vector<std::string> v{"Hello", "how", "are", "you"};
		gdwg::Graph<std::string, double> graph{v.begin(),v.end()};
		gdwg::Graph<std::string, double> empty;
		empty = graph;
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

SCENARIO("Move assignment test") {
	WHEN("Creating a list to test") {
		std::vector<std::string> v{"Hello", "how", "are", "you"};
		gdwg::Graph<std::string, double> graph{v.begin(),v.end()};
		gdwg::Graph<std::string, double> empty;
		empty = std::move(graph);;
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

SCENARIO("Inserting node test") {
  GIVEN("A graph") {
    gdwg::Graph<std::string, int> g;
    WHEN("We insert a node into it") {
      g.InsertNode("hello");
      THEN("That node is in the graph") {
        REQUIRE(g.IsNode("hello"));
      }
    }
  }
}

SCENARIO("Inserting node-that-goes-out-of-scope test") {
  WHEN("Adding a string `s` to a graph and that string `s` goes out of scope") {
    gdwg::Graph<std::string, int> g;
    {
      std::string s1{"Hello"};
      g.InsertNode(s1);
    }

    THEN("That string should still be in the graph") {
      REQUIRE(g.IsNode("Hello"));
    }
  }
}

SCENARIO("Inserting node that is already in the graph") {
  GIVEN("A graph with a node in it") {
    gdwg::Graph<char, int> g{'x'};
    WHEN("We try to insert that same node into the graph again") {
      const auto graph_before_call_to_insert = g;
      THEN("The graph remains unchanged and InsertNode() returns false") {
        REQUIRE(g.InsertNode('x') == false);
        REQUIRE(g == graph_before_call_to_insert);
      }
    }
  }
}


SCENARIO("Insert nodes on an empty graph") {
	WHEN("Insert 3 nodes on an empty graph") {
			gdwg::Graph<int, int> graph;
			graph.InsertNode(1);
			graph.InsertNode(2);
			graph.InsertNode(3);
			auto nodes = graph.GetNodes();
			THEN("Add one node") {
				REQUIRE(graph.IsNode(1)==true);
				REQUIRE(graph.IsNode(2)==true);
				REQUIRE(graph.IsNode(3)==true);
				REQUIRE(nodes.size()==3);
			}

	}

	WHEN("Insert redundant nodes to the same graph") {
			gdwg::Graph<int, int> graph;
			graph.InsertNode(1);
			graph.InsertNode(2);
			graph.InsertNode(3);
			graph.InsertNode(3);
			graph.InsertNode(3);
			auto nodes = graph.GetNodes();
			THEN("Redundant nodes should not be added") {
				REQUIRE(graph.IsNode(1)==true);
				REQUIRE(graph.IsNode(2)==true);
				REQUIRE(graph.IsNode(3)==true);
				REQUIRE(nodes.size()==3);
			}
}

}


SCENARIO("Insert edge test") {
  GIVEN("A graph with 2 nodes") {
    gdwg::Graph<std::string, int> g;
    g.InsertNode("hello");
    g.InsertNode("world");
    REQUIRE(!g.IsConnected("hello", "world"));
    WHEN("We insert an edge between those 2 nodes") {
      g.InsertEdge("hello", "world", 42);
      THEN("That edge should be in the graph") {
        REQUIRE(g.IsConnected("hello", "world"));
      }
    }
  }
}


SCENARIO("Insert edge - exceptional cases") {
  GIVEN("A list of nodes") {
    gdwg::Graph<std::string, int> g;
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    WHEN("Insert an source node that does not belong to the graph") {
      THEN("Should throw exception") {
    	  REQUIRE_THROWS_WITH(g.InsertEdge("brisbane", "sydney", 42), "Cannot call Graph::InsertEdge when either src or dst node does not exist");
      }
    }

    WHEN("Insert an destination node that does not belong to the graph") {
          THEN("Should throw exception") {
        	  REQUIRE_THROWS_WITH(g.InsertEdge("sydney", "adelaide", 42), "Cannot call Graph::InsertEdge when either src or dst node does not exist");
          }
   }
  }
}


SCENARIO("Delete node test") {
  GIVEN("A graph with 2 nodes") {
    gdwg::Graph<std::string, int> g;
    g.InsertNode("hello");
    g.InsertNode("world");
    WHEN("Deleting 2 nodes") {
      g.DeleteNode("hello");
      g.DeleteNode("world");
      THEN("Nodes should be removed as required") {
        REQUIRE(g.IsNode("hello")==false);
        REQUIRE(g.IsNode("world")==false);
        REQUIRE(g.GetNodes().size()==0);
      }
    }
  }
}


SCENARIO("Delete nodes - typical & exceptional cases") {

  GIVEN("Graph with existing nodes and edges - true-case testing") {
      gdwg::Graph<std::string, int> g;
      //inserting ndoes
      g.InsertNode("sydney");
      g.InsertNode("melbourne");
      g.InsertNode("brisbane");

      //inserting edges
      g.InsertEdge("sydney", "melbourne", 42);
      g.InsertEdge("sydney", "brisbane", 42);

      REQUIRE(g.IsNode("sydney")==true);
      REQUIRE(g.IsNode("melbourne")==true);
      REQUIRE(g.IsNode("brisbane")==true);

      REQUIRE(g.IsConnected("sydney","melbourne")==true);
      REQUIRE(g.IsConnected("sydney","brisbane")==true);

      WHEN("Delete one node") {
    	  g.DeleteNode("sydney");
  		  THEN("Nodes and edges associated to it should also be removed") {
  			REQUIRE(g.IsNode("sydney")==false);
  			REQUIRE_THROWS_WITH(g.IsConnected("sydney","melbourne"),"Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
  			REQUIRE_THROWS_WITH(g.IsConnected("sydney","brisbane"),"Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
  		  }
      }
   }

  GIVEN("Graph with nothing in it and trying to delete from the graph") {
    gdwg::Graph<std::string, int> g;
    WHEN("Trying to delete 2 nodes that does not exist in the graph") {
    	REQUIRE(g.DeleteNode("hello")==false);
    	REQUIRE(g.DeleteNode("world")==false);
		  THEN("That edge should be in the graph") {
			REQUIRE(g.IsNode("hello")==false);
			REQUIRE(g.IsNode("world")==false);
		  }
    }
  }
}


SCENARIO("Replace node - replace new element with old element") {
  GIVEN("A graph with 0 nodes") {
	std::vector<std::string> v{"Hello", "how", "are", "you"};
	gdwg::Graph<std::string, double> graph{v.begin(),v.end()};
    WHEN("Trying to delete 2 nodes that does not exist in the graph") {
    	REQUIRE(graph.DeleteNode("hello")==false);
    	REQUIRE(graph.DeleteNode("world")==false);
		  THEN("That edge should be in the graph") {
			REQUIRE(graph.IsNode("hello")==false);
			REQUIRE(graph.IsNode("world")==false);
		  }
    }
  }
}


SCENARIO("Inserting an edge that is already in the graph") {
  GIVEN("A graph with an edge in it") {
  	const auto edge = std::make_tuple("Hello", "There!", 5.4);
  	const auto edges = std::vector<std::tuple<std::string, std::string, double>>{edge};
  	gdwg::Graph<std::string, double> graph{edges.begin(), edges.end()};
    WHEN("We try to insert that same edge back into it") {
      const auto graph_before_call_to_insert = graph;
      THEN("The graph remains unchanged and InsertEdge() returns false") {
        REQUIRE(graph.InsertEdge("Hello", "There!", 5.4) == false);
        REQUIRE(graph == graph_before_call_to_insert);
      }
    }
  }
}

SCENARIO("Insert edge exception test") {
	std::string s1{"Hello"};
	std::string s2{"how"};
	std::string s3{"are"};
	auto e1 = std::make_tuple(s1, s2, 5.4);
	auto e2 = std::make_tuple(s2, s3, 7.6);
	auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
	gdwg::Graph<std::string, double> graph{e.begin(), e.end()};

	WHEN("We try to insert an edge into the existing graph with nodes that arent in it") {
		std::string u{"c"};
		THEN("An exception is thrown") {
      REQUIRE_THROWS_WITH(graph.InsertEdge("a",u,1), "Cannot call Graph::InsertEdge when either src or dst node does not exist");
		}
	}
}

SCENARIO("IsConnected true-case test") {
  GIVEN("A graph with 2 nodes in it") {
    gdwg::Graph<double, int> g{4.6, -9.8};
    WHEN("We insert an edge between these 2 nodes") {
      g.InsertEdge(4.6, -9.8, 35);
      THEN("Those 2 nodes are connected in the graph") {
        REQUIRE(g.IsConnected(4.6, -9.8));
      }
    }
  }
}

SCENARIO("IsConnected false-case test") {
  GIVEN("A graph") {
    gdwg::Graph<double, int> g;
    WHEN("We insert 2 nodes in it but NOT an edge between them") {
      g.InsertNode(4.6);
      g.InsertNode(-9.8);
      THEN("Those 2 nodes are NOT connected in the graph") {
        REQUIRE(!g.IsConnected(4.6, -9.8));
      }
    }
  }
}

SCENARIO("IsConnected exception test") {
  GIVEN("A graph") {
    const gdwg::Graph<char, double> g{'a', 'b', 'c'};
    WHEN("We try to check if 2 nodes (at least 1 of which is NOT in the graph) are connected") {
      THEN("An exception is thrown") {
        REQUIRE_THROWS_WITH(g.IsConnected('a', 'Z'), "Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
        REQUIRE_THROWS_WITH(g.IsConnected('S', 'b'), "Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
        REQUIRE_THROWS_WITH(g.IsConnected('S', 'Z'), "Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
      }
    }
  }
}

SCENARIO("GetNode() correctness & coverage test") {

	WHEN("A graph contains something and GetNode() is called") {
		std::vector<std::string> v{"Hello", "how", "are", "you"};
		gdwg::Graph<std::string, double> graph{v.begin(),v.end()};
		auto nodes = graph.GetNodes();
		THEN("Elements should be identifiable in the return vector") {
			REQUIRE(std::find(nodes.begin(), nodes.end(), "Hello") != nodes.end());
			REQUIRE(std::find(nodes.begin(), nodes.end(), "how") != nodes.end());
			REQUIRE(std::find(nodes.begin(), nodes.end(), "are") != nodes.end());
			REQUIRE(std::find(nodes.begin(), nodes.end(), "you") != nodes.end());
		}
	}

	WHEN("A graph contains nothing and GetNode() is called") {
		gdwg::Graph<std::string, double> graph{};
		auto nodes = graph.GetNodes();
		THEN("Nothing should be in the return vector") {
			REQUIRE(nodes.size()==0);
			REQUIRE(std::find(nodes.begin(), nodes.end(), "Hello") == nodes.end());
		}
	}
}

SCENARIO("GetConnected() correctness & coverage test") {

	WHEN("A graph contains something and GetConnected() is called") {
		gdwg::Graph<std::string, int> g;
		  //inserting ndoes
		g.InsertNode("sydney");
		g.InsertNode("melbourne");
		g.InsertNode("brisbane");
		g.InsertNode("adelaide");
		g.InsertNode("perth");
		g.InsertNode("darwin");
		g.InsertNode("hobart");

		  //inserting edges
		g.InsertEdge("sydney", "melbourne", 42);
		g.InsertEdge("sydney", "brisbane", 42);
		g.InsertEdge("sydney", "perth", 42);
		g.InsertEdge("sydney", "darwin", 42);
		g.InsertEdge("sydney", "hobart", 42);

		auto nodes = g.GetConnected("sydney");
		THEN("Elements should be identifiable in the return vector") {
			REQUIRE(std::find(nodes.begin(), nodes.end(), "melbourne") != nodes.end());
			REQUIRE(std::find(nodes.begin(), nodes.end(), "brisbane") != nodes.end());
			REQUIRE(std::find(nodes.begin(), nodes.end(), "perth") != nodes.end());
			REQUIRE(std::find(nodes.begin(), nodes.end(), "darwin") != nodes.end());
			REQUIRE(std::find(nodes.begin(), nodes.end(), "hobart") != nodes.end());
		}
	}
}

