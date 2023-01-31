// by Ahmet Bilal Yildiz 
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "randgen.h"
#include "strutils.h"
#include "TempDynStack.h"
#include "TempDynStack.cpp"

using namespace std;

struct cell{ // cell is the struct keeps number of rows x and number of cols y that is used in the stack while generating and finding path
	// rows and cols
	int x;
	int y;
	
	cell(int row = 0, int col = 0)
	: x(row), y(col)  
	{}

};

struct cell_info{ //cell_info struct keeps left, right, up, down and visited walls opennes connection and is used in the vector which keeps stack
	// wals on the right, left, up and down of a cell
	int l, r, u, d;
	// visited
	bool visited;

	cell_info(int left = 1, int right = 1, int up = 1, int down = 1, bool v = false)
		: l(left), r(right), u(up), d(down), visited(v)
	{}

};

// functions
vector<string> wallsCanOpen( cell &current, vector<vector<cell_info>> & my_info_vector, int M, int N); // walsCanOpen checks the proper conditions and the visited statements of neighboring cell for a given cell // it returns a vector of suitable walls(directions) // used in the maze generating process
vector<string> cellsCanGo( cell &current, vector<vector<cell_info>> & my_path_vector, int M, int N); //cellsCanGo checks the proper conditions, opennes of the wall and visited statements of the neighbor cells for a given cell. // it returns a vector of suitable cells(directions) to go
bool all_cells_visited(vector<vector<cell_info>> & my_info_vector, int M, int N); // it checks the all visited statements of all cells of the matrix version of maze and returns true if all cells visited else return false 
void add_new_cell(Stack<cell> &stack, vector<vector<cell_info>> & my_info_vector, int M, int N); // it adds a new cell to the stack and is used in maze generation
void go_new_cell(Stack<cell> &stack, vector<vector<cell_info>> & my_path_vector, int M, int N); // it adds new cell to the stack and is used in finding path process

int main(){
	
	// getting inputs
	int K, M, N;
	cout << "Enter the number of mazes: ";
	cin >> K;

	cout << "Enter the number of rows and columns (M and N): ";
	cin >> M >> N;

	// maze generation (1st faze of the homework)

	vector<vector<vector<cell_info>>> mazes; // it keeps the all mazes

	for(int i = 1; i < K+1; i++){
		// starting with an empty stack
		Stack<cell> mystack;
		cell initial;
		mystack.push(initial);
		cell_info first;
		int total_wall = 0;

		vector<vector<cell_info>> my_info_vector( M, vector<cell_info>(N, first)); // declaring a vector to store all the infos of the cells
		my_info_vector[0][0].visited = true; // updating the first cells info

		while(! all_cells_visited(my_info_vector, M ,N)){
		
			add_new_cell(mystack, my_info_vector, M, N);
		
		}

		// adding newly generated maze to  mazes
		mazes.push_back(my_info_vector);
		
		// forming the filename
		string f_name;
		f_name = "maze_"+ itoa(i)+".txt"; 
		 
		ofstream myfile(f_name); // opening the file

		// writing to the file
		myfile << M << " " << N << endl;
		// in the whole code x represents the row numbers and y represents the col numbers but specificly while writing to the file y:row and x:col to make everything suitable with the hw1 document 
		for(int i = 0; i < M; i ++ ){
			for(int j =0; j < N; j++){
				myfile << "x=" << j << " " << "y=" << i << " " << "l=" << my_info_vector[i][j].l << " " << "r=" << my_info_vector[i][j].r << " " << "u=" << my_info_vector[i][j].u << " " << "d=" << my_info_vector[i][j].d << endl;
			}
		}
	}

	// path finding (2nd faze of the homework)

	// getting 5 more inputs
	int mazeID, entryX, entryY, exitX, exitY;
	cout << "Enter a maze ID between 1 to " << K <<" inclusive to find a path: ";
	cin >> mazeID;

	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> entryX >> entryY;

	cout <<"Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> exitX>> exitY;

	// finding path
	cell entery(entryY, entryX);
	cell exit(exitY, exitX);

	Stack<cell> my_path; // starting with an empty stack
	my_path.push(entery); // adding starting cell to the stack

	vector<vector<cell_info>> my_path_vector = mazes[mazeID-1];
	// updating the visited info of the mazes to false 
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			my_path_vector[i][j].visited = false;
		}
	}
	my_path_vector[entery.x][entery.y].visited = true;

	while( my_path.top().x != exit.x || my_path.top().y != exit.y){ // until find the exit point
		
		go_new_cell(my_path, my_path_vector, M, N);

	}

	// forming the filename
	string pf_name;
	pf_name = "maze_"+ itoa(mazeID)+"_path"+ "_" + itoa(entryX)+ "_" + itoa(entryY) +"_" + itoa(exitX)+ "_" +itoa(exitY)+ ".txt"; 
		 
	ofstream mypath_file(pf_name); // opening the file

	// changing the stack order
	Stack<cell> temp;
	cell temp_cell;
	while(! my_path.isEmpty()){
		temp_cell = my_path.topAndPop();
		temp.push(temp_cell);
	}
	// writing to the file
	while(! temp.isEmpty()){
		temp_cell = temp.topAndPop(); // in the whole code x represents the row numbers and y represents the col numbers but specificly while writing to the file y:row and x:col to make everything suitable with the hw1 document 
		mypath_file << temp_cell.y << " " << temp_cell.x << endl; 
	}

