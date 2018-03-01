//must retype namespaces!
using namespace std;
using namespace png;

vector<int> AnalyzeImage (string fileName)
{
	image<rgb_pixel> picture(fileName);
	// Get height and width of the picture of the board that is uploaded
	int height = picture.get_height();
	int width = picture.get_width();
	
	//set up a vector for saving all the pegs
	vector<int> pegs(15,0); 

	//set up 2 vectors for row and col offsets (each separate and the values in relationship to the bottom left corner of the tan board)
	//bottom left of tan board is in position (411,736) in 0th board
	vector<int> coloffset = {373,309,439,242,367,501,169,303,434,557,110,236,367,491,628};
	vector<int> rowoffset = {-524,-406,-406,-297,-297,-290,-186,-186,-186,-186,-71,-76,-73,-72,-61};
	
	//threshold for the tan background and find corner with maxrow and mincol
	//Make some vectors for the board to check the max / min later
	vector<int> boardRows;
	vector<int> boardCols;
	
	//open the image and check all the rows and columns for rgb values that match the board
	for (int r = 0; r < height; ++r){
		for (int c = 0; c < width; ++c){
			//check for these color values    r: [200-230] g: [170-220] b: [140-185]
			int red = picture[r][c][0];
			int green = picture[r][c][1];
			int blue = picture[r][c][2];
			if (red <= 230 && red >= 200 && green <= 220 && green >= 170 && blue <= 185 && blue >= 140){
				boardRows.push_back(r);
				boardCols.push_back(c);
			}
		}
	}
	
	//find bottom left corner of triangular board
	double bottom = *max_element( boardRows.begin() , boardRows.end() );  
	double left = *min_element( boardCols.begin() , boardCols.end() ); 
	
	//use another for loop to go from 0 to 14 for pegs to go through row and col offsets
	for (int ii = 0; ii < 15; ++ii) {
		//check an area 20 by 20 to find the pegs on the board
		for (int r = -10; r < 10; ++r) {
			for (int c = -10; c < 10; ++c){
				//index row and col offsets and add to the corner location
				int row = bottom + rowoffset.at(ii) +r;
				int col = left + coloffset.at(ii) +c;
				//threshold/check for orange at these new locations within the 20x20 area
				//get the color values for orange peg --> r: [125-230]  g: [30-140]  b: [30-115]
				int red = picture[row][col][0];
				int green = picture[row][col][1];
				int blue = picture[row][col][2];
				//in general for the values: red larger than both blue and green, red is twice as large compared to green and red is mostly larger than blue by 100
				//if we find orange change the pegs.at(#) = 1
				if (red > blue + 100 && red > green*2){	
					pegs.at(ii) = 1;
				}
			}
		}
	}
	
	// Give this answer back to C++
	return pegs;
}