/* 
    Project 2 - Search (search.h)

    Kseniia Nastahunina

    The project is implenetation of a search engine similar to google. User inputs multiple words that and the engine
    serches in the file for a match depending on user's input. To help implement the project there are a few helper functions
    that are called in the searchEngine() function. 

*/

#pragma once

#include <iostream>
#include <set>
#include <map>
#include <fstream>
#include <sstream>  
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

/* The function checks if the string contains any letters or numbers. Takes
string to check as a parameter. Return true if any letter or number found and false otherwise. */
bool isWord(string s){

    for(size_t i = 0; i < s.size(); i++){

        if(isalpha(s[i])){

            return true;

        }
    }

    return false;
}

/* The function that removes any punctuation before or after string s. Takes parameter string s 
as parameter. Returns clear string.*/
string cleanToken(string s) {
    bool isPunct = true; 

    if(isWord(s)){
        for(size_t i = 0; i < s.size(); i++){ //for loop to find all punctuation

            s[i] = tolower(s[i]); //makes all letters lower case
        }
        while(isPunct){
            if(ispunct(s[0])){ //if the first char is punctuation 
                s.erase(0, 1); //remove the first char
                isPunct = true;
            }
            else{
                isPunct = false; //will stay false and exit while loop is both if's are not true.
            }
            auto last = s.size() - 1; //to check the last character in the string
            if(ispunct(s[last])){ //if the last char is punctuation
                s.erase(last, 1); //remove the last char
                isPunct = true;
            }
        }
        return s; 
    }
    else{
        s.clear(); //if there are no letters in s then returns clear string
        return s;
    }

}

/* The function divides sentence by words using sstream library. The parameter string text is 
the sentence to divide. Returns the set of divided words from the sentence.*/
set<string> getTokens(string text){

    string sub;
    stringstream x(text); //string to look in

    set<string> tokens;

    while(getline(x, sub, ' ')){// divides sentence into separate words by looking for space;
        tokens.insert(sub); //inserts words into set without duplicates
    }
    return tokens;
}

/* The function divides sentence by words using sstream library. It is a duplicate function of getTokens()
The parameter string text is the sentence to divide. Returns the vector of divided words from the sentence.
Used in buildIndexWithRank() (creative component) and findQueryMatches() as vector allows duplicates
comparing to sets. */
vector<string> getVectorTokens(string text){

    string sub;
    stringstream x(text); //string to look in

    vector<string> tokens;

    while(getline(x, sub, ' ')){ // divides sentence into separate words by looking for space;
        tokens.push_back(sub); //pushes separate words into vector
    }
    return tokens;
}

/* The function is used to return the cleared words from text string. It takes string text
as a parameter then adds it to a set word by word by using getToken(), calls cleanToken() to 
clean each word and return a set of a clean tokens.*/
set<string> gatherTokens(string text) {
    set<string> clearTokens;

    
    set<string> tokens = getTokens(text); //splits sentense into tokens

    for(auto str: tokens){
        str = cleanToken(str); //cleans every word from punctuation
        if(!str.empty()){
            clearTokens.insert(str); //adds clean tokens
        }
    }
    return clearTokens; 
}

/* The function is used to process urls and tokens from a file. Takes name of a file and map of strings and
set<string> as parameter. The function opens file reads every second line as regular sentence and breakes 
them into clear words. The other lines it reads as urls. Afterwards every 2 lines is adds urls into 
set<string> and adds clear words as key in the map and urls as value for easy search. The function
returns integer of number of urls processed. */
int buildIndex(string filename, map<string, set<string>>& index) {
    ifstream infile;
    string line;

    int lineNum = 1; //used to keep track of line number to know what to search for
    int urlCount = 0; //used to keep trak of url count to return it
    
    string url;
    string word; 

    set<string> tokens;

    infile.open(filename.c_str()); //opens file
        
    if (!infile.is_open()) { //checks if the file is open
        return 0;
    }
    else{
        while(getline(infile, line)){
            if(lineNum % 2 == 1){ //if line number is odd
                url = line;
                lineNum++;
                urlCount++;
            }
            else if(lineNum % 2 == 0){ //if line number is even 
                lineNum++; 
                word = line;
                tokens = gatherTokens(word); //splits sentense into words and cleans it
                for(auto map: tokens){
                        if(index.count(map) == 0){ //if key does not exist in the map
                            set<string>  urlSet;
                            urlSet.insert(url);
                            index[map] = urlSet;
                        }
                        else{
                            set<string>  urlSet = index.at(map);
                            urlSet.insert(url);
                            index[map] = urlSet; //add url to existing key
                        }
                }
            }            
        }
    }
    return urlCount;
}


