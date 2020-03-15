#include "board.h"

#include <cmath>

using namespace std;

Board::Board(): prev(nullptr), move(0){}

Board::Board(vector<vector<int> > m_tiles): tiles(m_tiles), prev(nullptr), move(0){
	 board_size = m_tiles.size();
}

string Board::toString(){
	string s = to_string(board_size);
	s.push_back('\n');
	for(int row = 0; row < board_size; row++){
		for(int col = 0; col < board_size; col++){
			s += to_string(tiles[row][col]) + " ";
		}
		s.push_back('\n');
	}
	return s;
}

int Board::dimension(){ // useless in c++
	return board_size;
}

int Board::hamming(){
	int ham_dist = 0;
	for(int row = 0; row < board_size; row++){
		for(int col = 0; col < board_size; col++){
			if(tiles[row][col] != 0 && tiles[row][col] != row * board_size + col + 1){
				ham_dist++;
			}
		}
	}
	return ham_dist;
}

int Board::manhattan(){
	int man_dist = 0;
	for(int row = 0; row < board_size; row++){
		for(int col = 0; col < board_size; col++){
			if(tiles[row][col] != 0){
				int r_row = (tiles[row][col] - 1) / board_size;
				int r_col = (tiles[row][col] - 1) % board_size;
				man_dist += abs(r_row - row) + abs(r_col - col);
			}
		}
	}
	return man_dist;
}

bool Board::isGoal(){
	for(int row = 0; row < board_size; row++){
		for(int col = 0; col < board_size; col++){
			if(tiles[row][col] != row * board_size + col + 1){
				if(row != board_size - 1 || col != board_size - 1) return false;
			}
		}
	}
	return true;
}

vector<Board>* Board::neighbors(){
	vector<Board>* vec = new vector<Board>;
	for(int row = 0; row < board_size; row++){
		for(int col = 0; col < board_size; col++){
			if(tiles[row][col] == 0){
				int dx[4] = {0, 0, -1, 1};
				int dy[4] = {1, -1, 0, 0};
				for(int i = 0; i < 4; i++){
					int x = row + dx[i];
					int y = col + dy[i];
					if(x < 0 || y < 0 || x >= board_size || y >= board_size) continue;
					
					Board n_board = *this;
					n_board.tiles[row][col] = n_board.tiles[x][y];
					n_board.tiles[x][y] = 0;
					vec->push_back(n_board);
				}
				return vec;
			}
		}
	}
	throw "Please enter valid board!!"; // should not be here.
}

Board* Board::twin(){
	Board* n_board = new Board;
	*n_board = *this;

	if(n_board->tiles[0][0] == 0){
		int temp = n_board->tiles[0][1];
		n_board->tiles[0][1] = n_board->tiles[1][1];
		n_board->tiles[1][1] = temp;
	}
	else{
		int temp = n_board->tiles[0][0];
		if(n_board->tiles[0][1] == 0){
			n_board->tiles[0][0] = n_board->tiles[1][0];
			n_board->tiles[1][0] = temp;
		}
		else{
			n_board->tiles[0][0] = n_board->tiles[0][1];
			n_board->tiles[0][1] = temp;
		}
	}
	return n_board;
}
