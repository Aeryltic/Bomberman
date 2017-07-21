#ifndef LOGS_H
#define LOGS_H

#include <string>

class Logs {
public:
    virtual ~Logs();
    static void open(std::string format, ...);
    static void log(std::string format, ...);
    static void close(std::string format, ...);

    static void sopen(std::string text);
    static void slog(std::string text);
    static void sclose(std::string text);
protected:

private:
    Logs();
    unsigned indent;
    static Logs instance;
};

using logs = Logs;

#endif // LOGS_H