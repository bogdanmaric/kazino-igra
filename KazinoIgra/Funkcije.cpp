#include "Funkcije.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string> 

using namespace std;

int odgovor;

void pocetak() {
	cout << "(1) Igraj na broj" << endl;
	cout << "(2) Igraj na boju" << endl;
	cout << "(3) Prikaz tabele skora" << endl;
	cout << "(4) Povratak u glavni meni" << endl;
	cout << "Odgovor: ";
	cin >> odgovor;

	while (proveraOdgovora(odgovor)) {
		cout << "Odgovor: ";
		cin >> odgovor;
	}
	cout << endl;
}


void pocetakBJ() {
	cout << "(1) Zapocni igru" << endl;
	cout << "(2) Prikaz tabele skora" << endl;
	cout << "(3) Povratak u glavni meni" << endl;
	cout << "Odgovor: ";
	cin >> odgovor;

	while (proveraOdgovora(odgovor)) {
		cout << "Odgovor: ";
		cin >> odgovor;
	}
	cout << endl;
}


bool proveraOdgovora(double odg, bool g) {
	try {
		if (!cin) {
			if (g)
				throw(GreskaUnosKaraktera());
			else {
				cout << endl;
				cin.clear();
				cin.ignore(100, '\n');
				return true;
			}
		}
		else
			return false;
	}
	catch (GreskaUnosKaraktera& g) {
		cout << endl;
		cout << "\x1B[31mGreska: \033[0m" << g;
		cin.clear();
		cin.ignore(100, '\n');
		return true;
	}
}


Igrac::Igrac() {
	kreiranjeIB();
	unosImena();
	unosBalansa();
}


bool brojStringValidacija(string a) {
	for (unsigned i = 0; i < a.length(); i++)
		if (isdigit(a[i]))
			return false;
	return true;
}


bool brojValidacija(string a) {
	for (unsigned i = 0; i < a.length(); i++)
		if (!isdigit(a[i]))
			return false;
	return true;
}


void Igrac::unosImena() {
	while (true) {
		cout << "Unesite vase ime(max 80 karaktera): ";
		cin >> ime;
		if (ime.length() > 80) {
			cout << endl << "\x1B[31mIme: \033[0m" << "\"" << ime << "\"" << " \x1B[31msadrzi broj karatekara preko dozvoljene granice\033[0m" << endl << "Pokusajte ponovo." << endl << endl;
			continue;
		}
		else if (!brojStringValidacija(ime)) {
			cout << endl << "\x1B[31mIme: \033[0m" << "\"" << ime << "\"" << " \x1B[31m nesme da sadrzi broj.\033[0m" << endl << "Pokusajte ponovo." << endl << endl;
			continue;
		}
		break;
	}
	cout << "Ime " << "\"" << ime << "\"" << " je uspesno uneto!" << endl;
}


void Igrac::unosBalansa() {
	string vrednost;
	while (true) {
		try {
			cout << "Unesite svotu novca koju zelite da dodate: ";
			cin >> vrednost;
			if (brojValidacija(vrednost))
				break;
			else
				throw(GreskaUnosKaraktera());
		}
		catch (GreskaUnosKaraktera& g) { cout << endl << "\x1B[31mGreska: \033[0m" << g; }
	}

	balans = stoi(vrednost);
	cout << "Vas balans iznosi " << balans << " dinara" << endl;
}


void Igrac::kreiranjeIB() {
	cout << endl;

	if (broj_igraca == 0)
		ind_broj = 1;

	else
		ind_broj = broj_igraca + 1;

	cout << "Vas indetifikacioni broj je: " << ind_broj << endl;
}


string Igrac::prikaziIme() {
	return ime;
}


double Igrac::prikaziBalans() {
	return balans;
}


Igrac* pretraga(string ime, int broj) {

	for (int i = 0; i < Igrac::broj_igraca; i++) {
		if (ime == Igrac::lista_igraca[i]->ime && broj == Igrac::lista_igraca[i]->ind_broj)
			return Igrac::lista_igraca[i];

	}

	throw (GreskaPretrage());

}

