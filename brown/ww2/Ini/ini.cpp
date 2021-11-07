#include "ini.h"

namespace Ini {
    Section & Document::AddSection(string name) {
        if (sections.count(name))
            return sections[name];
        sections[name] = Section();
        return sections[name];
    }

    const Section & Document::GetSection(const string &name) const {
        return sections.at(name);
    }

    size_t Document::SectionCount() const {
        return sections.size();
    }

    Document Load(istream &input) {
        input >> std::ws;
        char c;
        std::string trash;
        Document doc;
        while (c != EOF) {
            std::string current_section;
            input.get(c);
            if (c == '[') {
                getline(input, current_section, ']');
                getline(input, trash);
                auto& section = doc.AddSection(current_section);
                input >> std::ws;
                c = input.peek();
                while (c != '[' && c != EOF) {
                    std::string current_key;
                    getline(input, current_key, '=');
                    std::string current_value;
                    getline(input, current_value);
                    input >> std::ws;
                    section[current_key] = current_value;
                    c = input.peek();
                }
            }
        }
        return doc;
    }
}