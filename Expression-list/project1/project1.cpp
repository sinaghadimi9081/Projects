#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;
void menu(int & choice){
    cout<<"Enter 1 to 4 to choose an option from below: \n";
    cout<<"1) Enter a new expression: \n";
    cout<<"2) Show the largest expression \n";
    cout<<"3) Show all expressions \n";
    cout<<"4) Exit \n";
}
void test(int & num){
        while (cin.fail()){
        cout << "Your input is invalid, please try again: \n";
        cin.clear();
        cin.ignore(INT16_MAX,'\n');
        cin>>num;
    }
}

void optiontest(int & num){
        while (cin.fail() || num<1 || num>4){
        cout << "Your input is invalid, please try again: \n";
        cin.clear();
        cin.ignore(INT16_MAX,'\n');
        cin>>num;
    }
}
void newexpression(string & history, string & maxexpression, int & max){
    int righthand=0;
    int lefthand=0;
    char oper= ' ';
    cout <<"Please enter your expression: \n";
    cin>> righthand;
    test(righthand);
    cin>> oper;
    while (!((oper=='*')||(oper=='-')||(oper=='/')||(oper=='+')||(oper=='%'))){
        cout << "Your input is invalid, please try again: \n";
        cin.clear();
        cin.ignore(132,'\n');
        cin>>oper;
    }
    cin>>lefthand;
    test(lefthand);
    int result;
    switch (oper){
    case '+':
        result=righthand+lefthand;
        break;
    case '-':
        result=righthand-lefthand;
        break;
    case '*':
        result=righthand*lefthand;
        break;
    case '/':
        result=righthand/lefthand;
        break;
    
    case '%':
        result= righthand %  lefthand;
        break;
    }
    if (result>max){
        max=result;
        stringstream expressionmax;
        expressionmax << setw(5)<<righthand<<setw(5)<<oper<<setw(5)<<lefthand<<setw(5)<<" = "<<max<<'\n';
        maxexpression=expressionmax.str();
    }

    stringstream stream;
    stream << setw(5)<<righthand<<setw(5)<<oper<<setw(5)<<lefthand<<setw(5)<<" = "<<result<<'\n';
    string expression2=stream.str();
    cout  <<expression2;   
    history=history+expression2+'\n';
    
    
}

// void maxtest(int & result,int & righthand,int & lefthand, char & oper){
//     righthand=0;
//     lefthand=0;
//     char oper= ' ';
//     cout <<"Please enter the righthand \n";
//     cin>> righthand;
//     test(righthand);
//     cin>> oper;
//     while (!((oper=='*')||(oper=='-')||(oper=='/')||(oper=='+')||(oper=='%'))){
//         cout << "Your input is invalid, please try again: \n";
//         cin.clear();
//         cin.ignore(132,'\n');
//         cin>>oper;
//     }
//     cin>>lefthand;
//     test(lefthand);
//     int result;
//     if (oper=='+'){
//         result=righthand+lefthand;
//     }
//     if (oper=='-'){
//         result=righthand-lefthand;
//     }
//     if (oper=='*'){
//         result=righthand*lefthand;
//     }
//     if (oper=='/'){
//         result=righthand/lefthand;
//     }
//     if (oper=='%'){
//         result= righthand %  lefthand;
//     }
//     int max=0;
//     if (result>max){
//         max=result;
//     }
//     stringstream maxexper;
//     maxexper <<setw(5)<<righthand<<setw(5)<<oper<<setw(5)<<lefthand<<setw(5)<<" = "<<max<<'\n';
//     string maxexperession=maxexper.str();
//     cout  <<maxexperession; 
// }
void case1error(string & history, int & option){
    do{
        if(history==""){
            cout<<"There is no expression yet \nenter 1,3,4 to go back to menu and choose again:\n";
            cin>>option;
            optiontest(option);
        }
        else {
            cout<<history;
            cout<<"enter 1,3,4 to go back to menu and choose again or enter 2 to see the max expression again ";
            cin>>option;
            optiontest(option);
        }
    }while(option==2);
}
void case2error(string & history, int & option){
    do{
        if(history==""){
            cout<<"There is no expression yet \nenter 1,2,4 to go back to menu and choose again:\n";
            cin>>option;
            optiontest(option);
        }
        else {
            cout<<history;
            cout<<"enter 1,2,4 to go back to menu and choose again or enter 3 to see all expression again ";
            cin>>option;
            optiontest(option);
        }
    }while(option==3);
}
int main(){
    int result,righthand,lefthand;
    int max=-2147483647;
    char oper;
    string maxexpression;
    string history = "";
    int option;
    menu(option);
    cin>>option;
    optiontest(option);
    while (option==1 || option==2|| option==3 ){
        switch (option){
            case 1:
            do {
                newexpression(history,maxexpression,max);
                //menu(option);
                cout<<"Enter 1 to enter an expression again \nEnter 2,3,4 to go back to menu and choose from menu again:";
                cin>>option;
                optiontest(option);
            }while(option==1);
            menu(option);
            cin>>option;
            optiontest(option);
            break;
            case 2:
            case1error(maxexpression,option);
            cout<<maxexpression;
            menu(option);
            cin>>option;
            optiontest(option);
            break;
            case 3://all the expressions
            case2error(history,option);
            cout<<history;
            menu(option);
            cin>>option;
            optiontest(option);
            break;
        }
    }
    cout<<"bye!";
    return 0;
}
