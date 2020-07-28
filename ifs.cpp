#include <string>
#include <queue>

#include "goto.h"
#include "ifs.h"
#include "link.h"
#include "set.h"
#include "text.h"

Ifs::Ifs(string str, string str1)
    :Passage(str)
{

    if (str.find("if:") != -1)
        ifType = IFE;
    else if (str.find("else-if:") != -1)
        ifType = ELSE_IFE;
    else
        ifType = ELSEE;

    if (ifType == IFE || ifType == ELSE_IFE)
    {
        for (int i = str.find("$") + 1; str[i] != ' '; i++)
            varname += str[i];
        string place;

        if (str[str.find("is ") + 3] == 't')
            value = true;
        else
            value = false;

    }
    else
    {
        varname = "";
        value = false;
    }

    statement = str1.substr(1, str1.size() - 2);

}

void Ifs::command(Story* ins)
{

    if (((ifType == IFE || ifType == ELSE_IFE) && ins->vars[varname] == value) || ifType == ELSEE)
    {
        queue<Ifs> ifBlocks;

        complete = 1;
        PassageTokenizer ptok(statement);

        while (ptok.hasNextPart())
        {
            PartToken stok = ptok.nextPart();
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
                    ifBlocks.front().command(ins);

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
                    st.command(ins);
                }
                else if (stok.getType() == TEXT)
                {
                    Text tx(stok.getText());
                    tx.command(ins);
                }
                else if (stok.getType() == LINK)
                {
                    Link* link = new Link(stok.getText());
                    cout << link->getText();
                    ins->links.push_back(link);

                    ins->hitLink = 1;
                }
                else if (stok.getType() == GOTO)
                {
                    Goto gt(stok.getText());
                    gt.command(ins);
                    ins->hitGoto = 1;
                    break;
                }

                if (ins->hitGoto == 1)
                    break;

            }
            else if (stok.getType() == SET)
            {
                Set st(stok.getText());
                st.command(ins);
            }
            else if (stok.getType() == TEXT)
            {
                Text tx(stok.getText());
                tx.command(ins);
            }
            else if (stok.getType() == LINK)
            {
                Link* link = new Link(stok.getText());
                cout << link->getText();
                ins->links.push_back(link);

                ins->hitLink = 1;

            }
            else if (stok.getType() == GOTO)
            {
                Goto gt(stok.getText());
                gt.command(ins);
                ins->hitGoto = 1;
                break;
            }
        }
    }
}

string Ifs::getVar()
{
    return varname;
}

string Ifs::getStatement()
{
    return statement;
}

bool Ifs::getVal()
{
    return value;
}

IF_TYPE Ifs::getType()
{
    return ifType;
}