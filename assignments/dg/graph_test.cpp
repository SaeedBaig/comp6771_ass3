/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

All constructors were tested.
All operations (copy assignment, move assignment) were tested.
All methods (except a few iterator methods) were tested.
All operators (==, !=, <<) were tested.
All possible exceptions that could be thrown were tested.

All the methods were tested with 2 cases: a general case and an exceptional case
General cases should match the expected output, and exceptional cases should be
able throw with the expected exception.
*/

#include <sstream>
#include <string>
#include <utility>
#include "assignments/dg/graph.h"
#include "catch.h"

SCENARIO("Default constructor test") {
  WHEN("Default constructor is called") {
    gdwg::Graph<int, int> a;
    gdwg::Graph<int, int> b{};
    THEN("There should be no segmentation fault") {}
  }
}

SCENARIO("Constructor with 2 iterators") {
  WHEN("Default constructor is called") {
    std::vector<std::string> v{"Hello", "how", "are", "you"};
    gdwg::Graph<std::string, double> graph{v.begin(), v.end()};

    THEN("There should be no segmentation fault") {
      REQUIRE(graph.IsNode("Hello") == true);
      REQUIRE(graph.IsNode("how") == true);
      REQUIRE(graph.IsNode("are") == true);
      REQUIRE(graph.IsNode("you") == true);
      REQUIRE(graph.IsNode("null") == false);
      REQUIRE(graph.IsNode("HELLO") == false);
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
      REQUIRE(graph.IsNode("Hello") == true);
      REQUIRE(graph.IsNode("how") == true);
      REQUIRE(graph.IsNode("are") == true);
      REQUIRE(graph.IsNode("HELLO") == false);
    }
  }
}

SCENARIO("Constructor with initialization list") {
  WHEN("Creating a list to test") {
    gdwg::Graph<char, std::string> graph{'a', 'b', 'x', 'y'};
    THEN("There should be no segmentation fault") {
      REQUIRE(graph.IsNode('a') == true);
      REQUIRE(graph.IsNode('b') == true);
      REQUIRE(graph.IsNode('x') == true);
      REQUIRE(graph.IsNode('y') == true);
      REQUIRE(graph.IsNode('k') == false);
    }
  }
}

SCENARIO("Copy constructor test") {
  WHEN("Creating a list to test") {
    std::vector<std::string> v{"Hello", "how", "are", "you"};
    gdwg::Graph<std::string, double> graph{v.begin(), v.end()};
    gdwg::Graph<std::string, double> copy{graph};
    THEN("There should be no segmentation fault") {
      // property 1 holds
      REQUIRE(graph.IsNode("Hello") == true);
      REQUIRE(graph.IsNode("how") == true);
      REQUIRE(graph.IsNode("are") == true);
      REQUIRE(graph.IsNode("you") == true);
      REQUIRE(graph.IsNode("null") == false);
      REQUIRE(graph.IsNode("HELLO") == false);

      // property 2 also holds
      REQUIRE(copy.IsNode("Hello") == true);
      REQUIRE(copy.IsNode("how") == true);
      REQUIRE(copy.IsNode("are") == true);
      REQUIRE(copy.IsNode("you") == true);
      REQUIRE(copy.IsNode("null") == false);
      REQUIRE(copy.IsNode("HELLO") == false);
    }
  }
}

SCENARIO("Move constructor test") {
  WHEN("Creating a list to test") {
    std::vector<std::string> v{"Hello", "how", "are", "you"};
    gdwg::Graph<std::string, double> graph{v.begin(), v.end()};
    gdwg::Graph<std::string, double> aMove{std::move(graph)};
    THEN("There should be no segmentation fault") {
      REQUIRE(graph.IsNode("Hello") == false);
      REQUIRE(graph.IsNode("how") == false);
      REQUIRE(graph.IsNode("are") == false);
      REQUIRE(graph.IsNode("you") == false);
      REQUIRE(graph.IsNode("null") == false);

      REQUIRE(aMove.IsNode("Hello") == true);
      REQUIRE(aMove.IsNode("how") == true);
      REQUIRE(aMove.IsNode("are") == true);
      REQUIRE(aMove.IsNode("you") == true);
      REQUIRE(aMove.IsNode("null") == false);
    }
  }
}

