#include "iostream"
#include "string"
#include "cmath"
#pragma once

struct Vectores
{
	string name;
	float xyz[3];
};

class VectorSpace
{
public:
	VectorSpace();
	~VectorSpace();
	void VectorAdd(Vectores);
	float NumberCheck();
	void Transformer();

private:
	Vectores U;
	Vectores V;
	Vectores W;
	Vectores cameraPos;
	Vectores puntoMundo;
	float matriz[4][4];
};

