#include "VectorSpace.h"

using namespace std;

VectorSpace::VectorSpace()
{
    bool verified = false;
    while (!verified)
    {
        U.name = "l vector U";
        V.name = "l vector V";
        W.name = "l vector W";
        VectorAdd(U);
        Normalize(U);
        VectorAdd(V);
        Normalize(V);
        VectorAdd(W);
        Normalize(W);
        cameraPos.name = " la posicion de la camara";
        VectorAdd(cameraPos);
        puntoMundo.name = " la posicion del punto en el mundo";
        VectorAdd(puntoMundo);
        if (OrtonormalVerify())
            verified = true;
    }
    Transformer();
}

VectorSpace::~VectorSpace()
{

}

void VectorSpace::VectorAdd(Vectores &reference)
{
    cout << "Ingresa el valor x de" << reference.name << endl;
    reference.xyz[0] = NumberCheck();
    cout << "Ingresa el valor y de" << reference.name << endl;
    reference.xyz[1] = NumberCheck();
    cout << "Ingresa el valor z de" << reference.name << endl;
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
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            matriz[i][j] = 0.0f;
    }

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

    float matrizPunto[4] = {puntoMundo.xyz[0], puntoMundo.xyz[1], puntoMundo.xyz[2], 1};

    for (int i = 0; i < 4; i++)
        puntoFinal[i] = 0.0f;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            puntoFinal[i] += matriz[i][j] * matrizPunto[j];
        }
    }
    if (puntoFinal[3] != 1)
    {
        for (int i = 0; i < 4; i++)
            puntoFinal[i] = puntoFinal[i] / puntoFinal[3];
    }
}

void VectorSpace::Show()
{
    cout << "Matriz MTC" << endl;
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            cout << matriz[row][col] << "\t";
        }
        cout << endl;
    }
    cout << "\nPunto en coordenadas camara:" << endl;
    for (int en = 0; en < 3; en++)
    {
        cout << puntoFinal[en] << "\t";
    }
}

void VectorSpace::Normalize(Vectores& reference)
{
    Vectores temp = reference;
    for (int i = 0; i < 3; i++)
        reference.xyz[i] = reference.xyz[i] / sqrt(temp.xyz[0] * temp.xyz[0] + temp.xyz[1] * temp.xyz[1] + temp.xyz[2] * temp.xyz[2]);
}

bool VectorSpace::OrtonormalVerify()
{
    auto dot = [](Vectores& A, Vectores& B) {
        return A.xyz[0] * B.xyz[0] + A.xyz[1] * B.xyz[1] + A.xyz[2] * B.xyz[2];
        };
    auto norm = [](Vectores& A) {
        return sqrt(A.xyz[0] * A.xyz[0] + A.xyz[1] * A.xyz[1] + A.xyz[2] * A.xyz[2]);
        };
    const float EPS = 1e-6;

    if (fabs(norm(U) - 1.0f) > EPS) return false;
    if (fabs(norm(V) - 1.0f) > EPS) return false;
    if (fabs(norm(W) - 1.0f) > EPS) return false;

    if (fabs(dot(U, V)) > EPS) return false;
    if (fabs(dot(U, W)) > EPS) return false;
    if (fabs(dot(V, W)) > EPS) return false;

    return true;
}

