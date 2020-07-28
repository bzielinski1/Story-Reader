#pragma once
#ifndef __STORYTOKENIZER_H
#define __STORYTOKENIZER_H

#include <string>
using namespace std;


const string PASSAGE_START = "<tw-passagedata";
const string PASSAGE_START_TAG_CLOSE = ">";
const string PASSAGE_END = "</tw-passagedata>";
const string NAME_START = "name=\"";
const string NAME_END = "\"";
const string LINK_START = "[[";
const string LINK_SEPARATOR = "-&gt;";
const string LINK_END = "]]";
const string GOTO_START = "(go-to:";
const string SET_START = "(set:";
const string IF_START = "(if:";
const string ELSEIF_START = "(else-if:";
const string ELSE_START = "(else:";
const string COMMAND_END = ")";
const string BLOCK_START = "[";
const string BLOCK_END = "]";
const string GOTO_NAME_START = "&quot;";
const string GOTO_NAME_END = "&quot;";

class PassageToken {
private:
	string passage;
	string name;
public:
	string getName() const;
	string getText() const;

	PassageToken() {}
	PassageToken(const string pass) {
		passage = pass;
	}
	PassageToken(const string n, const string pass){
		name = n;
		passage = pass;
	}
};

class StoryTokenizer {
private:
	string story;
	int pos;
public:
	StoryTokenizer(){
		pos = 0;
	}
	StoryTokenizer(const string s){
		story = s;
		pos = 0;
	}
	bool hasNextPassage();
	PassageToken nextPassage();
};

enum section_t {LINK, GOTO, SET, IF, ELSEIF, ELSE, BLOCK, TEXT};

class PartToken
{
	private:
		string text;
		section_t type;
public:
	PartToken() : type(TEXT){}
	PartToken(string str, section_t t) : text(str), type(t) {}
	section_t getType() const;
	const string& getText() const;
};

class PassageTokenizer
{
private:
	string passage;
	int pos;
	section_t l_sect;
public:
	PassageTokenizer() : pos(0), l_sect(TEXT) {}
	PassageTokenizer(string str) : passage(str), pos(0), l_sect(TEXT) {}
	bool hasNextPart() const;
	PartToken nextPart();
};

#endif
