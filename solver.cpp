#include "solver.h"

#include <queue>
#include <stdexcept>

using namespace std;

Solver::Solver(Board& initial){
	priority_queue<Board*, vector<Board*>, board_compare> b_pq;
	priority_queue<Board*, vector<Board*>, board_compare> t_pq;
	
	Board* current = &initial; // priority board
	Board* t_current = initial.twin();

	current->mnht_dist = current->manhattan();
	t_current->mnht_dist = t_current->manhattan();

	b_pq.push(current);
	t_pq.push(t_current);

	while(1){
		b_pq.pop();
		t_pq.pop();

		if(current->isGoal()){
			isSolvable = true;
			break;
		}
		else if(t_current->isGoal()){
			isSolvable = false;
			break;
		}

		vector<Board>* b_vec = current->neighbors(); // get all neighbors of current board.
		vector<Board>* t_vec = t_current->neighbors();
		
		for(vector<Board>::iterator itr = b_vec->begin(); itr != b_vec->end(); itr++){
			Board* temp = &(*itr);
			temp->move = current->move + 1;
			temp->mnht_dist = temp->manhattan();

			if(!temp->equals(current->prev)){ // if the board is same as previous board of current board, ignore.
				temp->prev = current;
				b_pq.push(temp);
			}
		}

		for(vector<Board>::iterator itr = t_vec->begin(); itr != t_vec->end(); itr++){
			Board* temp = &(*itr);
			temp->move = t_current->move + 1;
			temp->mnht_dist = temp->manhattan();

			if(!temp->equals(t_current->prev)){ // if the board is same as previous board of current board, ignore.
				temp->prev = t_current;
				t_pq.push(temp);
			}
		}

		current = b_pq.top();
		t_current = t_pq.top();
	}

	if(isSolvable == true) Goal = current;	
}

int Solver::moves(){
	return Goal->move;
}

vector<Board>* Solver::solution(){
	vector<Board>* sol = new vector<Board>;
	Board current = *Goal;
	sol->push_back(current);

	while(current.prev != nullptr){
		current = *current.prev;
		sol->push_back(current);
	}
	
	return sol;
}
