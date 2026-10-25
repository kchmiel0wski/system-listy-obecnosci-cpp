#include<iostream>     //4zajecia    testowanie zasad polimorfizmu i dziedziczenia na funkcji drukuj i przykładowych osobach
#include<string>
using namespace std;

//Polimorfizm to możliwość wywołania tej samej metody na różnych obiektach i uzyskania różnych wyników.
//Mamy jedna funkcje ale rozne obiekty i dlatego wywolanie tej funkcji daje rozne efekty, bo kazdy obiekt reaguje inaczej
//Możliwe jest to dzięki trzem rzeczom: 1.dziedziczenie→ student i pracownik są też osoba
//                                      2.virtual→ metoda może być nadpisana w dzieciach
//                                      3.wskaźniki→ zachowują prawdziwy typ obiektu (tutaj status)

class osoba{
    private:   //private jest puste, bo protected to tak naprawde rozszerzony private o dziedziczenie, (protected tez udziela dostepu do informacji wewnatrz klasy)
    protected: //protected jest potrzebne do dziedziczenia, pomimo tego ze juz jest private
    string imie;
    string nazwisko;
    int numerindeksu;
    public:  //gettery pozyskuja konkretne informacje o poszczegolnych rodzajach ludzi ktorzy juz sa zapisani w mainie i dzieki return imie wyswietlaja do konsoli
             //gettery i settery trzeba zawsze zdefiniowac co maja robic, umownie get-pobierac, set-ustawiac
    string getImie(){  //getter pobierajacy imie i zwracjacy je tam gdzie zostal wywolany
        return imie;
     }
    string getNazwisko() { 
        return nazwisko;
     }
    int getNumerIndeksu() { 
        return numerindeksu;
     }
    void setImie(string noweImie)  { //przyklad dzialania: ania z maina trafia do noweImie i zostaje zapisana do imie, zeby moc je potem wyswielic
        imie = noweImie;
     }
    void setNazwisko(string noweNazwisko) {
         nazwisko = noweNazwisko;
         }
    void setNumerIndeksu(int nowyNumerIndeksu)  {
         numerindeksu = nowyNumerIndeksu;
         }

                            //funkcja drukuj znajduje sie w clasie osoba, bo: 1.W main mamy tablice wskaznikow na osoby  2.Inne funkcje nadpisuja ja po swojemu
    virtual void drukuj(){  //virtual pozwala na zmiane lub dodawanie roznych rzeczy w clasach dziedziczacych
        cout<<"Imie: "<<imie<<endl;
        cout<<"Nazwisko: "<<nazwisko<<endl;
        cout<<"Numer indeksu: "<<numerindeksu<<endl;
        cout<<"Osoba: "<<imie<<" "<<nazwisko<<" o indeksie "<<numerindeksu<<endl;
    }
};
                             //dziedziczenie pozwala dodtkowo zmieniac metody i pola klasy rodzica i dodawac wlasne pola i metody
class student: public osoba{ //student dziedziczy po klasie osoba pola (imiem nazwisko, itp) i metody (gettery settery drukuj)
    public:
    void drukuj(){
        cout<<"Imie: "<<getImie()<<endl;   //getter wyswietlajacy imie
        cout<<"Nazwisko: "<<getNazwisko()<<endl;
        cout<<"Numer indeksu: "<<getNumerIndeksu()<<endl;
        cout<<"Student: "<<getImie()<<" "<<getNazwisko()<<" o indeksie "<<getNumerIndeksu()<<endl;
    }
};

class pracowmik: public osoba{
    public:
    void drukuj(){    //za kazdym razem trzeba przepisywac cala skladnie funkcji bo zazwyczaj chcemy cos zmienic lub dopisac w tej funkcji, wiec musi byc wszytsko jasno okreslone 
        cout<<"Imie: "<<getImie()<<endl;
        cout<<"Nazwisko: "<<getNazwisko()<<endl;
        cout<<"Numer indeksu: "<<getNumerIndeksu()<<endl;
        cout<<"Pracownik: "<<getImie()<<" "<<getNazwisko()<<" o indeksie "<<getNumerIndeksu()<<endl;
    }
};

