#ifndef _BoaRD__
#define _BoaRD__

#include <typeinfo>
#include <string>
#include <vector>

using namespace std;

class Board{	
protected:
	int board_size;
	vector<vector<int> > tiles; 

public:
	Board* prev;
	int move;
	int mnht_dist;

    Board();
	Board(vector<vector<int> > m_tiles);

	string toString();

	int dimension();

	int hamming();

	int manhattan();

	bool isGoal();

	template <typename Object>
	bool equals(Object *y){
		if(y == this) return true;
		if(y == nullptr) return false;
		if(typeid(y) != typeid(this)) return false;
		if(y->board_size != board_size) return false;

		for(int i = 0; i < board_size; i++){
			for(int j = 0; j < board_size; j++){
				if(tiles[i][j] != y->tiles[i][j]) return false;
			}
		}

		return true;
	};

	vector<Board>* neighbors();

	Board* twin();

	class board_compare{
    public:
        bool operator()(Board* b1, Board* b2){
            int lp = b1->mnht_dist + b1->move;
            int rp = b2->mnht_dist + b2->move;
            if(lp == rp) return b1->hamming() > b2->hamming();
            return lp > rp;
        }
	};

	bool operator!=(Board* b1){
		return this != b1;
	}
};

#endif
