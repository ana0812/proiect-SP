#include<iostream>
#include"Oferta.h"
#include"Agentie.h"
#include<vector>
#include<string>
#include<fstream>
using namespace std;
#pragma warning(disable : 4996)

Agentie a;


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

void corect(char* s)
{
    if (s[0] >= 'a' && s[0] <= 'z')
        s[0] = s[0] - 'a' + 'A';
    for (int i = 1; i < strlen(s); i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i] + 'a' - 'A';
}

void cautare(vector<Oferta> const& oferte, vector <string> const& tari)
{
    int ok1 = 0, ok2 = 0;// ok1 o sa fie 1 daca  vrea filtru dupa locatie, ok2 daca vrea filtru dupa perioada
    cout << "Daca doresti sa filtrezi ofertele in functie de locatie, APASATI 1, altfel APASATI 0." << '\n';
    int x;
    cin >> x;
    cin.ignore();
    if (x == 1)
        ok1 = 1;

    cout << "Daca doresti sa filtrezi ofertele vazute in functie de perioada, APASATI 1, altfel APASATI 0." << '\n';
    cin >> x;
    cin.ignore();
    if (x == 1)
        ok2 = 1;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\n';
    int z = 0;// ca sa  se incrementeze  cand se printeaza oferte, sa stiu daca dupa criteriile utilizatorului s-au gasit sau nu oferte
    //daca z=0  dupa if-uri inseamna ca nu s a agsit vreo oferte pt el
    if (ok1 == 0 && ok2 == 0)// daca nu doreste in functie de tara sau de perioada se afiseaza toate ofertele
    {
        for (string const& tara : tari)
        {
            cout << "	---Tara: " << tara << " ---" << endl << endl;
            for (Oferta o : oferte)
            {
                // string1.compare(string2) -> 0 daca sunt identice stringurile
                if (!tara.compare(o.get_tara()))
                {
                    o.afisare(); //afisez folosind functie
                    // n am mai folosit supraincarcarea ptc imi afisa si Tara: si nu voiam sa se repete
                    cout << endl;
                    z = 1;
                }
            }
        }
    }
    else
        if (ok1 == 1 && ok2 == 0)//daca vrea in functie de tara
        {
            cout << "Alegeti tara in care doriti sejurul." << '\n';
            cout << "Tara cautata: ";
            char sir[40];
            cin >> sir;
            cin.ignore();
            corect(sir);//folosesc functia in care transform ceva gen FrAnTa in Franta
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\n';
            for (Oferta o : oferte)
            {
                char c[40];
                strcpy(c, o.get_tara().c_str());//am pus stringul care reprezinta tara intr-un char
                if (strcmp(sir, c) == 0)//vad daca tara din oferta e la fel ca tara ceruta de utilizator
                {
                    o.afisare();
                    cout << endl;
                    z = 1;// am afisat ceva deci   pot sa il intreb pe utilizator daca doreste sa  rezerve ceva
                            // sau daca z=0 la sfarsit, stiu  sa mi cer scuze ca nu a gasit nimic
                }
            }
        }
        else if (ok1 == 0 && ok2 == 1)// daca am filtru de perioada
        {
            char ciu[40], csu[40];// char-urile pentru data de inceput si data de sfarsit cerute de utilizator
            // c-char  i-inceput  u- utilizator  deci ciu este char-ul primit de la utilizator pentru data de inceput
            //analog pentru csu(data de sfarsit de la utilizator) cio(data de inceput din oferta), cso(data de sfarsit din oferta)
            cout << "Alegeti perioada minima in care doriti sejurul." << '\n';
            cin >> ciu;
            cin.ignore();
            cout << "Alegeti perioada maxima in care doriti sejurul." << '\n';
            cin >> csu;
            cin.ignore();
            char* piu, * psu;// fiecare pointer pentru a folosii strtok ul pe char-uri, le despart prin . 
            piu = strtok(ciu, ".");
            int viu[4], vsu[4]; // pun in vectori  numerele care reprezinta datele din perioade, ca sa le pot compara
            int i = 0;
            while (piu != NULL)// in acest while  pun in vectorul de numere datele din perioade
            {
                int n = 0;
                for (int j = 0; j < strlen(piu); j++)
                    n = n * 10 + piu[j] - '0';
                viu[i] = n;
                i++;
                piu = strtok(NULL, ".");
            }
            i = 0;
            psu = strtok(csu, ".");
            while (psu != NULL)
            {
                int n = 0;
                for (int j = 0; j < strlen(psu); j++)
                    n = n * 10 + psu[j] - '0';
                vsu[i] = n;
                i++;
                psu = strtok(NULL, ".");
            }

            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\n';
            for (string const& tara : tari)
            {
                for (Oferta o : oferte)
                    if (!tara.compare(o.get_tara()))
                    {// pentru fiecare  oferta pe care o am in fisier,compar cu perioadele pe care le am primit de la utilizator
                        char cio[40], cso[40];
                        char* pio, * pso;
                        int vio[4], vso[4];
                        strcpy(cio, o.get_di().c_str());
                        strcpy(cso, o.get_ds().c_str());
                        i = 0;
                        pio = strtok(cio, ".");
                        while (pio != NULL)
                        {
                            int n = 0;
                            for (int j = 0; j < strlen(pio); j++)
                                n = n * 10 + pio[j] - '0';
                            vio[i] = n;
                            i++;
                            pio = strtok(NULL, ".");
                        }
                        i = 0;
                        pso = strtok(cso, ".");
                        while (pso != NULL)
                        {
                            int n = 0;
                            for (int j = 0; j < strlen(pso); j++)
                                n = n * 10 + pso[j] - '0';
                            vso[i] = n;
                            i++;
                            pso = strtok(NULL, ".");
                        }
                        int da1 = 0;
                        if (viu[2] < vio[2])// data de la utilizator  de inceput trebuie sa fie <= decat data de la oferta ca sa fie valabil
                            da1 = 1;
                        else if (viu[2] == vio[2])
                        {
                            if (viu[1] < vio[1])
                                da1 = 1;
                            else if (viu[1] == vio[1])
                            {
                                if (viu[0] <= vio[0])
                                    da1 = 1;
                            }
                        }
                        int da2 = 0;
                        if (vsu[2] > vso[2])// data de la utilizator de sfarsit trebuie sa fie >=  decat data din oferta ca sa fie valabila
                            da2 = 1;
                        else if (vsu[2] == vso[2])
                        {
                            if (vsu[1] > vso[1])
                                da2 = 1;
                            else if (vsu[1] == vso[1])
                            {
                                if (vsu[0] >= vso[0])
                                    da2 = 1;
                            }
                        }
                        //daca am in oferta 10.05.2020- 15.05.2020
                        //daca utilizatorul cere 01.05.2020-15.05.2020  deci e buna perioada, afiseaza oferta
                        //daca utilizatorul cere 10.05.2020-15.05.2020 deci e buna, afiseaza oferta
                        // daca utilizatorul cere  10.05.2020-14.05.2020 deci nu e buna, ca nu corespunde data de sfarsit
                                //utilizatorul cere ca vrea ceva pana pe 14 mai dar, oferta e pana pe 15
                        if (da1 == 1 && da2 == 1)//daca si data de inceput si data de sfarsit de la utilizator sunt bine, am oferte
                            //care corespund
                        {
                            cout << "	---Tara: " << tara << " ---" << endl << endl;
                            o.afisare();
                            z = 1;
                            cout << endl;
                        }
                    }
            }
        }
        else if (ok1 == 1 && ok2 == 1)//daca imi cere si tara si perioada fac ce am, facut la ultimele 2 functii dar le combin
        {
            cout << "Alegeti tara in care doriti sejurul." << '\n';
            cout << "Tara cautata: ";
            char sir[40];
            cin >> sir;
            cin.ignore();
            corect(sir);
            char ciu[40], csu[40];
            cout << "Alegeti perioada minima in care doriti sejurul." << '\n';
            cin >> ciu;
            cin.ignore();
            cout << "Alegeti perioada maxima in care doriti sejurul." << '\n';
            cin >> csu;
            cin.ignore();
            char* piu, * psu;
            piu = strtok(ciu, ".");
            int viu[4], vsu[4];
            int i = 0;
            while (piu != NULL)
            {
                int n = 0;
                for (int j = 0; j < strlen(piu); j++)
                    n = n * 10 + piu[j] - '0';
                viu[i] = n;
                i++;
                piu = strtok(NULL, ".");
            }
            i = 0;
            psu = strtok(csu, ".");
            while (psu != NULL)
            {
                int n = 0;
                for (int j = 0; j < strlen(psu); j++)
                    n = n * 10 + psu[j] - '0';
                vsu[i] = n;
                i++;
                psu = strtok(NULL, ".");
            }

            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\n';
            for (string const& tara : tari)
            {
                for (Oferta o : oferte)
                    if (!tara.compare(o.get_tara()))
                    {
                        char cio[40], cso[40];
                        char* pio, * pso;
                        int vio[4], vso[4];
                        strcpy(cio, o.get_di().c_str());
                        strcpy(cso, o.get_ds().c_str());
                        i = 0;
                        pio = strtok(cio, ".");
                        while (pio != NULL)
                        {
                            int n = 0;
                            for (int j = 0; j < strlen(pio); j++)
                                n = n * 10 + pio[j] - '0';
                            vio[i] = n;
                            i++;
                            pio = strtok(NULL, ".");
                        }
                        i = 0;
                        pso = strtok(cso, ".");
                        while (pso != NULL)
                        {
                            int n = 0;
                            for (int j = 0; j < strlen(pso); j++)
                                n = n * 10 + pso[j] - '0';
                            vso[i] = n;
                            i++;
                            pso = strtok(NULL, ".");
                        }
                        int da1 = 0;
                        if (viu[2] < vio[2])
                            da1 = 1;
                        else if (viu[2] == vio[2])
                        {
                            if (viu[1] < vio[1])
                                da1 = 1;
                            else if (viu[1] == vio[1])
                            {
                                if (viu[0] <= vio[0])
                                    da1 = 1;
                            }
                        }
                        int da2 = 0;
                        if (vsu[2] > vso[2])
                            da2 = 1;
                        else if (vsu[2] == vso[2])
                        {
                            if (vsu[1] > vso[1])
                                da2 = 1;
                            else if (vsu[1] == vso[1])
                            {
                                if (vsu[0] >= vso[0])
                                    da2 = 1;
                            }
                        }
                        char* c = new char[o.get_tara().length() + 1];
                        strcpy(c, o.get_tara().c_str());
                        if (strcmp(sir, c) == 0 && da1 == 1 && da2 == 1)
                        {
                            o.afisare();
                            cout << endl;
                            z = 1;
                        }


                    }
            }

        }
    if (z == 0)
    {
        cout << "Ne pare rau ca nu ati gasit nicio oferta. Puteti cauta iar APASAND 1." << '\n';
        int q;
        cin >> q;
        cin.ignore();
        if (q == 1)
            cautare(oferte, tari);
    }
    cout << "Doresti sa rezervi una dintre ofertele vazute? APASATI 1 daca da, APASATI 0 daca nu" << '\n';
    int a;
    cin >> a;
    cin.ignore();
    if (a == 1)
    {
        cout << "Care este numarul sejurului ales?" << '\n';
        int b;
        cin >> b;
        cin.ignore();
        //rezervare(b, oefrte);
    }
    else
    {
        cout << " Daca doresti sa cauti alta oferta APASATI 1." << '\n';
        int b;
        cin >> b;
        cin.ignore();
        if (b == 1)
            cautare(oferte, tari);
    }
}

