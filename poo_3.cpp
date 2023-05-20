#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <exception>
#include <list>

using namespace std;

class Animal
{
protected:
    string nume;
    int varsta;

public:
    Animal(string nume, int varsta); // param
    Animal();                        // neparametrizat
    virtual ~Animal() {}             // destructor
    Animal(const Animal &animal1);
    virtual void CitesteDate();
    virtual void ScrieDate();

    friend istream &operator>>(istream &is, Animal &a)
    {
        is >> a.nume >> a.varsta;
        return is;
    }

    friend ostream &operator<<(ostream &os, Animal &a)
    {
        os << a.nume << " " << a.varsta;
        return os;
    }

    Animal &operator=(const Animal &obiect)
    {
        if (this != &obiect)
        {
            nume = obiect.nume;
            varsta = obiect.varsta;
        }
        return *this;
    }
};

Animal::Animal(string nume, int varsta) : nume(nume), varsta(varsta){};
Animal::Animal() : nume(" "), varsta(0){};
Animal::Animal(const Animal &animal1) : nume(animal1.nume), varsta(animal1.varsta){};

void Animal::CitesteDate()
{
    cout << "introdu numele si varsta animalului";
    cin >> nume >> varsta;
}
void Animal::ScrieDate()
{
    cout << "informatii despre animal:" << nume << " " << varsta << endl;
}

// memorarea a n obiecte din clasa Animal
vector<Animal> MemorareAnimal(int n)
{
    vector<Animal> obiecte;
    for (int i = 0; i < n; i++)
    {
        Animal obiect = Animal();
        obiecte.push_back(obiect);
    }
    return obiecte;
}

// citirea a n obiecte din clasa Animal
void CitireAnimal(vector<Animal> &obiecte)
{
    for (int i = 0; i < obiecte.size(); i++)
    {
        cin >> obiecte[i];
    }
}

// afisare a n obiecte din clasa Animal
void AfisareAnimal(vector<Animal> &obiecte)
{
    for (int i = 0; i < obiecte.size(); i++)
    {
        cout << obiecte[i];
    }
}

class Nevertebrate : public Animal
{
public:
    Nevertebrate();
    Nevertebrate(string nume, int varsta);
    Nevertebrate(const Nevertebrate &other);
    ~Nevertebrate(){};
    void CitesteDate() override;
    void ScrieDate() override;

    friend istream &operator>>(istream &is, Nevertebrate &n)
    {
        Animal *animal = &n; // Upcasting
        is >> *animal;
        return is;
    }

    friend ostream &operator<<(ostream &os, Nevertebrate &n)
    {
        Animal *animal = &n; // Upcasting
        os << *animal;
        return os;
    }

    Nevertebrate &operator=(const Animal &obiect)
    {
        Animal::operator=(obiect); // operatorul din clasa de baza
        return *this;
    }
};

Nevertebrate::Nevertebrate() : Animal("", 0){};
Nevertebrate::Nevertebrate(string nume, int varsta) : Animal(nume, varsta){};
Nevertebrate::Nevertebrate(const Nevertebrate &other) : Animal(other){};
void Nevertebrate::CitesteDate()
{
    Animal::CitesteDate(); 
}

void Nevertebrate::ScrieDate()
{
    Animal::ScrieDate(); 
}

class Vertebrate : public Animal
{
public:
    Vertebrate() : Animal("", 0) {}
    Vertebrate(string nume, int varsta) : Animal(nume, varsta) {}
    Vertebrate(const Vertebrate &other) : Animal(other) {}
    ~Vertebrate() {}
    void CitesteDate() override;
    void ScrieDate() override;

    friend istream &operator>>(istream &is, Vertebrate &n)
    {
        Animal &BazaAnimal = n; // upcasting
        is >> BazaAnimal;
        return is;
    }

    friend ostream &operator<<(ostream &os, Vertebrate &n)
    {
        Animal &BazaAnimal = n; // upcasting
        os << BazaAnimal;
        return os;
    }

    Vertebrate &operator=(const Animal &obiect)
    {
        Animal::operator=(obiect); // operatorul din clasa de baza
        return *this;
    }
};
void Vertebrate::CitesteDate()
{
    Animal::CitesteDate();
}

void Vertebrate::ScrieDate()
{
    Animal::ScrieDate();
}

class Pesti : public Vertebrate
{
    int lungime;
    string tip_peste;

public:
    Pesti() : Vertebrate(){};
    Pesti(int lung, string Tip_peste, string nume, int varsta) : Vertebrate(nume, varsta), lungime(lung), tip_peste(Tip_peste){};
    Pesti(const Pesti &other) : Vertebrate(other), lungime(other.lungime), tip_peste(other.tip_peste){};
    ~Pesti(){};

