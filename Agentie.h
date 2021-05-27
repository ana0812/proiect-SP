#pragma once
#include"Oferta.h"
#include<vector>
#include<iostream>

class Agentie
{
	int logareCont;
	vector<Oferta> oferte;
	int nrTari, nrOferte;
	vector<string>tari;

public:
	Agentie(int=0, int=0);
	friend void inregistrareCont();
	friend void delogare();
	friend void rezervare();

	void setTara(const string& s);
	void setOferta(Oferta& o);
	friend ostream& operator<<(ostream&, const Agentie&);
	//static int logareCont;

};

//int Agentie::logareCont = 0;

