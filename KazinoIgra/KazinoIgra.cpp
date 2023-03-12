
#include "Funkcije.h"
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;


//PRIPREMA PODATAKA
Igrac** Igrac::lista_igraca = new Igrac * [10];
int Igrac::broj_igraca = 0;

Igra** Kazino::lista_igara = new Igra * [2];
int Kazino::broj_elemenata_liste = 2;

static int odgovor;
static int kraj = false;



//INTERFEJS ZA KORISNIKA
void dobrodoslica() {
	cout << "\033[3;43;34m==================================================\033[0m" << endl;
	cout << "===\033[3;85;33m           DOBRO DOSLI U KAZINO            \033[0m===" << endl;
	cout << "\033[3;43;34m==================================================\033[0m\n\n";

}

void glavniMeni() {
	cout << "(1) Kreiranje/ulogovanje u nalog" << endl;
	cout << "(2) Izaberi igru" << endl;
	cout << "(3) Povecaj balans igraca" << endl;
	cout << "(4) Povecaj budzeta kazina" << endl;
	cout << "(5) Kraj igre" << endl;
	cout << "Odgovor: ";
	cin >> odgovor;

	while (proveraOdgovora(odgovor)) {
		cout << "Odgovor: ";
		cin >> odgovor;
	}
	cout << endl;
}

//OPCIJE GLAVNOG MENIJA
void kreiranjeNaloga() {
	cout << "(1) Kreiranje naloga" << endl;
	cout << "(2) Prijavljivanje na postojeci nalog" << endl;
	cout << "(3) Povratak u glavni meni" << endl;
	cout << "Odgovor: ";
	cin >> odgovor;
	while (proveraOdgovora(odgovor)) {
		cout << "Odgovor: ";
		cin >> odgovor;
	}


}

void biranjeIgre() {
	cout << "(1) Pseudo-rulet" << endl;
	cout << "(2) BlackJack" << endl;
	cout << "(3) Povratak u glavni meni" << endl;
	cout << "Odgovor: ";
	cin >> odgovor;

	while (proveraOdgovora(odgovor)) {
		cout << "Odgovor: ";
		cin >> odgovor;
	}

}

void krajIgre() {
	cout << "\033[3;104;30mHvala vam na poseti!\033[0m" << endl;
	cout << "\033[3;100;30m***Kazino je zatvoren***\033[0m";
}

Igrac* igrac = nullptr;

int main()
{
	Kazino::lista_igara[0] = new PseudoRulet();
	Kazino::lista_igara[1] = new BlackJack();
	Kazino k;
	k.dohvatiBudzet();

	while (!kraj) {

		dobrodoslica();
		cout << "Broj dosutpnih mesta za registraciju (" << Igrac::broj_igraca << "/10)" << endl;
		cout << "Budzet kazina je: " << k.dohvatiBudzet() << " dinara" << endl << endl;

		if (igrac != nullptr) {
			cout << "Igrac: " << igrac->prikaziIme() << endl;
			cout << "Balans: " << igrac->prikaziBalans() << " dinara" << endl;
		}

		glavniMeni();
		switch (odgovor) {

		case 1:
			kreiranjeNaloga();

			switch (odgovor) {
			case 1:
				try {
					if (Igrac::broj_igraca == 10)
						throw(GreskaListaIgraca());
					igrac = new Igrac();
					Igrac::lista_igraca[Igrac::broj_igraca++] = igrac;
					cout << endl << "Dobro dosli " << igrac->prikaziIme() << "!" << endl;
				}
				catch (GreskaListaIgraca& g) {
					cout << "\x1B[31mGreska: \033[0m" << g;
				}
				break;
				{

			case 2:
				string ime;
				string broj;
				cout << endl;

				try {
					while (true) {
						try {
							cout << "Unesite ime vaseg naloga: ";
							cin >> ime;
							if (!brojStringValidacija(ime))
								throw(GreskaUnosBrojeva());
							else
								break;
						}
						catch (GreskaUnosBrojeva& g) { cout << endl << "\x1B[31mGreska: \033[0m" << g; }
					}

					while (true) {
						try {
							cout << "Unesite indetifikacioni broj vaseg naloga: ";
							cin >> broj;
							if (brojValidacija(broj))
								break;
							else
								throw(GreskaUnosBrojeva());
						}
						catch (GreskaUnosBrojeva& g) { cout << endl << "\x1B[31mGreska: \033[0m" << g; }
					}

					igrac = pretraga(ime, stoi(broj));
				}
				catch (GreskaPretrage& g) { cout << endl << "\x1B[31mGreska: \033[0m" << g; }
				break;
				}
			case 3:
				break;
			default:
				cout << endl;
				cout << "\x1B[31mBroj koji ste uneli nije ponudjen.\033[0m";
				cout << endl;
			}
			break;

		case 2:
			try {
				if (igrac == nullptr)
					throw(GreskaPrijave());
				if (k.dohvatiBudzet() < 500)
					throw(GreskaBudzet());
				else if (igrac->balans < 100)
					throw (GreskaBalans());
				biranjeIgre();	//Odraditi pseudo rulet
			}
			catch (GreskaPrijave& g) { cout << "\x1B[31mGreska: \033[0m" << g; break; }
			catch (GreskaBudzet& g) { cout << "\x1B[31mGreska: \033[0m" << g; break; }
			catch (GreskaBalans& g) { cout << "\x1B[31mGreska: \033[0m" << g; break; }

			switch (odgovor) {

			case 1:
				k.lista_igara[0]->zapocniIgru(igrac);
				break;

			case 2:
				k.lista_igara[1]->zapocniIgru(igrac);
				break;

			case 3:
				break;

			default:
				cout << endl;
				cout << "\x1B[31mBroj koji ste uneli nije ponudjen.\033[0m";
			}
			break;

		case 3:

			try {
				if (igrac != nullptr)
					k.povecanjaBalansaIgraca(igrac);
				else
					throw(GreskaPovecanjeBalansa());
			}
			catch (GreskaPovecanjeBalansa& g) {
				cout << "\x1B[31mGreska: \033[0m" << g;
			}
			break;

		case 4:
			k.povecanjaBudzetKazina();
			break;

		case 5:
			krajIgre();
			kraj = true;
			break;

		default:
			cout << "\x1B[31mGreska: Broj koji ste uneli nije ponudjen.\033[0m";
			cout << endl;
		}

	}

}