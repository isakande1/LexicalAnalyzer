/*
 * lex.h
 *
 * CS280
 * Spring 2023
*/

#include<sstream>
#include <string>
#include <iostream>
#include <map>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;
string tempWord;
string word;
int lineum;
string line;
int num =0;
string w;
string flag;
string flag1;
string flag2;
string flag3;
string flag4;


///////////////////////////
vector<string> allToken;
vector <string> allLex;
vector <string> identList;
vector<string> numericList;
vector<float> numericList2;
vector<string> stringList;
///////////////////////////////////////

string tok;
string lex;

fstream read;
///////////////////////////
int totalTok  =0;
int totalIdents =0;
int totalNumeric=0;
int totalString=0;

//////////////////////////////////

//Class definition of LexItem
class LexItem {
    string	token;
    string	lexeme;
    int	lnum;

public:
    LexItem() {
        string error = "ERR";
        lnum = -1;
    }
    LexItem(string token, string lexeme, int line) {
        this->token = token;
        this->lexeme = lexeme;
        this->lnum = line;
    }


    string	GetToken() const { return token; }
    string	GetLexeme() const { return lexeme; }
    int	GetLinenum() const { return lnum; }
};


class Project{
public:
    int tokenCount=0;

    ///////////////////////////////////////
    LexItem checkInt(string& word) {

        for (int i = 0; i < word.length(); i++) {
            if (!isdigit(word.at(i))) {
                tempWord = word.substr(0,i);
                word.erase(0,i);
                return LexItem("ICONST", tempWord, lineum);
            }

        }
        tempWord = word;
        word.erase();
        return LexItem("ICONST", tempWord, lineum);
    }


    LexItem checkReal(string& word ) {
        size_t lastDot =0;

        int tokenCount =0;

        ////////////////////////
        for(char i : word){
            if(i=='.'){
                tokenCount+=1;
            }
        }
        if(tokenCount>1) {
            lastDot = word.find_last_of('.',word.length()) ;
            tempWord=word.substr(0,(lastDot+1));
            word.erase();

            return  LexItem("ERR", tempWord, lineum);
        }
        ////////////////////////////////////////
        for (int i = 0; i < word.length(); i++) {
            if (!(isdigit(word.at(i)) || word.at(i) == '.')) {
                tempWord = word.substr(0,i);
                word.erase(0,i);
                return LexItem("RCONST", tempWord, lineum);
            }
        }
        tempWord = word;
        word.erase();
        return  LexItem("RCONST", tempWord, lineum);
    }
    LexItem checkIdent(string& word) {
        //  char peek;
        LexItem lexi;
        if ((word.at(0) == '_' || isalpha(word.at(0)))) {
            for (int i = 1; i < word.length(); i++) {
                /////@$ potential check to include
                if (!(isalnum(word.at(i)) || (word.at(i) == '_'))) {
                    tempWord = word.substr(0, i);
                    word.erase(0, i);
                    //totalIdents+=1;
                    if (flag1=="-v"&&flag2=="-nconst"&&flag3=="-sconst"&&flag4=="-ident"){
                        if (tempWord == "if" ) {
                           // totalIdents -= 1;
                            lexi = LexItem("IF", tempWord, lineum);
                        } else if (tempWord == "writeln" ) {
                          //  totalIdents -= 1;
                            lexi = LexItem("WRITELN", tempWord, lineum);
                        }else{
                            lexi =LexItem("IDENT", tempWord, lineum);
                        }
                        return  lexi;
                    }
                    return LexItem("IDENT", tempWord, lineum);

                }
            }


        }
        tempWord = word;
        word.erase();
        if (flag1=="-v"&&flag2=="-nconst"&&flag3=="-sconst"&&flag4=="-ident"){
            if (tempWord == "if" ) {
                //totalIdents -= 1;
                lexi = LexItem("IF", tempWord, lineum);
            } else if (tempWord == "writeln" ) {
               // totalIdents -= 1;
                lexi = LexItem("WRITELN", tempWord, lineum);
            }else{
                lexi =LexItem("IDENT", tempWord, lineum);
            }

            return  lexi;
        }

        return LexItem("IDENT", tempWord, lineum);
    }

