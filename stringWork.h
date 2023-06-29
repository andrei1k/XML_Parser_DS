#ifndef STRINGWORK_H
#define STRINGWORK_H

#include <string>
#include <fstream>

class StringWork{

public:

    static void format(std::string& xml){

        StringWork::removeNewLines(xml);
        for(int i = 1; i < xml.size(); i++){
            if(xml[i] == '<' && xml[i - 1] != '\n'){
                xml.insert(i, 1, '\n');
                i++;
            }
            else if(xml[i] == '>' && i + 1 < xml.size() && xml[i + 1] != '\n'){
                xml.insert(i + 1, 1, '\n');
            }
        }
    }

    static void removeNewLines(std::string& xml){

        for(int i = 0; i < xml.size(); i++){
            if(xml[i] == '\n'){
                xml.erase(i, 1);
                i--;
            }
        }
    }

    static std::string readFile(std::istream& in){

        std::string xml = "";
        while(!in.eof()){
            char c;
            in.get(c);
            if(in.eof())
                break;

            xml.push_back(c);
        }
        return xml;
    }

    static std::string getTagName(std::string tag, bool openTag = true){
        
        tag.pop_back();
        std::stringstream stream(tag);
        stream.get();
        if(!openTag)
            stream.get();

        std::string name;
        stream >> name;

        return name;
    }

    static void emptyTagToOpenTag(std::string& tag){
        tag.erase(tag.size() - 2, 1);
    }

    static void removeWhiteSpaces(std::string& s){

        removeFrontWhiteSpaces(s);

        while(isWhiteSpace(s.back())){
            s.pop_back();
        }
    }

    static void removeFrontWhiteSpaces(std::string& s){

        while(isWhiteSpace(s[0])){
            s.erase(0, 1);
        }
    }

    static bool isWhiteSpace(char c){

        return (c == ' ' || c == '\n' || c == 9 || c == 13);
    }

    static void removeWSFromStream(std::stringstream& stream){

        while(!stream.eof() && isWhiteSpace(stream.peek())){
            stream.get();
        }
    }

    static void formatRequest(std::string& request){

        for(int i = 0; i < request.size(); i++){
            
            if(request[i] == '[' || request[i] == '/'){
                request.insert(i, 1, '\n');
                i++;
                if(request[i] == '/'){
                    request.erase(i, 1);
                }
           }
        }
    }
};


#endif // !STRINGWORK_H