/* CREATIVE COMPONENT
The function is used to process urls and tokens from a file. Takes name of a file. The function 
opens file reads every second line as regular sentence and breakes them into clear words. The other 
lines it reads as urls. Afterwards every 2 lines is adds urls into first map<stinrg, map<string, int>>
as key and adds clear words as key in the second map map<string, int>, the value for this map is count,
the number of token occurances in the file. The function returns map <string, map<string, int>>
with processed urls, tockens and rank of tokens in urls. */
map <string, map<string, int>> buildIndexWithRank(string filename){
    map <string, map<string, int>> mapByRank;

    ifstream infile;
    string line;
    int lineNum = 1;
    
    string url;
    string word; 

    vector<string> tokens;

    infile.open(filename.c_str()); //opens file
        
    if (!infile.is_open()) { //checks if the file is open
        cout << "Unable to open file. Try another file name." << endl;
        return mapByRank;
    }
    else{
        while(!infile.eof()){
            getline(infile, line);
                url = line;
                lineNum++;

                getline(infile, line);
                word = line;
                tokens = getVectorTokens(word);
                
                map<string, int> rank;
                for(auto i: tokens){
                    i = cleanToken(i);
                    if(rank.count(i) == 0){
                        rank[i] = 1;
                    }
                    else{
                        int count = rank.at(i);
                        count++;
                        rank[i] = count;
                    }
                }

                mapByRank[url] = rank;
        }
    }
    return mapByRank;
}

/* CREATIVE COMPONENT
The function processes the word used wants a rank for and looks inserts the result into map with 
urls as key and rank as value. Takes words to look for in the file and file name as parameters.
retutns map of string and ints.*/
map<string, int> rankUrls(string word, string filename){
    map <string, map<string, int>> mapByRank;
    map<string, set<string>> index;
    
    set<string> urls;

    map<string, int> result;

    buildIndex(filename, index);
    mapByRank = buildIndexWithRank(filename);

    urls = index.at(word);


    for(auto i: urls){
        map<string, int> map = mapByRank.at(i);
        int count = map.at(word);
        result[i] = count;
    }

    return result;
}

/* CREATIVE COMPONENT
Void function to print out the result of rankUrls(). Used for testing purposes.*/
void printRank(map<string, int> mapByRank){
    cout << "Map contains: " << endl;
    for(auto i: mapByRank){
        cout << "URL: " << i.first << " Rank: " << i.second << endl;
    }
}

/*The function to set union of two words. Takes two sets of strings as parameters and uses them to find union.
Returns one set of strings as result.*/
set<string> merge(set<string> value1, set<string> value2){
    set<string> result;
    set_union(value1.begin(), value1.end(), value2.begin(), value2.end(),  inserter(result, result.end()));
    return result;
}

/*The function to set intersection of two words. Takes two sets of strings as parameters and uses them to find 
intersection. Returns one set of strings as result.*/
set<string> inter(set<string> value1, set<string> value2){
    set<string> result;
    set_intersection(value1.begin(), value1.end(), value2.begin(), value2.end(), inserter(result, result.end()));
    return result;
}

/*The function to set difference of two words. Takes two sets of strings as parameters and uses them to find 
difference. Returns one set of strings as result.*/
set<string> diff(set<string> value1, set<string> value2){
    set<string> result;
    set_difference(value1.begin(), value1.end(), value2.begin(), value2.end(), inserter(result, result.end()));
    return result;

}

/*The function is used to quicklt find a match url with given words. Takes map with urls and tokens
and a string with words that user input to match url. Calls merge and/or inter and/or diff function depending
on user input. Also uses vector of strings as it can store duplicates. Returns set of string with 
the result of matches.*/
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    string tokenZero;

    for(size_t str = 0; str < sentence.size(); str++){
        sentence[str] = tolower(sentence[str]); //makes all letters lower case
    }

    vector<string> words = getVectorTokens(sentence); //splits all words without cleaning it
    tokenZero = words[0];
    
    if(tokenZero[0] == '+' || tokenZero[0] == '-'){
        tokenZero.erase(0,1); //erases if there + or - before the first word
    }

    result = index.at(tokenZero); //takes the first word to compare to
    

    for(auto i = 1; i < words.size(); i++){ //won't enter if there is only one word in the sentence
        string token = words[i];
        
        if(token[0] == '+'){ //if user wants to serach for intersection 
            token.erase(0,1);
            result = inter(result, index.at(token));
        }
        else if(token[0] == '-'){ //if user wants to serach for diiference
            token.erase(0,1);
            result = diff(result, index.at(token));
        }
        else{ //if user wants to find union
            result = merge(result, index.at(token));
        }
    }
    
    return result;  
}

/*Void user interface function. Takes file name to search in as parameter and to process by using buildIndex().
Asks user for words to search and finds match by using findQueryMatches() function, if users input enter 
then exits search.*/
void searchEngine(string filename) {

    map<string, set<string>> index;
    set<string> result;
    string userInput;

    cout << "Stand by while building index..." << endl;
    cout << "Indexed " << buildIndex(filename, index) << " pages containing " << index.size() << " unique terms " << endl;

    
    cout << "Enter query sentence (press enter to quit): ";
    getline(cin, userInput); //gets a line of users input

    while(userInput.length() != 0){
        cout << userInput << endl;
        result = findQueryMatches(index, userInput);
        cout << "Found " << result.size() << " matching pages" << endl;
        for(auto i: result){ //prints out all the results
            cout << i << endl;
        }
        cout << "Enter query sentence (press enter to quit): ";
        getline(cin, userInput); //gets a line of users input
    }

    cout << "Thank you for searching!" << endl;
    exit(1); //exits
}


