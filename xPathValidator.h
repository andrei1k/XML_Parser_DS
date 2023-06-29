#ifndef XPATHVALIDATOR_H
#define XPATHVALIDATOR_H

#include <string>
#include <sstream>

#include "validator.h"

class xPathValidator{
public:

    static bool isValid(const std::string& xPath){

        std::stringstream stream(xPath);
        std::string child;

        bool isMonkey = false;

        while(!stream.eof()){

            if(isMonkey){
                return false;
            }

            getline(stream, child, '/');
            if(!isChild(child, isMonkey)){
                return false;
            }
        }

        return true;
    }

    static bool isChild(const std::string& child, bool& isMonkey){

        std::stringstream stream(child);
        std::string component;
        getline(stream, component, '[');
        if(!Validator::isName(component)){
            return false;
        }

        if(!stream.eof()){

            if(child.back() != ']'){
                return false;
            }

            getline(stream, component, ']');
            if(!isArgument(component)){
                return false;
            }

            if(isMonkeyA(component))
                isMonkey = true;
        }

        stream.get();
        return stream.eof();
    }

    static bool isArgument(const std::string& argument){

        if(argument.empty()){
            return false;
        }

        return isNumber(argument) || isParity(argument) || isMonkeyA(argument);
    }

    static bool isNumber(const std::string& argument){

        for(int i = 0; i < argument.size(); i++){
            
            if(argument[i] < '0' || argument[i] > '9')
                return false;
        }

        return true;
    }

    static bool isParity(const std::string& argument){

        if(argument.find("=") == std::string::npos){
            return false;
        }

        std::stringstream stream(argument);

        return Validator::isParity(stream);

    }

    static bool isMonkeyA(std::string argument){

        if(argument[0] != '@')
            return false;

        argument.erase(0, 1);

        return Validator::isName(argument);
    }

};

#endif // !XPATHVALIDATOR_H