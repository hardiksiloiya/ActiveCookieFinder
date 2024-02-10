#include<iostream>
#include<fstream>
#include<sstream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<string>
using namespace std;

struct Cookie{
    string name;
    string date;
};

bool parseLine(const string& line, Cookie& cookie){
    istringstream ss(line);
    if(!getline(ss,cookie.name,',')) return false;
    string timestamp;
    if(!getline(ss,timestamp,',')) return false;
    cookie.date=timestamp.substr(0,10);
    return true;
}

pair<vector<string>,unordered_map<string,int>> countCookies(const string& filePath,const string& date){
    unordered_map<string,int> cookieCount;
    vector<string> order;
    unordered_set<string> seen;
    ifstream file(filePath);
    string line;
    if(!file.is_open()){
        cerr<<"Unable to open file"<<endl;
        return{};
    }
    while(getline(file,line)){
        Cookie cookie;
        if(!parseLine(line,cookie)){
            continue;
        }
        if(cookie.date!=date) continue;
        if(seen.insert(cookie.name).second){
            order.push_back(cookie.name);
        }
        cookieCount[cookie.name]++;
    }
    return make_pair(order,cookieCount);
}

vector<string> findMostActiveCookies(const unordered_map<string,int>& cookieCount,const vector<string>& order){
    vector<string> mostActiveCookies;
    int maxCount=0;
    for(const auto& cookieName:order){
        int count=cookieCount.at(cookieName);
        if(count>maxCount){
            mostActiveCookies.clear();
            maxCount=count;
        }
        if(count==maxCount){
            mostActiveCookies.push_back(cookieName);
        }
    }
    return mostActiveCookies;
}

int main(int argc,char** argv){
    if(argc!=4||string(argv[2])!="-d"){
        cerr<<"Usage: "<<argv[0]<<" <file_path> -d <date>"<<endl;
        return 1;
    }
    string filePath=argv[1];
    string date=argv[3];
    auto p=countCookies(filePath,date);
    auto mostActiveCookies=findMostActiveCookies(p.second,p.first);
    for(const auto& cookie:mostActiveCookies){
        cout<<cookie<<endl;
    }
    return 0;
}
