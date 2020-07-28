#ifndef TEXT_H
#define TEXT_H

#include <string>
using namespace std;

#include "passage.h"

class Text : public Passage
{
	public:
		Text(string str) : Passage(str) {};
		void command(Story* ins);
};
#endif // !TEXT_H