double Kazino::budzet = 500;

double Kazino::dohvatiBudzet() {
	return budzet;
}

void Kazino::povecanjaBalansaIgraca(Igrac* igrac) {
	double balans = 0;
	cout << "Unesite svotu novca: ";
	cin >> balans;
	while (proveraOdgovora(balans)) {
		cout << "Unesite svotu novca: ";
		cin >> balans;
	}
	igrac->balans += balans;
	cout << "Uspesno ste povecali vas balans!" << endl;
	cout << "Trenutno stanje na vasem racunu je: " << igrac->balans << " dinara" << endl;
}

void Kazino::povecanjaBudzetKazina() {
	double balans = 0;
	cout << "Unesite svotu novca: ";
	cin >> balans;
	while (proveraOdgovora(balans)) {
		cout << "Unesite svotu novca: ";
		cin >> balans;
	}
	Kazino::budzet += balans;
	cout << "Uspesno ste povecali budzet kazina!" << endl;
	cout << "Trenutno stanje budzeta kazina je: " << Kazino::budzet << " dinara" << endl;
}

Skor::Skor() { igrac = ""; rezultat = 0; id_igrac = 0; }	

Skor::Skor(string ime, double re, int id) {
	igrac = ime;
	rezultat = re;
	id_igrac = id;
}

void Skor::postaviRezultat(int d) {
	rezultat += d;
}

string Skor::dohvatiIgrac() {
	return igrac;

}

double Skor::dohvatiRezultat() {
	return rezultat;
}

Igra::Igra() {
	lista_skorova = nullptr;
	broj_elemenata_skor = 0;
}

void Igra::listaSkorova(Igrac* igrac) {

	char separator = '#';
	int razmak = 8;
	if (broj_elemenata_skor > 0) {
		cout << "|" << setw(5) << "Mesto" << '|' << setw(10) << "Igraci" << '|' << right << setw(10) << "Skor" << '|' << endl;
		cout << "|-----" << setw(10) << "|----------" << right << setw(10) << "|----------|" << endl;
		for (int i = 0; i < broj_elemenata_skor; i++) {
			if (lista_skorova[i]->id_igrac != igrac->ind_broj) {
				cout << "|" << right << setw(5) << i + 1 << '|' << right << setw(10) << lista_skorova[i]->dohvatiIgrac() << '|' << right << setw(10) << lista_skorova[i]->dohvatiRezultat() << '|' << endl;
				cout << "|-----" << setw(10) << "|----------" << right << setw(10) << "|----------|" << endl;
			}
			else {
				cout << "|\033[1;47;35m" << right << setw(5) << i + 1 << '|' << right << setw(10) << lista_skorova[i]->dohvatiIgrac() << '|' << right << setw(10) << to_string((int)lista_skorova[i]->dohvatiRezultat()) << "\033[0m|" << endl;
				cout << "|-----" << setw(10) << "|----------" << right << setw(10) << "|----------|" << endl;
			}
		}
		cout << endl;
	}
	else
		cout << "\033[3;43;30mTabela je prazna\033[0m" << endl << endl;


}


void Igra::sortirajSkor() {

	int i, j;
	Skor* temp;
	for (i = 1; i < broj_elemenata_skor; i++)
	{
		temp = lista_skorova[i];
		j = i - 1;

		while (j >= 0 && lista_skorova[j]->dohvatiRezultat() < temp->rezultat)
		{
			lista_skorova[j + 1] = lista_skorova[j];
			j = j - 1;
		}
		lista_skorova[j + 1] = temp;
	}
}


PseudoRulet::PseudoRulet() {
	igra = "Pseudorulet";
	brojevi = new int[37];
	for (int i = 0; i < 37; brojevi[i] = i++);
	broj_elemenata_brojeva = 37;
	odabir = new bool[37]{ false };
	boja = 'r';
	lista_skorova = new Skor * [10];
	broj_elemenata_skor = 0;
}


void PseudoRulet::resetuj() {
	for (int i = 0; i < broj_elemenata_brojeva; odabir[i++] = false);
}


