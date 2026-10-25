#include<iostream>  
#include<string>
#include<fstream>
using namespace std;

class ISerializable {
    public:
    virtual string serialize() = 0;
    virtual void saveToFile(string nazwaPliku) = 0;
};

void drukuj(ISerializable* obj) {
    cout << obj->serialize() << endl;
}

class osoba : public ISerializable {
    private:
    protected:
    string imie;
    string nazwisko;
    int numerindeksu;
    public:
    string getImie() {
         return imie;
         }
    string getNazwisko() {
         return nazwisko; 
        }
    int getNumerIndeksu() {
         return numerindeksu; 
        }
    void setImie(string noweImie) {
         imie = noweImie; 
        }
    void setNazwisko(string noweNazwisko) {
         nazwisko = noweNazwisko;
         }
    void setNumerIndeksu(int nowyNumerIndeksu) {
         numerindeksu = nowyNumerIndeksu;
         }
    string serialize() {
        return "Osoba: " + imie + " " + nazwisko + " o indeksie " + to_string(numerindeksu);
    }
    virtual void saveToFile(string nazwaPliku) {
        ofstream plik(nazwaPliku);
        plik << "Imie: " << imie << endl;
        plik << "Nazwisko: " << nazwisko << endl;
        plik << "Numer indeksu: " << numerindeksu << endl;
        plik << serialize() << endl;
        plik.close();
    }
    virtual void drukuj() {
        cout << "Imie: " << imie << endl;
        cout << "Nazwisko: " << nazwisko << endl;
        cout << "Numer indeksu: " << numerindeksu << endl;
        cout << serialize() << endl;
    }
};

class student : public osoba {
    public:
    string serialize() {
        return "Student: " + getImie() + " " + getNazwisko() + " o indeksie " + to_string(getNumerIndeksu());
    }
    void drukuj() {
        cout << "Imie: " << getImie() << endl;
        cout << "Nazwisko: " << getNazwisko() << endl;
        cout << "Numer indeksu: " << getNumerIndeksu() << endl;
        cout << serialize() << endl;
    }
};

class studentZaoczny : public student {
    public:
    string serialize() {
        return "Student zaoczny: " + getImie() + " " + getNazwisko() + " o indeksie " + to_string(getNumerIndeksu());
    }
    void drukuj() {
        cout << "Imie: " << getImie() << endl;
        cout << "Nazwisko: " << getNazwisko() << endl;
        cout << "Numer indeksu: " << getNumerIndeksu() << endl;
        cout << serialize() << endl;
    }
};

class pracowmik : public osoba {
    public:
    string serialize() {
        return "Pracownik: " + getImie() + " " + getNazwisko() + " o indeksie " + to_string(getNumerIndeksu());
    }
    void drukuj() {
        cout << "Imie: " << getImie() << endl;
        cout << "Nazwisko: " << getNazwisko() << endl;
        cout << "Numer indeksu: " << getNumerIndeksu() << endl;
        cout << serialize() << endl;
    }
};