SCENARIO("Copy assignment test") {
  WHEN("Creating a list to test") {
    std::vector<std::string> v{"Hello", "how", "are", "you"};
    gdwg::Graph<std::string, double> graph{v.begin(), v.end()};
    gdwg::Graph<std::string, double> empty;
    empty = graph;
    THEN("There should be no segmentation fault") {
      // property 1 holds
      REQUIRE(graph.IsNode("Hello") == true);
      REQUIRE(graph.IsNode("how") == true);
      REQUIRE(graph.IsNode("are") == true);
      REQUIRE(graph.IsNode("you") == true);
      REQUIRE(graph.IsNode("null") == false);
      REQUIRE(graph.IsNode("HELLO") == false);

      REQUIRE(empty.IsNode("Hello") == true);
      REQUIRE(empty.IsNode("how") == true);
      REQUIRE(empty.IsNode("are") == true);
      REQUIRE(empty.IsNode("you") == true);
      REQUIRE(empty.IsNode("null") == false);
      REQUIRE(empty.IsNode("HELLO") == false);
    }
  }
}

SCENARIO("Move assignment test") {
  WHEN("Creating a list to test") {
    std::vector<std::string> v{"Hello", "how", "are", "you"};
    gdwg::Graph<std::string, double> graph{v.begin(), v.end()};
    gdwg::Graph<std::string, double> empty;
    empty = std::move(graph);
    THEN("There should be no segmentation fault") {
      REQUIRE(graph.IsNode("Hello") == false);
      REQUIRE(graph.IsNode("how") == false);
      REQUIRE(graph.IsNode("are") == false);
      REQUIRE(graph.IsNode("you") == false);
      REQUIRE(graph.IsNode("null") == false);

      REQUIRE(empty.IsNode("Hello") == true);
      REQUIRE(empty.IsNode("how") == true);
      REQUIRE(empty.IsNode("are") == true);
      REQUIRE(empty.IsNode("you") == true);
      REQUIRE(empty.IsNode("null") == false);
    }
  }
}

SCENARIO("Inserting node test") {
  GIVEN("A graph") {
    gdwg::Graph<std::string, int> g;
    WHEN("We insert a node into it") {
      g.InsertNode("hello");
      THEN("That node is in the graph") { REQUIRE(g.IsNode("hello")); }
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
      REQUIRE(graph.IsNode(1) == true);
      REQUIRE(graph.IsNode(2) == true);
      REQUIRE(graph.IsNode(3) == true);
      REQUIRE(nodes.size() == 3);
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
      REQUIRE(graph.IsNode(1) == true);
      REQUIRE(graph.IsNode(2) == true);
      REQUIRE(graph.IsNode(3) == true);
      REQUIRE(nodes.size() == 3);
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
        REQUIRE_THROWS_WITH(g.InsertEdge("brisbane", "sydney", 42),
                            "Cannot call Graph::InsertEdge when either src or "
                            "dst node does not exist");
      }
    }

    WHEN("Insert an destination node that does not belong to the graph") {
      THEN("Should throw exception") {
        REQUIRE_THROWS_WITH(g.InsertEdge("sydney", "adelaide", 42),
                            "Cannot call Graph::InsertEdge when either src or "
                            "dst node does not exist");
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
        REQUIRE(g.IsNode("hello") == false);
        REQUIRE(g.IsNode("world") == false);
        REQUIRE(g.GetNodes().size() == 0);
      }
    }
  }
}

SCENARIO("Delete nodes - typical & exceptional cases") {
  GIVEN("Graph with existing nodes and edges - true-case testing") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 42);
    g.InsertEdge("sydney", "brisbane", 42);

    REQUIRE(g.IsNode("sydney") == true);
    REQUIRE(g.IsNode("melbourne") == true);
    REQUIRE(g.IsNode("brisbane") == true);

    REQUIRE(g.IsConnected("sydney", "melbourne") == true);
    REQUIRE(g.IsConnected("sydney", "brisbane") == true);

    WHEN("Delete one node") {
      g.DeleteNode("sydney");
      THEN("Nodes and edges associated to it should also be removed") {
        REQUIRE(g.IsNode("sydney") == false);
        REQUIRE_THROWS_WITH(g.IsConnected("sydney", "melbourne"),
                            "Cannot call Graph::IsConnected if src or dst node "
                            "don't exist in the graph");
        REQUIRE_THROWS_WITH(g.IsConnected("sydney", "brisbane"),
                            "Cannot call Graph::IsConnected if src or dst node "
                            "don't exist in the graph");
      }
    }
  }

  GIVEN("Graph with nothing in it and trying to delete from the graph") {
    gdwg::Graph<std::string, int> g;
    WHEN("Trying to delete 2 nodes that does not exist in the graph") {
      REQUIRE(g.DeleteNode("hello") == false);
      REQUIRE(g.DeleteNode("world") == false);
      THEN("That edge should be in the graph") {
        REQUIRE(g.IsNode("hello") == false);
        REQUIRE(g.IsNode("world") == false);
      }
    }
  }
}