void PseudoRulet::stampajtf() {
	for (int i = 0; i < 37; i++)
		cout << odabir[i] << " ";
	cout << endl;
}


void PseudoRulet::postaviSkor(Igrac* ig, int d) {
	bool flag = false;
	if (broj_elemenata_skor < 10) {
		for (int i = 0; i < broj_elemenata_skor; i++)
			if (ig->ime == lista_skorova[i]->dohvatiIgrac() && ig->ind_broj == lista_skorova[i]->id_igrac) {
				lista_skorova[i]->postaviRezultat(d);
				flag = true;
				break;
			}
		if (!flag) {
			Skor* s = new Skor(ig->ime, d, ig->ind_broj);
			lista_skorova[broj_elemenata_skor] = s;
			lista_skorova[broj_elemenata_skor++];
		}
	}

	if (broj_elemenata_skor > 0) {
		sortirajSkor();
	}

	else
		throw(GreskaListaSkorovaPuna());
}


void PseudoRulet::rulet(Igrac* igrac, int duzina) {

	srand(time(NULL));
	int nasumican_broj, rezultat = 0;
	cout << "Broj koji je odabrao rulet je: ";
	nasumican_broj = rand() % (brojevi[broj_elemenata_brojeva - 1] - brojevi[0] + 1) + brojevi[0];
	cout << nasumican_broj << endl;

	try {
		for (int i = 0; i < broj_elemenata_brojeva; i++) {
			if (odabir[i] == true && brojevi[i] != nasumican_broj) {
				igrac->balans -= 100;
				Kazino::budzet += 100;
				rezultat -= 10;
			}

			else if (odabir[i] == true && brojevi[i] == nasumican_broj) {
				igrac->balans += 100;
				Kazino::budzet -= 100;
				rezultat += 10;
			}
		}
		postaviSkor(igrac, rezultat);

	}
	catch (GreskaListaSkorovaPuna& g) { cout << g << endl; }


}


void odabirBroja(PseudoRulet* c, Igrac* igrac) {
	int od = 1;
	cout << "\x1B[33mMozete postaviti ulog na vise od jednog broja.\nDobitak(Novcani: +100, Skor: +10), Gubitak(Novcani: -100, Skor: -10).\033[0m" << endl;
	while (true) {
		if (od <= 0)
			break;
		cout << "Brojevi koji su raspolozivi su:" << endl;
		c->stampajNiz();
		cout << endl;
		while (true) {

			try {
				cout << "Igrac: " << igrac->ime << endl;
				cout << "Balans: " << igrac->balans << " dinara" << endl << endl;
				if (igrac->balans < 100)
					throw (GreskaOdabirBalans());
				if (Kazino::budzet < 500)
					throw (GreskaBudzet());
				int duzina_unos, broj;
				cout << "Koliko brojeva zelite da odaberete?" << endl;
				cout << "Odgovor: ";
				cin >> duzina_unos;

				if (duzina_unos * 100 > igrac->balans)
					throw (GreskaOdabirBalans());
				if (!proveraOdgovora(duzina_unos, false) && duzina_unos <= c->broj_elemenata_brojeva) {
					for (int i = 0; i < duzina_unos; i++) {

						try {
							while (true) {
								cout << "Unesite broj(" << i + 1 << "): ";
								cin >> broj;
								if (!proveraOdgovora(broj))
									break;
								else
									continue;
							}
							cout << endl;

							int flag = false;
							for (int j = 0; j < c->broj_elemenata_brojeva; j++) {
								if (c->brojevi[j] == broj) {
									c->odabir[j] = true;
									flag = true;
									break;
								}

							}

							if (!flag) {
								throw(GreskaOdabirBroja());
							}
						}
						catch (GreskaOdabirBroja& g) { cout << "\x1B[31mGreska: \033[0m" << g; i--; }

					}

					c->rulet(igrac, duzina_unos);
					c->resetuj();

					for (int i = 0; i < c->broj_elemenata_skor; i++)
						if (igrac->ime == c->lista_skorova[i]->dohvatiIgrac() && igrac->ind_broj == c->lista_skorova[i]->id_igrac) {
							cout << "Igrac: " << c->lista_skorova[i]->dohvatiIgrac() << endl;
							cout << "Skor: " << c->lista_skorova[i]->dohvatiRezultat() << endl;
							break;
						}

					cout << endl;

					while (true) {
						cout << "Zelite li ponovo da igrate(0 i negativni brojevi - ne, pozitivni brojevi - da): ";
						cin >> od;

						if (!proveraOdgovora(od))
							break;
						else
							continue;
					}
					if (od) {
						cout << "#################################################################################" << endl;
						c->stampajNiz();
						cout << endl;
						continue;
					}
					else
						break;
				}
				else
					throw(GreskaKarakterVelicina()); //Nije dozvoljena velicina
			}
			catch (GreskaKarakterVelicina& g) { cout << "\x1B[31mGreska: \033[0m" << g; } //Obrada greske
			catch (GreskaOdabirBalans& g) { cout << "\x1B[31mGreska: \033[0m" << g; od = 0; break; } //Obrada greske
			catch (GreskaBudzet& g) { cout << "\x1B[31mGreska: \033[0m" << g; od = 0; break; } //Obrada greske

		}
	}
}

