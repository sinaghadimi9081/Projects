#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void getOption(string &option);
void menu();
void getCin(int &left,char & oper,int &right);
void showerror();

//__________________________________________________________________________________
//----------------------------------------------------------------------------------
//enum list {add,listall,listbyoperator,listsummary,quit};
class Expression{
    private:
    int p_left;
    char p_oper;
    int p_right;
    public:
    Expression (int left,char oper,int right): p_left(left),p_oper(oper),p_right(right){
    }
    char getP_oper(){
        return p_oper;
    }
    int result(){
    int result=0;
    switch (p_oper){
    case '+':
        result=p_left+p_right;
        break;
    case '-':
        result=p_left-p_right;
        break;
    case '*':
        result=p_left*p_right;
        break;
    case '/':
        result=p_left/p_right;
        break;
    case '%':
        result=p_left%p_right;
        break;
    }
    return result;
}
    string toString(){
        stringstream add;
        add << setw(5)<<p_left<<setw(5)<<p_oper<<setw(5)<<p_right<<setw(5)<<" = "<<result()<<'\n';
        string expression=add.str();
        return expression;
    }
    Expression *clone(){
        Expression *clone=new Expression(p_left,p_oper,p_right);
        return clone;
    }

};

string listall(vector<Expression> &list,int size){
        string expression;
        string history;
        for (int i=0;i<size;i++){
            expression=list[i].toString();
            history=history+expression+'\n';
        }
        return history;
}

string listbyoperator(vector<Expression> &list,int size,char userOperator){
        string expression;
        string history;

        if (userOperator!='+' && userOperator!='-' && userOperator!='*' && userOperator!='/' && userOperator!='%'){
            stringstream stream;
            stream<<"No expression is found with the operator:"<<setw(1)<<userOperator<<endl;
            string error=stream.str();
            return error;
        }
        for (int i=0;i<size;i++){
            if(userOperator==list[i].getP_oper()){
                if(userOperator=='+'){
                    expression=list[i].toString();
                    history=history+expression+'\n';
                }
                if(userOperator=='-'){
                    expression=list[i].toString();
                    history=history+expression+'\n';
                }
                if(userOperator=='*'){
                    expression=list[i].toString();
                    history=history+expression+'\n';
                }
                if(userOperator=='/'){
                    expression=list[i].toString();
                    history=history+expression+'\n';
                }
                if(userOperator=='%'){
                    expression=list[i].toString();
                    history=history+expression+'\n';
                }
            }
        }
        if (history==""){
            stringstream error;
            error<<"No expression is found with the operator: "<<userOperator<<endl;
            history=error.str();
        }
        return history;
    }

void listsummary(vector<Expression> &list,int size){
    int sum=0;
    int reduction=0;
    int multiple=0;
    int division=0;
    int modular=0;
    int max=-2147483647;
    int min=2147483647;
    for (int i=0;i<size;i++){
            if(list[i].getP_oper()=='+'){
                sum++;
            }
            if(list[i].getP_oper()=='-'){
                reduction++;
            }
            if(list[i].getP_oper()=='*'){
                multiple++;
            }
            if(list[i].getP_oper()=='/'){
                division++;
            }
            if(list[i].getP_oper()=='%'){
                modular++;
            }
            if(list[i].result()>max){
                max=list[i].result();
            }
            if(list[i].result()<min){
                min=list[i].result();
            }
        }
    cout<<"Total number of expressions: "<<size<<endl;
    cout<<"Number of '+' expression: "<<sum<<endl;
    cout<<"Number of '-' expression: "<<reduction<<endl;
    cout<<"Number of '*' expression: "<<multiple<<endl;
    cout<<"Number of '/' expression: "<<division<<endl;
    cout<<"Number of '%' expression: "<<modular<<endl;
    cout<<"Largest expression: "<<max<<endl;
    cout<<"Smallest expression: "<<min<<endl;
}

int main (){
    int index=0;
    string option;
    int left,right;
    char oper;
    vector<Expression> list;
    cout<<"Welcome to expression managemnt program"<<endl;
    menu();
    getOption(option);
    //checkoption(option);
    while (option!="quit"){
        if(option=="add"){
            getCin(left,oper,right);
            if(cin.fail()){
                showerror();
            }
            else if((oper!='*' && oper!='-' && oper!='+' && oper!='/' && oper!='%')){
                cout<<"Unsupported expression operator."<<endl;
            }
            else{
                Expression newexpression(left,oper,right);
                list.push_back(newexpression);
                cout<<list[index].toString();
                index++;
            }
            menu();
            cin.ignore(214748,'\n');
        }    
        else if(option=="listall"){
            int size=list.size();
            if (size==0){
                cout<<"There is no expression"<<endl;
            }
            else{
                cout<<listall(list,size);
            }
            menu(); 
        }
        else if(option=="listbyoperator"){
            int size=list.size();
            if (size==0){
                cout<<"There is no expression"<<endl;
            }
            else{
                char userOperator;
                cout<<"Please enter the operator:"<<endl;
                cin>>userOperator;
                cout<<listbyoperator(list,list.size(),userOperator);
                cin.ignore(214748,'\n');
            }
            menu(); 
        }
        else if(option=="listsummary"){
            int size=list.size();
            if(size==0){
                cout<<"There is no expression"<<endl;
            }
            else{
                listsummary(list,size);
            }
            menu(); 
        }
        
        else if(option=="exit"){
            break;
        }
        else{
            cout<<"Unsupported command. Please try again."<<endl;
            menu();
        }
        
        getOption(option);
    }
    //cout<<list.size()<<endl;
    cout<<"Thank you. Goodbye.";
    return 0;
}


//________________________________________________________________________________________________________________
//----------------------------------------------------------------------------------------------------------------
void getCin(int &left,char & oper,int &right){
cout<<"Enter an expression:"<<endl;
    cin>>left;
    cin>>oper;
    cin>>right;
}
void getOption(string &option){
    cin.clear();
    getline(cin,option);
}
void menu(){
    cout<<"Please enter a command (add, listall, listbyoperator, listsummary, exit): ";
}
void showerror(){
    cin.clear();
    cin.ignore();
    cout<<"Invalid operand. Number is expected."<<endl;
}
