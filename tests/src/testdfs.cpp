#include <catch.hpp>
#include <modeling/vertexdata.h>
#include <modeling/edgedata.h>
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

    DFS dfs(&g);
    dfs.begin(s0);
    
    REQUIRE(dfs.explored(s0));
    REQUIRE(dfs.explored(s1));
    REQUIRE(dfs.explored(s2));
    REQUIRE(dfs.explored(s3));

    REQUIRE(dfs.closed(s0));
    REQUIRE(dfs.closed(s1));
    REQUIRE(dfs.closed(s2));
    REQUIRE(dfs.closed(s3));

    REQUIRE(dfs.order().size() == 3);
    REQUIRE(dfs.componentsCount() == 1);
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

    DFS dfs(&g);
    dfs.begin(s0);

    REQUIRE(dfs.componentsCount() == 2);
}

TEST_CASE("Test DFS partiel non connexe") {
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

    DFS dfs(&g, false);
    dfs.begin(s0);

    REQUIRE(dfs.closed(s0));
    REQUIRE(dfs.closed(s1));
    REQUIRE(dfs.closed(s2));
    REQUIRE(dfs.closed(s3));
    REQUIRE(!dfs.closed(s4));
    REQUIRE(!dfs.closed(s5));
    REQUIRE(!dfs.closed(s6));

    REQUIRE(dfs.componentsCount() == 1);
}

TEST_CASE("Test DFS prefixe-suffixe") {
    Graphe<EdgeData, VertexData> g;
    auto s0 = g.creerSommet("s0", VertexData());
    auto s1 = g.creerSommet("s1", VertexData());
    auto s2 = g.creerSommet("s2", VertexData());

    g.creeArete("a1", EdgeData(), s0, s1);
    g.creeArete("a2", EdgeData(), s1, s2);

    DFS dfs(&g);
    dfs.begin(s0);

    REQUIRE(dfs.prefixNumber(s0) == 1);
    REQUIRE(dfs.prefixNumber(s1) == 2);
    REQUIRE(dfs.prefixNumber(s2) == 3);

    REQUIRE(dfs.suffixNumber(s0) == 3);
    REQUIRE(dfs.suffixNumber(s1) == 2);
    REQUIRE(dfs.suffixNumber(s2) == 1);
}

TEST_CASE("Test DFS prefixe-suffixe 2") {
    Graphe<EdgeData, VertexData> g;
    auto s0 = g.creerSommet("s0", VertexData());
    auto s1 = g.creerSommet("s1", VertexData());
    auto s2 = g.creerSommet("s2", VertexData());

    g.creeArete("a1", EdgeData(), s0, s1);
    g.creeArete("a2", EdgeData(), s1, s2);
    g.creeArete("a3", EdgeData(), s0, s2);

    DFS dfs(&g);
    dfs.begin(s0);

    REQUIRE(dfs.explored(s0));
    REQUIRE(dfs.explored(s1));
    REQUIRE(dfs.explored(s2));

    REQUIRE(dfs.closed(s0));
    REQUIRE(dfs.closed(s1));
    REQUIRE(dfs.closed(s2));


    REQUIRE(dfs.prefixNumber(s0) == 1);
    REQUIRE(dfs.prefixNumber(s1) == 3);
    REQUIRE(dfs.prefixNumber(s2) == 2);

    REQUIRE(dfs.suffixNumber(s0) == 3);
    REQUIRE(dfs.suffixNumber(s1) == 2);
    REQUIRE(dfs.suffixNumber(s2) == 1);
}

TEST_CASE("Test DFS topologique") {
    Graphe<EdgeData, VertexData> g;
    auto s0 = g.creerSommet("s0", VertexData());
    auto s1 = g.creerSommet("s1", VertexData());
    auto s2 = g.creerSommet("s2", VertexData());
    auto s3 = g.creerSommet("s3", VertexData());
    auto s4 = g.creerSommet("s4", VertexData());
    auto s5 = g.creerSommet("s5", VertexData());

    g.creeArete("a1", EdgeData(), s0, s1);
    g.creeArete("a2", EdgeData(), s1, s2);
    g.creeArete("a3", EdgeData(), s2, s5);

    g.creeArete("a4", EdgeData(), s0, s3);
    g.creeArete("a5", EdgeData(), s3, s4);
    g.creeArete("a6", EdgeData(), s4, s5);

    DFS dfs(&g);
    dfs.begin(s0);

    REQUIRE(!dfs.hasCycle());
    REQUIRE(dfs.topologicalNumber(s5) == 6);
    REQUIRE(dfs.topologicalNumber(s4) == 5);
    REQUIRE(dfs.topologicalNumber(s3) == 4);
    REQUIRE(dfs.topologicalNumber(s2) == 3);
    REQUIRE(dfs.topologicalNumber(s1) == 2);
    REQUIRE(dfs.topologicalNumber(s0) == 1);
}