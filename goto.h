#ifndef GOTO_H
#define GOTO_H

#include "passage.h"

class Goto : public Passage
{
	private:
		string gpassage;
	public:
		Goto(string str);
		string getPassage();
		void command(Story* ins);
};
#endif // !GOTO_H
