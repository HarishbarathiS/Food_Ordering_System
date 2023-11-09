#include <bits/stdc++.h>
#include <ctime>
#include <unistd.h>
using namespace std;

const string Admin_id = "12344321";
const string Admin_password = "meAdmin";


void delay(int num){
    time_t delay = num;
    sleep(delay);
    system("cls");
}

class UserDB{
    public:
    unordered_map<string,vector<string>> db; // mobile,<password,location>
    unordered_set<string> usedPasswords;

    void addUser(string mobile){
        string password;
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
            system("cls");
            db[mobile].push_back(location);
            cout << "User successfully added!";
            delay(2);
        }

    void Authenticate(string mobile){
        string password;
        bool loop = true;
        while(loop){
                //cout << "Enter your mobile no. : ";
                //cin >> mobile;
                cout << "Enter your password : ";
                cin >> password;
                system("cls");
            if(db[mobile][0] == password){
                cout << "User Authentication successful!!" << endl;
                loop = false;
                delay(2);
            }else{
                cout << "Sorry can't find any user with the given credentials" << endl;
                cout << "Try again!!" << endl;
                delay(2);
            }
        }
    }

    string getUserPlace(string number){
        for(auto it : db){
            if(it.first == number){
                return it.second[1];
                break;
            }
        }
    }
};

struct Shop{
    public:
    string name;
    string type;
    string cuisine;
    vector<pair<string,double>>food_items;
};

struct OrderSchema{
    public:
    string item_name;
    double price;
    double quantity;
};

struct Bill{
    public:
    string order_id;
    string res_name;
    vector<OrderSchema> details;
};

class Admin{
    public:
    vector<Shop> shops;
    void addshop(){
        Shop newShop;
        string name,type,cuisine;
        cout << "Enter shop name : ";
        cin.ignore();
        getline(cin,newShop.name);
        cout << "Veg | Non-veg | Both ? ";
        cin >> newShop.type;
        cout << "Enter the type of cuisine offered : ";
        cin.ignore();
        getline(cin,newShop.cuisine);
        system("cls");
        add_items(newShop);
    }

    void add_items(Shop newShop){
        int num;
        vector<pair<string,double>> items;
        cout << "Enter the number of food items to be added : ";
        cin >> num;
        system("cls");
        int i = 1;
        while(i <= num){
            string food;
            double price;
            cout << "Food name " << i << " : ";
            cin.ignore();
            getline(cin,food);         
			cout <<  "Food price " << i << " : ";
            cin >> price;
            items.push_back(make_pair(food,price));
            i++;
            system("cls");
        }
        newShop.food_items = items;
        shops.push_back(newShop);
        system("cls");
    }

    void DisplayRestaurants(){
        cout << "Restaurants : " << endl;
        int i = 1;
        for(auto it : shops){
            cout << i  << " " << it.name << " | " << it.type  << " | " << it.cuisine << " | " << endl;
            i++;
        }
    }

    void DisplayFoodItems(int num){
        int i=1;
        for(auto it : shops[num-1].food_items){
            cout << i << " Item : " << it.first << " | " << " Price : " << it.second << endl;
            i++;
        }
    }

    string getRestaurantName(int num){
        return shops[num-1].name;
    }

    pair<string,double> getNameandPrice(int num1, int num2,int quantity){
        double price;
        int count = 1;
        string food_name;
        for(auto it : shops[num1-1].food_items){
            if(count==num2){
                price = it.second*quantity;
                food_name = it.first;
                break;
            }
            else{
                count++;
            }
        }
        return make_pair(food_name,price);
    }

    double getTotal(Bill order1){
        double tot_price = 0;
        for(auto pair : order1.details){
            tot_price += pair.price;
        }
        return tot_price;
    }
};



class Order : public Admin{
    public:
    queue<Bill> q;
    void pushOrder(Bill bill){
        q.push(bill);
    }

    void printOrders(){
        int size = q.size();
        int i = 1;
        while(size--){
            cout << "---------------Order " << i << "------------------" << endl;
            Bill order = q.front();
            cout << "Order id : " << order.order_id << endl;
            cout << "Restaurant name : " << order.res_name << endl;
            cout << "Items :" << endl;
            for(auto it : order.details){
                cout << "Item Name : " << it.item_name << " | " << "Price : " 
                << it.price << " | " << "Quantity : " << it.quantity << endl;
            }
            cout << "---------------Order " << i << "------------------" << endl;
            q.pop();
            q.push(order);
            i++;
        }
        int num;
        cout << "Enter -1 to go back ";
        cin >> num;
        if(num == -1){
            system("cls");
            cout << "Exiting...";
            delay(2);
        }
    }

