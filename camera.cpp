#include"camera.h"

//REFERENCE:
//this code is a modified version from the book "INTRODUCTION TO 3D GAME Programming with DirectX 9.0 by Frank Luna
//code changed and modified by stephan vinent
// Date modified: 1/21/2016
camera::camera()
{
	position = D3DXVECTOR3(0,0,0);
	right = D3DXVECTOR3(1,0,0);
	up = D3DXVECTOR3(0,1,0);
	look = D3DXVECTOR3(0,0,1);
}
void camera::forward(float a)
{

	//THE PLAYER WILL MOVE WITH THE UP ARROW DIRECTION
	position += D3DXVECTOR3(look.x,0,look.z) * a;

	position += up * a;

}


void camera::strafe(float a)
{

	//THIS IS FOR LEFT AND RIGHT MOVEMENT
	position += D3DXVECTOR3(right.x,0,right.z) * a;

	position += right * a;

}



void camera::y(float a)
{
	//THIS IS TO INCREASE OF DECREASE THE Y AXIS
	position += up * a;

}


void camera::angleUp(float a)
{
	
	//THIS IS FOR TURNING
	D3DXMATRIX rot;
	D3DXMatrixRotationAxis(&rot,&right,a);

	D3DXMatrixRotationAxis(&rot,&up,a);

	D3DXVec3TransformCoord(&right,&right,&rot);
	D3DXVec3TransformCoord(&look,&look,&rot);

}


void camera::angleRight(float a)
{
	
	D3DXMATRIX rot;
	D3DXMatrixRotationAxis(&rot,&right,a);

	D3DXVec3TransformCoord(&up,&up,&rot);
	D3DXVec3TransformCoord(&look,&look,&rot);

}


void camera::getpos(D3DXVECTOR3* positions)
{
	*positions = position;
}


void camera::setpos(D3DXVECTOR3* positions)
{
	 position = *positions;
}



void camera::getView(D3DXMATRIX* positions)
{
	D3DXVec3Normalize(&look,&look);

	D3DXVec3Cross(&up,&look,&right);
	D3DXVec3Normalize(&up,&up);

	D3DXVec3Cross(&right,&up,&look);
	D3DXVec3Normalize(&right,&right);

	float x  = -D3DXVec3Dot(&right,&position);
	float y  = -D3DXVec3Dot(&up,&position);
	float z  = -D3DXVec3Dot(&look,&position);

	(*positions)(0,0) = right.x;
	(*positions)(0,1) = up.x;
	(*positions)(0,2) = look.x;
	(*positions)(0,3) = 0;

	(*positions)(1,0) = right.y;
	(*positions)(1,1) = up.y;
	(*positions)(1,2) = look.y;
	(*positions)(1,3) = 0;

	(*positions)(2,0) = right.z;
	(*positions)(2,1) = up.z;
	(*positions)(2,2) = look.z;
	(*positions)(2,3) = 0;

	(*positions)(3,0) = x;
	(*positions)(3,1) = y;
	(*positions)(3,2) = z;
	(*positions)(3,3) = 1;





}


void camera::Keyuse(char key,HINSTANCE h,HWND hwnd)
{

	//THIS IS NOT IN USE
	ZeroMemory(state,sizeof(state));

	DirectInput8Create(h,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&input,0);

	input->CreateDevice(GUID_SysKeyboard,&board,0);
	board->SetDataFormat(&c_dfDIKeyboard);
	board->SetCooperativeLevel(hwnd,DISCL_NONEXCLUSIVE|DISCL_FOREGROUND);
	board->Acquire();

	ZeroMemory(state,sizeof(state));

	board->GetDeviceState(sizeof(state),(void**)&board);

	board->Acquire();

	//return (state[key]& 0x80) != 0;


}


bool camera::keyAction(char key)
{
	return (GetAsyncKeyState(key) & 0x8000f) != 0;
}
