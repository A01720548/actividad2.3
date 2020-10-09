#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;


string formattedLine(string singleLine) {
    string formattedString;
    formattedString = singleLine.substr(16);
    string retVal;
    int spacePos;
    vector<string> vec;

    size_t pos = 0;
    string token;
    string delimiter = ".";
    while ((pos = formattedString.find(delimiter)) != string::npos) {
        token = formattedString.substr(0, pos);

        while (token.size() < 3) {
            token = '0' + token;
        }

        formattedString.erase(0, pos + delimiter.length());

        vec.push_back(token);
    }

    while (formattedString.size() < 8) {
        formattedString = '0' + formattedString;
    }

    vec.push_back(formattedString);
    for (int i = 0; i < vec.size(); i++) {
        retVal = retVal + vec[i];
    }
    return retVal;
}

int main() {

    ifstream file("bitacora.txt", ios::binary);
    list<string> contents;
    string singleLine;
    while (getline(file, singleLine))
        contents.push_back(formattedLine(singleLine));

    cout << contents.size() << " lines in memory" << endl;
    file.close();

    contents.sort();


    string ipInicial = "02107267477:5984 Failed password for illegal user guest";

    string ipFinal = "78008485375:4848 Illegal user";

    list<string>::iterator start;
    list<string>::iterator end;

    start = find(contents.begin(), contents.end(), ipInicial);

    // cout << *start << '\n';

    end = find(contents.begin(), contents.end(), ipFinal);


    ofstream sorted("result.txt", ios::binary);
    for (list<string>::iterator i = start; i != end; i++)
        sorted << *i << endl;

    sorted << *end << endl;
    return 0;
}
