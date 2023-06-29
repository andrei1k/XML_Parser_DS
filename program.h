#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <string>
#include <vector>

#include "xmlRequests.h"

void enterXmlPath(std::string& path);
unsigned menu();
void createXmlRequests(std::string& path, xmlRequests*& xmlTreeRequests);
std::vector<std::string> makeRequest(xmlRequests* xmlTreeRequests);
void printAnswer(const std::vector<std::string>& answer);
void pressToContinue();
//void printXmlTree(xmlTree* tree);

void program(){

    std::cout << "Hello!\n";

    std::string path;

    xmlRequests* request = nullptr;

    do{
        createXmlRequests(path, request);
    }while(request->isEmpty());
    
    unsigned option;

    do{

        option = menu();
        if(option == 1){
            createXmlRequests(path, request);
        }
        else if(option == 2){

            std::vector<std::string> answer = makeRequest(request);
            printAnswer(answer);
            pressToContinue();

        }
        // else if(option == 4){
        //     std::cout << "This option is unavailable because i do not want to put this function in the class.\n";
        //     // printXmlTree(request->root);
        //     pressToContinue();

        // }

    }while(option != 3);

    delete request;
    
}

unsigned menu(){

    unsigned option;

    do{
        system("CLS");

        std::cout << "Menu:\n";
        std::cout << "1. Open another xml file\n";
        std::cout << "2. Make xPath request\n";
        std::cout << "3. Close program\n";
       // std::cout << "4. print tree\n";
        std::cout << "Choose option: ";
        std::cin >> option;

        system("CLS");

    }while(option < 1 && option > 3);

    return option;

}

void enterXmlPath(std::string& path){

    std::cout << "Enter path of the xml file you want to open: ";

    if(std::cin.peek() == '\n')
        std::cin.get();

    getline(std::cin, path);
    
    system("CLS");

}

void createXmlRequests(std::string& path, xmlRequests*& xmlTreeRequests){
    
    do{

        if(xmlTreeRequests != nullptr){
            delete xmlTreeRequests;
        }
        enterXmlPath(path);
        xmlTreeRequests = new xmlRequests(path);

    }while(xmlTreeRequests->isEmpty());
    

}

std::vector<std::string> makeRequest(xmlRequests* xmlTreeRequests){

    if(xmlTreeRequests == nullptr){
        return std::vector<std::string>{};
    }

    std::cout << "Enter xPath request: ";

    std::string request;

    if(std::cin.peek() == '\n')
        std::cin.get();

    getline(std::cin, request);

    return xmlTreeRequests->completeRequest(request);

}

void printAnswer(const std::vector<std::string>& answer){

    // std::cout << "Do you want to print your answer?\nEnter \'y\' for yes, something else for no: ";
    // char ans;
    // std::cin >> ans;

    // if(ans == 'y'){

        for(int i = 0; i < answer.size(); i++){
            std::cout << answer[i] << '\n';
        }
    // }

}

void pressToContinue(){

    std::cout << "\nPress enter to continue...\n";

    std::cin.get();
    std::cin.get();
}

// void printXmlTree(xmlTree* tree){

//     if(tree == nullptr){
//         std::cout << "empty\n";
//         return;
//     }

//     std::cout << "Name: " << tree->name << std::endl;

//     std::cout << "Atributes: ";
//     for(int i = 0 ; i < tree->atributes.size() ; i++){
//         std::cout << tree->atributes[i].first << " = " << tree->atributes[i].second << '|';
//     }

//     std::cout << std::endl;

//     std::cout << "Content: ";
//     for(int i = 0 ; i < tree->content.size() ; i++){
//         std::cout << tree->content[i] << '|';
//     }

//     std::cout << std::endl;

//     for(int i = 0 ; i < tree->children.size(); i++){
//         printXmlTree(tree->children[i]);
//     }

// }

#endif // !PROGRAM_H