class ListaObecnosci{
    private:
    osoba* grupa[10];
    int obecny[10];
    int liczbaosob=0;

    public:
    void dodajOsobe(osoba* nowaosoba) {
        if (liczbaosob < 10) {
            grupa[liczbaosob]=nowaosoba;
            obecny[liczbaosob]=0;
            liczbaosob++;
        }
    }
    void ustawobecnosc(string nazwiskoSprawdzane) {
        for(int i = 0; i < liczbaosob; i++) {
            if(grupa[i]->getNazwisko() == nazwiskoSprawdzane) {
                obecny[i] = 1;
                break;
            }
        }
    }
    void wyswietllisteobecnosci() {
        cout << "\nLista obecnosci" << endl;
        for(int i = 0; i < liczbaosob; i++) {
            if(grupa[i] != nullptr) {
                cout << grupa[i]->getNazwisko() << " " << grupa[i]->getImie() << " - " << (obecny[i] ? "1" : "0") << endl;
            }
        }
    }
    void edycjadanych(){
        string nazwiskodozmienienia, imie, nazwisko;
        int indeks, opcje;
        cout<<"Podaj nazwisko osoby, ktorej dane chcesz zmienic: ";
        cin>>nazwiskodozmienienia;
        for(int i=0; i<liczbaosob; i++){
            if(grupa[i]->getNazwisko()==nazwiskodozmienienia){
                cout<<"Co chcesz zmienic: 1.Imie \n2.Nazwisko \n3.Indeks \n4.Obecnosc ";
                cin>>opcje;
                if(opcje==1){ 
                    cout<<"Podaj nowe imie: ";
                     cin>>imie;
                      grupa[i]->setImie(imie);
                     }
                else if(opcje==2){
                     cout<<"Podaj nowe nazwisko: ";
                     cin>>nazwisko;
                      grupa[i]->setNazwisko(nazwisko);
                     }
                else if(opcje==3){ 
                    cout<<"Podaj nowy indeks: ";
                     cin>>indeks;
                      grupa[i]->setNumerIndeksu(indeks);
                     }
                else if(opcje==4){ 
                    cout<<"Zmien obecnosc: 0 lub 1 "; 
                     cin>>obecny[i];
                     }
                else{ 
                    cout<<"Nie ma takiej opcji"<<endl;
                 }
                return;
            }
        }
        cout<<"Nie znaleziono takiej osoby"<<endl;
    }
    void usuwanieosob(){
        string nazwisko;
        cout<<"Podaj nazwisko osoby, ktora chcesz usunac: ";
        cin>>nazwisko;
        for(int i=0; i<liczbaosob; i++){
            if(grupa[i]->getNazwisko()==nazwisko){
                grupa[i]=grupa[liczbaosob-1];
                obecny[i]=obecny[liczbaosob-1];
                liczbaosob--;
                return;
            }
        }
        cout<<"Nie ma takiego nazwiska"<<endl;
    }
};

class InterfejsUzytkownika{
    private:
    osoba* katalog;
    int* liczbaosob;
    ListaObecnosci* listy;
    int* liczbaList;
    int aktywnaLista;

    void dodajDoKatalogu(){
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
        cout<<"Dodano do katalogu."<<endl;
    }

    void utworzListe(){
        if(*liczbaList < 2){
            (*liczbaList)++;
            aktywnaLista = (*liczbaList)-1;
            cout<<"Utworzono liste nr "<<*liczbaList<<endl;
        } else {
            cout<<"Osiagnieto limit list."<<endl;
        }
    }

    void wybierzListe(){
        cout<<"Dostepne listy: 1-"<<*liczbaList<<". Wybierz: ";
        int nr; cin>>nr;
        if(nr >= 1 && nr <= *liczbaList){
            aktywnaLista = nr-1;
            cout<<"Wybrano liste "<<nr<<endl;
        } else {
            cout<<"Nieprawidlowy numer."<<endl;
        }
    }