    void insertData(string& to ,string& le){
        allToken.push_back(to);
        allLex.push_back(le);
        // if(flag != "-v"){
        if((to=="IDENT" || tok == "SIDENT" || to=="NIDENT") && ( find(identList. begin() , identList.end(), lex) == identList. end())){
            identList.push_back(le);
            totalIdents+=1;
        }

        if(( to == "ICONST" || to=="RCONST") && (find(numericList.begin() , numericList.end(), lex) == numericList. end()) ){
            numericList.push_back(le);
            numericList2.push_back(stof(le));
        }

        if( to=="SCONST" && ( find(stringList.begin(), stringList. end(), lex ) == stringList. end()) ) {
            stringList.push_back(le);
            totalString +=1;
        }



    }


    LexItem checkSident(string& wor){
        if( (wor.at(0) =='@') && (wor.at(1)=='_' || isalpha(wor.at(1)))  ){
            for(int i =2; i<wor.length(); i++){
                /////@$ potential check to include
                if(!(isalnum(wor.at(i)) || (wor.at(i) =='_'))){
                    tempWord = wor.substr(0,i);
                    wor.erase(0,i);
                    //  totalIdents+=1;
                    return  LexItem("SIDENT", tempWord, lineum);

                }
            }
        }
        tempWord = word;
        word.erase();
        // totalIdents+=1;
        return  LexItem("SIDENT", tempWord, lineum);

    }

    LexItem checkNident(string& word){
        if( (word.at(0) =='$') && (word.at(1)=='_' || isalpha(word.at(1)))  ){
            for(int i =2; i<word.length(); i++){
                /////@$ potential check to include
                if(!(isalnum(word.at(i)) || (word.at(i) =='_'))){
                    tempWord = word.substr(0,i);
                    word.erase(0,i);
                    // totalIdents+=1;
                    return  LexItem("NIDENT", tempWord, lineum);

                }
            }
        }
        tempWord = word;
        word.erase();
        //   totalIdents+=1;
        return  LexItem("NIDENT", tempWord, lineum);

    }

