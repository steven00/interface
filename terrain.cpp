//REFERENCE:
//this code is a modified version from the book "INTRODUCTION TO 3D GAME Programming with DirectX 9.0 by Frank Luna
//code changed and modified by stephan vinent
// Date modified: 1/21/2016


#include"terrain.h"
heightmap hm;
HRESULT result = 0;
terrain::terrain(IDirect3DDevice9* dev,string file,int verRowCount,int verColCount,int grid,float scale)
{


	hm.rawFile(file,verRowCount*verColCount,scale);
	terrainVertIndices( dev,verRowCount*verColCount,(verRowCount-1)*grid,(verColCount-1)*grid, verRowCount, verColCount, grid);
}



void terrain::terrainVertIndices(IDirect3DDevice9* dev,int verts,int width,int depth,int verRowCount,int verColCount,int grid)
{

	dev->CreateVertexBuffer(verts*sizeof(vertex),D3DUSAGE_WRITEONLY,D3DFVF_XYZ|D3DFVF_TEX1,D3DPOOL_MANAGED,&vb,0);

	int xi = -width * 0.5;
	int zi = depth * 0.5;

	int xf = width * 0.5;
	int zf = -depth * 0.5;

	float uTex = 1/ (float)(verRowCount-1);
	float vTex = 1/(float)(verColCount-1);

	vertex* v = 0;
	vb->Lock(0,0,(void**)&v,0);

	int i = 0;

	for(int z = zi; z >= zf; z -= grid)
	{
		int j = 0;
		for(int x = xi; x <= xf; x += grid)
		{

			int index = i * verRowCount + j;
			v[index] = vertex((float)x,(float)hm.map[index],
				(float)z,(float)j*uTex,(float)i * vTex);

			j++;
		}
		i++;
	}
	vb->Unlock();

	int tri = ((verRowCount-1) * (verColCount-1) * 2);
	dev->CreateIndexBuffer(tri * 3 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&ib,0);

	WORD* indice = 0;
	ib->Lock(0,0,(void**)&indice,0);

	int startIndice = 0;

	for(int i = 0;i < (verColCount - 1); i++)
	{
		for(int j = 0; j < (verRowCount -1); j++)
		{
			indice[startIndice] =  i * verRowCount + j;
			indice[startIndice + 1] =  i * verRowCount + j+1;
			indice[startIndice + 2] =  (i+ 1) * verRowCount + j;

			indice[startIndice + 3] =  (i+ 1) * verRowCount + j;
			indice[startIndice + 4] =  i * verRowCount + j + 1;
			indice[startIndice + 5] =  (i+ 1) * verRowCount + j+ 1;

			startIndice += 6;
		}

	}

	ib->Unlock();

}


void terrain::texture(IDirect3DDevice9* dev,int verRowCount,int verColCount,float scale,int colorPick)
{
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(&projection,D3DX_PI /2,(float)640/(float)480,1,1000);
	dev->SetTransform(D3DTS_PROJECTION,&projection);

	D3DXVECTOR3 LightDir(0,1,0);

	int texelWid = verRowCount - 1;
	int texelheight = verColCount - 1;

	D3DXCreateTexture(dev,texelWid,texelheight,0,0,D3DFMT_X8R8G8B8,D3DPOOL_MANAGED,&tex);


	D3DSURFACE_DESC surface;
	tex->GetLevelDesc(0,&surface);

	

	D3DLOCKED_RECT lockRect;
	D3DXCOLOR color;
	tex->LockRect(0,&lockRect,0,0);
	DWORD* texValue = (DWORD*)lockRect.pBits;
	for(int i = 0;i < texelheight; i++)
	{

		for(int j = 0;j < texelWid; j++)
		{
		float h = (float)hm.mapEntrance(i,j,verColCount)/scale;

		if( h < 42.5)
		{
			/*if(colorPick == 1)
			color = D3DCOLOR_XRGB(255,249,57);
			if(colorPick == 2)*/
			color = D3DCOLOR_XRGB(157,145,113);
		}

		else
		{
			//color = D3DCOLOR_XRGB(154,1,22);
			if(colorPick == 1)
				color = D3DCOLOR_XRGB(154,1,22);

			if(colorPick == 2)
		color = D3DCOLOR_XRGB(100,0,211);

			if(colorPick == 3)
		color = D3DCOLOR_XRGB(0,110,211);
			if(colorPick == 4)
		color = D3DCOLOR_XRGB(255,110,211);

			if(colorPick == 5)
		color = D3DCOLOR_XRGB(255,201,15);

			if(colorPick == 6)
		color = D3DCOLOR_XRGB(14,95,32);


		}


		texValue[i*lockRect.Pitch/4 +j] = (D3DCOLOR)color;
		}


	}

	tex->UnlockRect(0);


	D3DXFilterTexture(tex,0,0,D3DX_DEFAULT);


	dev->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	dev->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	dev->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);

	D3DXMatrixPerspectiveFovLH(&projection,D3DX_PI*0.25,(float)640/(float)480,1,1000);
	dev->SetTransform(D3DTS_PROJECTION,&projection);
}

//THIS WILL GET THE LENGTH OF THE HEIGHT OF THE TERRAIN
float terrain::getHeight(float xAxis,float zAxis,int verRowCount,int verColCount,int grid)
{
	xAxis = ((float)((verRowCount -1 )*grid))/2 + xAxis;
	zAxis = ((float)((verColCount - 1)*grid))/2 + zAxis;

	xAxis /= (float)grid;
	zAxis /= (float)grid;


	float column = floorf(xAxis);
	float row = floorf(zAxis);

	float A = hm.mapEntrance(row,column,verRowCount);
	float B = hm.mapEntrance(row,column+1,verRowCount);
	float C = hm.mapEntrance(row+1,column,verRowCount);
	float D = hm.mapEntrance(row+1,column+1,verRowCount);


	float dx = xAxis - column;
	float dz = zAxis - row;

	float height = 0;

		float uy = B - A;
		float vy = C - A;


		height = A + interpolation(0,uy,dx) + interpolation(0,vy,dz);


	

		return height;


}

void terrain::terrainDraw(IDirect3DDevice9* dev,D3DXMATRIX* W,bool tri,int verRowCount,int verColCount,bool wireFrame)
{
	dev->SetTransform(D3DTS_WORLD,W);
	dev->SetStreamSource(0,vb,0,sizeof(vertex));
	dev->SetFVF(D3DFVF_XYZ|D3DFVF_TEX1);
	dev->SetIndices(ib);

	dev->SetTexture(0,tex);

	dev->SetRenderState(D3DRS_LIGHTING,false);


	//dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,(verRowCount *verColCount),0,(((verRowCount-1) *(verColCount-1))*2));

	dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,4096,0,7938);

	dev->SetRenderState(D3DRS_LIGHTING,true);

	if(wireFrame == true)
	dev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

}
