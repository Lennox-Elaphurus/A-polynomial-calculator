#define MAX_TIMES 20
#define MAX_LENGTH 10
#include <string>
using std::string;
class Polynomial
{
    string name; //MAX_LENGTH name of Polynomial
    int pol[MAX_TIMES];  //MAX_TIMES
public:
    Polynomial();
    Polynomial(const Polynomial &other);
    Polynomial(const string & name0, const string & pol0);
    Polynomial operator+(const Polynomial &other);
    Polynomial operator+=(const Polynomial &other);
    Polynomial operator-(const Polynomial &other);
    Polynomial operator-=(const Polynomial &other);
    Polynomial operator*(const Polynomial &other);
    Polynomial operator*=(const Polynomial &other);
    void operator=(const Polynomial &other);
    std::ostream& operator<<(std::ostream& cout)
    //bool operator==(const Polynomial &other) const;
    int gcd()const;
    void simp();
    long long int assign(int c);
    friend bool isUsed(const std::string& name);
    friend vector<Polynomial>::iterator findPol(const std::string&  name);
};
void menu();

void saveByName();
bool isValidPol(const string& pol);
bool isUsed(const std::string& name);

void listAllPolynomials();

void freeCalculation();
vector<Polynomial>::iterator findPol(const std::string&  name);

void assignCtoX();
