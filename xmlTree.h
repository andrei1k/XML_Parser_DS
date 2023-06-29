#ifndef XMLTREE_H
#define XMLTREE_H

#include <iostream>
#include <string>
#include <vector>

struct xmlTree{
public:

    xmlTree() = default;
    xmlTree(const xmlTree&) = delete;
    xmlTree& operator=(const xmlTree&) = delete;

    ~xmlTree(){
        for(int i = 0; i < children.size(); i++){
            delete children[i];
        }
    }

public:

    std::string name{};
    std::vector<std::pair<std::string, std::string>> atributes{};
    std::vector<std::string> content{};
    std::vector<xmlTree*> children{};

};

#endif // !XMLTREE_H