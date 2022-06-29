#include "Graph.h"
#include <iostream>


Graph::Graph(ifstream &ifs) {
	int nodes = 0;
    int edges = 0;
    int weight = 0;
    string name = "";
    string neighborName = "";

    ifs >> nodes;
    ifs >> edges;
    //For error "syntax error in line 2 near '['"
    ifs.ignore();

    //Making the nodes
    for (int i = 0; i < nodes; i++) 
    {
		Vertex newNode;
		string temp = "";
		getline(ifs, temp);
		newNode.label = temp;
		vertices.push_back(newNode);
	}
//Assigning the adjacent neighbors + index
    while (ifs >> name) 
    {
		int index = 0;
        int neighborIndex = 0;
		
		ifs >> neighborName;
		ifs >> weight;
		
		for (unsigned int i = 0; i < vertices.size(); i++) {
            //Assign an index in vertices to name
			if (name == vertices.at(i).label) {
				index = i;
			}
            //Assign index to neighbor 
			if (neighborName == vertices.at(i).label) {
				neighborIndex = i;
			}
		}
		//Push back the neighbors into the vertices with weight
        //http://www.cplusplus.com/reference/utility/pair/pair/
		vertices.at(index).neighbors.push_back(make_pair(neighborIndex, weight));
	}
}

void Graph::output_graph(const string &fileName)
{
    ofstream outFS(fileName.c_str());

    if (!outFS.is_open())
    {
        cout << "Error" << endl;
        return;
    }

    outFS << "digraph G {" << endl;
    for (unsigned i = 0; i < vertices.size(); ++i)
    { //assign distance and label
        if (vertices.at(i).distance != INT_MAX) 
        {
				outFS << "	" << vertices.at(i).label << "[label= \"" << vertices.at(i).label << " " << vertices.at(i).distance << "\"];" << endl;
				list<pair<int, int> >::iterator j;
                //assign distance and label to neighbor vertices
				for (j = vertices.at(i).neighbors.begin(); j != vertices.at(i).neighbors.end(); j++) 
                {
					outFS << "	" << vertices.at(i).label << " -> " << vertices.at(j->first).label << endl;
                }
	    }
    }
    outFS << "}";
	outFS.close();
	string command = "dot -T jpg " + fileName + " -o pic.jpg";
	system(command.c_str());	    
}


Graph::~Graph() 
{
	vertices.clear();
}

//https://d1b10bmlvqabco.cloudfront.net/attach/ilv1r6m8xjc64o/h7ks2ibk8jg6s3/ioki9sunvh1o/graphs.pdf
// for each vertex u in V[G] - [s] do
// color[u] = WHITE (White means undiscovered)
// d[u] = Infinity (distance from s)
// pr[u] = NIL (previous vertex)
// color[s] = GRAY, d[s] = 0, pr[s] = NIL, Q = {}
// ENQUEUE(Q,s)
// while Q ≠ {} do
// u = DEQUEUE(Q)
// for each v in Adjacent[u] do
// if color[v] == WHITE then
// color[v] = GRAY (Gray means discovered, but not expanded)
// d[v] = d[u] + 1
// pr[v] = u
// ENQUEUE(Q, v)
// color[u] = BLACK (Black means expanded)
void Graph::bfs()
{
    // for each vertex u in V[G] - [s] do
    for (unsigned i = 0; i < vertices.size(); ++i)
    {
        // color[u] = WHITE (White means undiscovered)
        // d[u] = Infinity (distance from s)
        // pr[u] = NIL (previous vertex)
        vertices.at(i).color = "WHITE";
        vertices.at(i).distance = INT_MAX;
        vertices.at(i).prev = 0;
    }
    // color[s] = GRAY, d[s] = 0, pr[s] = NIL, Q = {}

    vertices.at(0).color = "GRAY";
    vertices.at(0).distance = 0;

    // ENQUEUE(Q,s)
    queue<Vertex*> vertexQueue;
    vertexQueue.push(&vertices.at(0));
    
    // while Q ≠ {} do
    while (!vertexQueue.empty())
    {
        Vertex* frontVertex = vertexQueue.front();
        // u = DEQUEUE(Q)
		vertexQueue.pop();

        // for each v in Adjacent[u] do
        list<pair<int, int> >::iterator i;
        for(i = frontVertex->neighbors.begin(); i != frontVertex->neighbors.end(); ++i)
        {
            // if color[v] == WHITE then
            if (vertices.at(i->first).color == "WHITE") 
            { 
                //Make the distance 0 otherwise garbage number
                vertices.at(i->first).distance = 0;

                // color[v] = GRAY (Gray means discovered, but not expanded)
                // d[v] = d[u] + 1
                // pr[v] = u
                // ENQUEUE(Q, v)
                vertices.at(i->first).color = "GRAY";
                vertices.at(i->first).prev = frontVertex;
				vertices.at(i->first).distance += vertices.at(i->first).prev->distance + 1;
                vertexQueue.push(&vertices.at(i->first));
			}
        }
        // color[u] = BLACK (Black means expanded)
        frontVertex->color = "BLACK";
    }
}
