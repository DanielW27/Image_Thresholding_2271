#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include "png.hpp"

using namespace std;
using namespace png;

int main()
{
	//upload board image
	image<rgb_pixel> pic("Board_00.png");
	//set up a vector for the pegs from the user
	vector<int> pegs(15,-1);
	cout << "Enter if there are pegs or not with 0 being no peg and 1 being 1 peg for the holes in order from 1 to 15: ";
	for (int ii = 0; ii < pegs.size(); ++ ii){
		cin >> pegs.at(ii); //enter vector values with spaces in between each value entered
	}
	
	//set up 2 vectors for row and col hole  (each separate)
	//for 0th board that was uploaded
	vector<int> colspot = {784,720,850,653,778,912,580,714,845,968,521,647,778,902,1039};
	vector<int> rowspot = {212,330,330,439,439,446,550,550,550,550,665,660,663,664,675};
	
	//go through each peg spot and use the values from two vectors above to draw the pegs
	for (int ii = 0; ii < pegs.size(); ++ii) {
		//check if there is a peg or not
		if (pegs.at(ii) == 1){
			//draw a square peg that is white to show the where it is on the board
			for (int r = -20; r < 20; ++r) {
				for (int c = -20; c < 20; ++c){
					//use the coordinates for the holes to draw the peg
					int row = rowspot.at(ii) + r;
					int col = colspot.at(ii) + c;
					pic[row][col] = rgb_pixel(255,255,255);
				}
			}
		}
	}
	//save the picture with a new name
	pic.write("Board_w_Pegs.png");
	return 0;
}