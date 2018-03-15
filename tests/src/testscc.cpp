#include <catch.hpp>
#include <modeling/modelinggraph.h>
#include <algorithm/dfs.h>

TEST_CASE("Test CFC") {
    ModelingGraph g;
    auto s0 = g.creerSommet("s0", VertexData());
    auto s1 = g.creerSommet("s1", VertexData());
    auto s2 = g.creerSommet("s2", VertexData());
    auto s3 = g.creerSommet("s3", VertexData());
    auto s4 = g.creerSommet("s4", VertexData());
    auto s5 = g.creerSommet("s5", VertexData());

    g.creeArete("a0", EdgeData(), s0, s1);
    g.creeArete("a1", EdgeData(), s1, s2);
    g.creeArete("a2", EdgeData(), s2, s0);
    g.creeArete("a3", EdgeData(), s3, s4);

    auto scc = DFS::stronglyConnectedComponents(&g);

    scc.at(s0);
    scc.at(s1);
    scc.at(s2);
    scc.at(s3);
    scc.at(s4);
    scc.at(s5);

    REQUIRE(scc[s0] == scc[s1]);
    REQUIRE(scc[s1] == scc[s2]);

    REQUIRE(scc[s0] != scc[s3]);
    REQUIRE(scc[s0] != scc[s4]);
    REQUIRE(scc[s0] != scc[s5]);

    REQUIRE(scc[s3] != scc[s4]);
    REQUIRE(scc[s3] != scc[s5]);

    REQUIRE(scc[s4] != scc[s5]);
}