#ifndef LINK_H
#define LINK_H

#include "passage.h"

class Story;
class Link : public Passage
{
private:
	string dispText;
	string lpassage;
public:
	Link(string str);
	string getPassage();
	string getText();
	void command(Story* ins);

};
#endif // !LINK_H