void PseudoRulet::zapocniIgru(Igrac* igrac) {
	cout << endl;
	int rad = true;
	while (rad) {
		cout << "\033[3;44;30m############################\033[0m" << endl;
		cout << "\033[3;44;30m#\033[0m";
		cout << "\033[3;104;30mDobro dosli u Pseudorulet!\033[0m";
		cout << "\033[3;44;30m#\033[0m" << endl;
		cout << "\033[3;44;30m############################\033[0m" << endl << endl;

		cout << "Broj dosutpnih mesta za skor (" << Igra::broj_elemenata_skor << "/10)" << endl;
		cout << "Budzet kazina: " << Kazino::budzet << " dinara" << endl << endl;

		cout << "Igrac: " << igrac->ime << endl;
		cout << "Balans: " << igrac->balans << " dinara" << endl;
		pocetak();

		switch (odgovor) {

		case 1:
			odabirBroja(this, igrac);
			break;

		case 2:
			odabirBoje(this, igrac);
			break;

		case 3:
			cout << "\033[3;104;30mTabela Skora Pseudoruleta\033[0m" << endl;
			listaSkorova(igrac);
			break;

		case 4:
			cout << "\033[3;100;30m***Pseudo rulet je zatvoren***\033[0m" << endl;
			rad = false;
			break;

		default:
			cout << "\x1B[31mGreska: Broj koji ste uneli nije ponudjen.\033[0m";
			cout << endl;
		}
	}
}

void PseudoRulet::stampajNiz() {
	for (int i = 0; i < broj_elemenata_brojeva; i++) {
		if (i == broj_elemenata_brojeva - 1) {
			cout << i << endl;
			continue;
		}

		cout << i << ", ";
	}
}

char proveraBoje(char b) {
	return b;
}

void PseudoRulet::ruletBoja(Igrac* igrac, char b) {
	char rboja;
	srand(time(NULL));
	int nasumican_broj, rezultat = 0;
	cout << "Broj koji je odabrao rulet je: ";
	nasumican_broj = rand() % (brojevi[broj_elemenata_brojeva - 1] - brojevi[0] + 1) + brojevi[0];
	cout << nasumican_broj << endl;

	if (nasumican_broj != 0)
		if (nasumican_broj % 2 == 0)
			rboja = 'b';
		else
			rboja = 'r';
	else
		rboja = 'z';


	try {
		if (b != rboja) {
			igrac->balans -= 100;
			Kazino::budzet += 100;
			rezultat -= 10;
		}

		else {
			igrac->balans += 100;
			Kazino::budzet -= 100;
			rezultat += 10;
		}
		postaviSkor(igrac, rezultat);

	}
	catch (GreskaListaSkorovaPuna& g) { cout << g << endl; }

}