    void display(string& tok, string& flag) {
        if (tok == "ERR") {
            for (auto i = allToken.begin(), j = allLex.begin(); i != allToken.end(); ++i,++j) {
                if (*i == "IDENT" || *i == "ICONST" || *i == "SIDENT" || *i == "NIDENT" || *i == "SCONST" || *i == "RCONST" ) {
                    cout << *i << "(" << *j << ")" << endl;
                } else if (*i == "ERR") {
                    cout << "Error in line " << lineum << " (" << *j << ")" << endl;
                } else {
                    cout << *i << endl;
                }

            }
            /////////////////////////////////regular
            exit(1);
        }

        if(flag ==""){
            totalIdents = totalIdents -3;

            cout<<"\n" <<"Lines: " << lineum << endl;
            cout<<"Total Tokens: " << totalTok <<endl;
            cout<<"Identifiers: "   << totalIdents<<endl;
            cout<<"Numbers: "  <<totalNumeric<< endl;
            cout<<"Strings: "  <<totalString <<endl;
            exit(0);
        }



        if(flag1=="-v"&&flag2=="-nconst"&&flag3=="-sconst"&&flag4=="-ident") {
            for (auto i = allToken.begin(), j = allLex.begin(); i != allToken.end(); ++i, ++j) {
                if (*i == "IDENT" || *i == "ICONST" || *i == "SIDENT" || *i == "NIDENT" || *i == "SCONST" ||
                    *i == "RCONST") {
                    cout << *i << "(" << *j << ")" << endl;
                } else {
                    cout << *i << endl;
                }
            }


            cout << "\n" << "Lines: " << lineum << endl;
            cout << "Total Tokens: " << totalTok << endl;
            cout << "Identifiers: " << totalIdents << endl;
            cout << "Numbers: " << totalNumeric << endl;

            cout << "Strings: " << totalString << endl;
            if(!(totalNumeric ==0 && totalIdents==0)){
                cout << "IDENTIFIERS:" << endl;
                sort(identList.begin(), identList.end());
                for (auto i = identList.begin(); i != identList.end(); ++i) {
                    if (*i != identList.back()) {
                        cout << *i << ", ";
                    } else {
                        cout << *i << endl;
                    }

                }

                cout<<"NUMBERS:" <<endl;
                sort(numericList2.begin(),numericList2.end());
                for(auto i = numericList2.begin();  i!= numericList2.end(); ++i){
                    cout<< *i <<endl;
                }}
            if (totalString != 0) {
                cout << "STRINGS:" << endl;
                sort(stringList.begin(), stringList.end());
                for (auto i = stringList.begin(); i != stringList.end(); ++i) {
                    cout << "'" << *i << "'" << endl;
                }
            }
            ////////////////////////////////////////end v /////////////////////

        }else if(flag =="-v"){
            for (auto i = allToken.begin(), j = allLex.begin(); i != allToken.end(); ++i, ++j) {
                if (*i == "IDENT" || *i == "ICONST" || *i == "SIDENT" || *i == "NIDENT" || *i == "SCONST" ||
                    *i == "RCONST") {
                    cout << *i << "(" << *j << ")" << endl;
                } else {
                    cout << *i << endl;
                }
            }
            cout << "\n" << "Lines: " << lineum << endl;
            cout << "Total Tokens: " << totalTok << endl;
            cout << "Identifiers: " << totalIdents << endl;
            cout << "Numbers: " << totalNumeric << endl;
            cout<<"Strings: "  <<totalString <<endl;
            if(!(totalNumeric ==0 && totalIdents==0)){
                cout << "IDENTIFIERS:" << endl;
                sort(identList.begin(), identList.end());
                for (auto i = identList.begin(); i != identList.end(); ++i) {
                    if (*i != identList.back()) {
                        cout << *i << ", ";
                    } else {
                        cout << *i << endl;
                    }

                }

                cout<<"NUMBERS:" <<endl;
                sort(numericList2.begin(),numericList2.end());
                for(auto i = numericList2.begin();  i!= numericList2.end(); ++i){
                    cout<< *i <<endl;
                }}
            if(totalString>2){
                sort(stringList.begin(), stringList.end());
                cout<<"STRINGS:" <<endl;
                for(auto i = stringList.begin();  i!= stringList.end(); ++i){
                    cout<<"'" <<*i <<"'" <<endl;
                }
            }

        }
        else if(flag =="-sconst"){
//
            for (auto i = allToken.begin(), j = allLex.begin(); i != allToken.end(); ++i,++j) {
                if (*i == "IDENT" || *i == "ICONST" || *i == "SIDENT" || *i == "NIDENT" || *i == "SCONST" ||
                    *i == "RCONST") {
                    cout << *i << "(" << *j << ")" << endl;
                } else {
                    cout << *i << endl;
                }
            }


            cout<<"\n" <<"Lines: " << lineum << endl;
            cout<<"Total Tokens: " << totalTok <<endl;
            cout<<"Strings: "  <<totalString <<endl;
            cout<<"STRINGS:" <<endl;
            sort(stringList.begin(), stringList.end());
            for(auto i = stringList.begin();  i!= stringList.end(); ++i){
                cout<<"'" <<*i <<"'" <<endl;
            }
        }else if(flag=="-nconst"){

            for (auto i = allToken.begin(), j = allLex.begin(); i != allToken.end(); ++i,++j) {
                if (*i == "IDENT" || *i == "ICONST" || *i == "SIDENT" || *i == "NIDENT" || *i == "SCONST" ||
                    *i == "RCONST") {
                    cout << *i << "(" << *j << ")" << endl;
                } else {
                    cout << *i << endl;
                }
            }


            cout<<"\n" <<"Lines: " << lineum << endl;
            cout<<"Total Tokens: " << totalTok <<endl;
            cout<<"Identifiers: "   << totalIdents<<endl;
            cout<<"Numbers: "  <<totalNumeric<< endl;
            cout<<"Strings: "  <<totalString <<endl;
            cout<<"NUMBERS:" <<endl;
            sort(numericList2.begin(),numericList2.end());
            for(auto i = numericList2.begin();  i!= numericList2.end(); ++i){
                cout<< *i <<endl;
            }
        }else if(flag=="-ident"){
            for (auto i = allToken.begin(), j = allLex.begin(); i != allToken.end(); ++i,++j) {
                if (*i == "IDENT" || *i == "ICONST" || *i == "SIDENT" || *i == "NIDENT" || *i == "SCONST" ||
                    *i == "RCONST") {
                    cout << *i << "(" << *j << ")" << endl;
                } else {
                    cout << *i << endl;
                }
            }


            cout<<"\n" <<"Lines: " << lineum << endl;
            cout<<"Total Tokens: " << totalTok <<endl;
            cout<<"Identifiers: "   << totalIdents<<endl;
            cout<<"Numbers: "  <<totalNumeric<< endl;
            cout<<"Strings: "  <<totalString <<endl;
            cout<<"IDENTIFIERS:" <<endl;
            sort(identList.begin(),identList.end());
            for(auto i = identList.begin();  i!= identList.end(); ++i){
                if( *i != identList.back()){
                    cout<< *i <<", ";
                }else{
                    cout<< *i <<endl;
                }
                if(totalNumeric>4){
                    cout<<"NUMBERS:" <<endl;
                    sort(numericList2.begin(),numericList2.end());
                    for(auto i = numericList2.begin();  i!= numericList2.end(); ++i){
                        cout<< *i <<endl;
                    }
                }

            }
        }

    }


};