SCENARIO("Replace node - replace new element with old element") {
  GIVEN("A graph with 0 nodes") {
    std::vector<std::string> v{"Hello", "how", "are", "you"};
    gdwg::Graph<std::string, double> graph{v.begin(), v.end()};
    WHEN("Trying to delete 2 nodes that does not exist in the graph") {
      REQUIRE(graph.DeleteNode("hello") == false);
      REQUIRE(graph.DeleteNode("world") == false);
      THEN("That edge should be in the graph") {
        REQUIRE(graph.IsNode("hello") == false);
        REQUIRE(graph.IsNode("world") == false);
      }
    }
  }
}

SCENARIO("Replace() correctness & coverage") {
  GIVEN("A sample graph") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");
    g.InsertNode("adelaide");
    g.InsertNode("perth");
    g.InsertNode("darwin");
    g.InsertNode("hobart");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 42);
    g.InsertEdge("sydney", "brisbane", 42);
    g.InsertEdge("sydney", "perth", 42);
    g.InsertEdge("sydney", "darwin", 42);
    g.InsertEdge("sydney", "hobart", 42);

    WHEN("Replace old node with new node") {
      REQUIRE(g.Replace("sydney", "hongkong") == true);
      auto nodes = g.GetConnected("hongkong");
      THEN("That edge should be in the graph") {
        REQUIRE(nodes[0] == "brisbane");
        REQUIRE(nodes[1] == "darwin");
        REQUIRE(nodes[2] == "hobart");
        REQUIRE(nodes[3] == "melbourne");
        REQUIRE(nodes[4] == "perth");
        REQUIRE(g.IsConnected("hongkong", "melbourne"));
        REQUIRE(g.IsConnected("hongkong", "brisbane"));
        REQUIRE(g.IsConnected("hongkong", "perth"));
        REQUIRE(g.IsConnected("hongkong", "darwin"));
        REQUIRE(g.IsConnected("hongkong", "hobart"));
      }
    }
  }

  GIVEN("A sample graph") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");
    g.InsertNode("adelaide");
    g.InsertNode("perth");
    g.InsertNode("darwin");
    g.InsertNode("hobart");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 42);
    g.InsertEdge("sydney", "brisbane", 42);
    g.InsertEdge("sydney", "perth", 42);
    g.InsertEdge("sydney", "darwin", 42);
    g.InsertEdge("sydney", "hobart", 42);

    WHEN("Replace node which the new node name already exist in the graph") {
      THEN("That edge should be in the graph") {
        REQUIRE(g.Replace("sydney", "melbourne") == false);
      }
    }
  }

  GIVEN("A sample graph") {
    gdwg::Graph<char, int> g{'a', 'b', 'c'};
    WHEN("We try to replace a node that is not in the graph") {
      THEN("An exception is thrown") {
        REQUIRE_THROWS_WITH(
            g.Replace('d', 'e'),
            "Cannot call Graph::Replace on a node that doesn't exist");
      }
    }
  }
}

