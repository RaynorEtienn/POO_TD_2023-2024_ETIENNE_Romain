#include <iostream>

using namespace std;

void echange1(int a, int b);
void echange2(int const a,  int const b);
void echange3(int & a, int & b);
void echange4(int const & a, int const & b);

int main()
{
    {   /* 2.1

        int i;

        cout << "Entrez un entier :" << endl;
        cin >> i;
        cout << "Vous avez entré l'entier " << i << endl;

        Si la valeur d'entree n'est pas un entier on obtient une erreur type.

        */
    }


    {   /* 2.2.1

        int i = 1;
        int j(1);
        int const k = 2;
        k = i; ERREUR ICI : k const => ne peut pas etre modifiee

        */
    }

    {   /* 2.2.2
        int i = 0;
        int & j = i;
        int & k;    Besoin de l'initier à une valeur
             declaration of reference variable 'k' requires an initializer

        int & l = 0;    Doit se référencer sur un élément de type 'int' et non à une valeur
             non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'

        */
    }

    {   /* 2.2.3

        int i = 0;
        int & j = i;

        cout << "Initialisation" << endl;
        cout << "i : " << i << " j : " << j << endl;

        i = 1;
        cout << "i = 1" << endl;
        cout << "i : " << i << " j : " << j << endl;

        j = 2;
        cout << "j = 2" << endl;
        cout << "i : " << i << " j : " << j << endl;

        cout << "Fin Programme." << endl;

        */
    }

    {   /* 2.3 */

        int i(1);
        int j(2);

        cout << "Avant : i = "<< i <<" et j = " << j << endl;
        echange3(i,j);
        cout << "Apres echange1 : i = " << i << " et j = " << j << endl;
    }



    return 0;
}

/* Non fonctionnel : parametres en lecture seule, impossible d'ecrire
    void echange1(int a, int b)
    {
        int const tmp = b;
        b = a;
        a = tmp;
    }
*/

/* Non fonctionnel : parametres constants, impossible d'ecrire
    void echange2(int const a, int const b)
    {
        int const tmp = b;
        b = a;
        a = tmp;
    }
*/

void echange3(int & a, int & b)
{
    int const tmp = b;
    b = a;
    a = tmp;
}

/* Non fonctionnel :  parametres references constant, impossible d'ecrire
    void echange4(int const & a, int const & b)
    {
        int const tmp = b;
        b = a;
        a = tmp;
    }
*/