void odabirBoje(PseudoRulet* c, Igrac* igrac) {
	int od = 1;
	bool flag = true;
	while (flag) {
		if (od <= 0)
			break;
		while (true) {
			cout << endl;
			cout << "Igrac: " << igrac->ime << endl;
			cout << "Balans: " << igrac->balans << " dinara" << endl << endl;

			try {
				if (100 > igrac->balans)
					throw (GreskaBojaBalans());
				if (Kazino::budzet < 500)
					throw (GreskaBudzet());

			}
			catch (GreskaBojaBalans& g) { cout << "\x1B[31mGreska: \033[0m" << g; flag = false; break; }
			catch (GreskaBudzet& g) { cout << "\x1B[31mGreska: \033[0m" << g; flag = false; break; }

			cout << "\x1B[33m\nDobitak(Novcani: +100, Skor: +10), Gubitak(Novcani: -100, Skor: -10).\033[0m" << endl;
			char boja = 'r';
			while (true) {
				cout << "Koju boju zelite da izaberete(r - crvena, b - crna):" << endl;
				cout << "Odgovor: ";
				cin >> boja;
				cout << endl;

				try {
					if (boja != 'r' && boja != 'b')
						throw(GreskaIzborBoje());
					else
						break;
				}
				catch (GreskaIzborBoje& g) { cout << "\x1B[31mGreska: \033[0m" << g; }
			}

			c->ruletBoja(igrac, boja);

			for (int i = 0; i < c->broj_elemenata_skor; i++)
				if (igrac->ime == c->lista_skorova[i]->dohvatiIgrac() && igrac->ind_broj == c->lista_skorova[i]->id_igrac) {
					cout << "Igrac: " << c->lista_skorova[i]->dohvatiIgrac() << endl;
					cout << "Balans: " << igrac->balans << " dinara" << endl;
					cout << "Skor: " << c->lista_skorova[i]->dohvatiRezultat() << endl;
					break;
				}

			cout << endl;


			while (true) {
				cout << "Zelite li ponovo da igrate(0 i negativni brojevi - ne, pozitivni brojevi - da): ";
				cin >> od;

				if (!proveraOdgovora(od))
					break;
				else
					continue;
			}

			if (od) {
				cout << "#################################################################################" << endl;
				continue;
			}
			else
				break;
		}

	}

}


BlackJack::BlackJack() {
	igra = "BlackJack";
	lista_skorova = new Skor * [10];
	broj_elemenata_skor = 0;
	broj_karata = 52;

	for (int i = 0, s = 0; i < broj_karata; i++, s++) {
		if (s % 13 == 0)
			s = 0;
		karte[i] = spil{ s + 1, 0 };
	}

	rezultat_igrac = 0;
	rezultat_racunar = 0;
	broj_karata_igrac = 0;
	broj_karata_racunar = 0;

}

void BlackJack::zapocniIgru(Igrac* igrac) {
	cout << endl;
	int rad = true;
	while (rad) {
		cout << "\033[3;100;30m############################\033[0m" << endl;
		cout << "\033[3;100;30m##\033[0m";
		cout << "\033[2;47;35mDobro dosli u BlackJack!\033[0m";
		cout << "\033[3;100;30m##\033[0m" << endl;
		cout << "\033[3;100;30m############################\033[0m" << endl;

		cout << endl;

		cout << "Broj dosutpnih mesta za skor (" << Igra::broj_elemenata_skor << "/10)" << endl;
		cout << "Budzet kazina: " << Kazino::budzet << " dinara" << endl << endl;

		cout << "Igrac: " << igrac->ime << endl;
		cout << "Balans: " << igrac->balans << " dinara" << endl;

		pocetakBJ();

		switch (odgovor) {

		case 1:
			igranje(this, igrac);
			break;

		case 2:
			cout << "\033[2;47;35mTabela Skora BlackJack-a\033[0m" << endl;
			listaSkorova(igrac);
			break;

		case 3:
			cout << "\033[3;100;30m***BlackJack je zatvoren***\033[0m" << endl;
			rad = false;
			break;

		default:
			cout << "\x1B[31mGreska: Broj koji ste uneli nije ponudjen.\033[0m";
			cout << endl;
		}
	}
}

