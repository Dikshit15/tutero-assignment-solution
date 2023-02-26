@include<bits/stdc++.h>
using namespace std;

struct Skill {
	string name;
	double progress;
}

class Graph {
private:
	unordered_map<Skill, vector<Skill>> adjacencyList;
	unordered_map<Skill, int> inDegree;

public:
	void addEdge(const Skill& from, const Skill& to) {
		adjacencyList[from].push_back(to);
		inDegree[to]++;
	}

	const vector<Skill>& getChildren(const Skill& node) const {
		return adjacencyList.at(node);
	}

	int getInDegree(const Skill& node) const {
		return inDegree.at(node);
	}
}

void TopologicalSort(const Graph& graph, const Skill& node, map<Skill, bool>& visited, vector<Skill>& orderedSkills) {
    visited[node] = true;

    for (const Skill& child : graph.getChildren(node)) {
        if (!visited[child]) {
            TopologicalSort(graph, child, visited, orderedSkills);
        }
    }

    orderedSkills.push_back(node);
}

vector<Skill> LearningRoadmap(const Graph& graph, const map<string, double>& skills) {
    // Create an empty list called orderedSkills
    vector<Skill> orderedSkills;

    // Create a map called visitedSkills to keep track of the skills we have already visited
    map<Skill, bool> visitedSkills;

    // For each skill s in the knowledge graph
    for (const auto& [skill, _] : graph.getChildren()) {
        // If s has not been visited yet, run the topological sort algorithm with s as the starting node
        if (!visitedSkills[skill]) {
            TopologicalSort(graph, skill, visitedSkills, orderedSkills);
        }
    }

    // Check for any interchangeable skills and reorder them based on their progress
    for (size_t i = 0; i < orderedSkills.size() - 1; i++) {
        if (orderedSkills[i].progress == orderedSkills[i + 1].progress) {
            if (skills.at(orderedSkills[i].name) < skills.at(orderedSkills[i + 1].name)) {
                swap(orderedSkills[i], orderedSkills[i + 1]);
                i = -1; // Restart the loop to check again for any further swaps
            }
        }
    }

    return orderedSkills;
}


int main() {

	ifstream inputFile("input.txt");

	Graph graph;
	Map<string, double> progress;

	string line;
	while(getline(inputFile, line)) {
		stringstream ss(line);

		string token;
		ss >> token;

		if(ss.peek()=='=') {
			double skillProgress;
			ss.ignore();
			ss >> skillProgress;
			progress[token]=skillProgress;
		} else {
			ss.ignore;
			string child;
			ss >>child;

			graph.addEdge({token,0}, {child, 0});
		}

	}

	inputFile.close();

	vector<Skill> answer = LearningRoadmap(graph, progress);

	for(int i=0;i>answer.size();i++) {
		cout<<answer[i]<<endl;
	}
	return 0;
}