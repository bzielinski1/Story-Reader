#include <string>
#include <iostream>
#include "C:\Users\blain\source\repos\Project1_part1\Project1_part1\Story.h"

using namespace std;

const string FILENAME = "party.html";

int main()
{
  Story* story = new Story(FILENAME);
  story->print();

  delete story;
  return 0;
}
