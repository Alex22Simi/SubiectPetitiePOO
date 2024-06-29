#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Petitie
{
	const int id;
	char* denumire;
	string categorie;
	int nrZileDeLaDepunere;
	bool starePetitie;//1->deschisa(true), 0 ->inchisa(false)
	static string localitate;
public:
	Petitie() :id(0)
	{
		this->denumire = new char[strlen("Anonima") + 1];
		strcpy(this->denumire, "Anonima");
		this->categorie = "Necunoscuta";
		this->nrZileDeLaDepunere = 0;
		this->starePetitie = 0;
	}
	Petitie(const int id, const char* denumire, string categorie,
		int nrZileDeLaDepunere, bool starePetitie):id(id)
	{
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->categorie = categorie;
		this->nrZileDeLaDepunere = nrZileDeLaDepunere;
		this->starePetitie = starePetitie;
	}
	//getteri
	const int getId()
	{
		return this->id;
	}
	char* getDenumire()
	{
		return this->denumire;
	}
	string getCategorie()
	{
		return this->categorie;
	}
	int getNrZileDeLaDepunere()
	{
		return this->nrZileDeLaDepunere;
	}
	bool getStarePetitie()
	{
		return this->starePetitie;
	}
	static string getLocalitate()
	{
		return localitate;
	}
	//setteri
	void setDenumire(const char* denumire)
	{
		if (this->denumire != NULL)
		{
			delete[] this->denumire;
		}
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
	}
	void setCategorie(string categorie)
	{
		this->categorie = categorie;
	}
	void setNrZileDeLaDepunere(int nrZileDeLaDepunere)
	{
		if (nrZileDeLaDepunere >= 0)
		{
			this->nrZileDeLaDepunere = nrZileDeLaDepunere;
		}
	}
	void setStarePetitie(bool starePetitie)
	{
		this->starePetitie = starePetitie;
	}
	void setLocalitate( string localitate)
	{
		Petitie::localitate = localitate;
	}
	Petitie(const Petitie& p):id(p.id)
	{
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy(this->denumire, p.denumire);
		this->categorie = p.categorie;
		this->nrZileDeLaDepunere = p.nrZileDeLaDepunere;
		this->starePetitie = p.starePetitie;
		
	}
	Petitie& operator=(const Petitie& p)
	{
		if (this != &p)
		{
			if (this->denumire != NULL)
			{
				delete[] this->denumire;
			}
			this->denumire = new char[strlen(p.denumire) + 1];
			strcpy(this->denumire, p.denumire);
			this->categorie = p.categorie;
			this->nrZileDeLaDepunere = p.nrZileDeLaDepunere;
			this->starePetitie = p.starePetitie;
		}
		return *this;
	}

	~Petitie()
	{
		if (this->denumire != NULL)
		{
			delete[] this->denumire;
		}
	}
	
	friend ostream& operator<<(ostream& out, const Petitie& p)
	{
		out << p.id << endl;
		out << p.denumire << endl;
		out << p.categorie << endl;
		out << p.nrZileDeLaDepunere << endl;
		out << p.starePetitie << endl;
		out << p.localitate << endl;
		return out;
	}
	//istream..

	bool operator!()
	{
		if (this->starePetitie == true && this->nrZileDeLaDepunere > 30)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void operator~()
	{
		if (this->starePetitie == true)
		{
			this->starePetitie = false;
		}
		
	}
	//citire/scriere fisier txt -> se fac la fel ca istream
	//si ostream, dar fara texte si fara atribute constante/staticce
	friend ofstream& operator <<(ofstream& out, const Petitie& p)
	{
		out << p.denumire << endl;
		out << p.categorie << endl;
		out << p.nrZileDeLaDepunere << endl;
		out << p.starePetitie << endl;
		return out;

	}
	friend ifstream& operator>>(ifstream& in, Petitie& p)
	{
		//citire un char* cu tot cu spatiu
		in >> ws;
		char aux[100];
		in.getline(aux, 99);
		if (p.denumire != NULL)
		{
			delete[] p.denumire;
		}
		p.denumire = new char[strlen(aux) + 1];
		strcpy(p.denumire, aux);
		//citire string de la tastatura cu tot cu spatiu
		in >> ws;
		getline(in, p.categorie);
		//citire numerice/bool
		in >> p.nrZileDeLaDepunere;
		//bool
		in >> p.starePetitie;
		return in;
	}
};
string Petitie::localitate = "Bucuresti";
class PetitieOnline:Petitie
{
	string site;
public:
	PetitieOnline() : Petitie()
	{
		this->site = "Necunoscut";
	}
	PetitieOnline(const int id, const char* denumire, string categorie,
		int nrZileDeLaDepunere, bool starePetitie, string site) :Petitie(id, denumire, categorie,
			nrZileDeLaDepunere, starePetitie)
	{
		this->site = site;
	}
	PetitieOnline(const PetitieOnline& p):Petitie(p)
	{
		this->site = p.site;
	}
	PetitieOnline operator=(const PetitieOnline& p)
	{
		if (this != &p)
		{
			Petitie :: operator=(p);
			this->site = p.site;
		}
		return *this;
	}
	~PetitieOnline()
	{

	}
	friend ostream& operator<<(ostream& out, const PetitieOnline& p)
	{
		out << (Petitie&)p;
		out << p.site << endl;
		return out;

	}
};

int main()
{
	Petitie p;
	cout << p << endl;

	Petitie p1(1, "Salvare copaci", "Natura", 35, 1);
	cout << p1 << endl;

	Petitie p2(2, "Reducere poluare", "Natura", 15, 0);
	cout << p2.getId() << endl;
	cout << p2.getDenumire() << endl;
	cout << p2.getCategorie() << endl;
	cout << p2.getNrZileDeLaDepunere() << endl;
	cout << p2.getStarePetitie() << endl;
	cout << p2.getLocalitate() << endl;
	cout << "Testare setter nrZileDep: ";
	p2.setNrZileDeLaDepunere(17);
	cout << p2.getNrZileDeLaDepunere() << endl << endl;

	Petitie p3(3, "Marire pensii", "Economic", 100, 1);
	cout << p3 << endl;

	cout << "Op de copiere:" << endl;
	Petitie p4(p3);
	cout << p4 << endl;

	cout << "Op =:" << endl;
	p4 = p1;
	cout << p4 << endl;

	//testare operator !
	if (!p1)
	{
		cout << "Petitia nu a fost rezolvata" << endl;
	}
	else
	{
		cout << "Petitia a fost rezolvata" << endl;
	}
	if (!p2)
	{
		cout << "Petitia nu a fost rezolvata." << endl;
	}
	else
	{
		cout << "Petitia a fost rezolvata." << endl;
	}
	//testare operator~
	cout << p3.getStarePetitie() << endl;
	~p3;
	cout << p3.getStarePetitie() << endl;
	//scriere in fisier txt
	ofstream f("exempluFis.txt", ios::out);
	f << p1;
	f.close();
	//citire din fisier txt
	ifstream g("exempluFis.txt", ios::in);
	cout << "citire fisier" << endl;
	cout << p2 << endl;
	g >> p2;
	g.close(); cout << endl;
	cout << "testare" << endl;
	cout << p1 << endl;
	cout << p2 << endl;
	//testare clasa derivata
	PetitieOnline po;
	cout << po << endl;
	PetitieOnline po1( 10, "Salvare iarba verde", "Natura", 10, 0, "NATURE");
	PetitieOnline po2 (11, "Salvare copaci", "Natura", 9, 0, "SITE");
	cout << po1 << endl;
	cout << po2 << endl;
	cout << po << endl;
	PetitieOnline po4(po);
	cout << po4 << endl;
	cout << po1 << endl;
	po4 = po1;
	cout << po4 << endl;


}