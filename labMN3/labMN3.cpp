#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
using namespace std;

int main()
{
    //1
    int n;
    float piv;

    std::cout << "n = ";
    cin >> n;
    float matrix[51][51];
    float L[51][51] = { 0 }, R[51][51] = { 0 };  //matricile L si R 
    L[1][1] = 1;


    std::cout << "Introdu elementele matricii A: ";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n + 1; j++)
        {
            cin >> matrix[i][j];
        }
    }
    int nrInterschimbari = 0;
    float det = 1;

    //2
    if (matrix[1][1] == 0)
    {
        int i = 1;
        do
        {
            i = i + 1;
        } while
            (matrix[i][1] == 0 && i <= n);
        if (i > n)
        {
            std::cout << "Sistemul nu are solutie unica!";
            exit(0);
        }
        for (int j = 1; j <= n + 1; j++)
        {
            swap(matrix[1][j], matrix[i][j]);

        }
        nrInterschimbari++;   //numaram interschimbarile
    }
    // Copiem matricea după interschimbări pentru a calcula corect L și R
    float A[51][52];
    std::cout << "matricea A dupa interschimbari: " << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n + 1; j++)
        {
            A[i][j] = matrix[i][j];  // retinem valoarea matricii după interschimbare
            std::cout << A[i][j] << " ";
        }
        std::cout << endl;
    }
    std::cout << "" << endl;

    //3
    for (int i = 2; i <= n; i++)
    {
        matrix[i][1] = matrix[i][1] / matrix[1][1];
    }
    //4
    for (int k = 2; k <= n; k++)
    {
        int i = k;
        do
        {
            float S = 0;
            piv = 0;
            for (int h = 1; h <= k - 1; h++)
            {
                S = S + matrix[i][h] * matrix[h][k];
            }
            piv = matrix[i][k] - S;
            i = i + 1;
        } while (piv == 0 && i <= n);
        if (piv == 0)
        {
            std::cout << "Sistemul nu are sol unica!";
            exit(0);
        }
        //4.4
        if (i != k + 1)
        {
            for (int j = 1; j <= n + 1; j++)
            {
                swap(matrix[k][j], matrix[i - 1][j]);
            }
            nrInterschimbari++;   //numaram interschimbarile
        }
        //4.5
        for (int j = k; j <= n; j++)
        {
            float S = 0;
            for (int h = 1; h <= k - 1; h++)
            {
                S = S + matrix[k][h] * matrix[h][j];
            }
            matrix[k][j] = matrix[k][j] - S;
        }
        //4.6
        for (int i = k + 1; i <= n; i++)
        {
            float S = 0;
            for (int h = 1; h <= k - 1; h++)
            {
                S = S + matrix[i][h] * matrix[h][k];
            }
            matrix[i][k] = (matrix[i][k] - S) / matrix[k][k];
        }
    }
    //5
    for (int i = 2; i <= n; i++)
    {
        float S = 0;
        for (int k = 1; k <= i - 1; k++)
        {
            S = S + matrix[i][k] * matrix[k][n + 1];
        }
        matrix[i][n + 1] = matrix[i][n + 1] - S;

    }
    //6
    matrix[n][n + 1] = matrix[n][n + 1] / matrix[n][n];
    //7
    for (int i = n - 1; i >= 1; i--)
    {
        float S = 0;
        for (int j = i + 1; j <= n; j++)
        {
            S = S + matrix[i][j] * matrix[j][n + 1];
        }
        matrix[i][n + 1] = (matrix[i][n + 1] - S) / matrix[i][i];
    }
    //8
    
    //afisare solutii
    std::cout << "Solutiile sunt: " << endl;
    for (int i = 1; i <= n; i++)
    {
        std::cout << "x" << i << " = " << matrix[i][n + 1] << std::endl;
    }

    // Construirea matricelor L și R 
    for (int j = 1; j <= n; j++)
    {
        R[1][j] = A[1][j];  //prima linie din R
    }
    //std::cout << "r11" << R[1][1]<<endl;  //debug
    for (int i = 2; i <= n; i++)
    {
        L[i][1] = A[i][1] / R[1][1];  //prima col din L
    }

    /*
    std::cout << "a31" << matrix[3][1] << endl;
    std::cout << "l31:" << L[3][1] << endl;  */   //debug

    // Calcularea elementelor din R
    for (int k = 2; k <= n; k++)
    {
        for (int j = k; j <= n; j++)
        {
            float sum = 0;
            for (int h = 1; h <= k - 1; h++)
            {
                sum += L[k][h] * R[h][j];
            }
            R[k][j] = A[k][j] - sum;
        }
    }

    // Calcularea elementelor din L
    for (int k = 1; k <= n; k++)
    {
        L[k][k] = 1;  //setarea valorii diagonalei lui L ca 1
        for (int i = k + 1; i <= n; i++)
        {
            float sum = 0;
            for (int h = 1; h <= k - 1; h++)
            {
                sum += L[i][h] * R[h][k];
            }
            L[i][k] = (A[i][k] - sum) / R[k][k];
        }
    }

    // Afișare matrice L
    std::cout << "\nMatricea L:\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (fabs(L[i][j]) < 1e-9)  // dacă valoarea este foarte mica, o facem 0  (altfel afiseaza -0 datorita formatului FLP)
                std::cout << "0 ";
            else
                std::cout << L[i][j] << " ";
        }
        std::cout << endl;
    }

    // Afișare matrice R
    std::cout << "\nMatricea R:\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            std::cout << R[i][j] << " ";
        }
        std::cout << endl;
    }

    det = pow(-1, nrInterschimbari);
    for (int i = 1; i <= n; i++)
    {
        det *= R[i][i];
    }
    std::cout << "Determinantul este : " << det << endl;
    std::cout << "Numarul total de permutari este : " << nrInterschimbari << endl;
    return 0;
}