void caut(vector<Oferta> const& oferte, vector <string> const& tari) {
    cout << "Bine ai venit in cautare!" << endl;
        cautare(oferte, tari);
}

bool  verificareCont(const string& mail) {
    ifstream c;
    c.open("cont.txt");
    string m, t, p;

    while (!c.eof()) {
        c >> m >> t >> p;
        if (!c.eof()) {
            if (!m.compare(mail))
                return false;
        }
    }
    c.close();
    return true;
}

void creareCont() {
    string mail, tel, par;
    cout << "Pentru a crea un cont va rugam sa introduceti urmatoarele date: " << endl;
    cout << "E-mail: "; cin >> mail;
    cout << "\nNumar de telefon: "; cin >> tel;
    cout << "\nParola: "; cin >> par;
    cout << mail << " " << tel << " " << par;

    if (!verificareCont(mail))
    {
        cout << "Deja exista un cont cu acest email. Va rugam incercati cu alta adresa.";
        return;
    }
        
    fstream c;
    c.open("cont.txt", ios::app);
    if (c.is_open()) {
        c << mail << " " << tel << " " << par << endl;
    }

    c.close();
}

bool verificareInr(const string& mail, const string& parola) {
    ifstream c;
    c.open("cont.txt");
    string m, t, p;

    while (!c.eof()) {
        c >> m >> t >> p;
        if (!c.eof()) {
            if (!m.compare(mail) && !p.compare(parola))
                return true;
        }
    }
    c.close();
    return false;
}

