#include"interface.h"


void Interface::XfilesColor(IDirect3DDevice9* dev,float color)
{

	
	mesh Meshss;
	
	Meshss.XfilesGraphics(dev,color);
}

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
//int shipDirectionalFlag = 0;
void Interface::movement(IDirect3DDevice9* dev,float dt,terrain t,camera & camcorder,int & shipDirectionalFlag,bool autoMovement)
{

	D3DXMATRIX views;
	camcorder.getView(&views);

	dev->SetTransform(D3DTS_VIEW,&views);
	//camera camcorder;
	int keypadDirect[4] = {UP,DOWN,LEFT,RIGHT};
	static float y = 0;
	
	//int shipDirectionalFlag = 0;
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale,10/6,10/6,10/6);

	D3DXMATRIX T;
	//D3DXMatrixTranslation(&T,0,70,250);

	D3DXMatrixTranslation(&T,camcorder.position.x,camcorder.position.y,camcorder.position.z+ 48);
	y += dt;

	D3DXMATRIX rotY;
	D3DXMatrixRotationY(&rotY,122.5);


	//THESE ARE USE TO TURN THE SHIP IN DIFFERENT DIRECTIONS	
	if(shipDirectionalFlag == DOWN)
	{
		D3DXMatrixRotationY(&rotY,0);
		D3DXMatrixTranslation(&T,camcorder.position.x,camcorder.position.y,camcorder.position.z+ 40);
	}

	if(shipDirectionalFlag == LEFT)
		D3DXMatrixRotationY(&rotY,221.5);

	if(shipDirectionalFlag == RIGHT)
		D3DXMatrixRotationY(&rotY,80);

	if(y >= 6.28f)
		y = 0;

	D3DXMATRIX world = rotY *scale* T;

	dev->SetTransform(D3DTS_WORLD,&world);

	if(autoMovement == true)
	{
		camcorder.forward(100.0f * dt+.05+.02);
		shipDirectionalFlag = UP;
	}
	else
	if(camcorder.keyAction(VK_UP) )
	{
		camcorder.forward(300.0f * dt+.25+.02);
		//camcorder.forward(100.0f * dt+.05+.02);
		shipDirectionalFlag = UP;
	}
	
	
	
	if(camcorder.keyAction(VK_DOWN) )
	{
		camcorder.forward(-300.0f * dt-.25+.02);
		//camcorder.forward(-100.0f * dt-.05+.02);
		shipDirectionalFlag = DOWN;
	}

	if(camcorder.keyAction(VK_LEFT) )
	{
		camcorder.strafe(-3.0f*dt-.39);
		//camcorder.strafe(-1.0f*dt-.09);
		//camcorder.angleUp(-1.0f*dt-.009);
		shipDirectionalFlag = LEFT;

	}

	if(camcorder.keyAction(VK_RIGHT) )
	{
		camcorder.strafe(3.0F*dt+.39);
		//camcorder.strafe(1.0F*dt+.09);
		//camcorder.angleUp(1.0F*dt+.009);
		shipDirectionalFlag = RIGHT;
	}


	if(camcorder.keyAction(VK_ESCAPE) )
		exit(0);
	
	D3DXVECTOR3 position;
	camcorder.getpos(&position);
	float h = t.getHeight(position.x,position.z,64,64,10);
	position.y = h + 25;
	camcorder.setpos(&position);
}



void Interface::ringLocation(IDirect3DDevice9* dev,ID3DXMesh* rings,bool active,int shape,float speed,float scale,char rotateAxis,float x, float y, float z)
{
	if(active == true)
	{
	UserSpeed += speed;
	TempSpeed += speed/2;
	if(TempSpeed > 4)
		TempSpeed = 0;
	
	//circle
	if(shape == 1)
	D3DXCreateTorus(dev,2,5,7,10,&rings,0);
//Triangle
	else if(shape == 2)
	D3DXCreateTorus(dev,2,5,5,3,&rings,0);
	//Diamond
	else if(shape == 3)
	D3DXCreateTorus(dev,2,5,5,4,&rings,0);
	//Dynamic
	else if(shape == 4)
	D3DXCreateTorus(dev,2,5,4,TempSpeed+3,&rings,0);
	else
		D3DXCreateTorus(dev,2,5,7,10,&rings,0);
	D3DXMATRIX scale1;
	D3DXMatrixScaling(&scale1,scale,scale,scale);
	D3DXMATRIX rotation;
	if(rotateAxis == 'x' || rotateAxis == 'X')
		D3DXMatrixRotationX(&rotation,UserSpeed);
	else if(rotateAxis == 'y' || rotateAxis == 'Y')
	D3DXMatrixRotationY(&rotation,UserSpeed);
	else if(rotateAxis == 'z' || rotateAxis == 'Z')
	D3DXMatrixRotationZ(&rotation,UserSpeed);
	else
		D3DXMatrixRotationY(&rotation,0);
	D3DXMATRIX T1;
	D3DXMatrixTranslation(&T1,x,y,z);

	D3DXMATRIX world1 = rotation * scale1* T1;
	dev->SetTransform(D3DTS_WORLD,&world1);
	
	rings->DrawSubset(0);

	}

}


void Interface::arbitraryEffects(IDirect3DDevice9* dev,vector<D3DMATERIAL9>& material01,vector<IDirect3DTexture9*> texture01,ID3DXMesh* model01,bool active,int arbitraryNum)
{
	if(active == true)
	{
	//first effect
	if(arbitraryNum == 1)
	for(int i = 0;i < material01.size(); i++)
	{
		model01->DrawSubset(i);
		//dev->SetMaterial(&material01[i]);
		dev->SetMaterial(&material01[24]);
		dev->SetTexture(0,texture01[4]);
		
		
	}
	//second effect
	else if(arbitraryNum == 2)
	for(int i = 0;i < material01.size(); i++)
	{
		model01->DrawSubset(i);
		dev->SetMaterial(&material01[9]);
		dev->SetTexture(0,texture01[4]);
		
		
	}
	//third effect
	else if(arbitraryNum == 3)
	for(int i = 0;i < material01.size()*13; i++)
	{
		model01->DrawSubset(i);
		dev->SetMaterial(&material01[i]);
		//dev->SetMaterial(&material01[24]);
		//dev->SetTexture(0,texture01[4]);
		
		
	}

	else if(arbitraryNum == 4)
	for(int i = 0;i < material01.size(); i++)
	{
		
		model01->DrawSubset(i);
		
		dev->SetTexture(0,texture01[1]);
		dev->SetMaterial(&material01[20]);
		
	}


	else
	for(int i = 0;i < material01.size(); i++)
	{
		
		model01->DrawSubset(0);
		
		dev->SetTexture(0,texture01[0]);
		dev->SetMaterial(&material01[0]);
		
	}

	}


	//model01->Release();

}


void Interface::terrainMode(IDirect3DDevice9* dev,terrain & t,bool active,bool wireframeFlag)
{

	if(active == true)
	{
	D3DXMATRIX id;
	D3DXMatrixIdentity(&id);

		
	t.terrainDraw(dev,&id,false,64,64,wireframeFlag);
	}
}


void Interface::terrainColor(IDirect3DDevice9* dev,terrain & t,int color)
{
	t.texture(dev,64,64,0.8,color);
}


void Interface::gameStop(float & speed,bool stopSoon)
{
	if(stopSoon == true)
	{
	speed += .016666666666666667;
	if(speed > 100)
		exit(0);
	}

}
