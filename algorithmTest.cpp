#include <iostream>
#include <cmath>
#include <math.h>
#include <string>
#include <cstring>
#include <limits>
#include <cfloat>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <set>
#include <map>
#include <utility>
#include <stack>


//map of teachers to room #s
//map of subjects to teachers
//three 2D arrays of room objects (physical map of school)
//room objects contain: traffic value, available directions, name
//classroom extends room; contains: teacherName, RoomNumber, Subject
//stairs objects (extends room)
//
//path object contains: list of instructions to get to the destination, toString that prints the instructions as readable by a human
//
//pair nodes with distances
//update distance if find a node we've already been to
//set of nodes
//
//navigated graph contains intersections
//second smaller navigation to navigate from closest intersection to destination
//
//

class Connection{
	private:
		std::string direction, landmark;
		int weight, roomnums[12];
	public:
		Connection(std::string dir, int weight, std::string landmark, int roomnums[12]){
			direction = dir;
			this->weight = weight;
			this->landmark = landmark;
			std::memmove(roomnums, this->roomnums, 12);
		}
		Connection(){
		}

		std::string getDir(){
			return direction;
		}

		std::string getLandmark(){
			return landmark;
		}

		int getRoomNums(){
			return *roomnums;
		}

		int getWeight(){
			return weight;
		}
};


int main(){
	int nodes[10], start, end, navPointer, dest;
	bool visitedNodes[10];
	Connection *weightGraph[10][10];


	std::cout << "Enter point to start from : ";
	std::cin >> start;
	std::cout << "Enter room number to navigate to : ";
	std::cin >> dest;

	for (int i=0; i < 10; i++){

		nodes[i] = INT_MAX;

		visitedNodes[i] = false;

		for(int j=0; j < 10; j++){
			
			weightGraph[i][j] = NULL;
	
		}
	}

	nodes[start] = 0;
	navPointer=start;

	std::cout << "MAP CREATION START" << std::endl;

	//(int*)(const int[12]){123,124,125,126,127,128,129,-1,-1,-1,-1,-1}
	//
	int fountRooms[] = {123,124,125,126,127,128,129,-1,-1,-1,-1,-1};

	weightGraph[0][1] = weightGraph[1][0] = new Connection("Go through hallway 3", 3, "Water fountain",fountRooms);

	std::cout << "FIRST POINT MADE" << std::endl;

	int iidxRooms[] = {100,101,102,103,104,105,106,107,108,109,-1,-1};

	weightGraph[0][2] = weightGraph[2][0] = new Connection("Go through hallway 1", 1, "iidx machine", iidxRooms);
	
	int janitorRooms[] = {110,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	
	weightGraph[1][3] = weightGraph[3][1] = new Connection("Go through the sketchy alley", 2, "janitor's closet", janitorRooms);
	
	int vendingRooms[] = {130,131,132,133,134,135,136,137,138,139,-1,-1};
	
	weightGraph[2][4] = weightGraph[4][2] = new Connection("Go through the main hallway", 3, "vending machine", vendingRooms);
		
	int bathRooms[] = {152,153,154,155,156,157,158,159,159,160,161,162};
	
	weightGraph[3][4] = weightGraph[4][3] = new Connection("Go through long hallway", 4, "bathroom", bathRooms);
	
	int compRooms[] = {140,141,142,143,144,145,146,147,148,149,150,151};
	
	weightGraph[3][5] = weightGraph[5][3] = new Connection("Go through very long hallway", 5, "computer lab", compRooms);
	
	int physicsRooms[] = {111,112,113,114,115,116,117,118,119,120,121,122};
	
	weightGraph[4][6] = weightGraph[6][4] = new Connection("Go through hallway", 3, "physics lab" , physicsRooms);
	
	int statsRooms[] = {170,171,172,173,-1,-1,-1,-1,-1,-1,-1,-1};
	
	weightGraph[5][6] = weightGraph[6][5] = new Connection("Go through smol hallway", 1, "stats classroom",statsRooms );
	
	int chinaRooms[] = {180,181,182,183,184,185,186,187,188,189,190,-1};
	
	weightGraph[5][9] = weightGraph[9][5] = new Connection("Go through hallway", 3, "mainland china", chinaRooms);
	
	int zeeboRooms[] = {199,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	
	weightGraph[6][7] = weightGraph[7][6] = new Connection("Cross the outside to the arts building",1,"gazeeeeeebo", zeeboRooms);
	
	int stairRooms[] = {200,201,202,204,205,231,213,240,206,208,207,209};
	
	weightGraph[7][8] = weightGraph[8][7] = new Connection("Traverse the staircase", 2, "stairs", stairRooms);

	//REMEMBER TO DELETE THESE LATER TO DEALLOCATE THE MEMORY
	//
	std::cout << "MAP CREATION COMPLETE" << std::endl;

	//ADD THE THING TO SEARCH FOR THE ROOM NUMBER AND SET END EQUAL TO THE INDEX

	while(true){

		for (int i=0; i<10; i++){

			std::cout << "checking to update navPointer; i = " << i << std::endl;


			std::cout << navPointer << std::endl;
			std::cout << end << std::endl;
			std::cout << nodes[i] << std::endl;
			std::cout << nodes[navPointer] << std::endl;
			std::cout << visitedNodes[i] << std::endl;

			if((nodes[i] < nodes[navPointer] && !visitedNodes[i])){
				navPointer=i;

				std::cout << "updating navpointer to : " << i << std::endl;

			}
		}

		std::cout << "navP = " << navPointer << std::endl;

		if(navPointer==end){
			break;
		}

		for (int i=0; i<10; i++){

			std::cout << "current address is (" << navPointer << ", " << i << ") ";
			std::cout << weightGraph[navPointer][i] << std::endl;

			if (weightGraph[navPointer][i]==NULL || visitedNodes[i] || nodes[i] < nodes[navPointer] + weightGraph[navPointer][i]->getWeight()){
				std::cout << "continuing" << std::endl;
				continue;
			}

			nodes[i] = nodes[navPointer] + weightGraph[navPointer][i]->getWeight();

			std::cout << "relaxing point : (" << navPointer;
			std::cout << ", " << i;
			std::cout << ")" << std::endl;
			std::cout << "new distance to " << i << " = " << nodes[i] << std::endl;
		}

		std::cout << "LOOP COMPLETE" << std::endl;

		visitedNodes[navPointer]=true;
		navPointer = end;

		std::cout << "navPointer RESET" << std::endl;
		
	}

	std::cout << "Distance to destination : " << nodes[end] << std::endl;

	std::stack<int> path;

	path.push(end);

	int pathPointer = end;

	while (pathPointer != start){
		for(int i=0; i < 10; i++){
			if(weightGraph[pathPointer][i]!=NULL){
				if(nodes[pathPointer]-weightGraph[pathPointer][i]->getWeight()==nodes[i]){
					pathPointer=i;
					path.push(pathPointer);
					std::cout << "adding " << pathPointer << " to path" << std::endl;
					break;
				}
			}
		}
	}

	std::cout << "the path is: ";
	while(!path.empty()){
		if(path.top()==end)
			std::cout << path.top();
		else
			std::cout << path.top() << " to ";
		path.pop();
	}
	std::cout << "; END OF PATH" << std::endl;
}