    void dodajNaListe(){
        cout<<"Osoby w katalogu:"<<endl;
        for(int i=0; i<*liczbaosob; i++)
            cout<<i+1<<". "<<katalog[i].getNazwisko()<<" "<<katalog[i].getImie()<<endl;
        cout<<"Wybierz numer osoby: ";
        int nr; cin>>nr;
        if(nr >= 1 && nr <= *liczbaosob){
            listy[aktywnaLista].dodajOsobe(&katalog[nr-1]);
            cout<<"Dodano na liste."<<endl;
        }
    }

    public:
    InterfejsUzytkownika(osoba* kat, int* lOsob, ListaObecnosci* lst, int* lList)
        : katalog(kat), liczbaosob(lOsob), listy(lst), liczbaList(lList), aktywnaLista(-1) {}

    void uruchom(){
        int wybor;
        do {
            cout<<"1-Dodaj osobe do katalogu"<<endl;
            cout<<"2-Utworz nowa liste"<<endl;
            cout<<"3-Wybierz liste"<<endl;
            cout<<"4-Dodaj osobe z katalogu na liste"<<endl;
            cout<<"5-Sprawdz obecnosc"<<endl;
            cout<<"6-Wyswietl liste obecnosci"<<endl;
            cout<<"7-Edycja danych"<<endl;
            cout<<"8-Usuwanie osoby z listy"<<endl;
            cout<<"0-Wyjscie"<<endl;
            if(aktywnaLista >= 0)
                cout<<"(aktywna lista: "<<aktywnaLista+1<<")"<<endl;
            cout<<"Wybierz opcje: ";
            cin>>wybor;

            if(wybor == 1) dodajDoKatalogu();
            else if(wybor == 2) utworzListe();
            else if(wybor == 3) wybierzListe();
            else if(wybor == 4){
                if(aktywnaLista < 0){
                     cout<<"Najpierw wybierz liste (opcja 3)."<<endl;
                      continue;
                     }
                dodajNaListe();
            }
            else if(wybor == 5){
                if(aktywnaLista < 0){ 
                    cout<<"Najpierw wybierz liste."<<endl; 
                    continue; 
                }
                string nazwiskoDoSprawdzenia;
                cout << "Podaj nazwisko osoby, ktora jest obecna: ";
                cin >> nazwiskoDoSprawdzenia;
                listy[aktywnaLista].ustawobecnosc(nazwiskoDoSprawdzenia);
            }
            else if(wybor == 6){
                if(aktywnaLista < 0){
                     cout<<"Najpierw wybierz liste."<<endl;
                      continue;
                     }
                listy[aktywnaLista].wyswietllisteobecnosci();
            }
            else if(wybor == 7){
                if(aktywnaLista < 0){
                     cout<<"Najpierw wybierz liste."<<endl;
                      continue; 
                    }
                listy[aktywnaLista].edycjadanych();
            }
            else if(wybor == 8){
                if(aktywnaLista < 0){ 
                    cout<<"Najpierw wybierz liste."<<endl; 
                    continue; 
                }
                listy[aktywnaLista].usuwanieosob();
            }
            else if(wybor == 0) cout << "Koniec programu." << endl;
            else cout << "nie ma takiej opcji" << endl;
        } while(wybor != 0);
    }
};

int main() {
    osoba* tab[3];            //tworzymy tablice wskazników, bo bez nich przy drukowaniu tabow ginie status tych osob czyli student lub pracownik
    osoba os1;                //osoby maja informacje o imieniu nazwisku, numerze indeksu i ze jest status osoba, a nie student czy cokolwiek innego
    os1.setImie("Michal");    //wskazniki powoduje ze w pelni wskazujemy na danego czlowieka czyli na studenta albo pracownika ktorzy maja status i reszte cech osoby
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

    tab[0] = &os1;
    tab[1] = &st1;
    tab[2] = &pr1;

    tab[0]->drukuj();
    tab[1]->drukuj();
    tab[2]->drukuj();

    return 0;
}