return 0;
}

vector<string> wallsCanOpen( cell &current, vector<vector<cell_info>> & my_info_vector, int M, int N){
	// cehcking all neighbour cells
	vector<string> mylist;

	if(current.y != 0 && ! my_info_vector[current.x][current.y-1].visited){
		mylist.push_back("l"); // there is no cell to visit
	}
	if(current.y != N-1 && !my_info_vector[current.x][current.y+1].visited ){
		mylist.push_back("r"); // there is no cell to visit
	}
	if(current.x != M-1 &&  ! my_info_vector[current.x+1][current.y].visited){
		mylist.push_back("u"); // there is no cell to visit
	}
	if(current.x != 0 &&  ! my_info_vector[current.x-1][current.y].visited){
		mylist.push_back("d"); // there is no cell to visit
	}

	return mylist;

}

vector<string> cellsCanGo( cell &current, vector<vector<cell_info>> & my_path_vector, int M, int N){
	// cehcking all neighbour cells
	vector<string> mylist;

	if(current.y != 0 && ! my_path_vector[current.x][current.y-1].visited && my_path_vector[current.x][current.y].l == 0){
		mylist.push_back("l"); // there is no cell to visit
	}
	if(current.y != N-1 && !my_path_vector[current.x][current.y+1].visited && my_path_vector[current.x][current.y].r == 0){
		mylist.push_back("r"); // there is no cell to visit
	}
	if(current.x != M-1 &&  ! my_path_vector[current.x+1][current.y].visited && my_path_vector[current.x][current.y].u == 0){
		mylist.push_back("u"); // there is no cell to visit
	}
	if(current.x != 0 &&  ! my_path_vector[current.x-1][current.y].visited && my_path_vector[current.x][current.y].d == 0){
		mylist.push_back("d"); // there is no cell to visit
	}

	return mylist;

}

bool all_cells_visited(vector<vector<cell_info>> & my_info_vector, int M, int N){ // it checks the all visited statements of all cells of the matrix version of maze and returns true if all cells visited else return false 

	for(int i = 0; i < M; i ++ ){
		for(int j =0; j < N; j++){
			if(my_info_vector[i][j].visited == false){ // if there is still unvisited cells exist
				return false;
			}
		}
	}
	return true;
}

