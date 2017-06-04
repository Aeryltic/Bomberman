#ifndef TYPEINDEXER_H
#define TYPEINDEXER_H


class TypeIndexer {
public:
    virtual ~TypeIndexer();
    template<typename T>
    unsigned id() {
        static unsigned _id = next_id++;
        return _id;
    }

private:
    TypeIndexer();

    static unsigned next_id;
};

#endif // TYPEINDEXER_H
