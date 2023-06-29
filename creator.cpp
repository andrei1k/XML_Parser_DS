#include "creator.h"

xmlTree* Creator::createXmlTree(const std::string& path){

    std::string xml;

    try{
        std::ifstream in(path);
        if(!in.is_open()){
            std::string error = path + " is invalid file name!";
            throw std::invalid_argument(error);
        }

        xml = StringWork::readFile(in);
        StringWork::removeWhiteSpaces(xml);
        Validator::isValidXml(xml);
    }
    catch(const std::invalid_argument& error){
        std::cout << error.what() << std::endl;
        // return nullptr;
        return new xmlTree{};
    }

    StringWork::format(xml);
    std::stringstream stream(xml);

    return createXmlTree(stream);

}

xmlTree* Creator::createXmlTree(std::stringstream& stream){

    // end of file
    if(stream.eof()){
        return nullptr;
    }

    std::string lineOfXml;
    getline(stream, lineOfXml);

    // end tag
    if(Validator::isEndTag(lineOfXml)){
        return nullptr;
    }

    xmlTree* node = new xmlTree();

    // empty tag
    if(Validator::isEmptyTag(lineOfXml)){

        StringWork::emptyTagToOpenTag(lineOfXml);

        openTagParse(lineOfXml, node->name, node->atributes);

        return node;
    }

    // creating node
    openTagParse(lineOfXml, node->name, node->atributes);

    // children and recurtion
    do{
        if(stream.peek() != '<'){
            getline(stream, lineOfXml);
            StringWork::removeWhiteSpaces(lineOfXml);
            if(lineOfXml != ""){
    	        node->content.push_back(lineOfXml);
            }
            continue;
        }

        xmlTree* child = createXmlTree(stream);

        if(child == nullptr){
            break;
        }

        node->children.push_back(child);

    }while(!stream.eof());

    return node;

}

void Creator::openTagParse(std::string tag, std::string& name, std::vector<std::pair<std::string, std::string>>& atributes){

    std::stringstream s(tag);
    s.get();

    std::string tagName;
    s >> tagName;
    s.get();

    if(s.eof()){
        tagName.pop_back();
    }

    name = tagName;

    while(!s.eof()){

        atributeParse(s, atributes);

        if(s.peek() == '>'){
            s.get();
            break;
        }
    }
}

void Creator::atributeParse(std::stringstream& stream, std::vector<std::pair<std::string, std::string>>& atributes){

    StringWork::removeWSFromStream(stream);

    if(stream.peek() == '>'){
        return;
    }

    std::pair<std::string, std::string> atribute;
    std::string value;

    getline(stream, value, '=');
    atribute.first = value;

    char quote = stream.get();

    getline(stream, value, quote);

    atribute.second = value;

    atributes.push_back(atribute);
}