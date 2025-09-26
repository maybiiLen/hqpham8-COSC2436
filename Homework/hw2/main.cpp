#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

struct Song {
    string title;
    string artist;
    string genre;
    int duration;
    
    Song(){
        title = "";
        artist = "";
        genre = "";
        duration = 0;
    }
};

struct Node {
    Song data;
    Node* next;
    
    Node(const Song& s){
        data = s;
        next = nullptr;
    }
};

class Playlist {
private:
    Node* head;

public:
    Playlist(){
        head = nullptr;
    }
    
    ~Playlist(){
        clear();
    }

    void add(const Song& s){
        Node* newNode = new Node(s);
        //if list is empty (head is null), make this the first node
        if(head == nullptr){
            head = newNode;
        } else {
            Node* current = head;
            //otherwise, traverse to the end and append, this add song to the end of the list in order
            while(current->next != nullptr){
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void removeBy(const string& field, const string& value){
        // Remove from head
        while(head != nullptr){
            string nodeValue;
            if(field == "title") nodeValue = head->data.title;
            else if(field == "artist") nodeValue = head->data.artist;
            else if(field == "genre") nodeValue = head->data.genre;
            else if(field == "duration") nodeValue = to_string(head->data.duration);
            
            if(nodeValue == value){
                Node* temp = head;
                head = head->next;
                delete temp;
            } else {
                break;
            }
        }
        
        // Remove from middle/end
        if(head == nullptr) return;
        
        Node* current = head;
        while(current->next != nullptr){
            string nodeValue;
            if(field == "title") nodeValue = current->next->data.title;
            else if(field == "artist") nodeValue = current->next->data.artist;
            else if(field == "genre") nodeValue = current->next->data.genre;
            else if(field == "duration") nodeValue = to_string(current->next->data.duration);
            
            if(nodeValue == value){
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
            } else {
                current = current->next;
            }
        }
    }

    void groupBy(const string& field){
        if(head == nullptr) return;
        
        // convert to array to work with grouping easier
        Song* songs = new Song[1000]; // assume max 1000 songs
        int songCount = 0;
        
        Node* current = head;
        while(current != nullptr){
            songs[songCount] = current->data;
            songCount++;
            current = current->next;
        }
        
        // arrays to track groups
        string* uniqueValues = new string[1000];
        int* groupStarts = new int[1000];
        int* groupSizes = new int[1000];
        int numGroups = 0;
        
        // find groups and track first appearance order
        for(int i = 0; i < songCount; i++){
            string fieldValue;
            if(field == "title") fieldValue = songs[i].title;
            else if(field == "artist") fieldValue = songs[i].artist;
            else if(field == "genre") fieldValue = songs[i].genre;
            else if(field == "duration") fieldValue = to_string(songs[i].duration);
            
            // check if this group already exists
            int groupIndex = -1;
            for(int j = 0; j < numGroups; j++){
                if(uniqueValues[j] == fieldValue){
                    groupIndex = j;
                    break;
                }
            }
            
            // if new group, create it
            if(groupIndex == -1){
                uniqueValues[numGroups] = fieldValue;
                groupStarts[numGroups] = i; // mark where this group first appeared
                groupSizes[numGroups] = 0;
                groupIndex = numGroups;
                numGroups++;
            }
            
            groupSizes[groupIndex]++;
        }
        
        // rebuild the list with grouped songs
        clear();
        
        for(int g = 0; g < numGroups; g++){
            // for each group, add all songs that belong to it in original order
            for(int i = 0; i < songCount; i++){
                string fieldValue;
                if(field == "title") fieldValue = songs[i].title;
                else if(field == "artist") fieldValue = songs[i].artist;
                else if(field == "genre") fieldValue = songs[i].genre;
                else if(field == "duration") fieldValue = to_string(songs[i].duration);
                
                if(fieldValue == uniqueValues[g]){
                    add(songs[i]);
                }
            }
        }
        
        delete[] songs;
        delete[] uniqueValues;
        delete[] groupStarts;
        delete[] groupSizes;
    }

    void print(ofstream& out){
        Node* current = head;
        while(current != nullptr){
            out << "[title: " << current->data.title 
                << "; artist: " << current->data.artist
                << "; genre: " << current->data.genre
                << "; duration: " << current->data.duration << "]" << endl;
            current = current->next;
        }
    }

    void clear(){
        while(head != nullptr){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// helper function to remove whitespace from both ends
string trim(const string& s){
    int start = 0;
    int end = s.length() - 1;
    
    // find first non-whitespace
    while(start <= end && (s[start] == ' ' || s[start] == '\t' || s[start] == '\r' || s[start] == '\n')){
        start++;
    }
    
    // find last non-whitespace
    while(end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\r' || s[end] == '\n')){
        end--;
    }
    
    if(start > end) return "";
    return s.substr(start, end - start + 1);
}

// helper function to parse a song record from a line like [title: ...; artist: ...; genre: ...; duration: ...]
Song parseSong(const string& line){
    Song song;
    string content = line;
    
    // remove brackets if present
    if(!content.empty() && content[0] == '[' && content[content.length()-1] == ']'){
        content = content.substr(1, content.length() - 2);
    }
    
    // split by semicolons and process each piece
    stringstream ss(content);
    string token;
    while(getline(ss, token, ';')){
        // find the colon that separates key from value
        int colonPos = -1;
        for(int i = 0; i < token.length(); i++){
            if(token[i] == ':'){
                colonPos = i;
                break;
            }
        }
        
        if(colonPos == -1) continue;
        
        string key = trim(token.substr(0, colonPos));
        string value = trim(token.substr(colonPos + 1));
        
        if(key == "title") song.title = value;
        else if(key == "artist") song.artist = value;
        else if(key == "genre") song.genre = value;
        else if(key == "duration") song.duration = stoi(value);
    }
    return song;
}

// helper function to parse 
void parseFieldValue(const string& inside, string& field, string& value){
    int colonPos = -1;
    for(int i = 0; i < inside.length(); i++){
        if(inside[i] == ':'){
            colonPos = i;
            break;
        }
    }
    
    if(colonPos == -1){
        field = trim(inside);
        value = "";
    } else {
        field = trim(inside.substr(0, colonPos));
        value = trim(inside.substr(colonPos + 1));
    }
}

int main(int argc, char* argv[]){
    ArgumentManager am(argc, argv);
    
    string inputFile = am.get("input");
    string commandFile = am.get("command");
    string outputFile = am.get("output");

    ifstream fin(inputFile);
    ifstream fcmd(commandFile);
    ofstream fout(outputFile);

    //test case to see if files can be open
    if(!fin.is_open() || !fcmd.is_open() || !fout.is_open()){
        return 1;
    }

    Playlist* pl = new Playlist();

    // 1) Read initial songs from input file
    string line;
    while(getline(fin, line)){
        // remove carriage return if present
        if(!line.empty() && line.back() == '\r') line.pop_back();
        line = trim(line);
        if(line.empty()) continue;
        
        Song song = parseSong(line);
        pl->add(song);
    }

    // 2) Read and execute commands from command file
    string commandLine;
    while(getline(fcmd, commandLine)){
        // remove carriage return if present
        if(!commandLine.empty() && commandLine.back() == '\r') commandLine.pop_back();
        commandLine = trim(commandLine);
        if(commandLine.empty()) continue;

        if(commandLine.find("Add(") != string::npos && commandLine.back() == ')'){
            // extract content inside parentheses
            int start = commandLine.find('(') + 1;
            int end = commandLine.find_last_of(')');
            string inside = commandLine.substr(start, end - start);
            
            Song song = parseSong(inside);
            pl->add(song);
        }
        else if(commandLine.find("Remove(") != string::npos && commandLine.back() == ')'){
            // extract content inside parentheses
            int start = commandLine.find('(') + 1;
            int end = commandLine.find_last_of(')');
            string inside = commandLine.substr(start, end - start);
            
            string field, value;
            parseFieldValue(inside, field, value);
            pl->removeBy(field, value);
        }
        else if(commandLine.find("Group(") != string::npos && commandLine.back() == ')'){
            // extract content inside parentheses
            int start = commandLine.find('(') + 1;
            int end = commandLine.find_last_of(')');
            string inside = commandLine.substr(start, end - start);
            
            string field = trim(inside);
            pl->groupBy(field);
        }
        else if(commandLine.find("Print") != string::npos){
            pl->print(fout);
        }
    }

    delete pl;
    fin.close();
    fcmd.close();
    fout.close();

    return 0;
}