LexItem print;
Project obj2;
///GETnExt
LexItem getNextToken(istream& in, int& lineum, stringstream& c) {
    totalTok+=1;
//    if(word=="END"){
//        totalIdents-=1;
//    }
    char firstChar = word.at(0);

    switch(firstChar){

        case '+':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("PLUS", tempWord, lineum);
            break;
        case '-':
            if(word.substr(1,2)=="eq"){
                tempWord = word.substr(0,3);
                word.erase(0,3);
                return  LexItem("SEQ", tempWord, lineum);

            }else if(word.substr(1,2)=="lt"){
                tempWord = word.substr(0,3);
                word.erase(0,3);
                return  LexItem("SLTHAN", tempWord, lineum);

            } else if(word.substr(1,2)=="gt" || word.substr(1,2)=="Gt"||word.substr(1,2)=="GT"){
                tempWord = word.substr(0,3);
                word.erase(0,3);
                return  LexItem("SGTHAN", tempWord, lineum);

            }else {
                tempWord = word.at(0);
                word.erase(0, 1);
                return LexItem("MINUS", tempWord, lineum);
            }
            break;
        case '*':
            if(word.length()>1&&word.at(1)=='*'){
                tempWord = word.substr(0,2);
                word.erase(0,2);
                return LexItem("SREPEAT", tempWord, lineum);
            }else{
                tempWord = word.at(0);
                word.erase(0,1);
                return LexItem("MULT", tempWord, lineum);
            }
            break;
        case '/':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("DIV", tempWord, lineum);
            break;
        case '^':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("EXPONENT", tempWord, lineum);
            break;

        case '=':
            if(word.length()>1 &&word.at(1)=='='){
                tempWord = word.substr(1,2);
                word.erase(0,2);

                return LexItem("NEQ", tempWord, lineum);
            }else{
                tempWord =word.at(0);
                word.erase(0,1);
                return LexItem("ASSOP", tempWord, lineum);
            }
            break;
        case '>':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("NGTHAN", tempWord, lineum);
            break;
        case '<':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("NLTHAN", tempWord, lineum);
            break;
        case '.':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("CAT", tempWord, lineum);
            break;
        case ';':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("SEMICOL", tempWord, lineum);
            break;
        case ',':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("COMMA", tempWord, lineum);
            break;
        case '(':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("LPAREN", tempWord, lineum);
            break;
        case ')':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("RPAREN", tempWord, lineum);
            break;
        case '{':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("LBRACES", tempWord, lineum);
            break;
        case '}':
            tempWord = word.at(0);
            word.erase(0,1);
            return LexItem("RBRACES", tempWord, lineum);
            break;
        case '\'':
            string tempString;
            int first = line.find('\'');
            line.erase(first,1);
            int last = line.find('\'');
            if(last> -1 && last<100){
                tempWord = line.substr(first, (last-first)) ;
                tempString = line.substr((last+1),(line.length()-first));
                c.str(string());
                c.clear();
                c<<tempString;
                line = tempString;
                tempString.erase();
                word.erase();
                return ( LexItem("SCONST", tempWord, lineum) );
            }else
                last = line.find('"');
            if(last<100 && last>-1){
                tempWord = line.substr(first, (last-first+1)) ;
                tempWord.insert(0,"'");
                stringstream l(line);
                c.str(string());
                c.clear();
                word.erase();

                return  LexItem("ERR", tempWord, lineum) ;

            }else{
                tempWord = line.substr(first,(line.length()) -first+1);
                tempWord.insert(0,"'");
                stringstream l(line);
                word.erase();
                c.str(string());
                c.clear();
                return ( LexItem("ERR", tempWord, lineum) );
            }
            break;
    }
    Project obj;
    if(isdigit(word.at(0))){

        if(word.find('.')<4){
            return (obj.checkReal(word));
        }else{
            return  (obj.checkInt(word));
        }
    }
    if( word.at(0)=='_' || isalpha(word.at(0)) ){
        return (obj.checkIdent(word));
    }else if(word.at(0) == '@'){
        return (obj.checkSident(word));
    }else if( word.at(0) == '$'){
        return (obj.checkNident(word));
    }
    tempWord = word.at(0);
    word.erase();
    c.str(string());
    c.clear();
    return ( LexItem("ERR", tempWord, lineum) );//possible trouble
}