class ListaObecnosci : public ISerializable {
    private:
    osoba* grupa[10];
    int obecny[10];
    int liczbaosob = 0;
    public:
    void dodajOsobe(osoba* nowaosoba) {
        if (liczbaosob < 10) {
            grupa[liczbaosob] = nowaosoba;
            obecny[liczbaosob] = 0;
            liczbaosob++;
        }
    }
    void ustawobecnosc(string nazwiskoSprawdzane) {
        for (int i = 0; i < liczbaosob; i++) {
            if (grupa[i]->getNazwisko() == nazwiskoSprawdzane) {
                obecny[i] = 1;
                break;
            }
        }
    }
    void wyswietllisteobecnosci() {
        cout << "\nLista obecnosci" << endl;
        for (int i = 0; i < liczbaosob; i++) {
            if (grupa[i] != nullptr) {
                cout << grupa[i]->getNazwisko() << " " << grupa[i]->getImie() << " - " << (obecny[i] ? "1" : "0") << endl;
            }
        }
    }
    string serialize() {
        string wynik = "Lista obecnosci:\n";
        for (int i = 0; i < liczbaosob; i++) {
            if (grupa[i] != nullptr) {
                wynik += grupa[i]->getNazwisko() + " " + grupa[i]->getImie() + " - " + (obecny[i] ? "1" : "0") + "\n";
            }
        }
        return wynik;
    }
    void saveToFile(string nazwaPliku) {
        ofstream plik(nazwaPliku);
        plik << serialize();
        plik.close();
    }
    osoba* znajdzOsobe(string nazwisko) {
        for (int i = 0; i < liczbaosob; i++) {
            if (grupa[i]->getNazwisko() == nazwisko)
                return grupa[i];
        }
        return nullptr;
    }
    void edycjadanych() {
        string nazwiskodozmienienia, imie, nazwisko;
        int indeks, opcje;
        cout << "Podaj nazwisko osoby, ktorej dane chcesz zmienic: ";
        cin >> nazwiskodozmienienia;
        for (int i = 0; i < liczbaosob; i++) {
            if (grupa[i]->getNazwisko() == nazwiskodozmienienia) {
                cout << "Co chcesz zmienic: 1.Imie \n2.Nazwisko \n3.Indeks \n4.Obecnosc ";
                cin >> opcje;
                if (opcje == 1) {
                     cout << "Podaj nowe imie: ";
                      cin >> imie; grupa[i]->setImie(imie);
                     }
                else if (opcje == 2) {
                     cout << "Podaj nowe nazwisko: ";
                      cin >> nazwisko;
                       grupa[i]->setNazwisko(nazwisko);
                     }
                else if (opcje == 3) {
                     cout << "Podaj nowy indeks: ";
                      cin >> indeks; 
                      grupa[i]->setNumerIndeksu(indeks);
                     }
                else if (opcje == 4) { 
                    cout << "Zmien obecnosc: 0 lub 1 ";
                     cin >> obecny[i];
                     }
                else { 
                    cout << "Nie ma takiej opcji" << endl;
                 }
                return;
            }
        }
        cout << "Nie znaleziono takiej osoby" << endl;
    }
    void usuwanieosob() {
        string nazwisko;
        cout << "Podaj nazwisko osoby, ktora chcesz usunac: ";
        cin >> nazwisko;
        for (int i = 0; i < liczbaosob; i++) {
            if (grupa[i]->getNazwisko() == nazwisko) {
                grupa[i] = grupa[liczbaosob - 1];
                obecny[i] = obecny[liczbaosob - 1];
                liczbaosob--;
                return;
            }
        }
        cout << "Nie ma takiego nazwiska" << endl;
    }
};

class InterfejsUzytkownika {
    private:
    osoba* katalog;
    int* liczbaosob;
    ListaObecnosci* listy;
    int* liczbaList;
    int aktywnaLista;

    void dodajDoKatalogu() {
        string imie, nazwisko;
        int indeks;
        cout << "Podaj imie: ";
         cin >> imie;
        cout << "Podaj nazwisko: "; 
        cin >> nazwisko;
        cout << "Podaj indeks: ";
         cin >> indeks;
        katalog[*liczbaosob].setImie(imie);
        katalog[*liczbaosob].setNazwisko(nazwisko);
        katalog[*liczbaosob].setNumerIndeksu(indeks);
        (*liczbaosob)++;
        cout << "Dodano do katalogu." << endl;
    }
    void utworzListe() {
        if (*liczbaList < 5) {
            (*liczbaList)++;
            aktywnaLista = (*liczbaList) - 1;
            cout << "Utworzono liste nr " << *liczbaList << endl;
        } else {
            cout << "Osiagnieto limit list." << endl;
        }
    }
    void wybierzListe() {
        cout << "Dostepne listy: 1-" << *liczbaList << ". Wybierz: ";
        int nr; cin >> nr;
        if (nr >= 1 && nr <= *liczbaList) {
            aktywnaLista = nr - 1;
            cout << "Wybrano liste " << nr << endl;
        } else {
            cout << "Nieprawidlowy numer." << endl;
        }
    }
    void dodajNaListe() {
        cout << "Osoby w katalogu:" << endl;
        for (int i = 0; i < *liczbaosob; i++)
            cout << i + 1 << ". " << katalog[i].getNazwisko() << " " << katalog[i].getImie() << endl;
        cout << "Wybierz numer osoby: ";
        int nr; cin >> nr;
        if (nr >= 1 && nr <= *liczbaosob) {
            listy[aktywnaLista].dodajOsobe(&katalog[nr - 1]);
            cout << "Dodano na liste." << endl;
        }
    }
    void zapiszDoPliku() {
        string nazwaPliku;
        cout << "Podaj nazwe pliku: ";
        cin >> nazwaPliku;
        cout << "Co chcesz zapisac?" << endl;
        cout << "9.1 - Cala lista obecnosci" << endl;
        cout << "9.2 - Konkretny student" << endl;
        int wyborZapisu; cin >> wyborZapisu;
        if (wyborZapisu == 1) {
            listy[aktywnaLista].saveToFile(nazwaPliku);
            cout << "Zapisano liste do pliku " << nazwaPliku << endl;
        } else if (wyborZapisu == 2) {
            string nazwisko;
            cout << "Podaj nazwisko studenta: ";
            cin >> nazwisko;
            osoba* znaleziony = listy[aktywnaLista].znajdzOsobe(nazwisko);
            if (znaleziony != nullptr) {
                znaleziony->saveToFile(nazwaPliku);
                cout << "Zapisano studenta " << nazwisko << " do pliku " << nazwaPliku << endl;
            } else {
                cout << "Nie znaleziono studenta o nazwisku " << nazwisko << endl;
            }
        } else {
            cout << "Nie ma takiej opcji." << endl;
        }
    }

