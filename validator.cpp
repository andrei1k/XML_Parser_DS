#include "validator.h"

bool Validator::isOpenTag(std::string tag){

    if(tag.size() < 2){
        return false;
    }

    if(tag[0] != '<' || tag.back() != '>'){
        return false;
    }

    std::stringstream s(tag);
    s.get();

    std::string tagName;
    s >> tagName;

    if(s.eof()){
        tagName.pop_back();
    }

    if(!isName(tagName)){
        return false;
    }

    StringWork::removeWSFromStream(s);
    while(!s.eof() && s.peek() != '>'){

        if(!isAtribute(s)){
            return false;
        }
    }

    return isEndOfTag(s);

}

bool Validator::isName(const std::string& name){

    if(name.empty()){
        return false;
    }

    if(name[0] != '_' && (name[0] < 'a' || name[0] > 'z') && (name[0] < 'A' || name[0] > 'Z')){
        return false;
    }

    int pos = name.find("xml");
    if(pos == 0){
        return false;
    }

    return doesNotHaveSpecialCharacters(name);
}

bool Validator::isAtribute(std::stringstream& atributes){

    StringWork::removeWSFromStream(atributes);

    if(atributes.peek() == '>'){
        return true;
    }
    
    return isParity(atributes);

}

bool Validator::isParity(std::stringstream& atribute){

    std::string value;

    getline(atribute, value, '=');

    if(!isName(value)){
        return false;
    }

    char quote = atribute.get();

    if((quote != '\'' && quote != '\"')){
        return false;
    }

    getline(atribute, value, quote);

    return doesNotHaveSpecialCharacters(value);

}

bool Validator::isEndTag(const std::string& tag){

    if(tag.size() < 3){
        return false;
    }

    if(tag[0] != '<' || tag[1] != '/' || tag.back() != '>'){
        return false;
    }

    std::stringstream s(tag);
    s.get();
    s.get();

    std::string tagName;
    s >> tagName;
    tagName.pop_back();


    if(!isName(tagName)){
        return false;
    }

    return isEndOfTag(s);
}

bool Validator::isEndOfTag(std::stringstream& s){

    s.get();
    s.get();
    if(!s.eof()){
        return false;
    }

    return true;   
}

bool Validator::isEmptyTag(std::string tag){

    if(tag.size() < 3){
        return false;
    }

    char end = tag.back();
    tag.pop_back();

    if(tag.back() != '/'){
        return false;
    }
    tag.pop_back();

    tag.push_back(end);

    return isOpenTag(tag);
}

bool Validator::isContent(const std::string& content){

    return doesNotHaveSpecialCharactersExcludingQuotes(content);
}

bool Validator::isValidXml(std::string xml){

    StringWork::format(xml);
    std::stringstream stream(xml);
    Stack<std::string> openTags;

    if(xml[0] != '<' || xml.back() != '>'){
        throw std::invalid_argument("Invalid XML");
    } 

    do{
        std::string content;
        getline(stream, content);
        
        if(isEmptyTag(content) || isContent(content)){}
        else if(isOpenTag(content)){
                openTags.push(content);
        }
        else if(isEndTag(content)){

            if(openTags.empty()){
                std::string error = "Expected open tag for " + content + "!";
                throw std::invalid_argument(error);
                return false;
            }
           
            if(StringWork::getTagName(content, false) != StringWork::getTagName(openTags.top())){

                std::string error = "Expected end tag for " + openTags.top() + " before " + content + "!";
                throw std::invalid_argument(error);
                return false;
            }
            
            openTags.pop();
        }
        else{
            std::string error = content + " is invalid data!";
            throw std::invalid_argument(error);
            return false;
        }

    }while(!stream.eof());

    if(!openTags.empty()){
        std::string error = "Expected end tag for " + openTags.top() + "!";
            throw std::invalid_argument(error);
            return false;
    }

    return true;

}

bool Validator::doesNotHaveSpecialCharacters(const std::string& str){

    for(int i = 1; i < str.size(); i++){
        if(str[i] == '<' || str[i] == '>' || str[i] == '&' || str[i] == '\'' || str[i] == '\"' || StringWork::isWhiteSpace(str[i])){
            return false;
        }
    }

    return true;
}

bool Validator::doesNotHaveSpecialCharactersExcludingQuotes(const std::string& str){

    for(int i = 1; i < str.size(); i++){
        if(str[i] == '<' || str[i] == '>' || str[i] == '&'){
            return false;
        }
    }

    return true;
}