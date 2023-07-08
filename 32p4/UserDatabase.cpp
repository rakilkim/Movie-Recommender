#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase()
    :called(false)
{
}

bool UserDatabase::load(const string& filename)
{
    if (!called) {
        string name = "";
        string email = "";
        vector<string> history;
        ifstream infile(filename);
        if (!infile)
            return false;
        int line = 1;       //keep track of which line of user's info 
        std::string s;
        while (getline(infile, s))
        {
            if (line == 1) {
                name = s;
                line++;
            }
            else if (line == 2) {
                email = s;
                line++;
            }
            else if (line == 3) {       //skip line that shows how many movies watched
                line++;
            }
            else if (line > 3 && s != "") {     //get history until empty line
                history.push_back(s);
            }
            else {      //when empty line insert all the data
                tmm.insert(email, User(name, email, history));
                name = "";
                email = "";
                for (vector<string>::iterator i = history.begin(); i != history.end();) {
                    i = history.erase(i);
                }
                line = 1;
            }
        }
        if (line != 1)      //if there was no empty line at the end of the file
            tmm.insert(email, User(name, email, history));
    }
    else
        return false;
    called = true;
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    if (!tmm.find(email).is_valid()) {
        return nullptr;
    }
    return &tmm.find(email).get_value();

}
