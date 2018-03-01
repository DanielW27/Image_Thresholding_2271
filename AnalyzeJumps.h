//namespaces
using namespace std;
using namespace png;

vector<vector<int>> AnalyzeJumps(vector<int> pegs)
{
	//go thru and look for all possible jumps! each set of 3 is start,hop,end holes in order based on how humans see the holes
	vector<int> list = {1,2,4,1,3,6,2,3,7,2,4,9,3,5,8,3,6,10,4,2,1,4,5,6,4,7,11,4,8,13,5,8,12,5,9,14,6,3,1,6,5,4,6,9,13,6,10,15,7,4,2,7,8,9,8,5,3,8,9,10,9,5,2,9,8,7,10,6,3,10,9,8,11,7,4,11,12,13,12,8,5,12,13,14,13,8,4,13,9,6,13,12,11,13,14,15,14,9,5,14,13,12,15,10,6,15,14,13};
	
	//save the jumps we find within a 2D vector
	vector<vector<int>> jumps;
	
	//use the jump values from master list to compare and find possible jumps based on the board we have
	//subtract one for each hole for how C++ reads it, done below
	for (int ii = 0; ii < 36; ++ii){  
		int start = list.at(3*ii) -1;  
		int hopOver = list.at((3*ii) + 1) -1;
		int fin = list.at((3*ii) + 2) -1;
		//check for all combinations of jumps based on peg locations
		if (pegs.at(start) == 1 && pegs.at(hopOver) == 1 && pegs.at(fin) == 0 ){
			//save the new peg locations in a new vector so that we can change them
			vector<int> copy = pegs;
			copy.at(start) = 0;
			copy.at(hopOver) = 0;
			copy.at(fin) = 1;
			
			//save these jumps we found to the vector we initialized earlier
			vector<int> thisJump = {start,fin};
			thisJump.insert(thisJump.end(),copy.begin(),copy.end());
			jumps.push_back(thisJump);
		}
	}

	return jumps;
}