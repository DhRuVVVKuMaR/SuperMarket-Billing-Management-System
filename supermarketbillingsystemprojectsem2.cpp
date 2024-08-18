#include <bits/stdc++.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <windows.h>

using namespace std;
// To Add colours
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//declaring a function named gotoxy that takes two integer parameters x and y. The void keyword indicates that the function does not return any value//
void gotoxy(int x, int y) {
//Here, a variable coord of type COORD is declared. COORD is a structure defined in the Windows API that represents a pair of X and Y coordinates//
    COORD coord;
    coord.X = x;
    coord.Y = y;

//This line calls the SetConsoleCursorPosition function from the Windows API, passing the handle to the standard output console (STD_OUTPUT_HANDLE) and the coord structure as arguments//
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//declaring a class named Item//
class Item {
protected:
    int itemNo;
    string itemName;
    double price;

public:

//constructor of the Item class with itemNo, itemName, and price as parameters//
    Item(int no, const string& name, double p) : itemNo(no), itemName(name), price(p) {}

//virtual keyword indicates that the function is overridden in a derived class//


    virtual void display() const
    {
        //Displays the item number, item name, and price of the object//
         cout << setw(5) << itemNo << setw(20) << itemName << setw(10) << price << endl;
    }

    int getItemNo() const {
        return itemNo;
    }
};

//declaring a class named Amount that inherits from the Item class//

class Amount : public Item {
    int quantity;
    double taxPercent = 18;

public:
    Amount(int no, const string& name, double p, int qty, double tax) : Item(no, name, p), quantity(qty), taxPercent(tax) {}

    //overriding the display function from the Item class//
    void display() const override {
        Item::display();
        cout<<endl;
        //Displays the quantity and tax percentage of the object//
        cout << setw(43) << quantity << setw(25) << taxPercent << endl;
    }

    //overriding the calculateTotal function from the Item class//
    double calculateTotal() const
    {
        double total = price * quantity * (1 + 0.18);
        double discount = total * 0.15;
        return total - discount ;
    }

};
//declaring a class named Supermarket that inherits from the Item class//
class Supermarket {
    vector<Amount> items;

public:
    void addItem() {
        int no, qty;
        string name;
        double price;
        double tax=18;

        cout << "Enter item number: ";
        cout<<endl;
        cin >> no;
        cout<<endl;

        cout << "Enter item name: ";
        cin.ignore();
        cout<<endl;
        getline(cin, name);

        cout << "Enter price: ";
        cout<<endl;
        cin >> price;
        cout<<endl;

        cout << "Enter quantity: ";
        cout<<endl;
        cin >> qty;
        cout<<endl;

        //cout << "Enter tax percent: ";
        //cin >> tax;

        //creates an object of the Amount class with the given parameters and pushes it into the items vector
        items.emplace_back(no, name, price, qty, tax);
    }
//overriding the displayBill function from the Item class//
    void displayBill() const {
        cout << "Item No." << setw(20) << "Item Name" << setw(10) << "Price" << setw(10) << "Qty" << setw(10) << "Tax %" << endl;
        cout << string(55, '-') << endl;
        double totalAmount = 0.0;
        for (const Amount& item : items) {
            item.display();
            totalAmount += item.calculateTotal();
        }
        cout << string(55, '-') << endl;
        cout << setw(45) << "Total Amount: " << totalAmount << endl;

    }
//overriding the saveToFile function from the Item class//
    void saveToFile()
     {
        //opens a file named "billing.txt" in append mode
        ofstream outFile("billing.txt", ios::app);

        //checks if the file was opened successfully
        if (outFile.is_open()) {
            for (const Amount& item : items) {
                outFile << item.calculateTotal() << endl;
            }
            outFile.close();
            cout << "Billing details saved to file." << endl;
        } else {
            cout << "Error opening file for writing." << endl;
        }
    }

//overriding the processPayment function from the Item class
    void processPayment(int method, double amount) {

        switch(method) {
            case 1:
                cout << "Payment processed successfully via cash for amount: " << amount << endl;
                break;
            case 2:
                cout << "Payment processed successfully via credit card for amount: " << amount << endl;
                break;
            case 3:
                cout << "Payment processed successfully via debit card for amount: " << amount << endl;
                break;
            default:
                cout << "Invalid payment method." << endl;
        }
    }
//overriding the returnItem function from the Item class
    void returnItem() {
        int itemNo;
        cout << "Enter the item number of the product to return: ";
        cin >> itemNo;

//finds the item with the given item number and deletes it from the items vector
        auto it = std::find_if(items.begin(), items.end(), [itemNo](const Amount& item) {
            //checks if the item number of the item matches the given item number
            return item.getItemNo() == itemNo;
        });

//if the item is found, it is deleted from the vector
        if (it != items.end()) {
            items.erase(it);
            cout << "Product returned successfully." << endl;
        } else {
            cout << "Product not found." << endl;
        }
    }
    void deliverItems() {
    string address, pinCode, phoneNumber;
    // Prompt the user to input delivery address details

    cout << "Enter delivery address: ";
    //cin.ignore() is used to clear if any existing input is there so that the new input can be taken easily
    cin.ignore();
    //getline is used to input line
    getline(cin, address);

    cout << "Enter pin code: ";
    getline(cin, pinCode);

    cout << "Enter phone number: ";
    getline(cin, phoneNumber);

    // Here, you can implement the delivery process, such as sending a confirmation message,
    // notifying the delivery personnel, updating the delivery status, etc.

    cout << "Items will be delivered to the following address: " << endl;
    cout << "Address: " << address << endl;
    cout << "Pin Code: " << pinCode << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Delivery in progress..." << endl;
    cout << "Thank you for shopping with us!" << endl;
}

void pdtreview()
{
    string review;
    cout<<"If you are an existing user please share the product review!! "<<endl;
    getline(cin,review);
}

void feedback()
{
        char choice;

        cout << "Please provide valuable your feedback ( 1 to 5 ): "<<endl;
        cin >> choice;
        cout<<endl;

        switch(choice)

                {

                case '1':
                cout << "Thank you for your valuable your feedback!!! "<<endl;
                cout << "Sorry for the inconvenience." << endl;
                cout<<"We'll contact you for the inconvenience casued."<<endl;
                break;

                case '2':
                cout << "Thank you for your valuable your feedback!!! "<<endl;
                cout<<"We'll contact you for the inconvenience casued."<<endl;
                break;

                case '3':
                cout << "Thank you for your valuable your feedback!!! "<<endl;
                cout<<"We are trying our best to improve everyday."<<endl;
                break;

                case '4':
                cout << "Thank you for your valuable your feedback!!! "<<endl;
                break;

                case '5':
                cout << "Thank you for your valuable your feedback!!! "<<endl;
                cout<<"Thank you so much !! "<<endl;
                cout<<"Delighted you liked our services !!"<<endl;
                break;

                default:
                cout << "Invalid Entry!!! " << endl;
                break;
        }
    }

    void exit()
    {
     cout<<"Thank You!!!!"<<endl;
    }

    void support()
    {
      cout<<"Sorry For The Inconvenience Caused!!"<<endl;
      cout<<"Phone Number : "<<endl;
      cout<<"7014120076"<<endl;

      cout<<"Alternate Phone Number : "<<endl;
      cout<<"9571462877"<<endl;

      cout<<"Email Address : "<<endl;
      cout<<"Chitranshsaxena85@gmail.com"<<endl;

      cout<<"Email Address : "<<endl;
      cout<<"Sarthak130905@gmail.com"<<endl;

      cout<<"Address : "<<endl;
      cout<<"ABB-3 , 914 JIIT - 62 "<<endl;
      cout<<"201309"<<endl;
      cout<<"Noida , Uttar Pradesh"<<endl;

    }
};


int main()
{
    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Set text color to cyan

    for ( int i = 0 ; i < 2 ; i++ ) {
        for ( int j = 0 ; j < 50 ; j++ )
        {
            cout << "*" ;
        }
        cout << endl ;
    }
    cout << endl;

    for ( int i = 0 ; i < 20 ; i++ )
    {
        cout << " " ;
    }

    cout << "WELCOME" << endl<<endl;
    for ( int i = 0 ; i < 22 ; i++ )
    {
     cout << " " ;
    }

    cout << "TO" << endl<<endl;
    for ( int i = 0 ; i < 15 ; i++ ) {
        cout << " " ;
    }

    cout << "E-17 Online Mart " << endl << endl;
    for ( int i = 0 ; i < 11 ; i++ ) {
        cout << " " ;
    }

    cout << "press any key to continue" << endl << endl <<endl;
    for ( int i = 0 ; i < 2 ; i++ ) {
        for ( int j = 0 ; j < 50 ; j++ ) {
            cout << "*" ;
        }
        cout << endl ;
    }
    //gets the user's choice from the main menu//
    gotoxy(23,15);

    char ch;
    ch = getch ();
    system("cls");

    // Example usage of colors
    setColor(FOREGROUND_RED | FOREGROUND_INTENSITY); // Set text color to red

//creates an instance of the Supermarket class and displays the main menu//
    Supermarket market;
    int choice;

    do {
        cout << "\nSupermarket Billing System\n";
        cout << "1. Add Item\n";
        cout << "2. Display Bill\n";
        cout << "3. Save to File\n";
        cout << "4. Process Payment\n";
        cout << "5. Return Item\n";
        cout<<  "6. Deliver Order\n";
        cout << "7. Feedback\n";
        cout << "8. Product Review\n";
        cout << "9. Coustomer Support\n";
        //cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                market.addItem();
                break;

            case 2:
                market.displayBill();
                break;

            case 3:
                market.saveToFile();
                break;

            case 4: {
                int method;
                double amount;
                //prompts the user to select a payment method and processes the payment

                cout << "Select payment method:\n";
                cout << "1. Cash\n";
                cout << "2. Credit Card\n";
                cout << "3. Debit Card\n";
                cin >> method;
                cout << "Enter the total amount to process payment: ";
                cin >> amount;
                market.processPayment(method, amount);
                break;
            }

            case 5:
                market.returnItem();
                break;

            case 6:
                market.deliverItems();
                break;

            case 7:
                market.feedback();
                break;


            case 8:
                market.pdtreview();

                break;

            case 9:
                market.support();
                break;

            case 10:
               market.exit();
               break;

            default:
                cout << "Invalid choice. Please try again." << endl;

        }
    }
    //continues displaying the main menu until the user chooses to exit
    while (choice != '7');

    for ( int i = 0 ; i < 2 ; i++ ) {
        for ( int j = 0 ; j < 50 ; j++ ) {
            cout << "*" ;
        }
        cout << endl ;
    }
    cout << endl;

//displays a goodbye message and thanks the user for shopping
    for ( int i = 0 ; i < 15 ; i++ ) {
        cout << " " ;
    }
    cout << " THANK YOU FOR SHOPPING " << endl<<endl;
    for ( int i = 0 ; i < 22 ; i++ ) {
        cout << " " ;
    }
    cout << " WITH " << endl<<endl;
    for ( int i = 0 ; i < 17 ; i++ ) {
        cout << " " ;
    }
    cout << " E-17 Online Mart " << endl << endl;
    for ( int i = 0 ; i < 15 ; i++ ) {
        cout << " " ;
    }
    cout << "PRESS ANY KEY TO CONTINUE" << endl << endl <<endl;
    for ( int i = 0 ; i < 2 ; i++ ) {
        for ( int j = 0 ; j < 50 ; j++ ) {
            cout << "*" ;
        }
        cout << endl ;
    }
    ch = getch ();
    system("cls");
    return 0;
}
