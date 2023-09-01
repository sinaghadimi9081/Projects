#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <exception>
using namespace std;

void getOption(string &option);
void menu();
//__________________________________________________________________________________
//----------------------------------------------------------------------------------
class ExceptionClass:public runtime_error{
    public:
    ExceptionClass(string error):runtime_error(error){
    }
    virtual string toString(){
        stringstream errormessage;
        errormessage<<what();
        return errormessage.str();
    }
};
class Expression{
    private:
    int p_left;
    char p_oper;
    int p_right;
    public:
    Expression (int left,char oper,int right): p_left(left),p_oper(oper),p_right(right){
        if (cin.fail()){
            cin.clear();
            cin.ignore();
            throw new ExceptionClass("Invalid operand. Number is expected.");
        }
        if((oper!='*' && oper!='-' && oper!='+' && oper!='/' && oper!='%')){
            throw new ExceptionClass("Unsupported expression operator.");
        }
    }
    virtual char getP_oper(){
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
    virtual string toString(){
        stringstream add;
        add << setw(5)<<p_left<<setw(5)<<p_oper<<setw(5)<<p_right<<setw(5)<<" = "<<result();
        string expression=add.str();
        return expression;
    }
    Expression *clone(){
        Expression *clone=new Expression(p_left,p_oper,p_right);
        return clone;
    }
};
class NamedExpression:public Expression{
    private:
    string p_name;
    public:
    NamedExpression(int left,char oper, int right, string name):Expression(left,oper,right),p_name(name){
        if(isalpha(name[0])==false){
            throw new ExceptionClass("First character is not valid");
        }
    }
    string toString(){
        stringstream namedexpression;
        namedexpression<<Expression::toString()<<setw(5)<<"NAME"<<"("<<p_name<<")"<<endl;
        return namedexpression.str();
    }
};
string listall(vector<Expression*> &list){
    string expression;
    string history;
    for (int i=0;i<list.size();i++){
        expression=list[i]->toString();
        history=history+expression+'\n';
    }
    return history;
}

string listbyoperator(vector<Expression*> &list,char userOperator){
        string expression;
        string history;
        if (userOperator!='+' && userOperator!='-' && userOperator!='*' && userOperator!='/' && userOperator!='%'){
            stringstream stream;
            stream<<"No expression is found with the operator:"<<setw(1)<<userOperator<<endl;
            string error=stream.str();
            return error;
        }
        for (int i=0;i<list.size();i++){
            if(userOperator==list[i]->getP_oper()){
                if(userOperator=='+'){
                    expression=list[i]->toString();
                    history=history+expression+'\n';
                }
                if(userOperator=='-'){
                    expression=list[i]->toString();
                    history=history+expression+'\n';
                }
                if(userOperator=='*'){
                    expression=list[i]->toString();
                    history=history+expression+'\n';
                }
                if(userOperator=='/'){
                    expression=list[i]->toString();
                    history=history+expression+'\n';
                }
                if(userOperator=='%'){
                    expression=list[i]->toString();
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

void listsummary(vector<Expression*> &list){
    int sum=0;
    int reduction=0;
    int multiple=0;
    int division=0;
    int modular=0;
    int max=-2147483647;
    int min=2147483647;
    for (int i=0;i<list.size();i++){
            if(list[i]->getP_oper()=='+'){
                sum++;
            }
            if(list[i]->getP_oper()=='-'){
                reduction++;
            }
            if(list[i]->getP_oper()=='*'){
                multiple++;
            }
            if(list[i]->getP_oper()=='/'){
                division++;
            }
            if(list[i]->getP_oper()=='%'){
                modular++;
            }
            if(list[i]->result()>max){
                max=list[i]->result();
            }
            if(list[i]->result()<min){
                min=list[i]->result();
            }
        }
    cout<<"Total number of expressions: "<<list.size()<<endl;
    cout<<"Number of '+' expression: "<<sum<<endl;
    cout<<"Number of '-' expression: "<<reduction<<endl;
    cout<<"Number of '*' expression: "<<multiple<<endl;
    cout<<"Number of '/' expression: "<<division<<endl;
    cout<<"Number of '%' expression: "<<modular<<endl;
    cout<<"Largest expression: "<<max<<endl;
    cout<<"Smallest expression: "<<min<<endl;
}
void constructobject(vector<Expression*>&Expression_List,int &Expression_index){
    try{
        string name;
        int left,right;
        char oper;
        cout<<"Enter an expression:"<<endl;
        getline(cin,name);
        cin>>left;
        cin>>oper;
        cin>>right;
        if(name[0]!='\0'){
            NamedExpression *newNamedExpression= new NamedExpression(left,oper,right,name);
            Expression_List.push_back(newNamedExpression);
            cout<<Expression_List[Expression_index]->toString();
            Expression_index++;
        }
        else{
            Expression *newexpression= new Expression(left,oper,right);
            Expression_List.push_back(newexpression);
            cout<<Expression_List[Expression_index]->toString()<<endl;
            Expression_index++;
        }
    }
    catch(ExceptionClass *PBadname){
        cout<<PBadname->what()<<endl;
    }

}
int main (){
    int Expression_index=0;
    int NamedExpression_index=0;
    string option;
    vector<Expression*> Expression_List;
    cout<<"Welcome to expression managemnt program"<<endl;
    menu();
    getOption(option);
    while (option!="quit"){
        if(option=="add"){
            constructobject(Expression_List,Expression_index);
            menu();
            cin.ignore(214748,'\n');
        }    
        else if(option=="listbyoperator"){
            if (Expression_List.size()==0){
                cout<<"There is no expression"<<endl;
            }
            else{
                char userOperator;
                cout<<"Please enter the operator:"<<endl;
                cin>>userOperator;
                cout<<listbyoperator(Expression_List,userOperator);
                cin.ignore(214748,'\n');
            }
            menu(); 
        }
        else if(option=="listsummary"){
            if(Expression_List.size()==0){
                cout<<"There is no expression"<<endl;
            }
            else{
                listsummary(Expression_List);
            }
            menu(); 
        }
        else if(option=="listall"){;
            if (Expression_List.size()==0){
                cout<<"There is no expression"<<endl;
            }
            else{
                cout<<listall(Expression_List);
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
    cout<<"Thank you. Goodbye.";
    return 0;
}
//________________________________________________________________________________________________________________
//----------------------------------------------------------------------------------------------------------------
void getOption(string &option){
    cin.clear();
    getline(cin,option);
}
void menu(){
    cout<<"Please enter a command (add, listall, listbyoperator, listsummary, exit): ";
}
