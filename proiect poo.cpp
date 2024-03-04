#include <iostream>
#include <string>
#include <vector>
using namespace std;
class articol{
protected:
    int cota;
    int numarExemplare;

public:
    articol(int cota=0, int numar=0): cota(cota), numarExemplare(numar){}

    articol(const articol& other): cota(other.cota), numarExemplare(other.numarExemplare){}


    virtual ~articol(){}

     int getCota () const{
        return this->cota;
    }

     void setNumarExemplare(int x){
        this->numarExemplare = x;
    }

    int getNumarExemplare (){
        return this->numarExemplare;
    }

    virtual void read(istream& is) {
        int cota;
        int  numarExemplare;

        cout<<"Cota: ";
        is >> this->cota;

        cout<<"numarExemplare este: ";
        is >> numarExemplare;


        this->cota = cota;
        this->numarExemplare = numarExemplare;
    }

    virtual void print(ostream& os) {
        cout<<"cota: ";
        os << this->getCota();
        cout<<endl;
        cout<<"Numar exemplare: ";
        os<< this->getNumarExemplare();
        cout<<endl;
    }


    friend ostream& operator<<(ostream& os, const articol& articol);
    friend istream& operator>>(istream& is, const articol& articol);

    articol& operator=(const articol& other) {
        if (this != &other) {
            this->cota = other.cota;
            this->numarExemplare = other.numarExemplare;
        }
        return *this;
    }


};

istream& operator>> (istream& is, articol& articol)
{
    articol.read( is);
    return is;
}

ostream& operator<< (ostream& os, articol& articol){
    articol.print( os);
    return os;
}


class carte: public articol{
protected:
    string titlu;

public:
    carte(int cota=0, int numar=0, string titlu=""): articol(cota, numar), titlu(titlu){}

    carte(const carte& other): articol(other), titlu(other.titlu){}

    ~carte(){};

    void  setTitlu(string titlu){
        this->titlu = titlu;
    }

    string getTitlu(){
        return this->titlu;
    }

    void read(istream& is) override {
        int cota;
        int  numarExemplare;
        string titlu;
        cout<<"Cota este: ";
        is >> cota;

        cout<<"numarul de exemplare este: ";
        is >> numarExemplare;

        cout<<"titlul este: ";
        is >> titlu;

        this->cota = cota;
        this->numarExemplare = numarExemplare;
        this->titlu = titlu;

    }

    void print(ostream& os) override {
        cout<<"cota este: ";
        os << this->getCota();
        cout<<endl;

        cout<<"Numar exemplare: ";
        os<< this->getNumarExemplare();
        cout<<endl;

        cout<<"Titlul este: ";
        os<<this->getTitlu()<<endl;
    }


    friend istream& operator>>(istream& is, const carte& carte);
    friend ostream& operator<<(ostream& os, const carte& carte);

    carte& operator=(const carte& other) {
        if (this == &other) {
            return *this;
        }
        articol::operator=(other);
        titlu = other.titlu;
        return *this;
    }

};

istream& operator>> (istream& is, carte& carte)
{
    carte.read(is);
    return is;
}

ostream& operator<< (ostream& os, carte& carte){
    carte.print( os);
    return os;
}


class CD: public articol{
protected:
    string lunaAparitie;
public:
    CD(int cota=0, int numar=0, string lunaAparitie=""): articol(cota, numar), lunaAparitie(lunaAparitie){}

    CD(const CD& other): articol(other), lunaAparitie(other.lunaAparitie){}

    ~CD(){};

    void setLunaAparitie(string x){
        this->lunaAparitie = x;
    }

    string getLunaAparitie(){
        return this->lunaAparitie;
    }
    void read(istream& is) override {
        articol::read(is);

        cout << "Luna aparitiei: ";
        is >> lunaAparitie;
    }

    void print(ostream& os) override {
        articol::print(os); // Call the base class print function
        cout << "Luna aparitiei este: " << lunaAparitie << endl;
    }


    friend istream& operator>>(istream& is,  CD& CD);
    friend ostream& operator<<(ostream& os,  CD& CD);

    CD& operator=(const CD& other) {
        if (this == &other) {
            return *this;
        }
        articol::operator=(other);
        lunaAparitie = other.lunaAparitie;
        return *this;
    }


};


istream& operator>> (istream& is, CD& CD)
{
    is >> CD.lunaAparitie;
    is>> dynamic_cast<articol&>(CD);
    return is;
}

ostream& operator<< (ostream& os, CD& CD){
    CD.print( os);
    return os;
}

class biblioteca{
private:
    vector <articol*> bibliotecaMea;
    static int nrArticoleImprumutate;
    static int nrArticolRestituite;
public:
    void addArticol(articol *A){

        try {
            if (A == nullptr) {
                throw invalid_argument("A este null.");
            }
            bibliotecaMea.push_back(A);
        } catch (const exception& e) {
            cerr << "Exception caught: " << e.what() << endl;
        }

    }

    void afisareBiblioteca()  {
        cout << "In biblioteca mea sunt: " << bibliotecaMea.size() << " articole" << endl;
        int i = 1;
        for (auto it = bibliotecaMea.begin(); it != bibliotecaMea.end(); it++, i++) {
            cout << "Articol " << i << ": " << endl;

            if ( carte* ptr = dynamic_cast< carte*>(*it)) {
                cout << "Type: carte" << endl;
                cout << *ptr << endl;
            } else if ( CD* ptr = dynamic_cast< CD*>(*it)) {
                cout << "Type: CD" << endl;
                cout << *ptr << endl;
            } else {
                cout << "Unknown type" << endl;
            }
        }
    }


