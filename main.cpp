#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief This function takes the line read from the file
 * and returns a string that has 0s where neeeded
 *
 * Complexity: O(n)
 * @param singleLine String read from file
 * @return string With 0s where needed
 */
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
    list<string> contents; //recursive list from standard library

    string singleLine;
    while (getline(file, singleLine))
        contents.push_back(formattedLine(singleLine));

    cout << contents.size() << " lines in memory" << endl;
    file.close();

    contents.sort();

    // Test Cases

    string ipInicial = "02107267477:5984 Failed password for illegal user guest";
    // This string contains the IP of one of the ones found in our list, we chose it randombly

    string ipFinal = "78008485375:4848 Illegal user";
    // Also another string more down the list

    // Iterators that will point to the node in our list, one for the initial search item
    //  another for the final search point
    list<string>::iterator start;
    list<string>::iterator end;


    /**
     * @brief This funcion wll search our list one by one until it finds a string equal to our input
     * Complexity: O(n)
     * Our iterator will point to that node
     */
    start = find(contents.begin(), contents.end(), ipInicial);

    // cout << *start << '\n';

    /**
     * @brief Same deal but it finds the end point of our search
     *  Complexity: O(n)
     */
    end = find(contents.begin(), contents.end(), ipFinal);


    /**
     * @brief This for loop will output into our file the ips that meet the criteria
     * Complexity: O(n)
     */
    ofstream sorted("result.txt", ios::binary);
    for (list<string>::iterator i = start; i != end; i++)
        sorted << *i << endl;

    sorted << *end << endl;
    return 0;
}
