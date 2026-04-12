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

ofstream outfile("account.txt", ios::app);
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

void addCash(string currentUser){
    system("cls");

    ifstream infile("account.txt");
    ofstream outfile("temp.txt");

    if(!infile || !outfile) {
        cout<<"\tError: File can't open!"<< endl;
    }

    string line;
    bool found= false;

            int cash;
            cout<<"\tEnter Cash: ";
            cin>>cash;

    while(getline(infile, line)) {
        if(line.empty()) continue;
           
        stringstream ss;
        ss<<line;
        string userid, userpass;
        int userbalance;
        char delimiter;

    getline(ss, userid, ':');
    getline(ss, userpass, ':');
    ss >> userbalance;       
         if(userid == currentUser){
            found=true;
            int newbalance= userbalance + cash;
            userbalance= newbalance;
            outfile<<userid<<":"<<userpass<<":"<<userbalance<<endl;
            cout<<"\tNew Balance is: "<<userbalance<<endl;
            }
            else
            outfile<<line<<endl;
        
    }
    if(!found){
        cout<<"\tUser not found!\n";
    }
    outfile.close();
    infile.close();
    remove("account.txt");
    rename("temp.txt", "account.txt"); 
    Sleep(5000);
}
void withdraw(string currentUser){

    ifstream infile("account.txt");
    ofstream outfile("temp.txt");

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
        if(currentUser == userid) {
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
    remove("account.txt");
    rename("temp.txt", "account.txt"); 
    Sleep(5000);
}
bool login(string &loggedInId) {
    string id, pass;
    cout<<"\tEnter Account No:";
    cin>>id;
    cout<<"\tEnter Password:";
    cin>>pass;

    ifstream infile("account.txt");
    if(!infile) {
        cout<<"\tError opening file!"<<endl;
        return false;
    }
    string line;
    while(getline(infile, line)) {
        if(line.empty()) continue;

        stringstream ss(line);
        string userid, userpass;
        int userbalance;

        getline(ss,userid,':');
        getline(ss,userpass,':');
        ss>>userbalance;

        if(id == userid && pass==userpass) {
            loggedInId= id;
            return true;
        }
    }
    return false;
}
void transferMoney(string senderId){
    system("cls");

    string receiverId;
    cout<<"\tEnter Receiver Account No: ";
    cin>>receiverId;

    int amount;
    cout<<"\tEnter Amount: ";
    cin>>amount;

    ifstream infile("account.txt");
    ofstream outfile("temp.txt");

    if(!infile || !outfile){
        cout<<"\tError opening file!\n";
        return;
    }

    string line;
    bool senderFound = false;
    bool receiverFound = false;

    int senderBalance = 0;

    // First pass: find sender balance
    while(getline(infile, line)){
        if(line.empty()) continue;

        stringstream ss(line);
        string userid, pass;
        int balance;

        getline(ss, userid, ':');
        getline(ss, pass, ':');
        ss >> balance;

        if(userid == senderId){
            senderFound = true;
            senderBalance = balance;
        }

        if(userid == receiverId){
            receiverFound = true;
        }
    }

    infile.close();

    if(!senderFound){
        cout<<"\tSender not found!\n";
        return;
    }

    if(!receiverFound){
        cout<<"\tReceiver not found!\n";
        return;
    }

    if(amount > senderBalance){
        cout<<"\tInsufficient balance!\n";
        return;
    }

    // Second pass: update balances
    infile.open("account.txt");

    while(getline(infile, line)){
        if(line.empty()) continue;

        stringstream ss(line);
        string userid, pass;
        int balance;

        getline(ss, userid, ':');
        getline(ss, pass, ':');
        ss >> balance;

        if(userid == senderId){
            balance -= amount;
        }
        else if(userid == receiverId){
            balance += amount;
        }

        outfile<<userid<<":"<<pass<<":"<<balance<<endl;
    }

    infile.close();
    outfile.close();

    remove("account.txt");
    rename("temp.txt", "account.txt");

    cout<<"\tTransfer successful!\n";
}
void checkBalance(string currentUser){
    system("cls");

    ifstream infile("account.txt");
    if(!infile){
        cout<<"\tError opening file!\n";
        return;
    }

    string line;
    bool found = false;

    while(getline(infile, line)){
        if(line.empty()) continue;

        stringstream ss(line);
        string userid, userpass;
        int userbalance;

        getline(ss, userid, ':');
        getline(ss, userpass, ':');
        ss >> userbalance;

        if(userid == currentUser){
            found = true;
            cout<<"\tYour Current Balance: "<<userbalance<<endl;
            break;
        }
    }

    if(!found){
        cout<<"\tUser not found!\n";
    }

    infile.close();
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
        cout<<"\t2. Login\n";
        cout<<"\t3. Exit\n";
        cout<<"\tEnter Your Choice: ";
        cin>>val;

        if(val == 1){
            openAccount(user);
        }

        else if(val == 2){
            string currentUser;

            if(login(currentUser)) {
                cout<<"\n\tLogin successful!\n";
                Sleep(2000);
                int choice;
                do{
                    system("cls");
                    cout<<"\t1. Add cash\n";
                    cout<<"\t2. Withdraw cash\n";
                    cout<<"\t3. Check Balance\n";
                    cout<<"\t4. Transfer Money\n";
                    cout<<"\t5. Logout\n";
                    cout<<"\tEnter Your Choice: ";
                    cin>>choice;

                    if(choice==1){
                    addCash(currentUser);
                    cout<<"\n\tPress Enter to continue...";
                    cin.ignore();
                    cin.get();
                    }
                    else if(choice==2){
                    withdraw(currentUser);
                    cout<<"\n\tPress Enter to continue...";
                    cin.ignore();
                    cin.get();
                    }
                    else if(choice==3){
                    checkBalance(currentUser);
                    cout<<"\n\tPress Enter to continue...";
                    cin.ignore();
                    cin.get();
                    }
                    else if(choice==4){
                    transferMoney(currentUser);
                    cout<<"\n\tPress Enter to continue...";
                    cin.ignore();
                    cin.get();
                    }
                }while(choice != 5);
            }
            else{
                cout<<"\tInvalid Account No or Password!\n";
                Sleep(2000);
            }
        }
        else if(val == 3) {
            system("cls");
            exit= true;
            cout<<"\tThank You for using our service!"<<endl;
            Sleep(2000);
        }

        else {
            cout<<"\tInvalid Choice!\n";
            Sleep(2000);
        }
    }
}