void BlackJack::igranje(BlackJack* b, Igrac* ig) {
	int odg, karta_igrac, karta_racunar, rezultat, skor;
	int odluka;
	srand(time(NULL));
	while (true) {
		resetuj();
		try {
			if (ig->balans < 50)
				throw(GreskaBJBalans());
			else if (Kazino::budzet < 500)
				throw(GreskaBudzet());
		}
		catch (GreskaBJBalans& g) { cout << "\x1B[31mGreska: \033[0m" << g; break; }
		catch (GreskaBudzet& g) { cout << "\x1B[31mGreska: \033[0m" << g; break; }
		cout << "\x1B[33mIgra se na devet rundi.\nDobitak(Novcani: +50, Skor: +10), Gubitak(Novcani: -50, Skor: -10), Nereseno(Novcani: 0, Skor: +5).\033[0m" << endl;

		for (int i = 0; i < 9; i++) {

			if (i + 1 == 9)
				cout << "###############\x1B[93mRunda(" + to_string(i + 1) + ") - zadnja runda\033[0m#############" << endl << endl;
			else
				cout << "###############\x1B[93mRunda(" + to_string(i + 1) + ")\033[0m#############" << endl << endl;

			if (i == 0) {
				karta_igrac = uzmiKartu();
				igrac[broj_karata_igrac++] = karta_igrac;
				rezultat_igrac += karta_igrac;


				//racunar
				if (rezultat_racunar < 125) {
					karta_racunar = uzmiKartu();
					racunar[broj_karata_racunar++] = karta_racunar;
					rezultat_racunar += karta_racunar;
				}
				else
					cout << "Racunar ne uzima kartu." << endl;

			}

			cout << "\x1B[36mIgrac: " << ig->ime << +"\033[0m" << endl;
			cout << "Karte: ";
			stampanjeRukuIgraca();
			cout << endl;
			cout << "Rezultat: " << rezultat_igrac;

			cout << endl << endl;

			cout << "\x1B[35mIgrac: Racunar\033[0m\n";
			cout << "Karte: ";
			stampanjeRukuRacunara();
			cout << endl;
			cout << "Rezultat: " << rezultat_racunar;

			cout << endl << endl;

			while (true) {
				cout << "Da li zelite da uzmete kartu ili ste zavrsili sa izvlacenjem(pozitiv broja - da, 0 ili negativan broj - ne): ";
				cin >> odg;

				if (!proveraOdgovora(odg))
					break;
				else
					continue;
			}
			cout << endl;

			if (odg > 0) {

				karta_igrac = uzmiKartu();
				igrac[broj_karata_igrac++] = karta_igrac;
				cout << "\x1B[36mKartu koju ste izvukli je: " << karta_igrac << "\033[0m" << endl;
				rezultat_igrac += karta_igrac;
			}
			else
				cout << "\x1B[36mNiste izvlacili kartu iz spila.\033[0m" << endl;

			if (rezultat_racunar < 17) {
				karta_racunar = uzmiKartu();
				racunar[broj_karata_racunar++] = karta_racunar;
				cout << "\x1B[35mKartu koju je racunar izvukao je: " << karta_racunar << "\033[0m" << endl;
				rezultat_racunar += karta_racunar;
			}
			else
				cout << "\x1B[35mRacunar nije izvlacio kartu iz spila.\033[0m" << endl;

			if (rezultat_igrac > 21 || rezultat_racunar > 21)
				break;
		}

		cout << "####################################" << endl << endl;

		if (rezultat_racunar > 21 && rezultat_igrac > 21) {
			cout << "\nRezultat je izjednacen!";
			rezultat = 2;
		}
		else if (rezultat_igrac > 21) {
			cout << "\nNazalost presli ste preko 21.";
			rezultat = 1;
		}
		else if (rezultat_racunar > 21) {
			cout << "\nCestitamo! Pobedili ste racunar jer je presao 21.";
			rezultat = 0;
		}
		else if (rezultat_igrac > rezultat_racunar) {
			cout << "\nCestitamo! Pobedili ste racunar jer imate bolji rezultat!";
			rezultat = 0;
		}
		else if (rezultat_igrac < rezultat_racunar) {
			cout << "\nNazalost racunar ima bolji rezultat.";
			rezultat = 1;
		}
		else if (rezultat_igrac == rezultat_racunar) {
			cout << "\nRezultat je izjednacen!";
			rezultat = 2;
		}

		try {
			if (rezultat == 0) {
				ig->balans += 50;
				Kazino::budzet -= 50;
				skor = 10;
			}

			else if (rezultat == 1) {
				ig->balans -= 50;
				Kazino::budzet += 50;
				skor = -10;
			}
			else {
				skor = 5;
			}

			postaviSkor(ig, skor);
		}
		catch (GreskaListaSkorovaPuna& g) { cout << g << endl; }

		cout << endl;

		for (int i = 0; i < b->broj_elemenata_skor; i++)
			if (ig->ime == b->lista_skorova[i]->dohvatiIgrac() && ig->ind_broj == b->lista_skorova[i]->id_igrac) {
				cout << "Igrac: " << b->lista_skorova[i]->dohvatiIgrac() << endl;
				cout << "Balans: " << ig->balans << " dinara" << endl;
				cout << "Skor: " << b->lista_skorova[i]->dohvatiRezultat() << endl;
				break;
			}

		cout << endl;

		while (true) {
			cout << "\nZelite li ponovo da igrate(pozitivni brojevi - da, 0 i negativni brojevi - ne): ";
			cin >> odg;

			if (!proveraOdgovora(odg))
				break;
			else
				continue;
		}
		if (odg) {
			cout << endl;
			continue;
		}
		else
			break;
	}
}

