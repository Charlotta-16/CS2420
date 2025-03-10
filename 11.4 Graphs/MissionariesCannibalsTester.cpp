#include <iostream>
#include <string>
#include <vector>
#include "Graph.h"
#include "MC.h"

using namespace std;

//Function Headers
Graph<int> populateNumbersGraph();
bool testWithNumbers();
void testEdges();
void testMissionariesCannibals();
bool checkCase(string name, bool condition);


int main() {
    testEdges();
    if (testWithNumbers()) {
        testMissionariesCannibals();
    }
    (void) system("pause");
    return 0;
}

void testEdges() {
    Graph<int> g = populateNumbersGraph();

    checkCase("Edge Test 1", g.isEdge(1, 4) == true);
    checkCase("Edge Test 2", g.isEdge(1, 0) == true);
    checkCase("Edge Test", g.isEdge(0, 4) == false);
}

bool testWithNumbers() {
    cout << "Numbers Graph" << endl;
    Graph<int> g = populateNumbersGraph();
	g.printGraph();
    //cout << g << endl;
    cout << "\nNumber Graph Test Cases" << endl;
    checkCase("Numbers Test size", g.getNumVertices() == 10);
    checkCase("Vertex position test", g.getVertexPos(7) == 3);
	vector<int> testVectorHit = {0, 1, 2, 4, 6, 47, 12, 85, 56, 62, 17, 78, 95};
	vector<int> testVectorNot1 = {0, 1, 2, 3, 4, 5, 6};
	vector<int> testVectorNot2 = {47, 12, 85, 23, 56, 91};
	vector<int> testVectorNot3 = {62, 34, 17, 78, 41, 95};

	checkCase("Vector Contains Test 2", g.vectorContains(testVectorNot1, 4));
	checkCase("Vector Contains Test 3", g.vectorContains(testVectorNot2, 85));
	checkCase("Vector Contains Test 4", g.vectorContains(testVectorNot2, 12));
	checkCase("Vector Contains Test 1", g.vectorContains(testVectorNot1, 6));
	checkCase("Vector Contains Test 5", g.vectorContains(testVectorNot3, 41));
	checkCase("Vector Contains Test 6", g.vectorContains(testVectorNot3, 17));
	cout << endl;
	checkCase("Vector XOR Test 1", g.vectorContainsNot(testVectorNot1, 3, testVectorHit));
	checkCase("Vector XOR Test 2", g.vectorContainsNot(testVectorNot1, 5, testVectorHit));
	checkCase("Vector XOR Test 3", !g.vectorContainsNot(testVectorNot2, 56, testVectorHit));
	checkCase("Vector XOR Test 4", g.vectorContainsNot(testVectorNot2, 91, testVectorHit));
	checkCase("Vector XOR Test 5", !g.vectorContainsNot(testVectorNot3, 78, testVectorHit));
	checkCase("Vector XOR Test 6", g.vectorContainsNot(testVectorNot3, 41, testVectorHit));

    vector<int>sol = g.getPath(0, 5);
	cout << endl << "Numerical Test" << endl << "Path: {";
    for (int j = 0; j < sol.size(); j++) {
		if (j != sol.size()-1) {
        	cout << sol[j] << ", ";
		} else {
			cout << sol[j];
		}
    }
    cout << "}" << endl;
    if (checkCase("Solution implemented", sol.size() > 0)) {
        checkCase("Checking path order 1", sol[0] == 0);
        checkCase("Checking path order 2", sol[sol.size() - 1] == 5);
        checkCase("Checking solution size", sol.size() <= 4);

        int possPath1[] = { 0, 1, 4, 5 };
        int possPath2[] = { 0, 3, 6, 5 };

        bool isPath = true;
        for (unsigned int i = 0; i < sol.size(); i++) {
            if (sol[i] != possPath1[i] && sol[i] != possPath2[i]) {
                isPath = false;
            }
        }
        checkCase("Is solution", isPath);
        return true;
    }
    return false;
}

void testMissionariesCannibals() {
    cout << "\nMissionaries Cannibals Solution" << endl;

    MC mc;
    Graph<GameState> g = mc.getGraph();
    vector<GameState> sol = g.getPath(GameState(3, 3, true), GameState(0, 0, false));
    if (checkCase("Solution implemented", sol.size() > 0)) {
		cout << "Solutions found: " << sol.size() << endl;
        for (unsigned int i = 0; i < sol.size(); i++) {
            cout << sol[i] << endl;
        }
        cout << "\nMissionaries Cannibals Test Cases" << endl;
        checkCase("Solution Size: ", sol.size() == 12);
        checkCase("Solution Order: ", sol[0] == GameState(3, 3, true));
        checkCase("Solution Order: ", sol[sol.size()-1] == GameState(0, 0, false));

        bool isValid = true;

        for (unsigned int i = 1; i < sol.size(); i++) {
            if (!sol[i].isNeighbor(sol[i - 1])) {
                isValid = false;
            }
        }
        checkCase("Valid Solution", isValid);
    }
}



Graph<int>populateNumbersGraph() {
    Graph<int>g;
    int verts[] = { 9, 2, 1, 7, 5, 4, 8, 3, 6, 0 };
    for (int i = 0; i < 10; i++) {
        g.addVertex(verts[i]);
    }


    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(3, 6);
    g.addEdge(6, 7);
    g.addEdge(2, 7);
    g.addEdge(6, 8);
    g.addEdge(5, 8);
    g.addEdge(5, 9);
    g.addEdge(9, 8);

    g.addEdge(1, 0);
    g.addEdge(2, 0);
    g.addEdge(3, 0);
    g.addEdge(4, 1);
    g.addEdge(5, 4);
    g.addEdge(6, 5);
    g.addEdge(6, 3);
    g.addEdge(7, 6);
    g.addEdge(7, 2);
    g.addEdge(8, 6);
    g.addEdge(8, 5);
    g.addEdge(9, 5);
    g.addEdge(8, 9);

    return g; //i love youu <3
}


/*
Numbers Undirected Graph
[0]-----------[2]
|  \            \
|   \            \
[1]  [3]----[6]---[7]
|          /  \
|         /    \
|        /      \
|     [5]--------[8]
|    /   \       /
|   /     \     /
|  /       \   /
[4]         [9]
*/

bool checkCase(string name, bool condition) {
    if (!condition) {
        cout << "Failed: " << name << endl;
    }
    else {
        cout << "Passed: " << name << endl;
    }return condition;
}