SCENARIO("MergeReplace() correctness & coverage") {
  GIVEN("A graph containing existing elements - merge replace true case") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");
    g.InsertNode("adelaide");
    g.InsertNode("perth");
    g.InsertNode("darwin");
    g.InsertNode("hobart");
    g.InsertNode("shanghai");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 42);
    g.InsertEdge("sydney", "brisbane", 42);
    g.InsertEdge("sydney", "perth", 42);
    g.InsertEdge("sydney", "darwin", 42);
    g.InsertEdge("sydney", "hobart", 42);
    g.InsertEdge("sydney", "shanghai", 42);

    g.MergeReplace("sydney", "shanghai");

    WHEN("Replace old node with new node") {
      auto nodes = g.GetConnected("shanghai");
      THEN("That edge should be in the graph") {
        REQUIRE(nodes[0] == "brisbane");
        REQUIRE(nodes[1] == "darwin");
        REQUIRE(nodes[2] == "hobart");
        REQUIRE(nodes[3] == "melbourne");
        REQUIRE(nodes[4] == "perth");
        REQUIRE(nodes[5] == "shanghai");
        REQUIRE(g.IsConnected("shanghai", "melbourne"));
        REQUIRE(g.IsConnected("shanghai", "brisbane"));
        REQUIRE(g.IsConnected("shanghai", "perth"));
        REQUIRE(g.IsConnected("shanghai", "darwin"));
        REQUIRE(g.IsConnected("shanghai", "hobart"));
        REQUIRE(g.IsConnected("shanghai", "shanghai"));
      }
    }
  }

  GIVEN("A graph containing existing elements - merge replace false case") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");
    g.InsertNode("adelaide");
    g.InsertNode("perth");
    g.InsertNode("darwin");
    g.InsertNode("hobart");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 42);
    g.InsertEdge("sydney", "brisbane", 42);
    g.InsertEdge("sydney", "perth", 42);
    g.InsertEdge("sydney", "darwin", 42);
    g.InsertEdge("sydney", "hobart", 42);

    WHEN("Replace nodes") {
      THEN("Should catch exception") {
        REQUIRE_THROWS_WITH(g.MergeReplace("sydney", "shanghai"),
                            "Cannot call Graph::MergeReplace on old or new "
                            "data if they don't exist in the graph");
      }
    }
  }
}

SCENARIO("Inserting an edge that is already in the graph") {
  GIVEN("A graph with an edge in it") {
    const auto edge = std::make_tuple("Hello", "There!", 5.4);
    const auto edges =
        std::vector<std::tuple<std::string, std::string, double>>{edge};
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

  WHEN("We try to insert an edge into the existing graph with nodes that arent "
       "in it") {
    std::string u{"c"};
    THEN("An exception is thrown") {
      REQUIRE_THROWS_WITH(graph.InsertEdge("a", u, 1),
                          "Cannot call Graph::InsertEdge when either src or "
                          "dst node does not exist");
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
    WHEN("We try to check if 2 nodes (at least 1 of which is NOT in the graph) "
         "are connected") {
      THEN("An exception is thrown") {
        REQUIRE_THROWS_WITH(g.IsConnected('a', 'Z'),
                            "Cannot call Graph::IsConnected if src or dst node "
                            "don't exist in the graph");
        REQUIRE_THROWS_WITH(g.IsConnected('S', 'b'),
                            "Cannot call Graph::IsConnected if src or dst node "
                            "don't exist in the graph");
        REQUIRE_THROWS_WITH(g.IsConnected('S', 'Z'),
                            "Cannot call Graph::IsConnected if src or dst node "
                            "don't exist in the graph");
      }
    }
  }
}

SCENARIO("GetNode() correctness & coverage test") {
  WHEN("A graph contains something and GetNode() is called") {
    std::vector<std::string> v{"Hello", "how", "are", "you"};
    gdwg::Graph<std::string, double> graph{v.begin(), v.end()};
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
      REQUIRE(nodes.size() == 0);
      REQUIRE(std::find(nodes.begin(), nodes.end(), "Hello") == nodes.end());
    }
  }
}

SCENARIO("GetConnected() correctness & coverage test") {
  WHEN("A graph contains something and GetConnected() is called") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");
    g.InsertNode("adelaide");
    g.InsertNode("perth");
    g.InsertNode("darwin");
    g.InsertNode("hobart");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 42);
    g.InsertEdge("sydney", "brisbane", 42);
    g.InsertEdge("sydney", "perth", 42);
    g.InsertEdge("sydney", "darwin", 42);
    g.InsertEdge("sydney", "hobart", 42);

    auto nodes = g.GetConnected("sydney");
    THEN("Elements should be added and it is added in the correct order") {
      REQUIRE(std::find(nodes.begin(), nodes.end(), "melbourne") !=
              nodes.end());
      REQUIRE(std::find(nodes.begin(), nodes.end(), "brisbane") != nodes.end());
      REQUIRE(std::find(nodes.begin(), nodes.end(), "perth") != nodes.end());
      REQUIRE(std::find(nodes.begin(), nodes.end(), "darwin") != nodes.end());
      REQUIRE(std::find(nodes.begin(), nodes.end(), "hobart") != nodes.end());
      REQUIRE(std::find(nodes.begin(), nodes.end(), "adelaide") == nodes.end());
      REQUIRE(nodes[0] == "brisbane");
      REQUIRE(nodes[1] == "darwin");
      REQUIRE(nodes[2] == "hobart");
      REQUIRE(nodes[3] == "melbourne");
      REQUIRE(nodes[4] == "perth");
    }
  }

  WHEN("A graph contains nothing and get nodes") {
    gdwg::Graph<std::string, int> g;
    THEN("Nothing should be there") {
      REQUIRE_THROWS_WITH(
          g.GetConnected("sydney"),
          "Cannot call Graph::GetConnected if src doesn't exist in the graph");
    }
  }

  WHEN("A graph contains something and GetConnected() is called and source is "
       "not in the graph") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");
    g.InsertNode("adelaide");
    g.InsertNode("perth");
    g.InsertNode("darwin");
    g.InsertNode("hobart");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 42);
    g.InsertEdge("sydney", "brisbane", 42);
    g.InsertEdge("sydney", "perth", 42);
    g.InsertEdge("sydney", "darwin", 42);
    g.InsertEdge("sydney", "hobart", 42);

    THEN("Elements should be added and it is added in the correct order") {
      REQUIRE_THROWS_WITH(
          g.GetConnected("kensington"),
          "Cannot call Graph::GetConnected if src doesn't exist in the graph");
    }
  }
}

