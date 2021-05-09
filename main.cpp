#include<iostream>
#include"Oferta.h"
#include<vector>
#include<string>
#include<fstream>
using namespace std;

void afisare(vector<Oferta> const& oferte, vector <string> const& tari) {
	cout << "1. Afisare oferte." << endl;
	cout << "2. Afisare oferte in functie de tara. In total oferim sejururi in "<<tari.size()<<" tari." << endl;
	cout << "Alegeti optiunea: ";

	int optiune; cin >> optiune; cout << endl;
	if (optiune == 1) {
		//Oferta o - trebe sa zic tipul elementelor(Oferta) 
		//"o" o sa fie pe rand fiecare element din vectorul :oferte
		for (Oferta const& o : oferte) {
			cout << o << endl;   //afisez folosind supraincarcarea operatorului
		}
	}
	else {
		for (string const& tara : tari) {
			cout << "	---Tara: " << tara<<" ---"<<endl<<endl;
			for (Oferta o : oferte) {
				// string1.compare(string2) -> 0 daca sunt identice stringurile
				if (!tara.compare(o.get_tara())) {
					o.afisare(); //afisez folosind functie
					// n am mai folosit supraincarcarea ptc imi afisa si Tara: si nu voiam sa se repete
					cout << endl;
				}
			}
		}
	}
}

int main()
{
	fstream fisier;
	fisier.open("oferte.txt", ios::in);
//primul rand din fisier: 2 2 Spania Franta
// numarul de oferte, numarul de tari, tarile
//apoi pe fiecare rand este scrisa cate o oferta

	//variabile pe care le folosesc la citirea din fisier
	string t, o, di, ds, h;
	int pr, nopti, pers,n, n_tari;
	int i = 0;

	fisier >> n; //citesc numarul de oferte
	vector <Oferta> oferte(n); //vectorul care o sa contina toate ofertele citite
	fisier >> n_tari; //citesc numarul de tari
	vector <string> tari(n_tari);
	int j = 0;
	string tara;
	//citesc tarile
	while (j < n_tari) {
		fisier >> tara;
		tari[j++] = tara;
	}
	
	if (fisier.is_open()) {
		while (1) {
			if (fisier.eof())
				break;
			fisier >> t >> o >> pr >> nopti >> di >> ds >> h >> pers;
			/*cout << t << " " << o << " " << pr << " " << nopti << " " << di << " " << ds << " " << h << " " << pers;*/
			oferte[i++].init(t, o, pr, nopti, di, ds, h, pers, i + 1);
			//n am stiut exact cum functioneaza dar nu mergea apelat constructoul - am facut functie pt initializare
		}
	}

	afisare(oferte, tari);

	/* cum functioneaza constructorul + adaugarea de elemente in vector
	Oferta o1("Spania", "Barcelona", 500, 7, "01.02.03", "02.02.02", "ana", 3,20);
	Oferta o2("Franta", "Paris", 700, 7, "01.02.03", "02.02.02", "ana", 3, 20);
	Oferta o3("Spania", "Valencia", 500, 7, "01.02.03", "02.02.02", "ana", 3, 20);

	vector <Oferta> oferte;
	oferte.push_back(o1);
	oferte.push_back(o2);
	oferte.push_back(o3);*/

}