#include "storytokenizer.h"

string PassageToken::getName() const
{
	return name;
}

string PassageToken::getText() const
{
	return passage;
}

section_t PartToken::getType() const 
{
    return type;
}
const string& PartToken::getText() const 
{
    return text;
}

bool StoryTokenizer::hasNextPassage()
{
	return story.find(PASSAGE_START, pos) != string::npos;
}
PassageToken StoryTokenizer::nextPassage()
{
   int next_loc, start_loc, end_loc, name_start, name_end;

   next_loc = story.find(PASSAGE_START, pos);
   start_loc = story.find(PASSAGE_START_TAG_CLOSE, next_loc) + 1;
   end_loc = story.find(PASSAGE_END, start_loc);

  if (next_loc == string::npos || end_loc == string::npos)
    return PassageToken();
  else
  { 
    pos = end_loc;
    name_start = story.find(NAME_START, next_loc) + NAME_START.size();
    name_end = story.find(NAME_END, name_start);

   if (name_start == string::npos || name_end == string::npos)
     return PassageToken(story.substr(start_loc, end_loc - start_loc));
   else
     return PassageToken(story.substr(name_start, name_end - name_start), story.substr(start_loc, end_loc - start_loc));
  }
}

bool PassageTokenizer::hasNextPart() const
{
    return pos < passage.size();
}

PartToken PassageTokenizer::nextPart()
{
    int start_loc, end_loc;
    PartToken ret;

    if (pos >= passage.size())
    {
        l_sect = TEXT;
        return ret;
    }
    start_loc = passage.find(BLOCK_START, pos);
    if ((l_sect == IF || l_sect == ELSEIF || l_sect == ELSE) && start_loc != string::npos) // if to handle blocks
    {
        end_loc = ++start_loc;
        int level = 1;
        while (level > 0 && end_loc < passage.size()) // while loop to get correct end location
        {
            if (passage.substr(end_loc, BLOCK_START.size()) == BLOCK_START)
                level++;
            else if (passage.substr(end_loc, BLOCK_START.size()) == BLOCK_END)
                level--;
            end_loc++;
        }
        l_sect = BLOCK;

        ret = PartToken(passage.substr(start_loc, end_loc - start_loc), BLOCK); // set the retrivial object 
        pos = end_loc; // set new position 
        return ret;
    }
    else // handle rest of the tokens
    {
        int nextset = passage.find(SET_START, pos); // locations of the next potential tokens
        int nextgoto = passage.find(GOTO_START, pos);
        int nextlink = passage.find(LINK_START, pos);
        int nextif = passage.find(IF_START, pos);
        int nextelseif = passage.find(ELSEIF_START, pos);
        int nextelse = passage.find(ELSE_START, pos);
        unsigned int nexttok = 0;

        nexttok = nextset; 
        if (nextgoto < nexttok) //finds the next token
            nexttok = nextgoto;
        if (nextlink < nexttok)
            nexttok = nextlink;
        if (nextif < nexttok)
            nexttok = nextif;
        if (nextelseif < nexttok)
            nexttok = nextelseif;
        if (nextelse < nexttok)
            nexttok = nextelse;

        l_sect = TEXT; //default last section
        if (nexttok > pos) 
            end_loc = nexttok;
        else if (nexttok == nextlink) // handle link tokens
        {
            end_loc = passage.find(LINK_END, nextlink) + LINK_END.size();
            l_sect = LINK;
        }
        else if (nexttok != string::npos) // handle rest of the tokens
        {
            end_loc = passage.find(COMMAND_END, pos) + 1;
            if (nexttok == nextgoto)
                l_sect = GOTO;
            else if (nexttok == nextset)
                l_sect = SET;
            else if (nexttok == nextif)
                l_sect = IF;
            else if (nexttok == nextelseif)
                l_sect = ELSEIF;
            else if (nexttok == nextelse)
                l_sect = ELSE;
            else
                l_sect = TEXT;
        }

        ret = PartToken(passage.substr(pos, end_loc - pos), l_sect); // set the retivial object
        pos = end_loc; // reset the position
        return ret;
    }
}
