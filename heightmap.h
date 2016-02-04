//REFERENCE:
//this code is a modified version from the book "INTRODUCTION TO 3D GAME Programming with DirectX 9.0 by Frank Luna
//code changed and modified by stephan vinent
// Date modified: 1/21/2016


#include<d3dx9.h>
#include<d3d9.h>
#include<vector>
#include<fstream>
#include<cmath>
using namespace std;

class heightmap
{

public:

	void rawFile(string file,int vertCountRow,float scale);
	int mapEntrance(int row,int column,int vertCount);

	vector<int> map;

};
