#include "xmlRequests.h"

xmlRequests::xmlRequests() : root(nullptr) {}

xmlRequests::xmlRequests(const std::string& path){

    root = Creator::createXmlTree(path);
}

xmlRequests::~xmlRequests(){
    delete root;
    root = nullptr;
}

std::vector<std::string> xmlRequests::completeRequest(std::string request){

    std::vector<std::string> answer;

    if(!xPathValidator::isValid(request)){
        std::cout << "Invalid xPath!\n";
        return answer;
    }

    StringWork::formatRequest(request);
    std::stringstream startStream(request);

    std::vector<xmlTree*> completeRequestList;
    std::string buffer;
    getline(startStream, buffer);

    if(buffer == root->name)
        completeRequestList.push_back(root);

    if(startStream.peek() == '['){
        startStream.get();
        getline(startStream, buffer, ']');
        startStream.get();
        if(xPathValidator::isParity(buffer)){
            std::vector<xmlTree*> next;
            parityParameter(completeRequestList, next, buffer);
            completeRequestList = next;
        }
        else if(xPathValidator::isMonkeyA(buffer)){
            monkeyParameter(completeRequestList, buffer, answer);
        }
    }

    request = StringWork::readFile(startStream);

    while(request != ""){
        // std::cout << request;
        completeRequestList = getNextLvl(completeRequestList, request, answer);
        
    }

    if(answer.empty()){

        for(int i = 0; i < completeRequestList.size(); i++){

            for(int j = 0; j < completeRequestList[i]->content.size(); j++){

                answer.push_back(completeRequestList[i]->content[j]);
            }
        }
    }

    return answer;

}

std::vector<xmlTree*> xmlRequests::getNextLvl(std::vector<xmlTree*> currLvl, std::string& request, std::vector<std::string>& answer){

   std::vector<xmlTree*> nextLvl;

    std::stringstream requestStream(request);

    std::string childName;

    getline(requestStream, childName);

    // makeNextLvl(currLvl, nextLvl, childName);


    if(requestStream.peek() == '['){

        requestStream.get();
        std::string parameter;
        getline(requestStream, parameter, ']');
        requestStream.get();

        // currLvl = nextLvl;
        // nextLvl.clear();

        if(xPathValidator::isParity(parameter)){

            makeNextLvl(currLvl, nextLvl, childName);
            currLvl = nextLvl;
            nextLvl.clear();

            parityParameter(currLvl, nextLvl, parameter);
        }
        else if(xPathValidator::isNumber(parameter)){

            numberParameter(currLvl, nextLvl, childName, parameter);
        }
        else{

            makeNextLvl(currLvl, nextLvl, childName);
            currLvl = nextLvl;
            nextLvl.clear();
            monkeyParameter(currLvl, parameter, answer);
        }
    }
    else{

        makeNextLvl(currLvl, nextLvl, childName);
        
    }

    request = StringWork::readFile(requestStream);
    return nextLvl;

}

void xmlRequests::makeNextLvl(std::vector<xmlTree*> currLvl, std::vector<xmlTree*>& nextLvl, std::string childName){

    for(int i = 0; i < currLvl.size(); i++){

        for(int j = 0; j < currLvl[i]->children.size(); j++){

            if(currLvl[i]->children[j]->name == childName){
                nextLvl.push_back(currLvl[i]->children[j]);
            }
        }
    }

}

void xmlRequests::parityParameter(std::vector<xmlTree*> currLvl, std::vector<xmlTree*>& nextLvl, std::string parameter){

    std::stringstream parameterStream(parameter);

    std::string key, wanted;
    getline(parameterStream, key, '=');
    getline(parameterStream, wanted);

    wanted.erase(0, 1);
    wanted.pop_back();

    for(int i = 0; i < currLvl.size(); i++){

        for(int j = 0; j < currLvl[i]->children.size(); j++){

            if(currLvl[i]->children[j]->name == key){

                for(int k = 0; k < currLvl[i]->children[j]->content.size(); k++){

                    if(currLvl[i]->children[j]->content[k] == wanted){
                        nextLvl.push_back(currLvl[i]);
                    }
                }

            }
        }

        // maybe

        for(int j = 0; j < currLvl[i]->atributes.size(); j++){
            
            if(currLvl[i]->atributes[j].first == key){

                if(currLvl[i]->atributes[j].second == wanted){
                    nextLvl.push_back(currLvl[i]);
                }
            }

        }
    }

}

void xmlRequests::numberParameter(std::vector<xmlTree*> currLvl, std::vector<xmlTree*>& nextLvl, std::string subChild, std::string parameter){

    unsigned index = stoi(parameter);

    for(unsigned i = 0; i < currLvl.size(); i++){

        unsigned currIndex = 0;

        for(int j = 0; j < currLvl[i]->children.size(); j++){

            if(currLvl[i]->children[j]->name == subChild){

                if(currIndex == index){
                    nextLvl.push_back(currLvl[i]->children[j]);
                    break;
                }

                currIndex++;
            }

        }
    }
}

void xmlRequests::monkeyParameter(std::vector<xmlTree*> currLvl, std::string parameter, std::vector<std::string>& answer){

    parameter.erase(0, 1);

    for(int i = 0; i < currLvl.size(); i++){

        for(int j = 0; j < currLvl[i]->atributes.size(); j++){

            if(currLvl[i]->atributes[j].first == parameter){

                answer.push_back(currLvl[i]->atributes[j].second);
            }
        }
    }
}

bool xmlRequests::isEmpty(){
    return root->name.size() == 0;
}