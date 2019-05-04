#define MAX_TIMES 20
#define MAX_LENGTH 10
#include <string>
using std::string;
class Polynomial
{
    string name; //MAX_LENGTH name of Polynomial
    char pol[MAX_TIMES+1];  //MAX_TIMES
    Polynomial(const Polynomial &other);
    Polynomial(const string & name0, const string & pol0);
    Polynomial operator+(const Polynomial &other);
    Polynomial operator-(const Polynomial &other);
    Polynomial operator*(const Polynomial &other);
    Polynomial operator=(const Polynomial &other);
    bool operator==(const Polynomial &other) const;
};