#ifndef SET_H
#define SET_H

#include "passage.h"

class Set : public Passage
{
	private:
		string varname;
		bool value;
	public:
		Set(string str);
		string getVar();
		bool getVal();
		void command(Story* ins);

};
#endif // !SET_H
