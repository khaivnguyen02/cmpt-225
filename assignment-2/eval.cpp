
#include "Scanner.h"
#include "Stack.h" // GENERIC STACK

#include <iostream>

using namespace std;

void performOperation(Stack<Token> &numstack, Stack<Token> &opstack)
{
    Token result;
    Token num2 = numstack.pop();
    Token num1 = numstack.pop();
    Token op = opstack.pop();
    result.tt = integer;
    if (op.tt == pltok)
        result.val = num1.val + num2.val;
    else if (op.tt == mitok)
        result.val = num1.val - num2.val;
    else if (op.tt == asttok)
        result.val = num1.val * num2.val;
    else
        result.val = num1.val / num2.val;
    numstack.push(result);
}
bool isValidOp(Stack<Token> &opstack)
{
    TokenType opType = opstack.peek().tt;
    if (opType == pltok || opType == mitok || opType == asttok || opType == slashtok)
        return true;
    else
        return false;
}
int main()
{
    Scanner S(cin);
    Token t;

    Stack<Token> numstack, opstack; // 2x Stacks of type Token

    t = S.getnext();

    while (t.tt != eof || opstack.isEmpty() == false)
    {
        if (t.tt == integer)
        {
            numstack.push(t);
            t = S.getnext();
        }
        else if (t.tt == lptok)
        {
            opstack.push(t);
            t = S.getnext();
        }
        else if (t.tt == rptok)
        {
            if (opstack.peek().tt == lptok)
            {
                Token ret = opstack.pop();
                t = S.getnext();
            }
            else
            {
                performOperation(numstack, opstack);
            }
        }
        else if (t.tt == pltok || t.tt == mitok || t.tt == eof)
        {
            if (!opstack.isEmpty() && isValidOp(opstack))
            {
                performOperation(numstack, opstack);
            }
            else
            {
                opstack.push(t);
                t = S.getnext();
            }
        }
        else if (t.tt == asttok || t.tt == slashtok)
        {
            if (!opstack.isEmpty() && (opstack.peek().tt == asttok || opstack.peek().tt == slashtok))
            {
                performOperation(numstack, opstack);
            }
            else
            {
                opstack.push(t);
                t = S.getnext();
            }
        }
    }
    Token result = numstack.peek();
    cout << "Result: " << result << endl;
    return 0;
}
