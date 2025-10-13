#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    
    string inputFile = am.get("input");
    string commandFile = am.get("command");
    string outputFile = am.get("output");
    
    ifstream fin(inputFile);
    ifstream fcmd(commandFile);
    ofstream fout(outputFile);
    
    if(!fin.is_open() || !fcmd.is_open() || !fout.is_open()){
        return 1;
    }
    
    // Read the starting URL (homepage)
    string currentPage;
    getline(fin, currentPage);
    
    // Remove carriage return if present
    if (!currentPage.empty() && currentPage.back() == '\r') {
        currentPage.pop_back();
    }
    
    // Initialize data structures
    stack<string> backStack;
    stack<string> forwardStack;
    queue<string> downloadQueue;
    
    // Process commands
    string commandLine;
    while (getline(fcmd, commandLine)) {
        // Remove carriage return
        if (!commandLine.empty() && commandLine.back() == '\r') {
            commandLine.pop_back();
        }
        
        if(commandLine.empty()) continue;
        
        if (commandLine.find("VISIT(") != string::npos) {
            // Extract URL from VISIT(url)
            int start = commandLine.find('(') + 1;
            int end = commandLine.find(')');
            string newUrl = commandLine.substr(start, end - start);
            
            // Push current page to back stack
            backStack.push(currentPage);
            
            // Clear forward stack
            while(!forwardStack.empty()) {
                forwardStack.pop();
            }
            
            // Update current page
            currentPage = newUrl;
        }
        else if (commandLine.find("BACK") != string::npos) {
            // Only navigate back if back stack is not empty
            if (!backStack.empty()) {
                // Push current page to forward stack
                forwardStack.push(currentPage);
                
                // Pop from back stack and make it current
                currentPage = backStack.top();
                backStack.pop();
            }
        }
        else if (commandLine.find("FORWARD") != string::npos) {
            // Only navigate forward if forward stack is not empty
            if (!forwardStack.empty()) {
                // Push current page to back stack
                backStack.push(currentPage);
                
                // Pop from forward stack and make it current
                currentPage = forwardStack.top();
                forwardStack.pop();
            }
        }
        else if (commandLine.find("DOWNLOAD(") != string::npos) {
            // Extract filename from DOWNLOAD(filename)
            int start = commandLine.find('(') + 1;
            int end = commandLine.find(')');
            string filename = commandLine.substr(start, end - start);
            
            // Add to download queue
            downloadQueue.push(filename);
        }
        else if (commandLine.find("PROCESS_DOWNLOAD") != string::npos) {
            // Remove front of download queue if not empty
            if (!downloadQueue.empty()) {
                downloadQueue.pop();
            }
        }
        else if (commandLine.find("PRINT(") != string::npos) {
            // Extract target from PRINT(target)
            int start = commandLine.find('(') + 1;
            int end = commandLine.find(')');
            string target = commandLine.substr(start, end - start);
            
            if (target == "current") {
                fout << "Current Page: " << currentPage << endl;
            }
            else if (target == "back") {
                fout << "Back Stack:" << endl;
                if (backStack.empty()) {
                    fout << "[empty]" << endl;
                } else {
                    // Print stack from top to bottom
                    stack<string> temp = backStack;
                    while (!temp.empty()) {
                        fout << temp.top() << endl;
                        temp.pop();
                    }
                }
            }
            else if (target == "forward") {
                fout << "Forward Stack:" << endl;
                if (forwardStack.empty()) {
                    fout << "[empty]" << endl;
                } else {
                    // Print stack from top to bottom
                    stack<string> temp = forwardStack;
                    while (!temp.empty()) {
                        fout << temp.top() << endl;
                        temp.pop();
                    }
                }
            }
            else if (target == "downloads") {
                fout << "Download Queue:" << endl;
                if (downloadQueue.empty()) {
                    fout << "[empty]" << endl;
                } else {
                    // Print queue from front to back
                    queue<string> temp = downloadQueue;
                    while (!temp.empty()) {
                        fout << temp.front() << endl;
                        temp.pop();
                    }
                }
            }
        }
    }
    
    fin.close();
    fcmd.close();
    fout.close();
    
    return 0;
}