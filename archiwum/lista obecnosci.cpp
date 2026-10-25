#include<iostream>      //5 zajecia
#include<string>
#include<fstream>
using namespace std;

class Iseriazable{
    public:
    virtual string przedstawSie() = 0;
    virtual void zapiszDoPliku(string nazwaPliku) = 0;
};

void drukuj(Iseriazable* obj){
    cout << obj->przedstawSie() << endl;
}

class osoba : public Iseriazable{   //czemu tu nie trzeba dzialac na wskazniku
    private:                            
    protected:
    string imie;
    string nazwisko;
    int numerindeksu;
    public:
    string getImie(){ 
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
    string przedstawSie(){
        return "Osoba: " + imie + " " + nazwisko + " o indeksie " + to_string(numerindeksu);
    }
    virtual void zapiszDoPliku(string nazwaPliku){   //po co tutaj tez musimy tworzyc ta funkcje, skoroc juz w interfjesie mamy
        ofstream plik(nazwaPliku);
        plik << "Imie: " << imie << endl;
        plik << "Nazwisko: " << nazwisko << endl;
        plik << "Numer indeksu: " << numerindeksu << endl;
        plik << przedstawSie() << endl;
        plik.close();
    }
    virtual void drukuj(){
        cout<<"Imie: "<<imie<<endl;
        cout<<"Nazwisko: "<<nazwisko<<endl;
        cout<<"Numer indeksu: "<<numerindeksu<<endl;
        cout<<przedstawSie()<<endl;
    }
};

class student: public osoba{
    public:
    string przedstawSie(){
        return "Student: " + getImie() + " " + getNazwisko() + " o indeksie " + to_string(getNumerIndeksu());
    }
    void drukuj(){
        cout<<"Imie: "<<getImie()<<endl;
        cout<<"Nazwisko: "<<getNazwisko()<<endl;
        cout<<"Numer indeksu: "<<getNumerIndeksu()<<endl;
        cout<<przedstawSie()<<endl;
    }
};

class studentZaoczny: public student{
    public:
    string przedstawSie(){
        return "Student zaoczny: " + getImie() + " " + getNazwisko() + " o indeksie " + to_string(getNumerIndeksu());
    }
    void drukuj(){
        cout<<"Imie: "<<getImie()<<endl;
        cout<<"Nazwisko: "<<getNazwisko()<<endl;
        cout<<"Numer indeksu: "<<getNumerIndeksu()<<endl;
        cout<<przedstawSie()<<endl;
    }
};

class pracowmik: public osoba{
    public:
    string przedstawSie(){
        return "Pracownik: " + getImie() + " " + getNazwisko() + " o indeksie " + to_string(getNumerIndeksu());
    }
    void drukuj(){
        cout<<"Imie: "<<getImie()<<endl;
        cout<<"Nazwisko: "<<getNazwisko()<<endl;
        cout<<"Numer indeksu: "<<getNumerIndeksu()<<endl;
        cout<<przedstawSie()<<endl;
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
    Iseriazable* obiektZapisu;

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
    void zapiszDoPliku(Iseriazable* obj){
        string nazwaPliku;
        cout<<"Podaj nazwe pliku do ktorego chcesz zapisac: ";
        cin>>nazwaPliku;
        obj->zapiszDoPliku(nazwaPliku);
    }

    public:
    InterfejsUzytkownika(osoba* kat, int* lOsob, ListaObecnosci* lst, int* lList, Iseriazable* obj)
        : katalog(kat), liczbaosob(lOsob), listy(lst), liczbaList(lList), aktywnaLista(-1), obiektZapisu(obj) {}

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
            cout<<"9-Zapis do pliku"<<endl;
            cout<<"0-Wyjscie"<<endl;
            if(aktywnaLista >= 0)
                cout<<"(aktywna lista: "<<aktywnaLista+1<<")"<<endl;
            cout<<"Wybierz opcje: ";
            cin>>wybor;

            if(wybor == 1) 
            dodajDoKatalogu();   
            
            else if(wybor == 2)
             utworzListe();
            
             else if(wybor == 3) 
             wybierzListe();
           
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
            else if(wybor==9){
                if (aktywnaLista<0){ 
                    cout<<"Najpierw wybierz liste."<<endl;
                    continue;
                }
                string nazwaPliku;
                int wyborZapisu;
                cout<<"Podaj nazwe pliku do ktorego chcesz zapisac:";
                cin>>nazwaPliku;
                cout<<"Wybierz co chcesz zapisac:"<<endl;
                cout<<"1. - Liste obecnosci"<<endl;
                cout<<"2. - Katalog osob"<<endl;
                cout<<"3. - Konkretnego studenta"<<endl;
                cin>>wyborZapisu;
                if (wyborZapisu==1){
                    cout<<"Zapisz liste obecnosci"<<endl;
                    obiektZapisu->zapiszDoPliku(nazwaPliku);
                }
                else if (wyborZapisu==2){
                    cout<<"Zapisz katalog osob"<<endl;
                    obiektZapisu->zapiszDoPliku(nazwaPliku);
                }
                else if(wyborZapisu==3){
                    string nazwiskostudenta;
                    cout<<"Zapisz konkretnego studenta"<<"\n"<<"Podaj nazwisko studenta: ";
                    cin>>nazwiskostudenta;
                    obiektZapisu->zapiszDoPliku(nazwaPliku);
                    cout<<"Zapisano studenta "<<nazwiskostudenta<<" do pliku "<<nazwaPliku<<endl;
                }
                else{
                    cout<<"Nie ma takiej opcji"<<endl;
                    continue;
                }

                ofstream plik(nazwaPliku);
                if(plik.is_open()){
                    plik<<obiektZapisu->przedstawSie()<<endl;
                    plik.close();
                    cout<<"Zapisano do pliku "<<nazwaPliku<<endl;
                }
                else {
                    cout<<"Nie mozna otworzyc pliku."<<endl;
                    continue;
                }
            }
            else if(wybor == 0) cout << "Koniec programu." << endl;
            else cout << "nie ma takiej opcji" << endl;
        } while(wybor != 0);
    }
};

int main() {
    osoba* tab[4];
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

    tab[0] = &os1;
    tab[1] = &st1;
    tab[2] = &pr1;
    tab[3] = &sz1;

    tab[0]->drukuj();
    tab[1]->drukuj();
    tab[2]->drukuj();
    tab[3]->drukuj();

    cout<<"\n przez interfejs Iprzedstawialny"<<endl;
    drukuj(&os1);
    drukuj(&st1);
    drukuj(&pr1);
    drukuj(&sz1);

    return 0;
}