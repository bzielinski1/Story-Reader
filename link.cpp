#include "link.h"

#include <string>

Link::Link(string str):Passage(str)
{
	int pos = str.find("-&gt");
    if (pos == -1)
    {
        dispText = str.substr(2, str.size() - 4);
        lpassage = dispText;
    }
    else
    {
        dispText = str.substr(2, str.size() - pos + 1);
        lpassage = str.substr(pos + 5, str.size() - pos - 7);
    }
}


void Link::command(Story* ins)
{

    ins->setPos(ins->pas[lpassage]);
}

string Link::getPassage()
{
    return lpassage;;
}

string Link::getText()
{
    return dispText;
}
