#ifndef XMLREQUESTS_H
#define XMLREQUESTS_H

#include <vector>
#include <string>
#include <sstream>

#include "xmlTree.h"
#include "stringWork.h"
#include "xPathValidator.h"
#include "creator.h"

class xmlRequests{

public:

    xmlRequests();
    xmlRequests(const std::string& path);
    ~xmlRequests();

    xmlRequests(const xmlRequests&) = delete;
    xmlRequests& operator=(const xmlRequests& copy) = delete;

    std::vector<std::string> completeRequest(std::string request);
    bool isEmpty();

private:

    xmlTree* root;

private:

    std::vector<xmlTree*> getNextLvl(std::vector<xmlTree*> currLvl, std::string& request, std::vector<std::string>& answer);
    void makeNextLvl(std::vector<xmlTree*> currLvl, std::vector<xmlTree*>& nextLvl, std::string childName);
    void parityParameter(std::vector<xmlTree*> currLvl, std::vector<xmlTree*>& nextLvl, std::string parameter);
    void numberParameter(std::vector<xmlTree*> currLvl, std::vector<xmlTree*>& nextLvl, std::string subChild, std::string parameter);
    void monkeyParameter(std::vector<xmlTree*> currLvl, std::string parameter, std::vector<std::string>& answer);

};

#endif // !XMLREQUESTS_H