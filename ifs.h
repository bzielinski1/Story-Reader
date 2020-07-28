#ifndef IFS_H
#define IFS_H

#include "passage.h"

enum IF_TYPE { IFE, ELSE_IFE, ELSEE };

class Ifs : public Passage
{
private:
    IF_TYPE ifType;
    string varname;
    bool value;
    string statement;
    int complete = 0;

public:
    Ifs(string str, string str1);
    string getVar();
    string getStatement();
    bool getVal();
    IF_TYPE getType();
    void command(Story* ins);
    int getComplete() { return complete; };

};


#endif