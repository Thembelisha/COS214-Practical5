#ifndef OLD1998SERVERACCESSHARDWARE_H
#define OLD1998SERVERACCESSHARDWARE_H

#include <string>
#include <vector>

class Old1998ServerAccessHardware
{
public:
    bool transmitRawString(const std::string& rawCommand);
    const std::vector<std::string>& getCommandLog() const;

private:
    std::vector<std::string> commandLog;
};

#endif
