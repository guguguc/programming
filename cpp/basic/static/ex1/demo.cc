#include <log4cplus/helpers/loglog.h>
#include <log4cplus/initializer.h>
#include <log4cplus/logger.h>

static log4cplus::Logger logger=log4cplus::Logger::getInstance("main");
void printMsgs()
{
}

int main()
{
    log4cplus::Initializer initializer;
    return 0;
}
