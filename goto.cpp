#include "goto.h"

Goto::Goto(string str):Passage(str)
{
	int pos = str.find("&quot;");
	for (int i = pos + 6; str[i] != '&'; i++)
	{
		gpassage += str[i];
	}
}

string Goto::getPassage()
{
	return gpassage;
}

void Goto::command(Story* ins)
{
	ins->setPos(ins->pas[gpassage]);
}