    void CitesteDate() override;
    void ScrieDate() override;
    
    friend istream &operator>>(istream &is, Pesti &n)
    {
        Vertebrate &BazaVertebrate = n; // upcasting
        is >> BazaVertebrate;
        return is;
    }

    friend ostream &operator<<(ostream &os, Pesti &n)
    {
        Vertebrate &BazaVertebrate = n; // upcasting
        os << BazaVertebrate;
        return os;
    }

    Pesti &operator=(const Vertebrate &obiect)
    {
        Vertebrate::operator=(obiect); // operatorul din clasa de baza
        return *this;
    }

    string getTip_peste() const { return tip_peste; }

    int getLungime() const { return lungime; }

    bool operator!=(const string &other) const
    {
        return tip_peste != other;
    };
};
void Pesti::CitesteDate()
{
    Vertebrate::CitesteDate();
}

void Pesti::ScrieDate()
{
    Vertebrate::ScrieDate();
}




class Pasari : public Vertebrate
{
    string tip_pasare;

public:
    Pasari() : Vertebrate(){};
    Pasari(string tip_pasare, string nume, int varsta) : Vertebrate(nume, varsta), tip_pasare(tip_pasare){};
    Pasari(const Pasari &other) : Vertebrate(other), tip_pasare(other.tip_pasare){};
    ~Pasari(){};
    void CitesteDate() override;
    void ScrieDate() override;
    friend istream &operator>>(istream &is, Pasari &n)
    {
        Vertebrate &BazaVertebrate = n; // upcasting
        is >> BazaVertebrate;
        return is;
    }

    friend ostream &operator<<(ostream &os, Pasari &n)
    {
        Vertebrate &BazaVertebrate = n; // upcasting
        os << BazaVertebrate;
        return os;
    }

    Pasari &operator=(const Vertebrate &obiect)
    {
        Vertebrate::operator=(obiect); // operatorul din clasa de baza
        return *this;
    }
};


void Pasari::CitesteDate()
{
    Vertebrate::CitesteDate();
}

void Pasari::ScrieDate()
{
    Vertebrate::ScrieDate();
}

class Mamifere : public Vertebrate
{
    string tip_mamifer;

public:
    Mamifere() : Vertebrate(){};
    Mamifere(string tip_mamifer, string nume, int varsta) : Vertebrate(nume, varsta), tip_mamifer(tip_mamifer){};
    Mamifere(const Mamifere &other) : Vertebrate(other), tip_mamifer(other.tip_mamifer){};
    ~Mamifere(){};
    void CitesteDate() override;
    void ScrieDate() override;
    friend istream &operator>>(istream &is, Mamifere &n)
    {
        Vertebrate &BazaVertebrate = n; // upcasting
        is >> BazaVertebrate;
        return is;
    }

    friend ostream &operator<<(ostream &os, Mamifere &n)
    {
        Vertebrate &BazaVertebrate = n; // upcasting
        os << BazaVertebrate;
        return os;
    }

    Mamifere &operator=(const Vertebrate &obiect)
    {
        Vertebrate::operator=(obiect); // operatorul din clasa de baza
        return *this;
    }
};
void Mamifere::CitesteDate()
{
    Vertebrate::CitesteDate();
}

void Mamifere::ScrieDate()
{
    Vertebrate::ScrieDate();
}

class Reptile : public Vertebrate
{
    string tip_reptile;

public:
    Reptile() : Vertebrate(){};
    Reptile(string tip_reptile, string nume, int varsta) : Vertebrate(nume, varsta), tip_reptile(tip_reptile){};
    Reptile(const Reptile &other) : Vertebrate(other), tip_reptile(other.tip_reptile){};
    ~Reptile(){};
    void CitesteDate() override;
    void ScrieDate() override;
    friend istream &operator>>(istream &is, Reptile &n)
    {
        Vertebrate &BazaVertebrate = n; // upcasting
        is >> BazaVertebrate;
        return is;
    }

    friend ostream &operator<<(ostream &os, Reptile &n)
    {
        Vertebrate &BazaVertebrate = n; // upcasting
        os << BazaVertebrate;
        return os;
    }

    Reptile &operator=(const Vertebrate &obiect)
    {
        Vertebrate::operator=(obiect); // operatorul din clasa de baza
        return *this;
    }
};
void Reptile::CitesteDate()
{
    Vertebrate::CitesteDate();
}

void Reptile::ScrieDate()
{
    Vertebrate::ScrieDate();
}

