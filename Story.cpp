#include "Story.h"
#include "goto.h"
#include "ifs.h"
#include "C:\Users\blain\source\repos\Project1_part1\Project1_part1\link.h"
#include "set.h"
#include "text.h"
#include "passage.h"
#include <iostream>
#include <istream>
#include <vector>
#include <fstream>
#include <string> 
#include <queue>
Story::Story(string file_name)
{
	string story, line;
	ifstream in(file_name);
	if (!in.is_open())
	{
		cout << "Couldn't open " << file_name << " for reading!\n";
	}

	getline(in, line);
	while (in && line != "</html>")
	{
		story += line + '\n';
		getline(in, line);
	}

	StoryTokenizer st(story);

	while (st.hasNextPassage())
	{
		PassageToken ptok = st.nextPassage();
		pas.emplace(ptok.getName(), passages.size());
		passages.push_back(ptok);
	}
}

/*void Story::print()
{
	for (int i = 0; i < passages.size(); i++)
	{

		PassageTokenizer ptok(passages[i].getText());
		cout << endl << "Passage " << passages[i].getName() << ":";
		while (ptok.hasNextPart())
		{
			PartToken stok(ptok.nextPart());

			if (stok.getType() == IF || stok.getType() == ELSEIF || stok.getType() == ELSE)
			{
				string copy = stok.getText();
				stok = ptok.nextPart();
				Ifs ifs(copy, stok.getText());
				cout << "If" << ":  var=" << ifs.getVar();
				if (ifs.getVal())
					cout << ", value=true";
				else
					cout << ", value=false";
				cout << endl << "START BLOCK";
				stok = ptok.nextPart();

				//if there are any elseif/else related to the previous if statement, that gets added to the queue as well
				while (stok.getType() == IF || stok.getType() == ELSE || stok.getType() == ELSEIF)
				{
					copy = stok.getText();
					stok = ptok.nextPart();
					Ifs extra(copy, stok.getText());
				}


				if (stok.getType() == SET)
				{
					Set st(stok.getText());
					st.command(this);
				}
				else if (stok.getType() == TEXT)
				{
					cout << endl << "Text:  \"" << ifs.getStatement() << "\"" << endl << "END BLOCK";
					Text tx(stok.getText());
					tx.command(this);
				}
				else if (stok.getType() == LINK)
				{
					Link* link = new Link(stok.getText());
					cout << "Link: display=" << link->getText() << ", target=" << link->getText();
				}
				else if (stok.getType() == GOTO)
				{
					Goto gt(stok.getText());
					gt.command(this);
				}


			}
			else if (stok.getType() == SET)
			{
				Set st(stok.getText());
				st.command(this);
			}
			else if (stok.getType() == TEXT)
			{
				Text tx(stok.getText());
				tx.command(this);
			}
			else if (stok.getType() == LINK)
			{
				Link* link = new Link(stok.getText());
				cout << "link: display=" << link->getText() << ", target=" << link->getText();
			}
			else if (stok.getType() == GOTO)
			{
				Goto gt(stok.getText());
				gt.command(this);
			}
		}
	}
}*/

void Story::run()
{
	int finished = 0; 


	while (finished == 0) 
	{

		hitLink = 0;
		hitGoto = 0;
		links.clear();

		queue<Ifs> ifBlocks;

		PassageTokenizer ptok(passages[pos].getText());


		while (ptok.hasNextPart())
		{


			PartToken stok(ptok.nextPart());

			if (stok.getType() == IF || stok.getType() == ELSEIF || stok.getType() == ELSE)
			{
				string copy = stok.getText();
				stok = ptok.nextPart();
				Ifs ifs(copy, stok.getText());
				ifBlocks.push(ifs);

				stok = ptok.nextPart();

				while (stok.getType() == ELSE || stok.getType() == ELSEIF)
				{
					copy = stok.getText();

					stok = ptok.nextPart();

					Ifs extra(copy, stok.getText());
					ifBlocks.push(extra);

				}


				while (!ifBlocks.empty())
				{
					ifBlocks.front().command(this);

					if (ifBlocks.front().getComplete() == 1)
					{
						while (!ifBlocks.empty())
							ifBlocks.pop();
					}
					else
					{
						ifBlocks.pop();
					}
				}


				if (stok.getType() == SET)
				{
					Set st(stok.getText());
					st.command(this);
				}
				else if (stok.getType() == TEXT)
				{
					Text tx(stok.getText());
					tx.command(this);
				}
				else if (stok.getType() == LINK)
				{
					Link* link = new Link(stok.getText());
					cout << link->getText();
					links.push_back(link);

					hitLink = 1;
				}
				else if (stok.getType() == GOTO)
				{
					Goto gt(stok.getText());
					gt.command(this);
					hitGoto = 1;
					break;
				}

				if (hitGoto == 1)
					break;


			}
			else if (stok.getType() == SET)
			{
				Set st(stok.getText());
				st.command(this);
			}
			else if (stok.getType() == TEXT)
			{
				Text tx(stok.getText());
				tx.command(this);
			}
			else if (stok.getType() == LINK)
			{
				Link* link = new Link(stok.getText());
				cout << link->getText();
				links.push_back(link);

				hitLink = 1;
			}
			else if (stok.getType() == GOTO)
			{
				Goto gt(stok.getText());
				gt.command(this);
				hitGoto = 1;
				break;
			}

			if (hitGoto == 1)
				break;
		}
		if ((hitLink == 0) && (hitGoto == 0))
			finished = 1;

		if (hitLink == 1)
		{
			int choicecount = 0;
			cout << "\n" << endl;

			for (int i = 0; i < links.size(); i++)
			{
				cout << i + 1 << ". " << links[i]->getText() << endl;
				choicecount++;
			}
			int choice;
			cout << "pick a choice: ";
			cin >> choice;

			while (!cin || choice < 1 || choice > choicecount)
			{
				cout << "Invalid Choice, Re-enter a number between 1 and " << choicecount << ": ";
				cin.clear();
				cin.ignore(10000, '\n');
				cin >> choice;
			}

			links[choice - 1]->command(this);

		}

	}
}

