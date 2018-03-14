#include <catch.hpp>
#include <modeling/modelinggraph.h>
#include <algorithm/dfs.h>

TEST_CASE("Test cycle chaine") {
    ModelingGraph g;
    auto s0 = g.creerSommet("s0", VertexData());
    auto s1 = g.creerSommet("s1", VertexData());
    auto s2 = g.creerSommet("s2", VertexData());

    g.creeArete("a0", EdgeData(), s0, s1);
    g.creeArete("a1", EdgeData(), s1, s2);

    DFS dfs(&g);
    dfs.begin(s0);

    REQUIRE(!dfs.hasCycle());
}

TEST_CASE("Test cycle boucle") {
    ModelingGraph g;
    auto s0 = g.creerSommet("s0", VertexData());

    g.creeArete("a0", EdgeData(), s0, s0);

    DFS dfs(&g);
    dfs.begin(s0);

    REQUIRE(dfs.hasCycle());
}

TEST_CASE("Test cycle arbre") {
    ModelingGraph g;
    auto s0 = g.creerSommet("s0", VertexData());
    auto s1 = g.creerSommet("s1", VertexData());
    auto s2 = g.creerSommet("s2", VertexData());

    g.creeArete("a0", EdgeData(), s0, s1);
    g.creeArete("a1", EdgeData(), s0, s2);

    DFS dfs(&g);
    dfs.begin(s0);

    REQUIRE(!dfs.hasCycle());
}

TEST_CASE("Test cycle cycle") {
    ModelingGraph g;
    auto s0 = g.creerSommet("s0", VertexData());
    auto s1 = g.creerSommet("s1", VertexData());
    auto s2 = g.creerSommet("s2", VertexData());

    g.creeArete("a0", EdgeData(), s0, s1);
    g.creeArete("a1", EdgeData(), s1, s2);
    g.creeArete("a2", EdgeData(), s2, s0);

    DFS dfs(&g);
    dfs.begin(s0);

    REQUIRE(dfs.hasCycle());
}