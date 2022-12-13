#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;

struct TreeNode {
    string name;
    bool isFile;
    int val;
    TreeNode* parent;
    vector<TreeNode*> children;
    TreeNode() : val(0), isFile(false) {} 
    TreeNode(int x) : val(x), isFile(false) {}
};

void populateVals(TreeNode* curr){
    if(curr->children.size() == 0){
        return;
    }
    for(TreeNode* child : curr->children){
        if(child->val == 0){
            populateVals(child);
        }
    }
    int sum = curr->val ?: 0;
    for(TreeNode* child : curr->children){
        sum = sum + child->val;
    }
    curr->val = sum;
}

void printTree(TreeNode* curr){
    for(TreeNode* child : curr->children){
        printTree(child);
    }
}

void traverseTree(TreeNode* curr, int* sum, int cutoff){
    if(curr->isFile == true){
        (*sum) = (*sum) + curr->val;
    }
    for(TreeNode* child : curr->children){
        traverseTree(child, sum, cutoff);
    }
}

void getDirSizes(TreeNode* curr, vector<int>* sizes){
    if(curr->isFile == false){
        sizes->push_back(curr->val);
    }
    for(TreeNode* child : curr->children){
       getDirSizes(child, sizes);
    }
}

void findSmallestDiff(TreeNode* currNode, int* smallestSoFar, int goal){
    if(currNode->isFile == true){
        return;
    }
    if(goal - currNode->val < *smallestSoFar){
        *smallestSoFar = currNode->val;
    }
    for(TreeNode* child : currNode->children){
        if(goal - currNode->val < *smallestSoFar){
            *smallestSoFar = currNode->val;
        }
        findSmallestDiff(child, smallestSoFar, goal);
    }
}

int main(){
    ifstream file;
    file.open("terminal.txt");
    if(!file.is_open()){
        cout<<"Unable to open the file."<<endl;
        return 0;
    }
    
    string line;
    string path = "$";
    TreeNode* root;
    TreeNode* currNode;

    int cutoff = 100000;
    int neededSpace = 30000000;
    int totalSpace = 70000000;
    vector<string> lines;

    while(getline(file, line)){
        lines.push_back(line);
    }

    for( int i = 0; i < lines.size(); i++){
        line = lines[i];
        cout<< i << " : " << line <<endl;
        if(line.find("$ cd /") != string::npos){
            root = new TreeNode();
            currNode = root;
            root->parent = nullptr;
            root->name = path;
        }
        else if(line.find("$ cd ..") != string::npos){
            int lastDirIndex = path.rfind('/');
            path = path.substr(0, lastDirIndex);
            currNode = currNode->parent;
        }
        else if(line.find("$ cd") != string::npos){
            string newDir = line.substr(5, line.length());
            path = path + '/' + newDir;
            // find child with the given directory name and set to current
            for(TreeNode* childNode : currNode->children){
                if(childNode->name == newDir){
                    currNode = childNode;
                }
            }
        }
        else if(line.find("dir ") != string::npos){
            string directory = line.substr(4, line.size());
            TreeNode* curr = new TreeNode();
            curr->name = directory;
            curr->parent = currNode;
            currNode->children.push_back(curr);
            // Helpful for seeing parent-child relationships
            // for( TreeNode*childNode : currNode->children){
            //     cout << currNode->name << "------   " << childNode->name << endl;
            // }
        }
        else if(line.find("$ ls") != string::npos){
            cout << "ls found" << endl;
        }
        else {
            // assume we have numbered file
            string size = line.substr(0, line.find(' '));
            string directory = line.substr(line.find(' ') + 1, line.size());
            TreeNode* curr = new TreeNode();
            curr->name = directory;
            curr->val = stoi(size);
            curr->parent = currNode;
            curr->isFile = true;
            currNode->children.push_back(curr);
        }

    }

    int sumOfSpace = 0;
    populateVals(root);
    printTree(root);
    traverseTree(root, &sumOfSpace, cutoff);

    vector<int>* dirSizes = new vector<int>();
    int difference = neededSpace - (totalSpace - root->val);
    cout << difference << endl;

    getDirSizes(root, dirSizes);
    int smallestSoFar = 1000000000;

    for( int elem : *dirSizes){
        if(elem < smallestSoFar && elem > difference) {
            smallestSoFar = elem;
        }
    }
    cout << "should be the end" << endl;
    cout << smallestSoFar << endl;
    file.close();
    return 0;
}