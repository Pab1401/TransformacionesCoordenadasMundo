#include "VectorSpace.h"

using namespace std;

VectorSpace::VectorSpace()
{
    U.name = "l vector U";
    V.name = "l vector V";
    W.name = "l vector W";
    VectorAdd(U);
    VectorAdd(V);
    VectorAdd(W);
    cameraPos.name = " la posicion de la camara";
    VectorAdd(cameraPos);
    puntoMundo.name = " la posicion del punto en el mundo";
    VectorAdd(puntoMundo);
}

VectorSpace::~VectorSpace()
{

}

void VectorSpace::VectorAdd(Vectores reference)
{
    cout << "Ingresa el valor x de" << reference.name;
    reference.xyz[0] = NumberCheck();
    cout << "Ingresa el valor y de" << reference.name;
    reference.xyz[1] = NumberCheck();
    cout << "Ingresa el valor z de" << reference.name;
    reference.xyz[2] = NumberCheck();

}

float VectorSpace::NumberCheck()
{
    bool validated = false;
    float number;
    while (!validated)
    {
        cin >> number;
        if (!cin.eof())
        {
            float peek;
            peek = cin.peek();
            if (peek == 10 && cin.good())
            {
                validated = true;
            }
            else
            {
                cout << "\nInput is not a number" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    return number;
}

void VectorSpace::Transformer()
{
    for (int i = 0; i < 3; i++)
    {
        matriz[0][i] = U.xyz[i];
        matriz[1][i] = V.xyz[i];
        matriz[2][i] = W.xyz[i];
        matriz[0][3] += -matriz[0][i] * cameraPos.xyz[i];
        matriz[1][3] += -matriz[1][i] * cameraPos.xyz[i];
        matriz[2][3] += -matriz[2][i] * cameraPos.xyz[i];
    }
    matriz[3][0] = 0;
    matriz[3][1] = 0;
    matriz[3][2] = 0;
    matriz[3][3] = 1;
}