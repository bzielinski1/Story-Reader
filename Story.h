#ifndef STORY_H
#define STORY_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "storytokenizer.h"


using namespace std;
class Link;
class Story
{
	private:
		int pos = 0;
	public:
		unordered_map<string, int> pas;
		unordered_map<string, bool> vars;
		vector<PassageToken> passages;
		vector<Link*> links;
		int hitLink = 0;
		int hitGoto = 0;
		Story(string);
		//void print();
		void run();
		int getPos() { return pos; };
		void setPos(int x) { pos = x; };
};

#endif