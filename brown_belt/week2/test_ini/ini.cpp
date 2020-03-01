#include"ini.h"
#include<iostream>
#include<string>
#include<algorithm>

namespace Ini {


    Document Load(std::istream &input) {
        Document doc;
        std::string type;
        while (!input.eof()) {
            Section* section;
            while(type[0] != '[' && !input.eof())
                getline(input, type);
            if(type[0] == '[')
                section = &doc.AddSection(std::string(type.begin()+1, type.end()-1));
            std::string str;
            if(input.eof())
                break;
            while(!input.eof())
            {
                getline(input, str);
                if(str[0] == '[')
                {
                    type = str;
                    break;
                }
                auto it = find(str.begin(), str.end(), '=');
                if(it != str.end())
                {
                    section->insert(make_pair(std::string(str.begin(), it),
                                              std::string(it + 1, str.end())));
                }
                else
                    continue;
            }
        }
        return doc;
    }


    Section& Document::AddSection(std::string name) {
        return sections[move(name)];
    }

    const Section& Document::GetSection(const std::string &name) const {
            return sections.at(name);

    }


    size_t Document::SectionCount() const {
        return sections.size();
    }

}