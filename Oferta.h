#pragma once
#include<string>
using namespace std;
class Oferta
{
	string tara, oras;
	int cod, pret, locuri_disponibile, nr_nopti;
	string data_inceput, data_sfarsit, hotel;
public:
	Oferta(){}
	Oferta(string Tara, string Oras, int Pret, int nopti, string d_inceput, string d_sfarsit, string Hotel, int Cod, int locuri_disp);
	void afisare();
	void init(string Tara, string Oras, int Pret, int nopti, string d_inceput, string d_sfarsit, string Hotel, int locuri_disp, int Cod);
	friend ostream& operator <<(ostream&, const Oferta&);
	string get_tara();
};

