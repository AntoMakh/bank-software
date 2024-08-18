#include <iostream>
#include <fstream>
#include <string>
using namespace std;

////////////////////////////////////////////////
////             CREATED BY : AntoMa        ////
////////////////////////////////////////////////
////////////////////////////////////////////////
//// GITHUB https://www.github.com/AntoMakh ////
////////////////////////////////////////////////

int main() {
    bool loggedOn = false;


    fstream accounts;
    accounts.open("accounts.txt", ios::in);

    if(accounts) {
        cout << "File exists, opened." << endl;
        accounts.close();
        accounts.open("accounts.txt", ios::in | ios::out);
    } else {
        cout << "File does not exist. Creating..." << endl;
        accounts.open("accounts.txt", ios::out);
    }

    cout << "Welcome to this software. Would you like to create an account (1), or login (2)?: ";
    int userInput;
    cin >> userInput;
    while(userInput != 1 && userInput != 2) {
        cout << "Please input a valid number: ";
        cin >> userInput;
    }
    if(userInput == 1) {
        string usernameInput;
        bool usernameExists;

        do {
            cout << "Choose a username: ";
            cin >> usernameInput;
            string line;
            usernameExists = false;
            accounts.clear();
            accounts.seekg(0, ios::beg);
            while(getline(accounts, line)) { // Reads line by line
                size_t pos = line.find(':');
                if(pos != string::npos) { //if not found, returns npos, if npos not returned, then found.
                    string storedUsername = line.substr(0, pos);
                    if(storedUsername == usernameInput) {
                        cout << "Username already exists.\n";
                        usernameExists = true;
                        break;
                    }
                }
            }
        } while(usernameExists);


        if(!usernameExists) {
            string userPassword;
            cout << "Please choose a password: ";
            cin >> userPassword;

            accounts.clear();
            accounts.seekp(0, ios::end);
            accounts << usernameInput << ":" << userPassword << endl;

            cout << "Account created with username: " << usernameInput << endl;
            cout << "Welcome " << usernameInput << "." << endl;
            loggedOn = true;
        }
    } else if (userInput == 2) {
        string usernameInput, passwordInput;
        bool usernameFound = false;
        
        cout << "Enter username: ";
        cin >> usernameInput;

        cout << "Enter password: ";
        cin >> passwordInput;

        string line;
        accounts.clear();
        accounts.seekg(0, ios::beg);
        while(getline(accounts, line)) {
            size_t pos = line.find(':');
            string storedUsername = line.substr(0, pos);
            string storedPassword = line.substr(pos+1);
            if(storedUsername == usernameInput && storedPassword == passwordInput) {
                cout << "Login successful. Welcome " << usernameInput << "." << endl;
                usernameFound = true;
                loggedOn = true;
                break;
            }
        }
        
        if(!usernameFound) {
            cout << "Invalid credentials. Please try again." << endl;
        }

    }  
    accounts.close();
    return 0;
}