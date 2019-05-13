#include<iostream>
#include<vector>
#include<string>
#include <cmath>
#define MAX_TIMES 20
#define MAX_LENGTH 10
#define MAX_SIZE 1024
#include"source.hpp"
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
bool isValidPol(const std::string& pol){
    bool isValid=false;
    //.find(",")=4294967295 means didn't find it ,I don't know why
    if(pol.find("(")!=4294967295&&pol.find(")")!=4294967295
    &&pol.find(",")!=4294967295)
        isValid=true;
    return isValid;
}
bool isUsed(const std::string& name){//friend
    vector<Polynomial>::iterator iter=Polynomials.begin();
    bool used=false;
    for(iter=Polynomials.begin();iter!=Polynomials.end();++iter){
        if(iter->name==name){
            used=true;
        }
    }
    return used;
}
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
void freeCalculation(){//just calculate from left to right
    std::out<<"Just write what you want to do without space(like: p=p1+p2-p3*p4): ";
    std::string operation;//"p=p1+p2-p3*p4"
    bool existAssign=0;
    std::string pol_name;//the pol to assign
    std::string pol_name2;//the temp pol
    int cntIndex=0;
    Polynomial answer;
    std::cin>>operation;
    std::cin.ignore(MAX_SIZE);

    //find the index of operators
    vector<int> operatorIndex; //store the index of operator
    int i=0;
    for(i=0;i<operation.length();++i){
        if(operation[i]=='+'||operation[i]=='-'||
        operation[i]=='*'||operation[i]=='='||){
            operatorIndex.push_back(i);
            if(operation[i]=='='){
                existAssign=1;
            }
        }
    }//end find the index of operators

    //deal with '='
    vector<Polynomial>::const_iterator thePol;
    if(existAssign){//pol=...
        if(isValidPol(pol_name)){
            thePol=findPol(pol_name);// is like pointer
            thePol.assign(operation,0,operatorIndex.at(0));
            ++cntIndex;
        }else{
            std::cout<<"Error, couldn't find "<<pol_name<<" ."<<std::endl;
            return;
        }
    }//end deal with '='

    //calculate
    int lastIndex=0;
    bool toSkip=existAssign; //to skip the '='
    vector<Polynomial>::const_iterator thePol2;//the pol to +-*
    for (cntIndex;cntIndex<operatorIndex.size();++cntIndex){
        if(toSkip) {
            toSkip=0;
            continue;
        };//to skip the '='
        pol_name2.assign(operation,operatorIndex.at(cntIndex-1) + 1,
        operatorIndex.at(cntIndex)-operatorIndex.at(cntIndex-1) - 1);//match the name between  operator
        if(isValidPol(pol_name2)){
            thePol2=findPol(pol_name2);
        else{
            std::cout<<"Error, couldn't find "<<pol_name2<<" ."<<std::endl;
            return;
        }

        switch(operation[operatorIndex.at(cntIndex)]){// debug: maybe ?
            case '+':{
                answer += thePol2;
                break;
            }
            case '-':{
                answer -= thePol2;
                break;
            }
            case '*':{
                answer *= thePol2;
                break;
            }
            default:{
                std::cout<<"Fail to match the operator "<<operation[operatorIndex.at(cntIndex)]<<" ."<<endl;
                return;
                break;
            }
        }
    }//end calculate

    if(existAssign){
        *thePol=answer;
        std::cout<<pol_name<<" = "<<*thePol<<std::endl;
    }else{
        std::cout<<"The answer is "<<answer<<std::endl;
    }
}
vector<Polynomial>::iterator findPol(const string& name){
    //find in <vector>Polynomials
    //already verified that name is in Polynomials
    vector<Polynomial>::iterator iter=Polynomials.begin();
    for(iter=Polynomials.begin();iter!=Polynomials.end();++iter){
        if(iter->name==name){
            return iter;
        }
    }
    std::cout<<"Error, didn't find the name in Polynomials"<<std::endl;
}
void assignCtoX(){
    int value=0;
    string pol_name;
    std::cout<<"The name of 'ax^n+bx^(n-1)+...' is: ";
    std::cin>>pol_name;
    vector<Polynomial>::const_iterator thePol;
    if(isValidPol(pol_name)){
        thePol=findPol(pol_name);
        std::cout<<"x = ";
        std::cin>>value;
        std::cout<<pol_name<<" = "<<thePol->assign(value)<<std::endl;
    }else{
        std::cout<<"Error, couldn't find "<<pol_name<<" ."<<std::endl;
        assignCtoX();
    }
}
long long int Polynomial::assign(int c){
    long long int value=0;
    int i=0;
    for(i=0;i<MAX_TIMES;++i){
        value+=pol[i]*std::pow(c,i);
    }
    return value;
}
int Polynomial::gcd()const{
    int theGcd=1;
    int i=0;
    for(i=0;pol[i]==0;++i); //find a not 0 coefficient(xishu)
    int chosen=abs(pol[i]);  //the not 0 coefficient(xishu)
    int i2=0;
    bool isGcd=true;
    for(i2=chosen;i2>=1;--i2){
        isGcd=true;
        for(i=0;i<MAX_TIMES;++i){
            if(pol[i]!=0&&pol[i]%i2!=0){
                isGcd=false;
                break;
            }
        }
        if(isGcd){
            theGcd=i2;
            break;
        }
    }
    return theGcd;
}
void Polynomial::simp(){
    int theGcd=gcd();
    int i=0;
    for(i=0;i<MAX_TIMES;++i){
        pol[i]/=theGcd;
    }
}
Polynomial::Polynomial(const Polynomial &other){
    name=other.name;
    int i=0;
    for(i=0;i<MAX_TIMES;++i){
        pol[i]=other.pol[i];
    }
}
Polynomial::Polynomial(const string & name0, const string & pol0){
    name=name0;
    //find x,return the pointer to atoi
    std::string polString=pol0;
    int start=0;
    std::string substring;
    int coefficient=0;  //xishu
    int exponent=0;     //zhishu
    while(true){
        if(start<MAX_LENGTH)
            substring=polString.substr(start);
        if(substring.empty()==false){
            if(coefficient==0)  //is a coefficient
                coefficient=std::stoi(substring);
            else{   //is an exponent
                exponent=std::stoi(substring);
                pol[exponent]=coefficient;
            }
        }else{//the last one whithout x
            if(coefficient!=0&&exponent==0){
                pol[0]=coefficient;
            }
            break;
        };
        //end input as int
        start=polString.find("^");
        //reinitialize
        coefficient=0;  //xishu
        exponent=0;     //zhishu
    }

}
Polynomial Polynomial::operator+(const Polynomial &other){
    Polynomial temp(*this);
    temp.name=this->name;
    int i=0;
    for(i=0;i<MAX_TIMES;++i){
        temp.pol[i]+=other.pol[i];
    }
    return temp;
}
Polynomial Polynomial::operator+=(const Polynomial &other){*this=*this+other;}
Polynomial Polynomial::operator-(const Polynomial &other){
    Polynomial temp(*this);
    temp.name=this->name;
    int i=0;
    for(i=0;i<MAX_TIMES;++i){
        temp.pol[i]-=other.pol[i];
    }
    return temp;
}
Polynomial Polynomial::operator-=(const Polynomial &other){*this=*this-other;}
Polynomial Polynomial::operator*(const Polynomial &other){
    Polynomial temp;
    temp.name=this->name;
    int i1=0;
    int i2=0;
    for(i1=0;i1<MAX_TIMES;++i1){
        for(i2=0;i2<MAX_TIMES;++i2){
            temp.pol[i1+i2]=this->pol[i1]+other.pol[i2];
        }
    }
    return temp;
}
Polynomial Polynomial::operator*=(const Polynomial &other){*this=*this*other;}
void Polynomial::operator=(const Polynomial &other){
    this->name=other.name;
    int i=0;
    for(i=0;i<MAX_TIMES;++i){
        pol[i]=other.pol[i];
    }
}
std::ostream& Polynomial::operator<<(std::ostream& cout){     // p=ax+b , no endl
    cout<<this->name<<"=";
    int i=0;
    bool isFirst=true;
    for(i=MAX_TIMES-1;i>=0;--i){
        if(this->pol[i]!=0){
            if(this->pol[i]>0&&isFirst==false) cout<<"+";
            if(isFirst) isFirst=false;
            cout<<this->pol[i];
            if(i!=0) cout<<"x^"<<i;
        }
    }
    return cout;
}
Polynomial::Polynomial(){
    name="";
    int i=0;
    for(i=0;i<MAX_TIMES;++i){
        pol[i]=0;
    }
}