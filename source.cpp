#include<iostream>
#include<vector>
#include<string>
#include <cmath>
#define MAX_TIMES 20
#define MAX_LENGTH 10
#define MAX_SIZE 1024
#define MAX_POLS 100
#define MAX_OPERATIONS 100
#include"source.hpp"
Polynomial Polynomials[MAX_POLS];
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
    &&pol.find(",")!=4294967295&&pol.find(" ")!=4294967295)
        isValid=true;
    return isValid;
}
bool isUsed(const std::string& name){//friend
    std::vector<Polynomial>::iterator iter=Polynomials.begin();
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
"""
Procedure:
1.find the index of operator in the string,put them into std::vector<int> operatorIndex
2.check whether there is a "=",let left value be the pol(check everytime input a pol)
3.for each step of calculation:
    take the string between each operator as a pol
    take out a operator from the operation list
    assign the result to "answer" or the p he wants

Polynomial Polynomials[MAX_POLS]
"""
    std::out<<"Just write what you want to do without space(like: p=p1+p2-p3*p4): ";
    std::string combinedPol;//e.g."p=p1+p2-p3*p4" ,space is not allowed
    bool existAssignOperator=0;//exist "="
    std::string pol_name;//the pol to assign
    std::string pol_name_tmp;//the temp pol
    int cntIndex=0;
    //count the number of operators,then use as index,for there may exist"="
    //e.g.(cntIndex;cntIndex<operatorIndex.size();++cntIndex)
    Polynomial answer;
    std::cin>>combinedPol;
    std::cin.ignore(MAX_SIZE);

    //find the index of operators
    int operatorIndex[MAX_TIMES]=0; //store the index of operator
    int i=0;
    int i2=0;
    for(i=0;i<combinedPol.length();++i){
        if(combinedPol[i]=='+'||combinedPol[i]=='-'
        ||combinedPol[i]=='*'||combinedPol[i]=='='){
            //operatorIndex.push_back(i);
            for(i2=0;i2<MAX_OPERATIONS;++i2){
                if(operatorIndex[i2]!=0){
                    operatorIndex[i2]=i;
                    break;
                }
            }
            if(combinedPol[i]=='='){
                existAssignOperator=1;
            }
        }
    }//end find the index of operators

    //deal with '='
    Polynomial* thePol;
    if(existAssignOperator){//pol=...
        if(isValidPol(pol_name)){
            thePol=findPol(pol_name);// is like pointer,let the p in p=...,pointed by thePol
            //thePol.assign(combinedPol,0,operatorIndex.at(0));
            ++cntIndex;//turn to next operation
        }else{
            std::cout<<"Error, couldn't find "<<pol_name<<" ."<<std::endl;
            return;
        }
    }//end deal with '='

    //calculate
    int lastIndex=0;
    bool toSkip=existAssignOperator; //to skip the '='
    std::vector<Polynomial>::const_iterator thePol2;//the pol to +-*
    for (cntIndex;cntIndex<operatorIndex.size();++cntIndex){
        if(toSkip) {
            toSkip=0;
            continue;
        };//to skip the '='
        pol_name_tmp.assign(combinedPol,operatorIndex.at(cntIndex-1) + 1,
        operatorIndex.at(cntIndex)-operatorIndex.at(cntIndex-1) - 1);//match the name between  operator
        if(isValidPol(pol_name_tmp)){
            thePol2=findPol(pol_name_tmp);
        }else{
            std::cout<<"Error, couldn't find "<<pol_name_tmp<<" ."<<std::endl;
            return;
        }

        switch(combinedPol[operatorIndex.at(cntIndex)]){// debug: maybe ?
            case '+':{
                answer += *thePol2; //thePol2 is a const_iterator
                break;              //answer is a Polynomial
            }
            case '-':{
                answer -= *thePol2;
                break;
            }
            case '*':{
                answer *= *thePol2;
                break;
            }
            default:{
                std::cout<<"Fail to match the operator "<<combinedPol[operatorIndex.at(cntIndex)]<<" ."<<std::endl;
                return;
                break;
            }
        }
    }//end calculate

    if(existAssignOperator){
        *thePol=answer;
        std::cout<<pol_name<<" = "<<*thePol<<std::endl;
    }else{
        std::cout<<"The answer is "<<answer<<std::endl;
    }
}
std::vector<Polynomial>::iterator findPol(const string& name){
    //find in <vector>Polynomials
    //already verified that name is in Polynomials
    std::vector<Polynomial>::iterator iter=Polynomials.begin();
    for(iter=Polynomials.begin();iter!=Polynomials.end();++iter){
        if(iter->name==name){
            return iter;
        }
    }
    std::cout<<"Error, didn't find the name in Polynomials"<<std::endl;
}
void assignCtoX(){
    int value=0;
    std::string pol_name;
    std::cout<<"The name of 'ax^n+bx^(n-1)+...' is: ";
    std::cin>>pol_name;
    std::vector<Polynomial>::iterator thePol;
    //std::iterator thePol;
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
std::ostream& operator<<(std::ostream& cout,const Polynomial& thePol){     // p=ax+b , no endl,friend
    cout<<thePol.name<<"=";
    int i=0;
    bool isFirst=true;
    for(i=MAX_TIMES-1;i>=0;--i){
        if(thePol.pol[i]!=0){
            if(thePol.pol[i]>0&&isFirst==false) cout<<"+";
            if(isFirst) isFirst=false;
            cout<<thePol.pol[i];
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