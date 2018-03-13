#include <catch.hpp>
#include <processor/vertexdata.h>
#include <processor/edgedata.h>
#include <graph/graphe.h>
#include <algorithm/dfs.h>

TEST_CASE("Test DFS") {
    Graphe<EdgeData, VertexData> g;
    auto s0 = g.creerSommet("s0", VertexData());
    auto s1 = g.creerSommet("s1", VertexData());
    auto s2 = g.creerSommet("s2", VertexData());
    auto s3 = g.creerSommet("s3", VertexData());

    g.creeArete("a1", EdgeData(), s0, s1);
    g.creeArete("a2", EdgeData(), s0, s2);
    g.creeArete("a3", EdgeData(), s1, s3);
    g.creeArete("a4", EdgeData(), s2, s3);

    DFS dfs(&g, s0);
    dfs.search();
    
    REQUIRE(dfs.explored(s0));
    REQUIRE(dfs.explored(s1));
    REQUIRE(dfs.explored(s2));
    REQUIRE(dfs.explored(s3));

    REQUIRE(dfs.closed(s0));
    REQUIRE(dfs.closed(s1));
    REQUIRE(dfs.closed(s2));
    REQUIRE(dfs.closed(s3));

    REQUIRE(dfs.order().size() == 4);
}

TEST_CASE("Test DFS non connexe") {
    Graphe<EdgeData, VertexData> g;
    auto s0 = g.creerSommet("s0", VertexData());
    auto s1 = g.creerSommet("s1", VertexData());
    auto s2 = g.creerSommet("s2", VertexData());
    auto s3 = g.creerSommet("s3", VertexData());
    auto s4 = g.creerSommet("s4", VertexData());
    auto s5 = g.creerSommet("s5", VertexData());
    auto s6 = g.creerSommet("s6", VertexData());

    g.creeArete("a1", EdgeData(), s0, s1);
    g.creeArete("a2", EdgeData(), s0, s2);
    g.creeArete("a3", EdgeData(), s1, s3);
    g.creeArete("a4", EdgeData(), s2, s3);
    g.creeArete("a5", EdgeData(), s4, s5);
    g.creeArete("a6", EdgeData(), s5, s6);
    g.creeArete("a7", EdgeData(), s6, s4);

    DFS dfs(&g, s0);
    dfs.search();

    REQUIRE(dfs.explored(s0));
    REQUIRE(dfs.explored(s1));
    REQUIRE(dfs.explored(s2));
    REQUIRE(dfs.explored(s3));
    REQUIRE(!dfs.explored(s4));
    REQUIRE(!dfs.explored(s5));
    REQUIRE(!dfs.explored(s6));

    REQUIRE(dfs.closed(s0));
    REQUIRE(dfs.closed(s1));
    REQUIRE(dfs.closed(s2));
    REQUIRE(dfs.closed(s3));
    REQUIRE(!dfs.closed(s4));
    REQUIRE(!dfs.closed(s5));
    REQUIRE(!dfs.closed(s6));

    REQUIRE(dfs.order().size() == 4);
}