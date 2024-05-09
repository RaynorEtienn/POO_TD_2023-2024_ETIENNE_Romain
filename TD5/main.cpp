#include <iostream>
#include <vector>
#include <memory>
#include "point2f.h"
#include "diag2f.h"
#include "rotation2f.h"

using namespace std;

int main()
{
    {    /* 1 - Conception de la classe virtuelle GenMatrix2x2f

    1.1
        multiply(Point2f) : méthode prenant un objet de type Point2f en entrée et retournant un objet de même type.
        val(int, int) : méthode prenant deux indices entiers en entrée et retournant une valeur correspondant à la position spécifiée dans la matrice.

    1.2
        Déclaration virtuelle "=0".

    1.3
        Non, car classe virtuelle.

    1.4
        Idem.

    1.5
        Oui, pointeur vers référence ok en classe virtuelle.

    1.6
        Deux Point2f en entrée

    */  }

    {   /* 2 - Conception de la classe Diag2f

        Diag2f matriceDiagonale(2.0, 3.0);

        // Utilisation d'un pointeur de base pour pointer vers un objet dérivé
        GenMatrix2x2f* ptrMatrice = &matriceDiagonale;

        // Création d'un point à transformer
        Point2f point(1.0, 1.0);

        // Utilisation du polymorphisme pour multiplier le point par la matrice
        Point2f pointTransforme = ptrMatrice->multiply(point);

        cout << "Point original: " << point << endl;
        cout << "Point après transformation: " << pointTransforme << endl;

        // Démonstration de l'accès aux valeurs de la matrice
        cout << "Valeur de la matrice à (0,0): " << ptrMatrice->val(0, 0) << endl;
        cout << "Valeur de la matrice à (1,0): " << ptrMatrice->val(1, 0) << endl; // Devrait être 0

    */  }

    {   /* 3 - Conception d’une classe Rotation2f

        Rotation2f rotationMatrix(M_PI / 2);

        // Utilisation d'un pointeur de type GenMatrix2x2f pour référencer notre matrice de rotation.
        GenMatrix2x2f* ptrMatrix = &rotationMatrix;

        // Création d'un point à transformer. Par exemple, le point (1, 0) devrait être transformé en (0, 1).
        Point2f point(1.0, 0.0);

        // Utilisation du polymorphisme pour effectuer la rotation sur le point.
        Point2f transformedPoint = ptrMatrix->multiply(point);

        cout << "Point original: " << point << endl;
        cout << "Point après rotation: " << transformedPoint << endl;

        // Pour la démonstration, affichons également les valeurs de la matrice de rotation.
        cout << "Valeur de la matrice à (0,0): " << ptrMatrix->val(0, 0) << endl;
        cout << "Valeur de la matrice à (0,1): " << ptrMatrix->val(0, 1) << endl;
        cout << "Valeur de la matrice à (1,0): " << ptrMatrix->val(1, 0) << endl;
        cout << "Valeur de la matrice à (1,1): " << ptrMatrix->val(1, 1) << endl;

    */  }

    {   /* 4 - Polymorphisme */

        // Création d'un vecteur contenant des pointeurs vers GenMatrix2x2f.
            vector<GenMatrix2x2f *> matrices(2);

            // Ajout d'une matrice diagonale au vecteur.
            Diag2f diagonalMatrix(2.0f, 3.0f);
            matrices[0] = &diagonalMatrix;

            // Ajout d'une matrice de rotation (90 degrés, soit π/2 radians) au vecteur.

            Rotation2f rotationMatrix(M_PI / 2);
            matrices[1] = &rotationMatrix;

            // Point initial à transformer.
            Point2f point(1.0, 2.0);
            cout << "Point initial: " << point << endl;

            // Application séquentielle des transformations et affichage des matrices.
            for (const auto& matrix : matrices) {
                point = matrix->multiply(point);
                cout << "Point après transformation: " << point << endl;
                cout << "Valeurs de la matrice: " << endl;
                cout << matrix->val(0, 0) << " " << matrix->val(0, 1) << endl;
                cout << matrix->val(1, 0) << " " << matrix->val(1, 1) << endl;
            }
    }


    { /* 5 - Bonus -> Non, pas pour cette fois. */  }

    return 0;
}