int parse(stringstream& s, LexItem& print){
    tempWord.erase();
    print =getNextToken(read, lineum,s);

    tok = (print.GetToken());
    lex = (print.GetLexeme());
    obj2.insertData(tok,lex);
    if(tok=="ERR"){
        s.str(string());
        s.clear();
        return 0;
    }
    if (tok =="RCONST" || tok =="ICONST"){
        totalNumeric+=1;
    }else if(tok =="SCONST"){
        //  totalString+=1;
    }

    while(word.length()>0){
        tempWord.erase();
        print =getNextToken(read, lineum,s);

        tok = (print.GetToken());
        lex = (print.GetLexeme());
        obj2.insertData(tok,lex);
        if(tok =="RCONST" || tok =="ICONST"){
            totalNumeric+=1;
        }else if(tok =="SCONST"){
            //totalString+=1;
        }

    }
    return 1;
}
///end GetMNext
int main(int arg, char *argv[]) {

    string filenameSecond;

    string filename = "";
///////////////////////////////


    ///////////////Test file availality///////////////////
    if (arg > 1) {
        filename = argv[1];
    }
    if(arg==6){

        flag1=argv[2];
        flag2=argv[3];
        flag3=argv[4];
        flag4=argv[5];
    }
    if(arg ==4){
        string arr = argv[3];
        if (arr.at(0) != '-') {
            cout << "ONLY ONE FILE NAME IS ALLOWED." << endl;
            exit(1);
        }
    }



    if (arg >= 3) {
        filenameSecond = argv[2];
        if (filenameSecond.at(0) != '-') {
            exit(1);
        }
        flag = argv[(arg - 1)];
    }


    // string line;
    if (filename.empty()) {
        cout << "NO SPECIFIED INPUT FILE." << endl;
        exit(0);
    }
    string filename2 = filename;
    read.open(filename2, ios::in);
    if (!read.is_open()) {
        cout << "CANNOT OPEN THE FILE " << filename << endl;
        exit(1);
    }

    ifstream filee(filename2, ios::binary | ios::ate);
    if (filee.tellg() < 1) {
        cout << "Lines: 0" << endl;
        cout << "Empty File." << endl;
        exit(1);
    }
    if (flag.length() > 1 && flag.at(0) == '-' &&
        !(flag == "-v" || flag == "-nconst" || flag == "-sconst" || flag == "-ident")) {
        cout << "UNRECOGNIZED FLAG " << "{" << flag << "}" << endl;
        exit(1);
    }
    //////////end////////////////////

    while (getline(read, line) && tok != "ERR") {

        tempWord.erase();
        lineum += 1;
        stringstream s(line);

        while (s >> word) {

            if (word.at(0) == '#') {
                s.str(string());
            } else {
                parse(s, print);
            }

        }

    }

    obj2.display(tok, flag);

}