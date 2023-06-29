#include <iostream>

#include "validator.h"
#include "creator.h"
#include "xmlTree.h"
#include "xPathValidator.h"
#include "program.h"

// void printXmlTree(xmlTree* tree);

int main(){


    program();
    // Validator validator("primer.txt");

    // std::cout << validator.isValid();

    // std::string emptytag = "<tag            />";
    // StringWork::emptyTagToOpenTag(emptytag);
    // std::cout << emptytag << Validator::isOpenTag(emptytag);


    // xmlTree* tree = Creator::createXmlTree("lesenprimer.txt");

    // printXmlTree(tree);

    // xmlTree* copyTree(tree);

    // delete tree;

    // printXmlTree(copyTree);

    // std::cout << xPathValidator::isValid("person[12222]");

    // std::cout << std::boolalpha << xPathValidator::isValid("person/address[@id]") << '\n';

    // TUK

    // xmlRequests* tree = new xmlRequests("lesenprimer.txt");
    // xmlRequests tre(*tree);
    // // root/person[address="Bulgaria"]/name
    // std::string request = "person[name=\"John Smith\"]/name";
    // // StringWork::formatRequest(request);
    // // std::cout << request;
    // std::vector<std::string> answer = tree->completeRequest(request);

    // for(int i = 0; i < answer.size(); i++) {
    //     std::cout << answer[i] << '\n';
    // }

    //TUK

    // std::vector<xmlTree*> requested = completeRequest(request, tree);


    // for(int i = 0; i < requested.size(); i++){
    //     requested[i]->printContent();
    // }


    return 0;
}

