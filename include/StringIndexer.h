#ifndef STRINGINDEXER_H
#define STRINGINDEXER_H

#include <string>

class StringIndexer {
public:
    virtual ~StringIndexer();
    static unsigned get_id(std::string& str);

private:
    StringIndexer();
};

#endif // STRINGINDEXER_H
