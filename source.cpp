#include<iostream>
#include<vector>
#define MAX_LENGTH 10
#define MAX_SIZE 1024
vector<Polynomial> Polynomials;
void menu(){
    std::cout<<"\tYou want to:"<<std::endl;
    std::cout<<"\t[1] Write 'ax^n+bx^n-1+...' as 'p'\n"//write and save by name
    <<"\t[2] Watch 'ax^n+bx^(n-1)+...' you wrote\n"//list the stored Polynomials
    <<"\t[3] p1 + p2 - p3 * p4 (write as you want)"//free calculation by operator
    <<"\t[4] When x = c, 'ax^n+bx^(n-1)+...' = ?\n"//assign number to x in Polynomial
    <<"\t[5] Close\n";
    std::cout<<"1/2/3/4/5?"<<std::endl;
    int operation=0;
    std::cin>>operation;
    std::cin.ignore(MAX_SIZE);
    switch(operation){
        case '1':{//write and save by name
            saveByName();
            break;
        }
        case '2':{//list the stored Polynomials
            listAllPolynomials();
            break;
        }
        case '3':{//free calculation by operator
            freeCalculation();
            break;
        }
        case '4':{//assign number to x in Polynomial
            assignCtoX();
            break;
        }
        case '5':{//Close
            return;
        }
        default:{
            std::cout<<"Sorry, I can't understand you."<<std::endl;
            menu();
            break;
        }
    }
}
void saveByName(){
    std::cout<<"You want to call it: ";
    string name;
    string pol;
    std::cin>>name;
    std::cin.ignore(MAX_SIZE);
    bool isNotValid=1;
    if(isUsed(name)){
        std::cout<<"My little brother, this name is used, remember?"<<std::endl;
        saveByName();
    }
    else{
        while(isNotValid){
            std::cout<<"Write the 'ax^n+bx^n-1+...' here: ";
            std::cin>>pol;
            std::cin.ignore(MAX_SIZE);
            isNotValid=!isValidPol(pol);
        }
        Polynomial newpol(name,pol);
        Polynomials.push_back(newpol);//add to vector
        std::cout<<"Fine, now I remember:"<<newpol<<std::endl;
    }
    menu();
}
bool isValidPol(const string& pol);
bool isUsed(string);//friend
void listAllPolynomials(){
    if(!Polynomials.empty();){
        std::cout<<"\tI remember: "<<std::endl;
        for (auto &pol : Polynomials){
            std::cout<<pol1<<std::endl;
        }
    }else{
        std::cout<<"There is nothing to show you."<<std::endl;
    }
    menu();
}
void freeCalculation(){
    std::out<<"Just write what you want to do without space(like: p=p1+p2-p3*p4): ";
    string operation;
    std::cin>>operation;
    std::cin.ignore(MAX_SIZE);
    int operatorIndex[MAX_LENGTH]={0};
    int i=0;
    for(i=0;i<operation.length();++i){

    }
    vector<string> tempstrings;
    string tempstr;

    //vector<Polynomial>::const_iterator iter=findPol(const string& name);
}
vector<Polynomial>::const_iterator findPol(const string& name);
void assignCtoX();
int Polynomial::gcd();
void Polynomial::simp();
Polynomial::Polynomial(const Polynomial &other);
Polynomial::Polynomial(const string & name0, const string & pol0);
Polynomial Polynomial::operator+(const Polynomial &other);
Polynomial Polynomial::operator-(const Polynomial &other);
Polynomial Polynomial::operator*(const Polynomial &other);
Polynomial Polynomial::operator=(const Polynomial &other);
Polynomial Polynomial::operator<<(const Polynomial &other);// p=ax+b , no endl