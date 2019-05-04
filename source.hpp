#define MAX_TIMES 20
#define MAX_LENGTH 10
#include <string>
using std::string;
class Polynomial
{
    string name; //MAX_LENGTH name of Polynomial
    int pol[MAX_TIMES+1];  //MAX_TIMES
public:
    Polynomial(const Polynomial &other);
    Polynomial(const string & name0, const string & pol0);
    Polynomial operator+(const Polynomial &other);
    Polynomial operator-(const Polynomial &other);
    Polynomial operator*(const Polynomial &other);
    Polynomial operator=(const Polynomial &other);
    Polynomial operator<<(const Polynomial &other);
    //bool operator==(const Polynomial &other) const;
    int gcd()const;
    void simp();
    friend bool isUsed(string);
};
void menu();

void saveByName();
bool isValidPol(const string& pol);
//bool isUsed(string);

void listAllPolynomials();

void freeCalculation();
vector<Polynomial>::const_iterator findPol(const string& name);

void assignCtoX();
#include"source.cpp"