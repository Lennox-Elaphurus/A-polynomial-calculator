#include<iostream>
#include<vector>
#define MAX_TIMES 20
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
void freeCalculation(){//just calculate from left to right
    std::out<<"Just write what you want to do without space(like: p=p1+p2-p3*p4): ";
    string operation;
    bool existAssign=0;
    string pol_name;//the pol to assign
    string pol_name2;//the temp pol
    int cntIndex=0;
    Polynomial answer;
    std::cin>>operation;
    std::cin.ignore(MAX_SIZE);

    //find the index of operators
    vector<int> operatorIndex;
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
    if(existAssign){//pol=...
        if(isValidPol(pol_name)){
            vector<Polynomial>::const_iterator thePol=findPol(pol_name);// is like pointer
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
vector<Polynomial>::const_iterator findPol(const string& name);
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
        std::cout<<pol_name<<" = "<<thePol->assign(value);<<endl;
    }else{
        std::cout<<"Error, couldn't find "<<pol_name<<" ."<<std::endl;
        assignCtoX();
    }
}
long long int Polynomial::assign(int c);
int Polynomial::gcd();
void Polynomial::simp();
Polynomial::Polynomial(const Polynomial &other);
Polynomial::Polynomial(const string & name0, const string & pol0);
Polynomial Polynomial::operator+(const Polynomial &other);
Polynomial Polynomial::operator+=(const Polynomial &other);
Polynomial Polynomial::operator-(const Polynomial &other);
Polynomial Polynomial::operator-=(const Polynomial &other);
Polynomial Polynomial::operator*(const Polynomial &other);
Polynomial Polynomial::operator*=(const Polynomial &other);
Polynomial Polynomial::operator=(const Polynomial &other);
Polynomial Polynomial::operator<<(const Polynomial &other);// p=ax+b , no endl
Polynomial::Polynomial(){
    name="";
    int i=0;
    for(i=0;i<MAX_TIMES+1;++i){
        pol[i]=0;
    }
}