#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
using namespace std;

class Account{
    private:
    string accountno, password;
    int Balance;
    public:
    Account() : accountno(""), password(""), Balance(0){}

    void setAccountNo(string id) {
        accountno = id;
    }

    void setPassword(string pass) {
        password= pass;
    }

    void setBalance(int balance) {
        Balance = balance;
    }

    string getAccountNo(){
        return accountno;
    }

    string getPassword(){
        return password;
    }

    int getBalance(){
        return Balance;
    }
};

void openAccount(Account user){
system("cls");
string id, pass;

cout<<"\tEnter Account No: ";
cin>>id;
user.setAccountNo(id);

cout<<"\tEnter a strong Password: ";
cin>>pass;
user.setPassword(pass);

user.setBalance(0);

ofstream outfile("C:/Users/Debabrata Kundu/Desktop/account.txt", ios::app);
if(!outfile){
    cout<<"\tError: File can't open!"<< endl;
}
else{
    outfile<<user.getAccountNo()<<":"<<user.getPassword()<<":"<<user.getBalance()<<endl;
    cout<<"\tAccount created successfully!"<<endl;
}
outfile.close();
Sleep(5000);
}

void addCash(Account user){
    system("cls");
    string id;
    cout<<"\tEnter Account No: ";
    cin>>id;

    ifstream infile("C:/Users/Debabrata Kundu/Desktop/account.txt");
    ofstream outfile("C:/Users/Debabrata Kundu/Desktop/temp.txt");

    if(!infile || !outfile) {
        cout<<"\tError: File can't open!"<< endl;
    }

    string line;
    bool found= false;

    while(getline(infile, line)) {
        stringstream ss;
        ss<<line;
        string userid, userpass;
        int userbalance;
        char delimiter;

getline(ss, userid, ':');
getline(ss, userpass, ':');
ss >> userbalance;        if(id == userid){
            found=true;
            int cash;
            cout<<"\tEnter Cash: ";
            cin>>cash;

            int newbalance= userbalance + cash;
            userbalance= newbalance;
            outfile<<userid<<":"<<userpass<<":"<<userbalance<<endl;
            cout<<"\tNew Balance is: "<<userbalance<<endl;
        }
        else{
            outfile<<line<<endl;
        }
    }
    if(!found) {
        cout<<"\t Enter Valid Account no! "<<endl;
    }
    outfile.close();
    infile.close();
    remove("C:/Users/Debabrata Kundu/Desktop/account.txt");
    rename("C:/Users/Debabrata Kundu/Desktop/temp.txt", "C:/Users/Debabrata Kundu/Desktop/account.txt"); 
    Sleep(5000);
}
void withdraw(){
    string id, pass;
    cout<<"\t Enter Account No"<<endl;
    cin>>id;

    cout<<"\t Enter password"<<endl;
    cin>>pass;

    ifstream infile("C:/Users/Debabrata Kundu/Desktop/account.txt");
    ofstream outfile("C:/Users/Debabrata Kundu/Desktop/temp.txt");

    if(!infile || !outfile) {
        cout<<"\tError: File can't open!"<< endl;
    }

    string line;
    bool found= false;

    while(getline(infile, line)) {
        stringstream ss;
        ss<<line;
        string userid, userpass;
        int userbalance;
        char delimiter;

getline(ss, userid, ':');
getline(ss, userpass, ':');
ss >> userbalance;
        if(id == userid && pass == userpass) {
            found=true;
            int cash;
            cout<<"\tEnter Cash: ";
            cin>>cash;
            if(cash <= userbalance) {
                int newBalance= userbalance - cash;
                userbalance= newBalance;
                outfile<<userid<<":"<<userpass<<":"<<userbalance<<endl;
                cout<<"\tTransaction was successful!"<<endl;
                cout<<"\tRemaining balance: "<<userbalance<<endl;
            }
            else {
                cout<<"\tInsufficient balance!"<<endl;
                outfile<<"\t"<<userid<<":"<<"\t"<<userpass<<":"<<"\t"<<userbalance<<endl;
            }
        }
        else{
            outfile<<line<<endl;
        }
    }
    if(!found){
        cout<<"\tInvalid Account No or Password!"<<endl;
    }
    outfile.close();
    infile.close();
    remove("C:/Users/Debabrata Kundu/Desktop/account.txt");
    rename("C:/Users/Debabrata Kundu/Desktop/temp.txt", "C:/Users/Debabrata Kundu/Desktop/account.txt"); 
    Sleep(5000);
}
int main() {
    Account user;

    bool exit= false;
    while(!exit){
        system("cls");
        int val;
        cout<<"\tWelcome to the Bank Account Management System\n";
        cout<<"\t*********************************\n";
        cout<<"\t1. Open new account\n";
        cout<<"\t2. Add cash\n";
        cout<<"\t3. Withdraw cash\n";
        cout<<"\t4. Exit\n";
        cout<<"\tEnter Your Choice: ";
        cin>>val;

        if(val == 1){
            openAccount(user);
        }

        else if(val == 2){
            addCash(user);
        }
        else if(val == 3) {
            withdraw();
        }

        else if(val == 4){
            system("cls");
            exit= true;
            cout<<"\tThank you for using our service!"<<endl;
            Sleep(3000);
        }
        Sleep(3000);
    }
}