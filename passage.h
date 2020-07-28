#ifndef PASSAGE_H
#define PASSAGE_H

#include <string>
#include "Story.h"

using namespace std;

class Passage
{
	private:
		string text;
	public: 
		Passage(string str) : text(str) {};
		string getText() { return text; };
		void command(Story* ins);
};
#endif
