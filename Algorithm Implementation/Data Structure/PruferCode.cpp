/**
  Tree to Prufer Code
  Works for both 0 and 1 indexed node numbering
  Complexity: O(VlogV)
  Source: Forthright48's blog
 **/

vector<int> treeToPruferCode (int nodes, vector<pair<int,int>> &edges) {
    unordered_set<int> neighbors[nodes+1]; // For each node, who is it's neighbor?

    for( int i = 0; i < edges.size(); i++ ) {
        pair<int,int> edge = edges[i];
        int u = edges[i].first; int v = edges[i].second;
        neighbors[u].insert(v);
        neighbors[v].insert(u);
    }

    priority_queue<int> leaves;
    for ( int i = 0; i <= nodes; i++ ) {
        if (neighbors[i].size() == 1 ) {
            leaves.push(-i); // Negating since we need min heap
        }
    }
    vector<int> pruferCode;
    int need = nodes - 2;
    while(need--) {
        int leaf = -leaves.top(); leaves.pop();
        int neighborOfLeaf = *(neighbors[leaf].begin());
        pruferCode.push_back(neighborOfLeaf);
        // Remove the leaf
        neighbors[neighborOfLeaf].erase(leaf);
        // The neighbor can become a new leaf
        if(neighbors[neighborOfLeaf].size() == 1) {
            leaves.push(-neighborOfLeaf);
        }
    }
    return pruferCode;
}

/*
  Prufer Code to Tree
  Complexity: O(VlogV)
 */

vector<pair<int,int>> pruferCodeToTree(vector<int> &pruferCode) {
    // Stores number count of nodes in the prufer code
    unordered_map<int,int> nodeCount;

    // Set of integers absent in prufer code. They are the leaves
    set<int> leaves;

    int len = pruferCode.size();
    int node = len + 2;

    // Count frequency of nodes
    for ( int i = 0; i < len; i++ ) {
        int t = pruferCode[i];
        nodeCount[t]++;
    }

    // Find the absent nodes
    for ( int i = 1; i <= node; i++ ) {
        if ( nodeCount.find ( i ) == nodeCount.end() ) leaves.insert ( i );
    }

    vector<pair<int,int>> edges;
    /*Connect Edges*/
    for ( int i = 0; i < len; i++ ){
        int a = prufer[i]; // First node

        //Find the smallest number which is not present in prufer code now
        int b = *leaves.begin(); // the leaf

        edges.push_back({a,b}); // Edge of the tree

        leaves.erase ( b ); // Remove from absent list
        nodeCount[a]--; // Remove from prufer code
        if ( nodeCount[a] == 0 ) leaves.insert ( a ); // If a becomes absent
    }

    // The final edge
    edges.push_back({*leaves.begin(), *leaves.rbegin()});
    return edges;
}