void add_new_cell(Stack<cell> &stack, vector<vector<cell_info>> & my_info_vector, int M, int N){ // it adds a new cell to the stack and is used in maze generation

	cell current;
	current = stack.top();

	vector<string> unopened = wallsCanOpen(current, my_info_vector, M, N); // forming the vector unvisited that contains unvisited cell directions	

	if( unopened.size() != 0){ // if there is at least  one unvisited cell
		// randomly chosing one unopened wall

		RandGen random;
		int d_index = random.RandInt(0, unopened.size()-1);

		// forming the new cell
		cell new_cell(current.x, current.y);

		// adding this unvisited direction (updating)
		if(unopened[d_index] == "l"){

			my_info_vector[current.x][current.y].l = 0; // updating the current_cell(new cell) acording to chosen direction
			new_cell.y --; // updating the new cell coordinate
			my_info_vector[new_cell.x][new_cell.y].r = 0; // updating the new cell info in the my_info_vector
			my_info_vector[new_cell.x][new_cell.y].visited = true; // new_cell is visited
		}
		else if(unopened[d_index] == "r"){

			my_info_vector[current.x][current.y].r = 0; // updating the current_cell(new cell) acording to chosen direction
			new_cell.y ++; // updating the new cell coordinate
			my_info_vector[new_cell.x][new_cell.y].l = 0; // updating the new cell info in the my_info_vector
			my_info_vector[new_cell.x][new_cell.y].visited = true; // new_cell is visited

		}
		else if(unopened[d_index] == "u"){

			my_info_vector[current.x][current.y].u = 0; // updating the current_cell(new cell) acording to chosen direction
			new_cell.x ++; // updating the new cell coordinate
			my_info_vector[new_cell.x][new_cell.y].d = 0; // updating the new cell info in the my_info_vector
			my_info_vector[new_cell.x][new_cell.y].visited = true; // new_cell is visited

		}
		else if(unopened[d_index] == "d"){

			my_info_vector[current.x][current.y].d = 0; // updating the current_cell(new cell) acording to chosen direction
			new_cell.x--; // updating the new cell coordinate
			my_info_vector[new_cell.x][new_cell.y].u = 0; // updating the new cell info in the my_info_vector
			my_info_vector[new_cell.x][new_cell.y].visited = true; // new_cell is visited

		}
		// adding new cell to the top of the stack
		stack.push(new_cell);
	}
	else{ // if the cell has no unvisited neighbor cell backstrack the stack until finding a cell which has an unvisited neighbor cell
	
		stack.pop();
		add_new_cell(stack, my_info_vector, M, N);
	}
	
}

void go_new_cell(Stack<cell> &stack, vector<vector<cell_info>> & my_path_vector, int M, int N){ // it adds new cell to the stack and is used in finding path process

	cell current;
	current = stack.top();
	vector<string> unopened = cellsCanGo(current, my_path_vector, M, N); // forming the vector unvisited that contains unvisited cell directions	

	if( unopened.size() != 0){ // if there is at least  one unvisited cell
		// randomly chosing one unopened wall

		RandGen random;
		int d_index = random.RandInt(0, unopened.size()-1);

		// forming the new cell
		cell new_cell(current.x, current.y);

		// adding this unvisited direction (updating)
		if(unopened[d_index] == "l"){

			new_cell.y --; // updating the new cell coordinate
			my_path_vector[new_cell.x][new_cell.y].visited = true; // new_cell is visited
		}
		else if(unopened[d_index] == "r"){

			new_cell.y ++; // updating the new cell coordinate
			my_path_vector[new_cell.x][new_cell.y].visited = true; // new_cell is visited

		}
		else if(unopened[d_index] == "u"){

			new_cell.x ++; // updating the new cell coordinate
			my_path_vector[new_cell.x][new_cell.y].visited = true; // new_cell is visited

		}
		else if(unopened[d_index] == "d"){

			new_cell.x--; // updating the new cell coordinate
			my_path_vector[new_cell.x][new_cell.y].visited = true; // new_cell is visited

		}
		// adding new cell to the top of the stack
		stack.push(new_cell);
	}
	else{ // if the cell has no unvisited and openned neighbor cell backstrack the stack until finding a cell which has an unvisited neighbor cell
	
		stack.pop();
		go_new_cell(stack, my_path_vector, M, N);
	}
	
}