void BlackJack::stampanjeRukuIgraca() {
	for (int i = 0; i < broj_karata_igrac; i++) {
		if (i == broj_karata_igrac - 1 || broj_karata_igrac == 1)
			cout << igrac[i];
		else
			cout << igrac[i] << ", ";
	}
}


void BlackJack::stampanjeRukuRacunara() {
	for (int i = 0; i < broj_karata_racunar; i++) {
		if (i == broj_karata_racunar - 1 || broj_karata_racunar == 1)
			cout << racunar[i];
		else
			cout << racunar[i] << ", ";
	}

}

int BlackJack::uzmiKartu() {

	static int ciklus = 0;
	if (ciklus == 1) {
		srand(time(NULL) * 10000);
		ciklus = 0;
	}
	else {
		srand(time(NULL));
		ciklus++;
	}


	int nasumican_broj, karta_izvucena;
	while (true) {

		nasumican_broj = rand() % 52;
		if (karte[nasumican_broj].ponavljanje < 4) {
			karta_izvucena = karte[nasumican_broj].broj;
			return karta_izvucena;
		}
		else
			continue;
	}

}

void BlackJack::resetuj() {

	for (int i = 0; i < broj_karata; i++) {
		karte[i].ponavljanje = 0;
		if (i < 9) {
			igrac[i] = 0;
			racunar[i] = 0;
		}
	}

	rezultat_igrac = 0;
	rezultat_racunar = 0;
	broj_karata_igrac = 0;
	broj_karata_racunar = 0;
}


void BlackJack::postaviSkor(Igrac* ig, int d) {

	bool flag = false;
	if (broj_elemenata_skor < 10) {
		for (int i = 0; i < broj_elemenata_skor; i++)
			if (ig->ime == lista_skorova[i]->dohvatiIgrac() && ig->ind_broj == lista_skorova[i]->id_igrac) {
				lista_skorova[i]->postaviRezultat(d);
				flag = true;
				break;
			}
		if (!flag) {
			Skor* s = new Skor(ig->ime, d, ig->ind_broj);
			lista_skorova[broj_elemenata_skor] = s;
			lista_skorova[broj_elemenata_skor++];
		}
	}

	if (broj_elemenata_skor > 0) {
		sortirajSkor();
	}

	else
		throw(GreskaListaSkorovaPuna());

}


