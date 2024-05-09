#include <iostream>
#include<vector>
#include<list>
#include<chrono>
#include<cstdlib>

#include"echange.h"

using namespace std;

int main()
{
    { /* Question 1 : les templates
        int a(0), b(1);
        cout << "a: " << a << " b: " << b << endl;

        echange(a, b);

        cout << "Swap" << endl;
        cout << "a: " << a << " b: " << b << endl;

        cout << "########################" << endl;
        cout << endl;
        cout << "########################" << endl;

        float a_f(0.1f), b_f(1.1f);
        cout << "a_f: " << a_f << " b_f: " << b_f << endl;

        echange(a_f, b_f);

        cout << "Swap" << endl;
        cout << "a_f: " << a_f << " b_f: " << b_f << endl;
    */ }

    { /* Question 2 : Conteneurs standards : vecteurs et listes
        // Vecteur
        vector<int> vecteur_1({1, 2, 3});

        // For Simple
        cout << endl << "For Simple Vector" << endl;
        for (int i(0); i < vecteur_1.size(); i++) {
            cout << vecteur_1[i]<< " ";
        }

        // For Auto
        cout << endl << "For Auto Vector" << endl;
        for (auto i : vecteur_1)
                cout << i << " ";

        // Liste
        list<int> liste_1({1, 2, 3});

        // For Simple
        cout << endl << "For Simple List" << endl;
        for (list<int>::iterator i = liste_1.begin(); i != liste_1.end(); ++i) {
            cout << *i << " ";
        }


        // For Auto
        cout << endl  << "For Auto List" << endl;
        for (auto i : liste_1)
                cout << i << " ";
    */ }

    {
        vector<float> vecteur;
        auto tstart(std::chrono::high_resolution_clock::now());

        for(int i(0); i < 100000000; i++)
        {
            float const f( float(rand())/float(RAND_MAX) );
            vecteur.push_back(f);
        }

        auto tstop(std::chrono::high_resolution_clock::now());
        auto elapsed(std::chrono::duration_cast<std::chrono::nanoseconds>(tstop-tstart));
        cout << "Vector: " << elapsed.count()/1000000.f << "ms" << endl;

        // Time: 2703.36ms
    }

    {
        list<float> liste;
        auto tstart(std::chrono::high_resolution_clock::now());

        for(int i(0); i < 100000000; i++)
        {
            float const f( float(rand())/float(RAND_MAX) );
            liste.push_back(f);
        }

        auto tstop(std::chrono::high_resolution_clock::now());
        auto elapsed(std::chrono::duration_cast<std::chrono::nanoseconds>(tstop-tstart));
        cout << "List: " << elapsed.count()/1000000.f << "ms" << endl;

        // Time: 9360.13ms
    }

    {
        vector<float> vecteur;
        vecteur.reserve(100000000);
        auto tstart(std::chrono::high_resolution_clock::now());

        for(int i(0); i < 100000000; i++)
        {
            float const f( float(rand())/float(RAND_MAX) );
            vecteur.push_back(f);
        }

        auto tstop(std::chrono::high_resolution_clock::now());
        auto elapsed(std::chrono::duration_cast<std::chrono::nanoseconds>(tstop-tstart));
        cout << "Vector Reserved: " << elapsed.count()/1000000.f << "ms" << endl;

        // Time: 2283.67ms < Time Vector Non-Reserved => Allowing memory take some time.
    }

    cout << endl << "Fin Programme ..." << endl;
}
