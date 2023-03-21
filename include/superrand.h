#ifndef SUPERRAND_H
#define SUPERRAND_H
#include <iostream>
#include <vector>
#include <random>

class superrand
{
    private:
        std::uniform_int_distribution<int> dis;

        bool exclusif;
        int maxi;
        int mini;
        std::vector <int> tabRandom;
        int taille;
        void testTaille();
        int calculValeur();
        void inversionMaxMini();
        static void inversionMaxMini(int& mini, int& maxi);
        static std::mt19937 mt;

    public:
        superrand(int mini, int maxi, int taille, bool exclusif = false);

        //Get
        int getMaxi() const;
        int getMini() const;
        int getTaille() const;
        std::vector <int> getTableau();

        //Set
        void setMaxi(int maxi);
        void setMini(int mini);
        void setTaille(int taille);

        void remplirTab();

        static int valeurUnique(int valMini, int valMaxi);



        int operator[] (int indice) const;
        ~superrand();

    protected:
};

#endif // SUPERRAND_H
