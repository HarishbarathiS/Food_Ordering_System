#include <bits/stdc++.h>
using namespace std;

const string Admin_id = "12344321";
const string Admin_password = "meAdmin";

class UserDB{
    public:
    unordered_map<string,vector<string>> db; // mobile,<password,location>
    unordered_set<string> usedPasswords;

    void addUser(){
        string mobile,password;
        cout << "Hi new user!!" << endl;
        cout << "Enter your mobile number :";
        cin >> mobile;
        bool loop = true;
        while(loop){
            cout << "Enter your password :";
            cin >> password;
                if(usedPasswords.find(password) == usedPasswords.end()){
                    usedPasswords.insert(password);
                    db[mobile].push_back(password);
                    loop = false;
                }else{
                    cout << "Oops! Password is already in use, try again with a different password" << endl;
                }
            }
            string location;
            cout << "Enter your location : ";
            cin >> location;
            db[mobile].push_back(location);
            cout << "User successfully added!";
        }

    void Authenticate(){
        string mobile,password;
        bool loop = true;
        while(loop){
                cout << "Enter your mobile no. : ";
                cin >> mobile;
                cout << "Enter your password :";
                cin >> password;
            if(db[mobile][0] == password){
                cout << "User Authentication successful!!" << endl;
                loop = false;
            }else{
                cout << "Sorry can't find any user with the given credentials" << endl;
                cout << "Try again!!" << endl;
            }
        }
    }
};

class Order{
    public:
};


int main(){
    UserDB d;
    while(true){
        cout << "1.Customer" << endl;
        cout << "2.Admin" << endl;
        int user;
        cin >> user;
        if(user == 1){
            cout << "1.New ?" << endl;
            cout << "2.Already have an account ?" << endl;
            int account;
            cin >> account;
            if(account == 1){
                d.addUser();
            }else if(account == 2){
                d.Authenticate();
            }
        }
    }
}