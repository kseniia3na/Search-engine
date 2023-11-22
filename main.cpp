/* 
    Project 2 - Search (main.cpp)

    Kseniia Nastahunina

    The project is implenetation of a search engine similar to google. The main in this project is used to test the code
    in search.h class. In the code below I tested multiple entaries in different functions to check is the code workes as
    implied. 

*/

#include <iostream>
#include "search.h"
#include <algorithm>

using namespace std;

int main() {
    
    //declared multipl strings to check for removed punctuation and later for created tokens after clear
    /*string test1 = "...H.e.!l.l.o.% make___ me Smi%le...!&";
    string test2 = "my ----CODE-----  ----- doesn't . &&work-- :(";
    string test3 = "shanon@uic.edu & me";
    string test4 = "One Fish Two Fish Red fish Blue fish !!!";
    string test5 = "?34?as?&&34a";

    //clearToken() tests.
    cout << "1. " << (cleanToken(test1)) << endl;
    cout << "2. " << (cleanToken(test2)) << endl;
    cout << "3. " << (cleanToken(test3)) << endl;
    cout << "5. " << (cleanToken(test5)) << endl;
    cout << "4. " << (cleanToken(test4)) << "\n" << "\n" << endl;

    //gatherTokens() tests.
    set<string> token1 = gatherTokens(test1);
    set<string> token2 = gatherTokens(test2);
    set<string> token3 = gatherTokens(test3);
    set<string> token4 = gatherTokens(test4);

    //used to print out the result of the functions.
    cout << "Token 1 consists: " << endl;
    for(auto i: token1){
        cout << i << endl;
    }*/
    

    //map created for testing purposes
    /*map<string, set<string>> index;

    //buildIndex() tests.
    int indexCount1 = buildIndex("tiny.txt", index);
    cout<< "1. Index count is: " << indexCount1 << endl;
    index.clear();
    int indexCount2 = buildIndex("stackoverflow.txt", index);
    cout<< "2. Index count is: " << indexCount2 << endl;
    index.clear();
    int indexCount3 = buildIndex("uiccs-news.txt", index);
    cout<< "3. Index count is: " << indexCount3 << endl;
    index.clear();
    int indexCount4 = buildIndex("uiccs.txt", index);
    cout<< "4. Index count is: " << indexCount4 << endl;
    index.clear();
    int indexCount5 = buildIndex("wiki-uni.txt", index);
    cout<< "5. Index count is: " << indexCount5 << endl;
    index.clear();
    int indexCount6 = buildIndex("cplusplus.txt", index);
    cout<< "6. Index count is: " << indexCount6 << endl;
    index.clear();

    
    cout << "Map contains: " << endl;
    for(auto i: index){
        cout << "Token: " << i.first;
        for(auto j: i.second){
            cout << " URL(s): " << j;
        }
        cout << endl;
    }


    //findQueryMatches() tests.
    findQueryMatches(index, "EGGS");
    findQueryMatches(index, "blue");
    findQueryMatches(index, "blue eggs");
    findQueryMatches(index, "blue +fish");
    findQueryMatches(index, "blue -fish");
    findQueryMatches(index, "oil -cheese fish +two"); //I added oil multiple times into "tiny.txt" to each "sentence" for testing purposes
    findQueryMatches(index, "instantiation");
    findQueryMatches(index, "vector +container");*/


    //multiple searchEngine() tests.
    searchEngine("cplusplus.txt");
    /*searchEngine("tiny.txt");
    searchEngine("stackoverflow.txt");
    searchEngine("uiccs-news.txt");
    searchEngine("wiki-uni.txt");*/


    //Creative component tests.
    /*map<string, int> rank;
    rank = rankUrls("oil", "tiny.txt"); //I added oil into "tiny.txt" multiple times to each "sentence" for testing purposes
    printRank(rank);
    rank = rankUrls("vector", "cplusplus.txt");
    printRank(rank);
    rank = rankUrls("comfortable", "uiccs-news.txt");
    printRank(rank);
    rank = rankUrls("element", "stackoverflow.txt");
    printRank(rank);*/

    return 0;
}
