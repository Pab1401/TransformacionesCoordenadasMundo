#include <iostream>
#include <string>
#include <cmath>
#pragma once

struct Vectores
{
	std::string name;
	float xyz[3];
};

class VectorSpace
{
public:
	VectorSpace();
	~VectorSpace();
	void VectorAdd(Vectores &reference);
	float NumberCheck();
	void Transformer();
	void Show();
	void Normalize(Vectores& reference);
	bool OrtonormalVerify();

private:
	Vectores U;
	Vectores V;
	Vectores W;
	Vectores cameraPos;
	Vectores puntoMundo;
	float puntoFinal[4];
	float matriz[4][4];
};

