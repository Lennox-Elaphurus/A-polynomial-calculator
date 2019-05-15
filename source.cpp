#include<iostream>
#include<string>
#include <math.h>
#define MAX_TIMES 20
#define MAX_LENGTH 10
#define MAX_SIZE 1024
#define MAX_POLS 100
#define MAX_OPERATIONS 100
#include"source.hpp"
Polynomial Polynomials[MAX_POLS];
void menu(){
    std::cout<<"\nYou want to:"<<std::endl;
    std::cout<<"\t[1] Write 'ax^n+bx^n-1+...' as 'p'\n"//write and save by name
    <<"\t[2] Watch 'ax^n+bx^(n-1)+...' you wrote\n"//list the stored Polynomials
    <<"\t[3] p1 + p2 - p3 * p4 (write as you want)\n"//free calculation by operator
    <<"\t[4] When x = c, 'ax^n+bx^(n-1)+...' = ?\n"//assign number to x in Polynomial
    <<"\t[5] Close\n";
    std::cout<<"1/2/3/4/5?"<<std::endl;
    int operation=0;
    std::cin>>operation;
    //std::cin.ignore(MAX_SIZE);
    switch(operation){
        case 1:{//write and save by name
            saveByName();
            break;
        }
        case 2:{//list the stored Polynomials
            listAllPolynomials();
            break;
        }
        case 3:{//free calculation by operator
            freeCalculation();
            break;
        }
        case 4:{//assign number to x in Polynomial
            assignCtoX();
            break;
        }
        case 5:{//Close
            return;
        }
        default:{
            std::cout<<"Sorry, I can't understand you."<<std::endl;
            std::cout<<"Your entered: "<<operation<<std::endl;
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
    bool isValid=false;
    if(isUsed(name)){
        std::cout<<"My little brother, this name is used, remember?"<<std::endl;
        std::cout<<"Try again."<<std::endl;
        saveByName();
    }
    else{
        while(true){
            std::cout<<"Write the 'ax^n+bx^n-1+...(cx^0)' here: ";
            std::cin>>pol;
            isValid=isValidPol(pol);
            if(isValid==true) break;//is valid
            std::cout<<"You entered ‘"<<pol<<"’ .It's not valid."<<std::endl;
            std::cout<<"Please write as 'ax^n+bx^n-1+...'."<<std::endl;
        }
        Polynomial newpol(name,pol);
        Polynomial* write=findPol("DEFAULT");//find an empty element
        *write=newpol;//add to list
        std::cout<<"Fine, now I remember:"<<*write<<std::endl;
    }
    menu();
}
bool isValidPol(const std::string& pol){
    bool isValid=false;
    //.find(",")=4294967295 means didn't find it ,I don't know why
    if(pol.find("(")==4294967295&&pol.find(")")==4294967295
    &&pol.find(",")==4294967295&&pol.find(" ")==4294967295)
        isValid=true;
    return isValid;
}
bool isUsed(const std::string& name){//friend
    Polynomial* polPtr=&Polynomials[0];
    bool used=false;
    //std::cout<<"Verifying '"<<name<<"'."<<std::endl;
    for(polPtr;polPtr!=&Polynomials[MAX_POLS];++polPtr){
        if(polPtr->name==name){
            used=true;
            break;
        }
    }
    return used;
}
void listAllPolynomials(){
    int i=0;
    if((Polynomials[0].name)!="DEFAULT"){
        std::cout<<"I remember: "<<std::endl;
        for (i=0;i<MAX_POLS;++i){
            if(Polynomials[i].name!="DEFAULT")
                std::cout<<"\t"<<Polynomials[i]<<std::endl;
        }
    }else{
        std::cout<<"There is nothing to show you."<<std::endl;
    }
    menu();
}
void freeCalculation(){//just calculate from left to right
/*
Procedure:
1.find the index of operator in the string,put them into int[] operatorIndex
2.check whether there is a "=",let left value be the pol(check everytime input a pol)
3.for each step of calculation:
    take the string between each operator as a pol
    take out a operator from the operation list
    assign the result to "answer" or the p he wants

How to verify whether it is the end?
Polynomial Polynomials[MAX_POLS]
*/
    std::cout<<"Just write what you want to do without space(like: p=p1+p2-p3*p4): ";
    std::string combinedPol;//e.g."p=p1+p2-p3*p4" ,space is not allowed
    bool existAssignOperator=0;//exist "="
    std::string pol_name;//the pol to assign
    std::string pol_name_tmp;//the temp pol
    int cntIndex=0;
    //count the number of operators,then use as index,for there may exist"="
    //e.g.(cntIndex;cntIndex<operatorIndex.size();++cntIndex)
    Polynomial answer;
    std::cin>>combinedPol;
    //std::cin.ignore(MAX_SIZE);

    //find the index of operators
    int operatorIndex[MAX_TIMES]={0}; //store the index of operator
    int i=0;
    int i2=0;
    for(i=0;i<combinedPol.length();++i){
        if(combinedPol[i]=='+'||combinedPol[i]=='-'
        ||combinedPol[i]=='*'||combinedPol[i]=='='){
            //operatorIndex.push_back(i);
            for(i2=0;i2<MAX_OPERATIONS;++i2){
                if(operatorIndex[i2]==0){
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
    Polynomial newPol(pol_name);
    if(existAssignOperator){//pol=...
        pol_name=mysubstr(combinedPol,0,operatorIndex[cntIndex]);
        //thePol.assign(combinedPol,0,operatorIndex.at(0));
        ++cntIndex;//turn to next operation
        if(isUsed(pol_name)){
            std::cout<<"valid pol_name:'"<<pol_name<<"' ."<<std::endl;
            thePol=findPol(pol_name);// is like pointer,let the p in p=...,pointed by thePol
        }else{
            std::cout<<"You used a new name: '"<<pol_name<<"' ."<<std::endl;
            thePol=findPol("DEFAULT");//find an empty element
            *thePol=newPol;
        }
    }//end deal with '='

    //calculate
    bool isFirst=true;//is the first time in the for
    if(existAssignOperator) isFirst=false;
    Polynomial* thePol_tmp;//the pol to +-*
    for (cntIndex;cntIndex<MAX_TIMES;++cntIndex){
        if(operatorIndex[cntIndex]==0&&operatorIndex[cntIndex+1]==0) break;
        if(isFirst){
            pol_name_tmp=mysubstr(combinedPol,0,operatorIndex[cntIndex]);
            //isFirst=false; need to change at the end of this turn to use it in switch
        }else{//cntIndex!=0
            pol_name_tmp=mysubstr(combinedPol,operatorIndex[cntIndex],operatorIndex[cntIndex+1]);
        }
        std::cout<<"pol_name_tmp:'"<<pol_name_tmp<<"' ."<<std::endl;
        if(isUsed(pol_name_tmp)){
            //std::cout<<"valid pol_name_tmp:'"<<pol_name_tmp<<"' ."<<std::endl;
            thePol_tmp=findPol(pol_name_tmp);
        }else{
            std::cout<<"Error, couldn't find '"<<pol_name_tmp<<"' ."<<std::endl;
            return;
        }

        switch(combinedPol[operatorIndex[cntIndex]]){// debug: maybe ?
            case '+':{
                answer = answer + *thePol_tmp; //thePol_tmp is a const_iterator
                break;              //answer is a Polynomial
            }
            case '-':{
                answer = answer - *thePol_tmp;
                break;
            }
            case '*':{
                answer = answer * *thePol_tmp;
                break;
            }
            default:{
                std::cout<<"Fail to match the operator '"<<combinedPol[operatorIndex[cntIndex]]<<"' ."<<std::endl;
                return;
                break;
            }
        }
        if(isFirst){
            isFirst=false;
            --cntIndex;
        }
    }//end calculate

    if(existAssignOperator){
        *thePol=answer;
        std::cout<<pol_name<<" = "<<*thePol<<std::endl;
    }else{
        std::cout<<combinedPol<<" = "<<answer<<std::endl;
    }
    menu();
}
Polynomial* findPol(const string& name){
    //find in Polynomials[]
    //already verified that the "name" is in Polynomials
    Polynomial* iter=&Polynomials[0];
    for(iter;iter!=&Polynomials[MAX_POLS];++iter){
        if(iter->name==name){
            return iter;
            std::cout<<"'"<<name<<"' found."<<std::endl;
        }
    }
    std::cout<<"Error, didn't find the '"<<name<<"' in Polynomials."<<std::endl;
    return NULL;
}
void assignCtoX(){
    int value=0;
    std::string pol_name;
    std::cout<<"The name of 'ax^n+bx^(n-1)+...' is: ";
    std::cin>>pol_name;
    Polynomial* thePol;
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
    menu();
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
        pol[i]=0;
    }
    for(i=0;i<MAX_TIMES;++i){
        pol[i]=other.pol[i];
    }
}
Polynomial::Polynomial(const string & name0, const string & pol0){
    name=name0;
    //initialize the latter empty coefficient
    int i=0;
    for(i=0;i<MAX_TIMES;++i){
        pol[i]=0;
    }
    std::string polString=pol0;
    int start=0;//the start of substring1
    int start2=0;//the start of substring2, used to get the second substring
    int plus=0;//the index of the position of "+"
    int minus=0;//the index of the position of "-"
    std::string substring=polString;
    int coefficient=0;  //xishu
    int exponent=0;     //zhishu
    while(true){
        //std::cout<<"Substring brfore:'"<<substring<<"'\n";
        if(start<MAX_LENGTH&&start!=-1&&start!=0)
        // when start=-1,it means didn't find "^"
        //when start=0,it's the original string
            substring=substring.substr(start+1);//substring from the next element of "^"
        //std::cout<<"Substring after:'"<<substring<<"'\n\n";
        if(substring.empty()==false){
            if(coefficient==0)  //is a coefficient
                coefficient=std::stoi(substring);
            else{   //is an exponent
                exponent=std::stoi(substring);
                pol[exponent]=coefficient;
                //reinitialize
                coefficient=0;  //xishu
                exponent=0;     //zhishu
                //end reinitialize
                if(substring.find("^")==-1&&substring.find("+")==-1
                &&substring.find("-")==-1) break;//is the last one
                if(substring.find("+")!=-1||substring.find("-")!=-1){
                //b+cx^d,delete b
                    //find start2
                    plus=substring.find("+");
                    minus=substring.find("-");
                    if(plus==-1){
                        if(minus==-1){//plus=-1,minus=-1
                            start2=0;
                        }else{//plus=-1,minus=c
                            start2=minus;
                        }
                    } else{
                        if(minus==-1){//plus=c,minus=-1
                            start2=plus;
                        }else{//plus=c1,minus=c2
                            start2=plus;
                            if(start2>minus) start2=minus;//to get the first operator
                        }
                    }//end find start2
                    substring=substring.substr(start2);//get the cx^d instead from b+cx^d
                    start=0;//or it will skip the c
                    continue;//don't need to start=substring.find("^");
                }
            }
        }else{//the last one whithout x
            if(coefficient!=0&&exponent==0){
                pol[0]=coefficient;
            }
            break;
        };
        //end input as int
        start=substring.find("^");// what if didn't find ?:return -1
        //std::cout<<"Substring:'"<<substring<<"'\n";
        
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
Polynomial Polynomial::operator-(const Polynomial &other){
    Polynomial temp(*this);
    temp.name=this->name;
    int i=0;
    for(i=0;i<MAX_TIMES;++i){
        temp.pol[i]-=other.pol[i];
    }
    return temp;
}
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
void Polynomial::operator=(const Polynomial &other){
    this->name=other.name;
    int i=0;
    for(i=0;i<MAX_TIMES;++i){
        pol[i]=other.pol[i];
    }
}
std::ostream& operator<<(std::ostream& cout,const Polynomial& thePol){     // p=ax+b , no endl,friend
    if(thePol.name!="DEFAULT") cout<<thePol.name<<"=";
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
    name="DEFAULT"; //the user can't use the name "DEFAULT"
    int i=0;
    for(i=0;i<MAX_TIMES;++i){
        pol[i]=0;
    }
}
std::string mysubstr(const std::string& str,int start,int end){
    std::string tempStr;
    if(end==0) end=str.length();
    int i=start+1;
    if(start==0) i-=1;
    for(i;i<end;++i){
        tempStr+=str[i];
    }
    return tempStr;
}