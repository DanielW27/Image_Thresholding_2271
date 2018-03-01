using namespace std;
using namespace png;

void PegAlgorithm(vector<int> pegs)
{
	//need 2D vector to add jumps and board layout 
	vector<vector<int>> explore = { {-1,-1,-1} }; //no beginning jump
	explore.at(0).insert(explore.at(0).end(),pegs.begin(),pegs.end()); //only the initial board layout
	//first spot: where did we come from --> parent id (beginning board before the jump) (this value corresponds with the row value)
	//second and third spot (vector w 2 spots): jump made from the parent --> start and end of jump
	//fourth spot on: what does board look like after the jump
	
	//set up a loop to explore all possible jumps from row 1 (0th row/id)
	for (int id = 0; id < explore.size(); id += 1) {
		//grab the current board from this id
		vector<int> currentboard(explore.at(id).begin() + 3, explore.at(id).end());
		//find possible jumps based on this board using part 2
		vector<vector<int>> jumps = AnalyzeJumps(currentboard);
		//add these jumps to the end of the explore list
		for (int ii = 0; ii < jumps.size(); ++ii) {
			int exploreEnd = explore.size();
			vector<int> pushBack = {id};
			explore.push_back(pushBack);
			explore.at(exploreEnd).insert(explore.at(exploreEnd).begin() +1, jumps.at(ii).begin(), jumps.at(ii).end());
		}
	}
	
	//use another loop to backtrack how we got to the solution
	int counter = 0;
	for (int id = 0; id < explore.size(); id += 1){
		//check for winners
		//accumulate the last 15 values in explore vector in order to see if it's one or more
		int result = accumulate(explore.at(id).begin() + 3, explore.at(id).end(),0);
		if (result == 1){
			counter ++;
			vector<int> win; //save and spit out the values
			int parentid = explore.at(id).at(0);
			
			win.push_back(explore.at(id).at(2));
			win.push_back(explore.at(id).at(1));
			while (parentid > 0) {
				//pushback in order of end value then start value 
				win.push_back(explore.at(parentid).at(2));
				win.push_back(explore.at(parentid).at(1));
				//the parentid we find below will go backwards on its own since it is reading the id value we saved in the 0th column position for each row
				parentid = explore.at(parentid).at(0); 
			}
			//reverse the vector in order to easily output the jumps needed
			reverse(win.begin(),win.end());
			
			cout << "Option " << counter << ":" << endl;
			//make for loop to cout the values from the vector and advance by 2 since we need to output two values at a time
			//cout all jumps to make to win the game
			for(int ii = 0; ii < win.size(); ii += 2){ 
				cout << "Jump from " << to_string(win.at(ii) +1) << " to " << to_string(win.at(ii+1) +1) <<endl;
			}
		}
	}
	
	//no return needed
	//couts for all jumps to make to win the game
}