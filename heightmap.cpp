//REFERENCE:
//this code is a modified version from the book "INTRODUCTION TO 3D GAME Programming with DirectX 9.0 by Frank Luna
//code changed and modified by stephan vinent
// Date modified: 1/21/2016


#include"heightmap.h"

void heightmap::rawFile(string file,int vertCount,float scale)
{

	vector<BYTE> in(vertCount);

	ifstream inFile(file.c_str(),ios_base::binary);


	inFile.read((char*)&in[0],in.size());

	inFile.close();

	map.resize(vertCount);

	for(int i = 0;i < in.size(); i++)
		map[i] = in[i];

	for(int i = 0; i < map.size(); i++)
		map[i] *= scale;

}


int  heightmap::mapEntrance(int row,int column,int vertCountRow)
{
	return map[row * vertCountRow + column];

}