    public:
    InterfejsUzytkownika(osoba* kat, int* lOsob, ListaObecnosci* lst, int* lList)
        : katalog(kat), liczbaosob(lOsob), listy(lst), liczbaList(lList), aktywnaLista(-1) {}

    void uruchom() {
        int wybor;
        do {
            cout << "1-Dodaj osobe do katalogu" << endl;
            cout << "2-Utworz nowa liste" << endl;
            cout << "3-Wybierz liste" << endl;
            cout << "4-Dodaj osobe z katalogu na liste" << endl;
            cout << "5-Sprawdz obecnosc" << endl;
            cout << "6-Wyswietl liste obecnosci" << endl;
            cout << "7-Edycja danych" << endl;
            cout << "8-Usuwanie osoby z listy" << endl;
            cout << "9-Zapisz do pliku" << endl;
            cout << "0-Wyjscie" << endl;
            if (aktywnaLista >= 0)
                cout << "(aktywna lista: " << aktywnaLista + 1 << ")" << endl;
            cout << "Wybierz opcje: ";
            cin >> wybor;

            if (wybor == 1) dodajDoKatalogu();

            else if (wybor == 2) utworzListe();

            else if (wybor == 3) wybierzListe();

            else if (wybor == 4) {
                if (aktywnaLista < 0) { 
                    cout << "Najpierw wybierz liste (opcja 3)." << endl;
                     continue;
                     }
                dodajNaListe();
            }
            else if (wybor == 5) {
                if (aktywnaLista < 0) {
                     cout << "Najpierw wybierz liste." << endl;
                      continue; 
                    }
                string nazwiskoDoSprawdzenia;
                cout << "Podaj nazwisko osoby, ktora jest obecna: ";
                cin >> nazwiskoDoSprawdzenia;
                listy[aktywnaLista].ustawobecnosc(nazwiskoDoSprawdzenia);
            }
            else if (wybor == 6) {
                if (aktywnaLista < 0) { 
                    cout << "Najpierw wybierz liste." << endl;
                     continue; 
                    }
                listy[aktywnaLista].wyswietllisteobecnosci();
            }
            else if (wybor == 7) {
                if (aktywnaLista < 0) {
                     cout << "Najpierw wybierz liste." << endl;
                      continue; 
                    }
                listy[aktywnaLista].edycjadanych();
            }
            else if (wybor == 8) {
                if (aktywnaLista < 0) {
                     cout << "Najpierw wybierz liste." << endl;
                      continue; 
                    }
                listy[aktywnaLista].usuwanieosob();
            }
            else if (wybor == 9) {
                if (aktywnaLista < 0) {
                     cout << "Najpierw wybierz liste." << endl; 
                     continue; 
                    }
                zapiszDoPliku();
            }
            else if (wybor == 0) 
            cout << "Koniec programu." << endl;
            else 
            cout << "Nie ma takiej opcji." << endl;
        } while (wybor != 0);
    }
};

int main() {
    osoba katalog[10];
    int liczbaosob = 0;
    ListaObecnosci listy[5];
    int liczbaList = 0;

    osoba os1;
    os1.setImie("Michal");
    os1.setNazwisko("Nowogrodzki");
    os1.setNumerIndeksu(12345);

    student st1;
    st1.setImie("Anna");
    st1.setNazwisko("Kowalska");
    st1.setNumerIndeksu(67890);

    pracowmik pr1;
    pr1.setImie("Jan");
    pr1.setNazwisko("Wisniewski");
    pr1.setNumerIndeksu(11111);

    studentZaoczny sz1;
    sz1.setImie("Piotr");
    sz1.setNazwisko("Zielinski");
    sz1.setNumerIndeksu(22222);

    osoba* tab[4];
    tab[0] = &os1;
    tab[1] = &st1;
    tab[2] = &pr1;
    tab[3] = &sz1;

    tab[0]->drukuj();
    tab[1]->drukuj();
    tab[2]->drukuj();
    tab[3]->drukuj();

    cout << "\nprzez interfejs ISerializable" << endl;
    drukuj(&os1);
    drukuj(&st1);
    drukuj(&pr1);
    drukuj(&sz1);

    InterfejsUzytkownika ui(katalog, &liczbaosob, listy, &liczbaList);
    ui.uruchom();

    return 0;
}