    void displayRestaurantOrders(string name){
        int size = q.size();
        int i = 1;
        bool flag = false;
        while(size--){
            Bill order = q.front();
            if(order.res_name == name){
                flag = true;
                cout << "---------------Order " << i << "------------------" << endl;
                cout << "Order id : " << order.order_id << endl; 
                cout << "Restaurant name : " << order.res_name << endl;
                cout << "Items :" << endl;
                for(auto it : order.details){
                    cout << "Item Name : " << it.item_name << " | " << "Price : " 
                    << it.price << " | " << "Quantity : " << it.quantity << endl;
                }
                cout << "---------------Order " << i << "------------------" << endl;
            }
                q.pop();
                q.push(order);
                i++;
        }
        if(!flag){
            cout << "No orders found for " + name  + "!"<< endl;
            delay(3);
        }else{
            int num;
            cout << "Enter -1 to go back ";
            cin >> num;
            if(num == -1){
                system("cls");
                cout << "Exiting...";
                delay(2);
            }
        }
    }
};


string genOrder_id(int num,string place){
    return to_string(num) + "#" + place;
}

int main(){
    system("cls");
    UserDB d;
    Admin a;
    Order o;
    while(true){
        cout << "1.Customer" << endl;
        cout << "2.Admin" << endl;
        cout << "3.Restaurant access" << endl;
        int user;
        cin >> user;
        system("cls");
        if(user == 1){
            cout << "1.New ?" << endl;
            cout << "2.Already have an account ?" << endl;
            int account;
            cin >> account;
            system("cls");
            string UserNumber; 
            if(account == 1){
                string mobile;
                cout << "Hi new user!!" << endl;
                cout << "Enter your mobile number : ";
                cin >> mobile;
                d.addUser(mobile);
                UserNumber = mobile;
            }else if(account == 2){
                string mobile;
                cout << "Enter your mobile number : ";
                cin >> mobile;
                d.Authenticate(mobile);
                UserNumber = mobile;
            }
            cout << endl;
            a.DisplayRestaurants();
            int pickShop;
            cout << "Enter the restaurant no. to order : ";
            cin >> pickShop;
            system("cls");
            // take shop no. from the user;
            // pass it as an argumnent to the below function
            string Userplace = d.getUserPlace(UserNumber);
            string order_id = genOrder_id(pickShop,Userplace);
             // order_id,res_name,name,price,quantity
            Bill order1;
            order1.order_id = order_id;
            order1.res_name = a.getRestaurantName(pickShop);
            while(1){
                a.DisplayFoodItems(pickShop);
                int num;
                cout << "Enter food item no. or enter -1 to exit : ";
                cin >> num;
                if(num == -1){
                    break;
                }else{                
                    int quantity;
                    cout << "Enter quantity : ";
                    cin >> quantity;
                    system("cls");
                    pair<string,double> temp = a.getNameandPrice(pickShop,num,quantity);
                    OrderSchema o1;
                    o1.item_name = temp.first;
                    o1.price = temp.second;
                    o1.quantity = quantity;
                    order1.details.push_back(o1);
                }                
            }
            system("cls");
            double tot_price = a.getTotal(order1);
            cout<<"The total price of your order is: "<< tot_price << endl;
            delay(5);
            cout << "Logging out..." << endl;
            delay(2);
            o.pushOrder(order1);
            // while loop for the users to order
            // store item name and price in a vector of pairs
            // calculate Total bill 
            // Order (vector) has to go in to the queue 
        }else if(user == 2){
            string id,password;
            bool loop = true;
            while(loop){
                cout << "Enter Admin ID : ";
                cin >> id;
                cout << "Enter Admin password : ";
                cin >> password;
                system("cls");
                if(id == Admin_id && password == Admin_password){
                    cout << "Admin Authentication successful";
                    loop = false;
                }else{
                    cout << "Id or password doesn't match" << endl;
                    cout << "Try again!!" << endl;
                }
                system("cls");
            }
            while(true){
                cout << "1. Add restaurant" << endl;
                cout << "2. Display orders" << endl;
                cout << "3. Exit" << endl;
                int choice;
                cin >> choice;
                system("cls");
                if(choice == 1){
                    a.addshop();
                }else if(choice == 2){
                    o.printOrders();
                }else{
                    cout << "Logging out...";
                    delay(2);
                    break;
                }
            }
        }else if(user == 3){
            string name;
            cout << "Enter restaurant name : ";
            cin.ignore();
            getline(cin,name);
            system("cls");
            o.displayRestaurantOrders(name);
        }
    }
}
