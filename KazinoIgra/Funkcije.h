#ifndef __FUNKCIJE_H__
#define __FUNKCIJEO_H__
#include  <iostream>

using namespace std;


bool proveraOdgovora(double, bool g = true);

class Greska {

public:
	virtual ostream& pisi(ostream& os) = 0;

	friend ostream& operator<<(ostream& os, Greska& g) {
		g.pisi(os);
		return os;
	}

};

class GreskaListaIgraca : public Greska {

	ostream& pisi(ostream& os) {
		os << "\x1B[31mIgrac nije kreiran jer je lista igraca popunjena.\033[0m" << endl;
		return os;
	}

};

class GreskaPretrage : public Greska {

	ostream& pisi(ostream& os) {
		os << "\x1B[31mIgrac nije pronadjen, proverite ime i indetnifikacioni broj\033[0m" << endl; //Postavljanje teksta greske u crvenoj boji //printf("\x1B[31mTexting\033[0m\t\t");
		return os;
	}

};

class GreskaPrijave : public Greska {

	ostream& pisi(ostream& os) {
		os << "\x1B[31mPotrebno je da se ulugujete u svoj nalog ili da kreirati novi da bi ste odabrali neku igru.\033[0m" << endl;
		return os;
	}

};

class GreskaPovecanjeBalansa : public Greska {

	ostream& pisi(ostream& os) {
		os << "\x1B[31mPotrebno je da se ulugujete u svoj nalog ili da kreirati novi da bi promenili balans.\033[0m" << endl;
		return os;
	}

};

class GreskaUnosKaraktera : public Greska {

	ostream& pisi(ostream& os) {
		os << "\x1B[31mDozvoljeni su samo brojevi.\033[0m" << endl;
		return os;
	}

};

class GreskaBudzet : public Greska {

	ostream& pisi(ostream& os) {
		os << "\x1B[31mBudzet kazina je ispod dozvoljene granice(minimum 500).\033[0m" << endl;
		return os;
	}

};

class GreskaBalans : public Greska {

	ostream& pisi(ostream& os) {
		os << "\x1B[31mNema te dovoljno novca na racunu da bi odabrali igru(minimum je 100).\033[0m" << endl;
		return os;
	}

};

class GreskaKarakterVelicina : public Greska {

	ostream& pisi(ostream& os) {
		os << "\x1B[31mDozvoljeni su samo brojevi i moraju biti unutar granice niza.\033[0m" << endl;
		return os;
	}

};

class GreskaOdabirBroja : public Greska {

	ostream& pisi(ostream& os) {
		os << "\x1B[31mBroj koji ste odabrali se ne nalazi u nizu raspolozivih brojeva za rulet. Pokusaj te ponovo.\033[0m" << endl;
		return os;
	}

};

class GreskaOdabirBalans : public Greska {

	ostream& pisi(ostream& os) {
		os << "\x1B[31mNemate dovoljno novca na racunu da bi pokrili gubitke u slucaju da ne pogodite brojeve.\033[0m" << endl;
		return os;
	}

};

class GreskaListaSkorovaPuna : public Greska {

	ostream& pisi(ostream& os) {
		os << "\x1B[31mNazalost lista skorova je puna, nije zabelezen vas skor\033[0m" << endl; //Postavljanje teksta greske u crvenoj boji //printf("\x1B[31mTexting\033[0m\t\t");
		return os;
	}

};

class GreskaIzborBoje : public Greska {

	ostream& pisi(ostream& os) {
		os << "\x1B[31mBoju koju ste izabrali nije validna. Dozvoljene su samo \"r\"(crvena) ili \"r\"(crna).\033[0m" << endl; //Postavljanje teksta greske u crvenoj boji //printf("\x1B[31mTexting\033[0m\t\t");
		return os;
	}

};

class GreskaBojaBalans : public Greska {

	ostream& pisi(ostream& os) {
		os << "\x1B[31mNemate dovoljno novca na racunu da bi pokrili gubitke u slucaju da ne pogodite boju.\033[0m" << endl;
		return os;
	}

};

class GreskaBJBalans : public Greska {

	ostream& pisi(ostream& os) {
		os << "\x1B[31mNemate dovoljno novca na racunu da bi nastavili sa igrom(minimum je 50).\033[0m" << endl;
		return os;
	}

};

class GreskaUnosBrojeva : public Greska {

	ostream& pisi(ostream& os) {
		os << "\x1B[31mUnos nesme biti broj.\033[0m" << endl;
		return os;
	}

};

bool brojStringValidacija(string a);
bool brojValidacija(string a);

class Igrac {
public:
	int ind_broj;
	string ime;
	double balans;
	static Igrac** lista_igraca;
	static int broj_igraca;


public:
	Igrac();

	void unosImena();

	void unosBalansa();

	void kreiranjeIB();
	void unosIB();

	int prikaziIndentifikator();

	string prikaziIme();

	double prikaziBalans();
};

Igrac* pretraga(string, int);//Funkcija za pretragu i vracenje igraca

class Skor {
public:
	double rezultat;
	string igrac;
	int id_igrac;

public:
	Skor();
	Skor(string, double, int);
	string dohvatiIgrac();
	double dohvatiRezultat();

	void postaviIgrac();
	void postaviRezultat(int);
	void postaviID();


};

class Igra : public Skor {
public:
	string igra;
	Skor** lista_skorova;
	int broj_elemenata_skor;


public:
	Igra();
	void listaSkorova(Igrac*);
	string nazivIgre();
	Igra& operator-(Skor);
	virtual void zapocniIgru(Igrac*) = 0;
	void sortirajSkor();
	virtual void postaviSkor(Igrac*, int) = 0;


};


class PseudoRulet : public Igra {
public:
	int rezultat;
	int* brojevi;
	int broj_elemenata_brojeva;
	bool* odabir;
	char boja;
	bool paran;
public:
	PseudoRulet();
	void zapocniIgru(Igrac*);
	void stampajNiz();
	friend void odabirBroja(PseudoRulet*, Igrac*);
	void rulet(Igrac*, int);
	void postaviSkor(Igrac*, int);
	void resetuj();

	friend void odabirBoje(PseudoRulet*, Igrac*);
	friend char proveraBoje(char);
	void ruletBoja(Igrac*, char);

	void stampajtf();
};

struct spil {
	int broj;
	int ponavljanje;
};

class BlackJack : public Igra {
	int rezultat_igrac;
	int rezultat_racunar;
	spil karte[52];
	int broj_karata;
	int igrac[9]{ 0 };
	int racunar[9]{ 0 };
	int broj_karata_igrac;
	int broj_karata_racunar;
public:
	BlackJack();
	void zapocniIgru(Igrac*);
	void igranje(BlackJack*, Igrac*);
	int uzmiKartu();
	void resetuj();
	void stampanjeRukuIgraca();
	void stampanjeRukuRacunara();
	void postaviSkor(Igrac*, int);
};


class Kazino {
public:
	static Igra** lista_igara;
	static int broj_elemenata_liste;
	static double budzet;

public:
	double dohvatiBudzet();
	void dodajIgru();
	void prikazListeIgara();
	void povecanjaBalansaIgraca(Igrac*);
	void povecanjaBudzetKazina();
	void odabirIgre();

};

#endif