#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "stack.h"
#include "stringWork.h"

class Validator{
public:

    // valid xml
    static bool isValidXml(std::string xml);

    // tags
    static bool isOpenTag(std::string tag);
    static bool isEndTag(const std::string& tag);
    static bool isEmptyTag(std::string tag);
    static bool isName(const std::string& name);
    static bool isParity(std::stringstream& atribute);

    
    // content
    static bool isContent(const std::string& content);

private:

    // help for tags
    static bool isAtribute(std::stringstream& atributes);
    static bool isEndOfTag(std::stringstream& s);
        
    // helper
    static bool doesNotHaveSpecialCharacters(const std::string& str);
    static bool doesNotHaveSpecialCharactersExcludingQuotes(const std::string& str);

};

#endif // VALIDATOR_H