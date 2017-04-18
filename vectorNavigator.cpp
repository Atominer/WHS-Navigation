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
#include <vector>

//map of teachers to room #s
//map of subjects to teachers
//three 2D arrays of room objects (physical map of school)
//room objects contain: traffic value, available directions, name
//classroom extends room; contains: teacherName, RoomNumber, Subject
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



//TO DO
//
//make output readable
//
//add functionality to search rooms by teacher and subject
//
//add functionality to navigate within a connection to find a room
//




class Connection{
	private:
		std::string direction, landmark;
		int weight;
		std::vector<int> roomnums;
	public:
		Connection(std::string dir, int weight, std::string landmark, std::vector<int> roomnums){
			direction = dir;
			this->weight = weight;
			this->landmark = landmark;
			for (int i : roomnums){
				this->roomnums.push_back(i);
			}
		}
		Connection(){
		}

		std::string getDir(){
			return direction;
		}

		std::string getLandmark(){
			return landmark;
		}

		int  getRoomNums(int n){
			return roomnums[n];
		}

		bool findRoom(int n){
			for (int r : roomnums){
				if(r==n)
					return true;
			}

			return false;
		}

		int getWeight(){
			return weight;
		}
};


int main(){
	int start, end, navPointer;
	std::vector<int> nodes;
	std::vector<bool> visitedNodes;
	//Connection *weightGraph[10][10];
	//std::vector<std::vector<Connection*>> weightGraph;
	std::map<std::pair<int,int>,Connection*> weightMap;

	//CONTINUE TRANSFERING TO VECTORS FROM THIS POINT


	std::cout << "Enter room number to start from : ";
	std::cin >> start;
	std::cout << "Enter room number to navigate to : ";
	std::cin >> end;

	std::cout << "MAP CREATION START" << std::endl;

	
	weightMap[std::make_pair(0,1)] = weightMap[std::make_pair(1,0)] = new Connection("Go through hallway 3", 3, "Water fountain",{123,124,125,126,127,128,129});

	std::cout << "FIRST POINT MADE" << std::endl;

	weightMap[std::make_pair(0,2)] = weightMap[std::make_pair(2,0)] = new Connection("Go through hallway 1", 1, "iidx machine", {100,101,102,103,104,105,106,107,108,109});
	
	weightMap[std::make_pair(1,3)] = weightMap[std::make_pair(3,1)] = new Connection("Go through the sketchy alley", 2, "janitor's closet", {110});
	
	weightMap[std::make_pair(2,4)] = weightMap[std::make_pair(4,2)] = new Connection("Go through the main hallway", 3, "vending machine", {130,131,132,133,134,135,136,137,138,139});
		
	weightMap[std::make_pair(3,4)] = weightMap[std::make_pair(4,3)] = new Connection("Go through long hallway", 4, "bathroom", {152,153,154,155,156,157,158,159,159,160,161,162});
	
	weightMap[std::make_pair(3,5)] = weightMap[std::make_pair(5,3)] = new Connection("Go through very long hallway", 5, "computer lab", {140,141,142,143,144,145,146,147,148,149,150,151});
	
	weightMap[std::make_pair(4,6)] = weightMap[std::make_pair(6,4)] = new Connection("Go through hallway", 3, "physics lab" , {111,112,113,114,115,116,117,118,119,120,121,122});
	
	weightMap[std::make_pair(5,6)] = weightMap[std::make_pair(6,5)] = new Connection("Go through smol hallway", 1, "stats classroom", {170,171,172,173});
	
	weightMap[std::make_pair(5,9)] = weightMap[std::make_pair(9,5)] = new Connection("Go through hallway", 3, "mainland china", {180,181,182,183,184,185,186,187,188,189,190});
	
	weightMap[std::make_pair(6,7)] = weightMap[std::make_pair(7,6)] = new Connection("Cross the outside to the arts building",1,"gazeeeeeebo", {199});
	
	weightMap[std::make_pair(7,8)] = weightMap[std::make_pair(8,7)] = new Connection("Traverse the staircase", 2, "stairs", {200,201,202,204,205,231,213,240,206,208,207,209});

	//REMEMBER TO DELETE THESE LATER TO DEALLOCATE THE MEMORY
	
	std::cout << "MAP CREATION COMPLETE" << std::endl;

	std::cout << "initializing node array" << std::endl;

	//LOOP THROUGH MAP TO FIND LARGEST NODE INDEX
	//SET ALL NODE VALUES TO int_MAX
	
	int numNodes = 0;

	for(std::map<std::pair<int,int>, Connection*>::iterator it = weightMap.begin(); it != weightMap.end(); ++it){
		if(it->first.first > numNodes)
			numNodes= it->first.first;
		if(it->first.second > numNodes)
			numNodes = it->first.second;
	}

	for(int i=0; i <= numNodes; i++){
		nodes.push_back(INT_MAX);
		visitedNodes.push_back(false);
	}
	
	bool startFound = false;
	bool endFound = false;

	for(std::map<std::pair<int,int>, Connection*>::iterator it = weightMap.begin(); it != weightMap.end(); ++it){

		std::cout << "LOCATING ROOM INDICES" << std::endl;

		if (it->second->findRoom(start) && !startFound){
			start = it->first.first;
			navPointer = start;
			nodes[start] = 0;

			startFound = true;
		}

		if(it->second->findRoom(end) && !endFound){
			end = it->first.first;
				
			endFound = true;
		}

		if(startFound && endFound)
			break;
	}
		
	std::cout << "was start found? : " << startFound << std::endl << "was end found? : " << endFound << std::endl;

	while(true){

		for (int i=0; i < nodes.size(); i++){

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

		for (int i=0; i < nodes.size(); i++){

			std::cout << "current address is (" << navPointer << ", " << i << ") ";
			
			if (weightMap.find(std::make_pair(navPointer, i)) == weightMap.end() || visitedNodes[i] || nodes[i] < nodes[navPointer] + weightMap[std::make_pair(navPointer, i)]->getWeight()){
				std::cout << "continuing" << std::endl;
				continue;
			}

			nodes[i] = nodes[navPointer] + weightMap[std::make_pair(navPointer,i)]->getWeight();

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
		for(int i=0; i < nodes.size(); i++){
			if(weightMap.find(std::make_pair(pathPointer,i)) != weightMap.end()){
				if(nodes[pathPointer]-weightMap[std::make_pair(pathPointer,i)]->getWeight()==nodes[i]){
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

	return 0;
}


