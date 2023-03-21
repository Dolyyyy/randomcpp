#include "superrand.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>


std::mt19937 superrand::mt(time(NULL));

superrand::superrand(int mini, int maxi, int taille, bool exclusif)
{
    this->maxi = maxi;
    this->mini = mini;
    this->taille = taille;
    this->exclusif = exclusif;

    inversionMaxMini();

    this->remplirTab();

}

superrand::~superrand()
{
    //dtor
}



//Private Methode

void superrand::inversionMaxMini() {
    if (this->maxi < this->mini) {
        int tmp = this->mini;

        this->mini = this->maxi;
        this->maxi = tmp;
    }

}

void superrand::inversionMaxMini(int & mini, int & maxi) {
    if (maxi < mini) {
        int tmp = mini;

        mini = maxi;
        maxi = tmp;
    }
}

//Private function

int superrand::calculValeur()
{
    int ret = this->dis(mt);
    return ret;
}

void superrand::testTaille() {
    if (this->exclusif) {
        this->taille = this->maxi - this->mini + 1;
    }
    this->tabRandom.resize(this->taille);
}

//Public function
void superrand::remplirTab() {
    this->dis = std::uniform_int_distribution <int>(this->mini, this->maxi);
    this->testTaille();
    std::vector<int> tmpTab;
    std::vector<int>::iterator it;
    int rand;

    do{
        rand = calculValeur();

        if (this->exclusif == true && tmpTab.size() > 0) {
            it = std::find(tmpTab.begin(), tmpTab.end(), rand);

            if (it != tmpTab.end()) {
                tmpTab.back();
            } else {
                tmpTab.push_back(rand);
            }

        } else {
            tmpTab.push_back(rand);
        }

    }while(this->tabRandom.size() != tmpTab.size());

    this->tabRandom = tmpTab;

}

int superrand::valeurUnique(int valMini, int valMaxi) {

    inversionMaxMini(valMini, valMaxi);
    std::uniform_int_distribution <int> dis(valMini,valMaxi);

    return dis(mt);
}

//Public access

//Acsesseur en ecriture.
void superrand::setMaxi(int maxi) {
    this->maxi = maxi;
    this->inversionMaxMini();
    this->remplirTab();
}

void superrand::setMini(int mini) {
    this->mini = mini;
    this->inversionMaxMini();
    this->remplirTab();
}

void superrand::setTaille(int taille) {
    this->taille = taille;
    this->inversionMaxMini();
    this->remplirTab();
}

//Acsesseur en lecture.

int superrand::getMaxi() const {
    return this->maxi;
}

int superrand::getMini() const {
    return this->mini;
}

int superrand::getTaille() const {
    return this->taille;
}

int superrand::operator[] (int indice) const {

    int ret = -1;

    if (this->taille >= indice) {
        ret = tabRandom[indice];
    }

    return ret;

}

std::vector <int> superrand::getTableau() {
    return this->tabRandom;
}
