#ifndef STRINGINDEXER_H
#define STRINGINDEXER_H

#include <string>

class StringIndexer {
public:
    virtual ~StringIndexer();
    static unsigned get_id(const std::string& str);
    //static const std::string& get_

private:
    StringIndexer();
};

#endif // STRINGINDEXER_H