template <typename T>
class AtlasZoologic
{
    list<T *> animale;
    static int numarAnimale;

public:
    AtlasZoologic() {}
    AtlasZoologic(const list<T *> &animale) : animale(animale) {}
    // copy constructor
    AtlasZoologic(const AtlasZoologic &other)
    {
        for (typename list<T *>::const_iterator i = other.animale.begin(); i != other.animale.end(); ++i)
        {
            T *AnimalCopiat = new T(**i);
            animale.push_back(AnimalCopiat);
        }
    }
    ~AtlasZoologic()
    {
        for (typename list<T *>::iterator i = animale.begin(); i != animale.end(); i++)
        {
            delete *i;
        }
    }



    const list<T *>& GetAnimal() const
    {
        return animale;
    }

    friend istream &operator>>(istream &is, AtlasZoologic<T> &atlas)
    {
        for (typename list<T *>::iterator i = atlas.animale.begin(); i != atlas.animale.end(); i++)
        {
            is >> **i;
        }
        return is;
    }

    friend ostream &operator<<(ostream &os, const AtlasZoologic<T> &atlas)
    {
        for (typename list<T *>::iterator i = atlas.animale.begin(); i != atlas.animale.end(); i++)
        {
            os << **i;
        }
        return os;
    }

    AtlasZoologic<T> &operator=(const AtlasZoologic<T> &atlas)
    {
        if (this != &atlas)
        {
            for (typename list<T *>::iterator i = animale.begin(); i != animale.end(); i++)
            {
                delete *i;
            }
            animale.clear();

            for (typename list<T *>::const_iterator i = atlas.animale.begin(); i != atlas.animale.end(); i++)
            {
                T *AnimalCopiat = new T(**i);
                animale.push_back(AnimalCopiat);
            }
        }
        return *this;
    }

    // incrementare numarAnimale la adaugare unei fise noi - functie statica
    static void IncrementNumarAnimale()
    {
        numarAnimale++;
    }

    AtlasZoologic<T> &operator+=(const T &animal)
    {
        T *newAnimal = new T(animal); 
        animale.push_back(newAnimal);
        IncrementNumarAnimale();
        return *this;
    }
};

template <typename T>
int AtlasZoologic<T>::numarAnimale = 0;



template <>
class AtlasZoologic<Pesti> : public AtlasZoologic<Vertebrate>
{
    Pesti peste;

public:
    AtlasZoologic() : AtlasZoologic<Vertebrate>() {}
    AtlasZoologic(int lung, string tip_peste, string nume, int varsta) : AtlasZoologic<Vertebrate>(), peste(lung, tip_peste, nume, varsta){};
    AtlasZoologic(const AtlasZoologic<Pesti> &other) : AtlasZoologic<Vertebrate>(other), peste(other.peste){};

    void SetPeste(const Pesti &newPeste)
    {
        peste = newPeste;
    }

    friend istream &operator>>(istream &is, AtlasZoologic<Pesti> &atlas)
    {
        Pesti newPeste;
        is >> newPeste;
        atlas.SetPeste(newPeste);
        return is;
    };

    friend ostream &operator<<(ostream &os, AtlasZoologic<Pesti> &atlas)
    {
        Pesti newPeste;
        os << newPeste;
        atlas.SetPeste(newPeste);
        return os;
    };

    AtlasZoologic<Pesti> &operator=(const AtlasZoologic<Pesti> &atlas)
    {
        if (this != &atlas)
        {
            AtlasZoologic<Vertebrate>::operator=(atlas);
            peste = atlas.peste;
        }
        return *this;
    }

    void RapitorLungime()
    {
        int numaraPesti = 0;
        const list<Vertebrate *>  &animale = GetAnimal();

        for (typename list<Vertebrate *>::const_iterator i = animale.begin(); i != animale.end(); ++i)
        {
            if (typeid(**i) == typeid(Pesti))
            {
                Pesti *peste = static_cast<Pesti *>(*i);
                if (peste->getTip_peste() == "rapitor" && peste->getLungime() >= 1)
                {
                    numaraPesti++;
                }
            }
        }

        cout << "Numarul de pesti rapitori de lungime mai mare sau egala cu 1m este: " << numaraPesti << endl;
    }
};

int main()
{
    try
    {
        Pesti peste(5, "rapitor", "ion", 5);
        AtlasZoologic<Pesti> atlas;

        peste.getLungime();
        peste.getTip_peste();
        if (peste.getLungime() < 0)
        {
            throw "Lungimea trebuie sa fie mai mare decat 0";
        }
        if (peste.getTip_peste() != "rapitor")
        {
            throw "Pestele nu este rapitor";
        }

        atlas += peste; 
        atlas.RapitorLungime();
    }
    catch (const char *message)
    {
        cout << "An error occurred: " << message << endl;
    }

    return 0;
}