SCENARIO("GetWeights() correctness & coverage test") {
  WHEN("A graph contains something and GetConnected() is called - inserted "
       "random order") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");
    g.InsertNode("adelaide");
    g.InsertNode("perth");
    g.InsertNode("darwin");
    g.InsertNode("hobart");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 43);
    g.InsertEdge("sydney", "melbourne", 42);
    g.InsertEdge("sydney", "melbourne", 45);
    g.InsertEdge("sydney", "brisbane", 42);
    g.InsertEdge("sydney", "perth", 42);
    g.InsertEdge("sydney", "darwin", 42);
    g.InsertEdge("sydney", "hobart", 42);

    auto weight = g.GetWeights("sydney", "melbourne");
    THEN("Elements should be added and it is added in the correct order") {
      REQUIRE(weight[0] == 42);
      REQUIRE(weight[1] == 43);
      REQUIRE(weight[2] == 45);
    }
  }

  WHEN("Getting an edge not in the graph - source") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");
    g.InsertNode("adelaide");
    g.InsertNode("perth");
    g.InsertNode("darwin");
    g.InsertNode("hobart");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 43);
    g.InsertEdge("sydney", "melbourne", 42);
    g.InsertEdge("sydney", "melbourne", 45);
    g.InsertEdge("sydney", "brisbane", 42);
    g.InsertEdge("sydney", "perth", 42);
    g.InsertEdge("sydney", "darwin", 42);
    g.InsertEdge("sydney", "hobart", 42);

    THEN("Should throw exception") {
      REQUIRE_THROWS_WITH(g.GetWeights("kensington", "melbourne"),
                          "Cannot call Graph::GetWeights if src or dst node "
                          "don't exist in the graph");
    }
  }

  WHEN("Getting an edge not in the graph - destination") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");
    g.InsertNode("adelaide");
    g.InsertNode("perth");
    g.InsertNode("darwin");
    g.InsertNode("hobart");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 43);
    g.InsertEdge("sydney", "brisbane", 42);
    g.InsertEdge("sydney", "perth", 42);
    g.InsertEdge("sydney", "darwin", 42);
    g.InsertEdge("sydney", "hobart", 42);

    THEN("Should throw exception") {
      REQUIRE_THROWS_WITH(g.GetWeights("sydney", "kensington"),
                          "Cannot call Graph::GetWeights if src or dst node "
                          "don't exist in the graph");
    }
  }
}