    void imprumutaArticol(int y){
         {
            int i = 0, x;
            bool found = false;

            for (auto it = bibliotecaMea.begin(); it != bibliotecaMea.end(); it++, i++) {
                if ((*it)->getCota() == int(y)) {
                    x = (*it)->getNumarExemplare();
                    if (x < 1) {
                        throw out_of_range("nu mai sunt exemplare valabile");
                    } else {
                        x--;
                        (*it)->setNumarExemplare(x);
                        found = true;
                        break;
                    }
                }
            }

            if (!found) {
                throw runtime_error("Nu s-a gasit articolul");
            }
            nrArticoleImprumutate++;
        }
    }

    void restituieArticole(int y ) {
        int i = 0, x;
        for (auto it = bibliotecaMea.begin(); it != bibliotecaMea.end(); it++, i++) {
            if ((*it)->getCota() == y) {
                x = (*it)->getNumarExemplare();
                x++;
                (*it)->setNumarExemplare(x);
                break;
            }
        }

        nrArticoleImprumutate++;
    }
    static int getNrArticoleImprumutate(){
        return nrArticoleImprumutate;
    }

    static int getNrArticoleRestituite(){
        return nrArticolRestituite;
    }


};

 int biblioteca:: nrArticolRestituite =0;

int biblioteca :: nrArticoleImprumutate =0 ;

void citireNElemente()  {
    int n, tipArticol;
    vector<articol*> articole;
    cout << "Cate elemente doresti sa adaugi? ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Alege tipul articolului ! " << endl;
        cout << "0 ..... carte" << endl;
        cout << "1 ...... CD" << endl;

        cin >> tipArticol;

        switch (tipArticol) {
            case 0: {
                carte* a = new carte();
                cin >> (*a);
                articole.push_back(a);
                break;
            }
            case 1: {
                CD* b = new CD();
                cin >> (*b);
                articole.push_back(b);
                break;
            }
            default: {
                cout << "Raspuns invalid! \n";
                break;
            }
        }
    }

    int i = 1;
    for (auto articol : articole) {
        cout << "Elementul " << i << ":" << endl;
        cout << (*articol);
        i++;
    }

    for (auto articol : articole) {
        delete articol;
    }
}

 void display(){
    cout<<"Apasa 0 pentru adauga articole noi"<<endl;
    cout<<"Apasa 1 pentru a imprumuta un articol"<<endl;
    cout<< "Apasa 2 pentru a returna un articol"<<endl;
    cout<<"Apasa 3 pentru a afisa biblioteca"<<endl;
    cout<<"Apasa STOP pentru a opri"<<endl;
}
void meniu() {
    biblioteca b;
    string comanda;
    int tipArticol;
    int n, d;

    comanda="ala";
    while(comanda != "STOP"){
        display();
        cin>>comanda;
        if(comanda == "0"){
            cout<<"Cate articole vrei sa adaugi? ";
            cin>>n;

            for(int i=1; i<=n;i++) {
                cout << "Alege tipul articolului ! " << endl;
                cout << "0 ..... carte" << endl;
                cout << "1 ...... CD" << endl;

                cin >> tipArticol;

                switch (tipArticol) {
                    case 0: {
                        articol *a = new carte();
                        cin >> (*a);
                        b.addArticol(a);
                        break;
                    }
                    case 1: {
                        articol *d = new CD();
                        cin >> (*d);
                        b.addArticol(d);
                        break;
                    }
                    default: {
                        cout << "Raspuns invalid! \n";
                        break;
                    }
                }
            }
        }

        else if(comanda == "1"){
            cout<<"introdu cota articolului pe care vrei sa il imprumuti";
            cin>>d;
            try{
                b.imprumutaArticol(d);
            } catch (const exception& e) {
                cerr << "Exception caught: " << e.what() << endl;
            }
        }
            else if(comanda == "2"){
            cout<<"introdu cota articolului pe care vrei sa il returnezi";
            cin>>d;
            b.restituieArticole(d);
            }
                else if(comanda == "3"){
                    b.afisareBiblioteca();
                }
                    else if(comanda == "STOP")  throw invalid_argument("meniul a fost oprit");}

};

template<class T>
class GestionareArticole {
private:
    vector<T*> articole;

public:
    void addArticol(T* articol) {
        articole.push_back(articol);
    }

    void afisareArticole() {
        for ( T* articol : articole) {
            if (typeid(*articol) == typeid(CD)) {
                 CD* cd = dynamic_cast< CD*>(articol);
                cout << "Avem un articol de tip CD" << endl;
            } else {
                cout << "Avem un articol de tip CARTE" << endl;
            }
        }
    }
};

template<>
void GestionareArticole<CD>::afisareArticole() {
    for ( CD* a : articole) {
        if (a->getLunaAparitie() == "ianuarie") {
            cout<<*a;
        }
    }
}


int main() {


    meniu();



//    GestionareArticole<articol> gestionareArticole;
//    GestionareArticole<CD> gestionareCD;
//
//    articol* a1 = new carte(1, 5, "alba ca zapada");
//    articol* a2 = new CD(2, 10, "ianuarie");
//    gestionareArticole.addArticol(a1);
//    gestionareArticole.addArticol(a2);
//
//    CD* cd1 = new CD(3, 20, "ianuarie");
//    CD* cd2 = new CD(4, 15, "aprilie");
//    gestionareCD.addArticol(cd1);
//    gestionareCD.addArticol(cd2);
//
//    gestionareArticole.afisareArticole();
//
//    gestionareCD.afisareArticole();
    return 0;
}
