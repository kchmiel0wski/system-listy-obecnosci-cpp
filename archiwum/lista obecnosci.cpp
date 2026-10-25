#include<iostream>       //2 zajecia
#include<string>
using namespace std;
class osoba{        //klasa dotyczaca osoby z katoalogu osob
    private:
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
};
class ListaObecnosci{      //klasa dotyczaca listy obecnosci
    private:
    osoba* grupa[10];      //tablica wskaznikow na osoby z katalogu, ktore sa na liscie obecnosci!!!
    int obecny[10];    
    int liczbaosob=0;      //liczba osob na LISCIE OBECNOSCI, (nie liczbie osob w katalogu)
    public:
    void dodajOsobe(osoba* nowaosoba) { 
        if (liczbaosob < 10) {
            grupa[liczbaosob]=nowaosoba;  //dodajemy osobe do grupy
            obecny[liczbaosob]=0;   
            liczbaosob++; 
        }
    }
    void ustawobecnosc(string nazwiskoSprawdzane) {
        for(int i = 0; i < liczbaosob; i++) {
            if(grupa[i]->getNazwisko() == nazwiskoSprawdzane) {  
                obecny[i] = 1;
                break;      //znaleziono takie nazwisko, ustawiono obecnosc i koniec petli
            }
        }
    }
    void wyswietllisteobecnosci() {
        cout << "\nLista obecnosci" << endl;
        for(int i = 0; i < liczbaosob; i++) {
            if(grupa[i] != nullptr) {    //sprawdzamy czy dany wskaznik na osobe nie jest pusty
                cout << grupa[i]->getNazwisko() << " - " << (obecny[i] ? "1" : "0") << endl;
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
                     cin>>indeks; grupa[i]->setNumerIndeksu(indeks);
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
                grupa[i]=grupa[liczbaosob-1];     //przesuwamy ostatnia osobe na miejsce usuwanej
                obecny[i]=obecny[liczbaosob-1];     //przesuwamy odpowiadajaca wartosc obecnosci
                liczbaosob--; 
                return;
            }
        }
        cout<<"Nie ma takiego nazwiska"<<endl;
    }  
};
int main() {
    int wybor;
    osoba katalog[10];        //katalog osob, z ktorego bedziemy dodawac osoby na liste obecnosci
    int liczbaosob = 0; 
    ListaObecnosci listy[2];  //mozliwosc utworzenia 2 list obecnosci
    int liczbaList = 0;       //liczba utworzonych list obecnosci
    int aktywnaLista = -1;    //numer aktywnej listy obecnosci (-1 to brak aktywnej listy)
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
        
        if (wybor == 1) {
            string imie, nazwisko;
            int indeks;
            cout << "Podaj imie: "; cin >> imie;
            cout << "Podaj nazwisko: "; cin >> nazwisko;
            cout << "Podaj indeks: "; cin >> indeks;
            katalog[liczbaosob].setImie(imie);
            katalog[liczbaosob].setNazwisko(nazwisko);
            katalog[liczbaosob].setNumerIndeksu(indeks);
            liczbaosob++;
            cout<<"Dodano do katalogu."<<endl;
        }
        else if (wybor == 2) {
            if(liczbaList < 2){
                liczbaList++;    //tworzymy nowa liste obecnosci
                aktywnaLista = liczbaList-1;   //ustawiamy ja jako aktywna
                cout<<"Utworzono liste nr "<<liczbaList<<endl;
            } else {
                cout<<"Osiagnieto limit list."<<endl;
            }
        }
        else if (wybor == 3) {
            cout<<"Dostepne listy: 1-"<<liczbaList<<". Wybierz: "; //1-liczbaList, bo numeracja list od 1, a indeksy od 0
            int nr; 
            cin>>nr;  
            if(nr >= 1 && nr <= liczbaList){ //sprawdzamy czy wybrany numer listy jest poprawny
                aktywnaLista = nr-1;     //ustawiamy aktywna liste (nr-1, bo numeracja list od 1, a indeksy od 0)
                cout<<"Wybrano liste "<<nr<<endl;
            } else {
                cout<<"Nieprawidlowy numer."<<endl;
            }
        }
        else if (wybor == 4) {
            if(aktywnaLista < 0){ 
                cout<<"Najpierw wybierz liste (opcja 3)."<<endl; 
                continue; 
            }
            cout<<"Osoby w katalogu:"<<endl;
            for(int i=0; i<liczbaosob; i++)
                cout<<i+1<<". "<<katalog[i].getNazwisko()<<" "<<katalog[i].getImie()<<endl;
            cout<<"Wybierz numer osoby: ";
            int nr; 
            cin>>nr;
            if(nr >= 1 && nr <= liczbaosob){
                listy[aktywnaLista].dodajOsobe(&katalog[nr-1]);
                cout<<"Dodano na liste."<<endl;
            }
        }
        else if (wybor == 5) {
            if(aktywnaLista < 0){ 
                cout<<"Najpierw wybierz liste."<<endl;
                 continue; 
                }
            string nazwiskoDoSprawdzenia;
            cout << "Podaj nazwisko osoby, ktora jest obecna: ";
            cin >> nazwiskoDoSprawdzenia;
            listy[aktywnaLista].ustawobecnosc(nazwiskoDoSprawdzenia);
        } 
        else if (wybor == 6) {
            if(aktywnaLista < 0){ 
                cout<<"Najpierw wybierz liste."<<endl; 
                continue; 
            }
            listy[aktywnaLista].wyswietllisteobecnosci();
        } 
        else if(wybor==7) {
            if(aktywnaLista < 0){ 
                cout<<"Najpierw wybierz liste."<<endl;
                 continue;
                 }
            listy[aktywnaLista].edycjadanych();
        }
        else if(wybor==8) {
            if(aktywnaLista < 0){ 
                cout<<"Najpierw wybierz liste."<<endl;
                 continue;
                 }
            listy[aktywnaLista].usuwanieosob();
        }
        else if (wybor == 0) {
            cout << "Koniec programu." << endl;
        }
        else {
            cout << "nie ma takiej opcji" << endl;
        }
    } while (wybor != 0);
    return 0;
}