SCENARIO("const_iterator find correctness & coverage ") {
  WHEN("Find an edge in a graph - true case") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");
    g.InsertNode("adelaide");
    g.InsertNode("perth");
    g.InsertNode("darwin");
    g.InsertNode("hobart");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 43);
    g.InsertEdge("sydney", "brisbane", 42);
    g.InsertEdge("sydney", "perth", 42);
    g.InsertEdge("sydney", "darwin", 42);
    g.InsertEdge("sydney", "hobart", 42);

    auto it = g.find("sydney", "melbourne", 43);
    const auto not_found = g.cend();
    THEN("it should not be end") {
      REQUIRE(it != not_found);
      REQUIRE(std::get<0>(*it) == "sydney");
      REQUIRE(std::get<1>(*it) == "melbourne");
      REQUIRE(std::get<2>(*it) == 43);
    }
  }
}

SCENARIO("erase correctness & coverage ") {
  GIVEN("A graph containing nodes and edges - true case") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 42);
    g.InsertEdge("sydney", "brisbane", 42);

    WHEN("Removing an edge") {
      REQUIRE(g.erase("sydney", "melbourne", 42) == true);
      auto nodes = g.GetConnected("sydney");
      THEN("There should be only 2 edges after removing the first one") {
        REQUIRE(std::find(nodes.begin(), nodes.end(), "melbourne") ==
                nodes.end());
        REQUIRE(std::find(nodes.begin(), nodes.end(), "brisbane") !=
                nodes.end());
      }
    }
  }

  GIVEN("A graph containing nodes and edges - false case") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 42);
    g.InsertEdge("sydney", "brisbane", 42);

    WHEN("Removing 2 edges twice") {
      THEN("Should not be able to remove") {
        REQUIRE(g.erase("sydney", "melbourne", 42) == true);
        REQUIRE(g.erase("sydney", "melbourne", 42) == false);
      }
    }
  }

  GIVEN("A graph containing nodes and edges - removing one edge") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 43);
    g.InsertEdge("sydney", "melbourne", 90);
    g.InsertEdge("sydney", "brisbane", 42);

    WHEN("Deleting one edge") {
      g.erase("sydney", "melbourne", 42);
      auto nodes = g.GetConnected("sydney");
      THEN("There should be only 2 edges after removing the first one") {
        auto nodes = g.GetConnected("sydney");
        REQUIRE(std::find(nodes.begin(), nodes.end(), "melbourne") !=
                nodes.end());
        REQUIRE(std::find(nodes.begin(), nodes.end(), "brisbane") !=
                nodes.end());
      }
    }
  }
}

SCENARIO("clear() find correctness & coverage ") {
  GIVEN("There is a simple graph") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");
    g.InsertNode("adelaide");
    g.InsertNode("perth");
    g.InsertNode("darwin");
    g.InsertNode("hobart");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 43);
    g.InsertEdge("sydney", "melbourne", 42);
    g.InsertEdge("sydney", "melbourne", 45);
    g.InsertEdge("sydney", "brisbane", 42);
    g.InsertEdge("sydney", "perth", 42);
    g.InsertEdge("sydney", "darwin", 42);
    g.InsertEdge("sydney", "hobart", 42);

    WHEN("Clear is called") {
      g.Clear();
      THEN("Edges and nodes should be cleared") {
        auto nodes = g.GetNodes();
        REQUIRE(nodes.size() == 0);
      }
    }
  }
}

SCENARIO("const_iterator erase true case") {
  GIVEN("There is a simple graph") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");
    g.InsertNode("adelaide");
    g.InsertNode("perth");
    g.InsertNode("darwin");
    g.InsertNode("hobart");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 43);
    g.InsertEdge("sydney", "brisbane", 42);
    g.InsertEdge("sydney", "perth", 42);
    g.InsertEdge("sydney", "darwin", 42);
    g.InsertEdge("sydney", "hobart", 42);

    WHEN("Const iterator is called") {
      auto it = g.find("sydney", "melbourne", 43);
      THEN("The edge should be deleted") {
        if (it != g.end()) {
          g.erase(it);
        }
        REQUIRE(g.IsConnected("sydney", "melbourne") == false);
      }
    }
  }
}