void inregistrareCont() {
    cout << "Va rugam sa va inregistrati in cont introducand urmatoarele informatii: " << endl;
    string mail, parola;
    cout <<"E-mail: "; cin >> mail;
    cout << "\nParola: "; cin >> parola;

    if (!verificareInr(mail, parola)) {
        cout << "Datele nu coincid cu baza noastra de date! Va rugam incercati din nou:)";
        return;
    }
    cout << "Ati intrat in cont";
    //Agentie::logareCont += 1;
    a.logareCont = 1;
}

void delogare() {
    a.logareCont = 0;
}

void rezervare() {
    if (a.logareCont) {
        //functia de rezervare
    }
    else {
        //te intorci in meniu/functia de logare
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
	//vector <Oferta> oferte(n); //vectorul care o sa contina toate ofertele citite
	fisier >> n_tari; //citesc numarul de tari
	//vector <string> tari(n_tari);

    Agentie aux(n, n_tari);
    a = aux;

	int j = 0;
	string tara;
	//citesc tarile
	while (j < n_tari) {
		fisier >> tara;
        a.setTara(tara);
		//tari[j++] = tara;
        j++;
	}
	
	if (fisier.is_open()) {
		while (1) {
			if (fisier.eof())
				break;
			fisier >> t >> o >> pr >> nopti >> di >> ds >> h >> pers;
			/*cout << t << " " << o << " " << pr << " " << nopti << " " << di << " " << ds << " " << h << " " << pers;*/
			//oferte[i++].init(t, o, pr, nopti, di, ds, h, pers, i + 1);
			//n am stiut exact cum functioneaza dar nu mergea apelat constructoul - am facut functie pt initializare
            Oferta o(t, o, pr, nopti, di, ds, h, pers, i + 1);
            a.setOferta(o);
		}
	}

    //cout << "merge";
    cout << a;

	//afisare(oferte, tari);
    //caut(oferte, tari);
    //creareCont();
    //inregistrareCont();

	/* cum functioneaza constructorul + adaugarea de elemente in vector
	Oferta o1("Spania", "Barcelona", 500, 7, "01.02.03", "02.02.02", "ana", 3,20);
	Oferta o2("Franta", "Paris", 700, 7, "01.02.03", "02.02.02", "ana", 3, 20);
	Oferta o3("Spania", "Valencia", 500, 7, "01.02.03", "02.02.02", "ana", 3, 20);

	vector <Oferta> oferte;
	oferte.push_back(o1);
	oferte.push_back(o2);
	oferte.push_back(o3);*/

}