#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename ,vector<string> &names ,vector<int> &scores ,vector<char> &grades){
    ifstream score(filename);
    string textline;
    while(getline(score,textline)){
        char n[100];
        int a = 0 , b = 0 ,c = 0 , sum = 0;
        sscanf(textline.c_str(),"%[^:]: %d %d %d",n,&a,&b,&c);
        sum = a+b+c ;
        names.push_back(n);
        scores.push_back(sum);
        grades.push_back(score2grade(sum));
    }
}

void getCommand(string &command ,string &key){
    string info ;
    cout << "Please input your command: ";
    getline(cin,info);
    int x = info.find_first_of(" ");
    command = info.substr(0,x);
    key = info.substr(x+1,info.length());
}

void searchName(vector<string> names ,vector<int> scores ,vector<char> grades ,string key){
    bool found = 0 ; 
    cout << "--------------------------------- " << "\n";
    for(unsigned int i = 0 ; i < names.size() ; i++){
        if(toUpperStr(key) == toUpperStr(names[i])){
            cout << names[i] <<"'s " << "score = " << scores[i] << "\n" ;
            cout << names[i] << "'s " << "grade = " << grades[i] << "\n" ;
            found = 1;
        }else if(found == 0 && i == names.size() - 1){
        cout << "Cannot found." <<endl ;
        }
    }
    cout << "--------------------------------- " << "\n";
}

void searchGrade(vector<string> names ,vector<int> scores ,vector<char> grades ,string key){
    cout << "--------------------------------- " << "\n";
    int x = 0 ;
    for(unsigned int i = 0 ; i < grades.size() ; i++){
        if(grades[i] == key[0]){
            cout << names[i] << " (" << scores[i] << ")\n" ;
            x++;
        }
    }
    if(x < 1) {
        cout << "Cannot found.\n" ;
    }
    cout << "--------------------------------- " << "\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
