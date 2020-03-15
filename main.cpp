#include "solver.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv){
	ifstream inFile;
	inFile.open(argv[1]);
	int x;
	size_t n;
	inFile >> n;

	vector<vector<int> > tiles(n);
	for(size_t i = 0; i < n; i++){
		for(size_t j = 0; j < n; j++){
		inFile >> x;
		tiles[i].push_back(x);
		}
	}

	inFile.close();

	try{
		Board initial(tiles);
		Solver solver(initial);

		if(!solver.isSolvable) cout << "No solution possible\n";
		else{
			cout << "Minimum number of moves = " << solver.moves() << "\n";
			vector<Board>* sol = solver.solution();
			for(vector<Board>::reverse_iterator ritr = sol->rbegin(); ritr != sol->rend(); ritr++){
				cout << (*ritr).toString() << "\n";
			}
		}

	} catch(exception &oor){cout << oor.what() << "\n";};

	return 0;
}

