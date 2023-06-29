#ifndef CREATOR_H
#define CREATOR_H

#include "xmlTree.h"
#include "validator.h"

class Creator{
public:

    static xmlTree* createXmlTree(const std::string& path);
    static xmlTree* createXmlTree(std::stringstream& stream);

    static void openTagParse(std::string tag, std::string& name, std::vector<std::pair<std::string, std::string>>& atributes);
    static void atributeParse(std::stringstream& stream, std::vector<std::pair<std::string, std::string>>& atributes);

};

#endif // !CREATOR_H