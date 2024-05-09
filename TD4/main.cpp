#include <iostream>
#include<list>

using namespace std;

int main()
{
    {   /* Pointeurs 1.1

        int i( 0 );
        // int * j( 1 ); // Pointeur sur 1 et non sur &i => int * j( &i );
        int * k( 0 );
        int * l( &i );
        int * m( l );
        // int * const n; // Pointeur sur rien et non sur &i => int * const n(&i)
        int * const o( l );
        int * p;
        int const * q(&i);
        // o = m; // o constant => besoin de modifier la déclaration de o
        p = m;
        // *q = 10; // q lecture seule
        *m = 10;
        // q = 10; // notation incompatible int const * =/= int
        // m = 10; // notation incompatible int * =/= int


        cout << *l << " " << *m << endl; // terminal => 10 10

        // Tailles : i = int => 16 ou 32 bits
        //           l = pointeur => 64 bits selon architecture
        //          *l = valeur pointée = i => 16 ou 32 bits

    */  }

    {   /* Pointeurs 1.2

        int i = 0;
        int * j = new int;
        *j = 1; // *j initialisé à 1
        cout << *j << endl; // terminal => 1
        *j = i; // *j initialisé à valeur i = 0
        cout << *j << endl; // terminal => 0
        delete j;

    */  }

    {   /* Tableaux

        int tab1[4] = { 1, 2, 3, 4}; // 4 valeurs mais 3 attribuées => 4ème valeur non attribuée
        cout << "tab1 : ";

        for(int i(0); i < 4; i++){
            cout << tab1[i] << ", ";
        }

        cout << endl << endl;

        int * tab2 = new int[4];
        cout << "tab2 : ";

        for(int j(0); j < 4; j++){
            tab2[j] = tab1[j];
        }

        for(int k(0); k < 4; k++){
            cout << tab2[k] << ", ";
        }

        cout << endl;

        delete[] tab2;

    */  }

    {   /* Iterateurs

        list<int> liste(10, 0);
        list<int>::iterator it;
        list<int>::reverse_iterator rit;

        int value(1);

        for(it = liste.begin(); it != liste.end(); ++it){
            *it = value;
            value++;
        }

        cout << "Reversed list standard: ";
        for(rit = liste.rbegin(); rit != liste.rend(); ++rit){cout << *rit << ", ";}
        cout << endl;
    */  }

    {   /* Bonus */
        list<int> liste(10, 0);

        int value(1);
        for(auto it = liste.rbegin(); it != liste.rend(); ++it){
            *it = value;
            value++;
        }

        cout << "Reversed list auto: ";
        for(auto rit = liste.rbegin(); rit != liste.rend(); ++rit){cout << *rit << ", ";}
        cout << endl;

    }




    return 0;
}
