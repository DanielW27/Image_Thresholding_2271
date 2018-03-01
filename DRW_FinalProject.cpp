#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include "png.hpp"
#include "AnalyzeImage.h"
#include "AnalyzeJumps.h"
#include "PegAlgorithm.h"

using namespace std;
using namespace png;

int main()
{
	//ask user for which board
	string fileName;
	cout << "Enter the name of image: ";
	cin >> fileName;
	
	//first function
	vector<int> pegs = AnalyzeImage(fileName);
	/*for (int ii = 0; ii < pegs.size(); ++ii){
	   cout << pegs.at(ii) << " ";
	}
	cout << endl; */
	
	//our second function analyzing jumps
	vector<vector<int>> jumps = AnalyzeJumps(pegs);
	/*for (auto row : jumps){
		for (auto c : row){
			cout << c << " ";
		}
		cout << endl;
	} */
	
	//third function
	PegAlgorithm(pegs);
	
	return 0;
}