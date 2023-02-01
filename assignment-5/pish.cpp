
#include "hash.h"
#include "Scanner.h"
#include "Parse.h"
#include "assert.h"
#include <cstdlib>
#include <cmath>
#include <stdexcept>

#include <iostream>
using namespace std;

#define tabstop 4

class var
{
public:
    string key;

    // * * * add some more attributes and methods here * * * //
    int value;

    var(string name, int value) : key(name), value(value) {} // constructor
};

Set<var> memmap;

int stringToInt(string s)
{
    int num = 0;

    if (s[0] != '-')
        for (int i = 0; i < s.length(); i++)
            num = num * 10 + (int(s[i]) - 48);
    else
    {
        for (int i = 1; i < s.length(); i++)
            num = num * 10 + (int(s[i]) - 48);
        num = num * (-1);
    }

    return num;
}

int evalExpnTree(ExpnNode *root)
{
    if (root->tok == integer) // Leaf node
    {
        return stringToInt(root->text);
    }
    if (root->tok == ident) // Identifier
    {
        if (memmap.search(root->text) == NULL)
            throw runtime_error("Cannot find identifier");
        return (memmap.search(root->text))->value;
    }
    if (root->tok == mitok && root->left_operand == NULL) // "-" Unary
    {
        if (root->right_operand->tok == integer)
            return stringToInt(root->right_operand->text) * (-1);
        else
        {
            if (memmap.search(root->right_operand->text) == NULL)
                throw runtime_error("Cannot find identifier");
            return memmap.search(root->right_operand->text)->value * (-1);
        }
    }
    if (root->tok == nottok && root->left_operand == NULL) // not operator
    {
        if (root->right_operand->tok == integer)
            return !stringToInt(root->right_operand->text);
        else
            return !evalExpnTree(root->right_operand);
    }
    // Evaluate left subtree
    int leftSubTree = evalExpnTree(root->left_operand);

    // Evaluate right subtree
    int rightSubTree = evalExpnTree(root->right_operand);

    // Check which operator to apply
    if (root->tok == pltok) // "+"
        return leftSubTree + rightSubTree;
    if (root->tok == mitok) // "-"  Binary
        return leftSubTree - rightSubTree;
    if (root->tok == asttok) // "*"
    {
        if (leftSubTree == 0 || rightSubTree == 0)
            return 0;
        return leftSubTree * rightSubTree;
    }
    if (root->tok == slashtok) // "/"
    {
        if (rightSubTree == 0)
            throw runtime_error("Cannot divided by 0"); // Exception Handling
        if (leftSubTree == 0)
            return 0;
        if (leftSubTree % rightSubTree == 0)
            return leftSubTree / rightSubTree;
        int result = floor(leftSubTree / rightSubTree);
        return result > 0 ? result : result - 1;
    }
    if (root->tok == lttok) // "<"
        return leftSubTree < rightSubTree;
    if (root->tok == gttok) // ">"
        return leftSubTree > rightSubTree;
    if (root->tok == eqtok) // "=="
        return leftSubTree == rightSubTree;
    if (root->tok == netok) // "!="
        return leftSubTree != rightSubTree;
    if (root->tok == letok) // "<="
        return leftSubTree <= rightSubTree;
    if (root->tok == getok) // ">="
        return leftSubTree >= rightSubTree;
    if (root->tok == ortok) // OR
    {
        if (leftSubTree == 0 || rightSubTree == 0)
            return 0;
        return 1;
    }
    if (root->tok == andtok) // AND
    {
        if (leftSubTree == 0 || rightSubTree == 0)
            return 0;
        return leftSubTree && rightSubTree;
    }
    return 0;
}

// * * * declare more things here * * * //

int run(StmtsNode *stmts);

int run(StmtsNode *stmts)
{
    if (stmts == NULL)
        return 0;

    // Print token
    if (stmts->stmt->tok == printtok)
    {
        int statement = evalExpnTree(stmts->stmt->expn);
        cout << statement << endl;
    }
    // Assignment token
    else if (stmts->stmt->tok == asgntok)
    {
        string varName = stmts->stmt->ident;
        int value = evalExpnTree(stmts->stmt->expn);
        var *newVar = new var(varName, value);
        memmap.insert(newVar);
    }
    // If token
    else if (stmts->stmt->tok == iftok)
    {
        if (evalExpnTree(stmts->stmt->expn) != 0)
            run(stmts->stmt->stmts);
    }
    // While token
    else if (stmts->stmt->tok == whiletok)
    {
        while (evalExpnTree(stmts->stmt->expn))
            run(stmts->stmt->stmts);
    }

    return run(stmts->stmts);
}

int main()
{
    StmtsNode *pTree;

    try
    {
        pTree = Parse(cin);
    }
    catch (string s)
    {
        cout << "Parse error: " << s << endl;
        return 0;
    }
    cout << "Parse Successful!\n";
    run(pTree);
    // cout << print(pTree);
}
