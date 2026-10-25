#include<iostream>         //1 zajecia  (zmiana struct w class i zaktualizowanie całego programu o tą zmianę)
#include<string>
using namespace std;
class osoba{  //DZIALANIE SETTEROW I GETTEROW:
    private:  //uzytkownik w main ustala imie, ktore trafia do tymczasowego imie w main, potem trafia do funkcji dodaj osobe, gdzie setter bierze to imie i zapisuje do private
    string imie;  //getter dziaa przeciwnie do settera, z privata pokonuje cala droge do maina, albo tam gdzie go wywołujemy dzieki return imie, zeby np wyswieltic imie
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
int obecny[10];      //tablica 10 miejsc z informacja obecny czy nieobecny
osoba grupa[10];     //tablica 10 osob gdzie kazde miejsce to osoba z polem imie, nazwisko, indeks
int liczbaosob=0;    //licznik osob w grupie, (zaczynamy od 0 bo potem dodajemy osoby)

void dodajOsobe(osoba* grupa, int &liczbaosob, string imie, string nazwisko, int indeks) {
    if (liczbaosob < 10) {
        grupa[liczbaosob].setImie(imie);
        grupa[liczbaosob].setNazwisko(nazwisko);
        grupa[liczbaosob].setNumerIndeksu(indeks);
        obecny[liczbaosob] = 0;
        liczbaosob++;
    }
}
void ustawobecnosc(osoba* grupa, string nazwiskoSprawdzane, int &liczbaosob) {
    for(int i = 0; i < liczbaosob; i++) {
        if(grupa[i].getNazwisko() == nazwiskoSprawdzane) {
            obecny[i] = 1;
            break;
        }
    }
}
void wyswietllisteobecnosci(osoba *grupa, int &liczbaosob) {
    cout << "\nLista obecnosci" << endl;
    for(int i = 0; i < liczbaosob; i++) {
        if(grupa[i].getNazwisko() != "") {
            cout << grupa[i].getNazwisko() << " - " << (obecny[i] ? "1" : "0") << endl;
        }
    }
}
void edycjadanych(osoba* grupa, int &liczbaosob){
    string nazwiskodozmienienia;
    int opcje;
    cout<<"Podaj nazwisko osoby, ktorej dane chcesz zmienic: ";
    cin>>nazwiskodozmienienia;
    for(int i=0; i<liczbaosob; i++){
        if(grupa[i].getNazwisko()==nazwiskodozmienienia){
            cout<<"Co chcesz zmienic: 1.Imie \n2.Nazwisko \n3.Indeks \n4.Obecnosc ";
            cin>>opcje;
            if(opcje==1){
                string noweImie;
                cout<<"Podaj nowe imie: ";
                cin>>noweImie;
                grupa[i].setImie(noweImie);
            }
            else if(opcje==2){
                string noweNazwisko;
                cout<<"Podaj nowe nazwisko: ";
                cin>>noweNazwisko;
                grupa[i].setNazwisko(noweNazwisko);
            }
            else if(opcje==3){
                int nowyIndeks;
                cout<<"Podaj nowy indeks: ";
                cin>>nowyIndeks;
                grupa[i].setNumerIndeksu(nowyIndeks);
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
void usuwanieosob(osoba* grupa, int &liczbaosob){
    string nazwisko;
    cout<<"Podaj nazwisko osoby, ktora chcesz usunac: ";
    cin>>nazwisko;
    for(int i=0; i<liczbaosob; i++){
        if(grupa[i].getNazwisko()==nazwisko){
            grupa[i]=grupa[liczbaosob-1];
            liczbaosob--;
            return;
        }
    }
    cout<<"Nie ma takiego nazwiska"<<endl;
}
int main() {
    int wybor;
    do {
       cout<<"1-Dodaj osobe"<<endl;
       cout<<"2-Sprawdz obecnosc-podaj nazwisko"<<endl;
       cout<<"3-Wyswietl liste obecnosci"<<endl;
       cout<<"4-Edycja danych"<<endl;
       cout<<"5-Usuwanie osoby"<<endl;
       cout<<"0-Wyjscie"<<endl;
       cout<<"Wybierz opcje: ";
       cin>>wybor;

       if (wybor == 1) {
           string imie, nazwisko;
           int indeks;
           cout << "Podaj imie: ";
            cin >> imie;
           cout << "Podaj nazwisko: ";
           cin >> nazwisko;
           cout << "Podaj indeks: "; cin >> indeks;
           dodajOsobe(grupa, liczbaosob, imie, nazwisko, indeks);
       }
       else if (wybor == 2) {
           string nazwiskoDoSprawdzenia;
           cout << "Podaj nazwisko osoby, ktora jest obecna: ";
           cin >> nazwiskoDoSprawdzenia;
           ustawobecnosc(grupa, nazwiskoDoSprawdzenia, liczbaosob);
       }
       else if (wybor == 3) {
           wyswietllisteobecnosci(grupa, liczbaosob);
       }
       else if(wybor==4) {
           edycjadanych(grupa, liczbaosob);
       }
       else if(wybor==5) {
           usuwanieosob(grupa, liczbaosob);
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