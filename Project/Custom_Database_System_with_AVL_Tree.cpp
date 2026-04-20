#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const string FILENAME="student_records.txt";

struct StudentRecord {
    int StudentID;
    string Name;
    float GPA;
};


struct AVLNode{
    StudentRecord data;
    AVLNode* left;
    AVLNode* right;
    int height;
};

AVLNode* newNOde(StudentRecord record){
    AVLNode* node= new AVLNode();
    node->data=record;
    node->left=nullptr;
    node->right=nullptr;
    node->height=1;
    return node;
}

int height(AVLNode* N){
    if(N==nullptr){
        return 0;
    }
    return N->height;
}

int getBalance(AVLNode* N){
    if(N==nullptr){
        return 0;
    }
    return height(N->left)-height(N->right);
}
AVLNode* rightRotate(AVLNode* y){
    AVLNode* x=y->left;
    AVLNode* T2=x->right;
    x->right=y;
    y->left=T2;
    y->height=max(height(y->left),height(y->right))+1;
    x->height=max(height(x->left),height(x->right))+1;
    return x;
}

AVLNode* leftRotate(AVLNode* x){
    AVLNode* y=x->right;
    AVLNode* T2=y->left;
    y->left=x;
    x->right=T2;
    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;
    return y;
}

AVLNode* insert(AVLNode* node,StudentRecord record){
    if(node==nullptr){
        return newNOde(record);
    }
    if(record.StudentID < node->data.StudentID){
        node->left=insert(node->left,record);
    }
    else if(record.StudentID > node->data.StudentID){
        node->right=insert(node->right,record);
    }
    else{
        cout<<"Error: Record with ID"<<record.StudentID<<"already exists."<<endl;
        return node;
    }
    node->height= 1 + max(height(node->left),height(node->right));
    int balance =getBalance(node);
    if(balance > 1 && record.StudentID < node->left->data.StudentID){
        return rightRotate(node);
    }
    if(balance < -1 && record.StudentID > node->right->data.StudentID){
        return leftRotate(node);
    }
    if(balance > 1 && record.StudentID > node->left->data.StudentID){
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance < -1 && record.StudentID < node->right->data.StudentID){
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

AVLNode* search(AVLNode* root,int id){
    if(root==nullptr || root->data.StudentID==id){
        return root;
    }
    if(id < root->data.StudentID){
        return search(root->left,id);
    }
    return search(root->right,id);
}

void inOrder(AVLNode* root){
    if(root!=nullptr){
        inOrder(root->left);
        cout<<setw(10)<<root->data.StudentID<<setw(25)<<left<<root->data.Name<<setw(4)<<fixed<<setprecision(2)<<root->data.GPA<<endl;
        inOrder(root->right);
    }
}

void saveToFile(AVLNode* root , ofstream& outfile){
    if(root!=nullptr){
        outfile<<root->data.StudentID<<endl;
        outfile<<root->data.Name<<endl;
        outfile<<root->data.GPA<<endl;
        saveToFile(root->left,outfile);
        saveToFile(root->right,outfile);        
    }
}

void saveDatabase(AVLNode* root){
    ofstream outfile(FILENAME);
    if(outfile.is_open()){
        saveToFile(root,outfile);
        outfile.close();
    }
    else{
        cout<<" Error: Unable to open file for saving !"<<endl;
    }
}

AVLNode* loadDatabase(){
    ifstream inFile(FILENAME);
    AVLNode* root=nullptr;
    StudentRecord record;
    if(inFile.is_open()){
        while(inFile >> record.StudentID){
            inFile.ignore();
            getline(inFile,record.Name);
            inFile>>record.GPA;
            root=insert(root,record);
        }
        inFile.close();
        cout<<" Database Loaded Successfully from "<<FILENAME<<endl;
    }
    else{
        cout<<" No existing database found. Starting with an empty database. "<<endl;
    }
    return root;
}
AVLNode* dbRoot=nullptr;

void cleanupTree(AVLNode* node){
    if(node==nullptr){
        return;
    }
    cleanupTree(node->left);
    cleanupTree(node->right);
    delete node;
}

void displayMenu(){
    int choice;
    int id;
    StudentRecord record;
    AVLNode* foundNode;
    dbRoot=loadDatabase();
    do{
        cout<<"AVL TREE CUSTOM DATABASE SYSTEM "<<endl;
        cout<<"1. Add New Student Record "<<endl;
        cout<<"2. Search Student Record by ID "<<endl;
        cout<<"3. Display All Records(Sorted by ID) "<<endl;
        cout<<"4. Exit "<<endl;
        cout<<"Enter Your Choice "<<endl;
        if(!(cin>>choice)){
            cout<<"Invalid input. Please enter a number between 1 and 4."<<endl;
            cin.clear();
            cin.ignore(10000,'\n');
            continue;
        }
        switch(choice){
            case 1:
               cout<<" ADD RECORD "<<endl;
               cout<<" Enter Student ID: "<<endl;
               if(!(cin>>record.StudentID)){
                cout<<" Invalid ID. Try again."<<endl;
                cin.clear();
                cin.ignore(10000,'\n'); 
                break;
              }
               cout<<" Enter Student Name: "<<endl;
               cin.ignore();
               getline(cin,record.Name);
               cout<<" Enter GPA: "<<endl;
               if(!(cin>>record.GPA)){
                  cout<<" Invalid GPA. Try again. "<<endl;
                  cin.clear();
                  cin.ignore(10000,'\n');
                  break;
               }
               dbRoot=insert(dbRoot,record);
               cout<<" Record insertion complete, Tree Structure Rebalanced "<<endl;
               break;
            case 2:
                cout<<" SEARCH RECORD "<<endl;
                cout<<" Enter Student ID  to Search: "<<endl;
                if(!(cin>>id)){
                    cout<<" Invalid ID. Try again."<<endl;
                    cin.clear();
                    cin.ignore(10000,'\n');
                    break;
                }
                foundNode=search(dbRoot,id);
                if(foundNode!=nullptr){
                    cout<<" RECORD FOUND "<<endl;
                    cout<<"ID: "<<foundNode->data.StudentID<<endl;
                    cout<<"Name: "<<foundNode->data.Name<<endl;
                    cout<<"GPA: "<<fixed<<setprecision(2)<<foundNode->data.GPA<<endl;
                }
                else{
                    cout<<" Record with ID "<<id<<" not found in the database. "<<endl;
                }
                break;
            case 3:
                cout<<" ALL RECORDS(Sorted by ID) "<<endl;
                if(dbRoot==nullptr){
                    cout<<" The database is currently empty."<<endl;
                }
                else{
                    cout<<"|   Student ID   |        Name         | GPA "<<endl;
                    cout<<"-----------------------------------------------"<<endl;
                    inOrder(dbRoot);
                }
                break;
            case 4:
                saveDatabase(dbRoot);
                cout<<" Exiting the program. "<<endl;
                cleanupTree(dbRoot);
                dbRoot=nullptr;
                break;
        default:
                cout<<" Invalid choice.Please try again."<<endl;
        }
    } while(choice!=4);
}
int main(){
    displayMenu();
    return 0;
}