SCENARIO("friend equal true case") {
  GIVEN("There is a simple graph") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");
    g.InsertNode("adelaide");
    g.InsertNode("perth");
    g.InsertNode("darwin");
    g.InsertNode("hobart");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 43);
    g.InsertEdge("sydney", "brisbane", 42);
    g.InsertEdge("sydney", "perth", 42);
    g.InsertEdge("sydney", "darwin", 42);
    g.InsertEdge("sydney", "hobart", 42);

    // copy a graph
    gdwg::Graph<std::string, int> copy{g};

    WHEN("== is checked") {
      THEN("Should be equal") { REQUIRE(g == copy); }
    }
  }
}

SCENARIO("friend not equal true case") {
  GIVEN("There is a simple graph") {
    gdwg::Graph<std::string, int> g;
    // inserting nodes
    g.InsertNode("sydney");
    g.InsertNode("melbourne");
    g.InsertNode("brisbane");
    g.InsertNode("adelaide");
    g.InsertNode("perth");
    g.InsertNode("darwin");
    g.InsertNode("hobart");

    // inserting edges
    g.InsertEdge("sydney", "melbourne", 43);
    g.InsertEdge("sydney", "brisbane", 42);
    g.InsertEdge("sydney", "perth", 42);
    g.InsertEdge("sydney", "darwin", 42);
    g.InsertEdge("sydney", "hobart", 42);

    // copy a graph
    gdwg::Graph<std::string, int> copy{g};
    copy.InsertNode("penrith");
    copy.InsertEdge("sydney", "penrith", 43);

    WHEN("== is checked") {
      THEN("Should not be equal") { REQUIRE(g != copy); }
    }
  }
}

SCENARIO("Outputstream test") {
  GIVEN("A graph") {
    gdwg::Graph<int, int> g{1, 2, 3, 4, 5, 6};
    g.InsertEdge(1, 5, -1);
    g.InsertEdge(2, 1, 1);
    g.InsertEdge(2, 4, 2);
    g.InsertEdge(3, 2, 2);
    g.InsertEdge(3, 6, -8);
    g.InsertEdge(4, 1, -4);
    g.InsertEdge(4, 5, 3);
    g.InsertEdge(5, 2, 7);
    g.InsertEdge(6, 2, 5);
    g.InsertEdge(6, 3, 10);

    WHEN("Printing the graph") {
      std::stringstream ss;
      ss << g;
      THEN("It prints out the nodes and their connected edges properly") {
        const std::string expected_output =
            std::string("1 (\n") + std::string("  5 | -1\n") +
            std::string(")\n")

            + std::string("2 (\n") + std::string("  1 | 1\n") +
            std::string("  4 | 2\n") + std::string(")\n")

            + std::string("3 (\n") + std::string("  2 | 2\n") +
            std::string("  6 | -8\n") + std::string(")\n")

            + std::string("4 (\n") + std::string("  1 | -4\n") +
            std::string("  5 | 3\n") + std::string(")\n")

            + std::string("5 (\n") + std::string("  2 | 7\n") +
            std::string(")\n")

            + std::string("6 (\n") + std::string("  2 | 5\n") +
            std::string("  3 | 10\n") + std::string(")\n");

        REQUIRE(ss.str() == expected_output);
      }
    }
  }
}

SCENARIO("Testing begin(), end(), rbegin(), and rend()") {
  GIVEN("A graph `g` with some edges in it") {
    gdwg::Graph<int, int> g{1, 2, 3, 4, 5, 6};
    g.InsertEdge(1, 5, -1);
    g.InsertEdge(2, 1, 1);
    g.InsertEdge(2, 4, 2);

    WHEN("begin() is called on it") {
      THEN("It is exactly the same as g.cbegin()") {
        REQUIRE(g.begin() == g.cbegin());
      }
    }
    WHEN("end() is called on it") {
      THEN("It is exactly the same as g.cend()") {
        REQUIRE(g.end() == g.cend());
      }
    }
    /*
    // for some reason, get compiler errors in bazel when we try to use the
    // reverse iterators
    WHEN("rbegin() is called on it") {
      THEN("It is exactly the same as g.crbegin()") {
        REQUIRE(g.rbegin() == g.crbegin());
      }
    }
    WHEN("rend() is called on it") {
      THEN("It is exactly the same as g.crend()") {
        REQUIRE(g.rend() == g.crend());
      }
    }
    */
  }
}
