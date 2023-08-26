//
//  eval.cpp
//

#include <string>
#include <stack>
using namespace std;

 // function declarations
string convert(const string& expression);
char   solution(const string& postfixed);
string removeSpaces(const string& spaced);
bool   validExpression(string& formula);

 // return's postfix form and result which will hold 'true' or 'false'
int evaluate(string infix, string& postfix, bool& result) {
    if (!validExpression(infix))
        return 1;
    
    postfix = convert(infix);
    char answer = solution(postfix);
    if (answer == 'T')
        result = true;
    else
        result = false;
    
    return 0;
}

 // converts infix notation to postfix
string convert(const string& expression) {
    string translation = "";
    stack<char> chStack;
    char c;
    
    for (int i = 0; i < expression.size(); i++) {
      c = expression.at(i);
      switch (c) {
        case 'T':
        case 'F':
            translation += c;
            break;
        case '(':
            chStack.push(c);
            break;
        case ')':
            while (chStack.top() != '(') {
                translation += chStack.top();
                chStack.pop();
            }
            chStack.pop();
            break;
        case '!':
            while (!chStack.empty()  &&  chStack.top() != '('
                   &&  chStack.top() != '&'  &&  chStack.top() != '^'
                   &&  !translation.empty()) {
                translation += chStack.top();
                chStack.pop();
            }
            chStack.push(c);
            break;
        case '&':
            while (!chStack.empty()  &&  chStack.top() != '('  &&  chStack.top() != '^') {
                translation += chStack.top();
                chStack.pop();
            }
            chStack.push(c);
            break;
        case '^':
            while (!chStack.empty()  &&  chStack.top() != '(') {
                translation += chStack.top();
                chStack.pop();
            }
            chStack.push(c);
            break;
        default:
            break;
        }
    }
    while (!chStack.empty()) {
        translation += chStack.top();
        chStack.pop();
    }
    return translation;
}

 // solves postfix binary expression
char solution(const string& postfixed) {
    stack<char> operandStack;
    char ch, operand1, operand2;
    
    for (int i = 0; i < postfixed.size(); i++) {
      ch = postfixed[i];
      switch (ch) {
        case 'T':
        case 'F':
            operandStack.push(ch);
            break;
        case '^':
            operand2 = operandStack.top();
            operandStack.pop();
            operand1 = operandStack.top();
            operandStack.pop();
            if (operand1 != operand2)
                operandStack.push('T');
            else
                operandStack.push('F');
            break;
        case '&':
            operand2 = operandStack.top();
            operandStack.pop();
            operand1 = operandStack.top();
            operandStack.pop();
            if (operand1 == 'T'  &&  operand2 == 'T')
                operandStack.push('T');
            else
                operandStack.push('F');
            break;
        case '!':
            operand1 = operandStack.top();
            operandStack.pop();
            if (operand1 == 'F')
                operandStack.push('T');
            else
                operandStack.push('F');
            break;
        }
    }
    return operandStack.top();
}

 // remove spaces from a string since spaces are valid
string removeSpaces(const string& spaced) {
   string spliced;
   for (int i = 0; i < spaced.size(); i++)
       if (spaced[i] != ' ')
           spliced += spaced[i];
   
   return spliced;
}

 // checks if binary expression is syntactically valid
bool validExpression(string& formula) {
    if (formula.empty()  ||  formula[0] == '&'  ||  formula[0] == '^'  ||  formula[0] == ')')
        return false;
    
    formula = removeSpaces(formula);
    stack<char> parenStack;
    const long size = formula.size();
    char curr = formula[0];
    int next;
    int numOps = 0;
    
    for (int i = 0; i < size; i++) {
      curr = formula[i];
      next = i + 1;
        if (next == size) break;
    
      switch (curr) {
        case 'T':
        case 'F':
            if (formula[next] == 'T'  ||  formula[next] == 'F'  ||  formula[next] == '(')
                return false;
            numOps++;
            break;
        case '!':
            if (formula[next] == '&'  ||  formula[next] == '^'  ||  formula[next] == ')')
                return false;
            break;
        case '&':
        case '^':
            if (formula[next] == '&'  ||  formula[next] == '^'  ||  formula[next] == ')')
                return false;
            break;
        case '(':
            if (formula[next] == '&'  ||  formula[next] == '^')
                return false;
            parenStack.push(curr);
            break;
        case ')':
            if (parenStack.empty()  ||  formula[next] == 'T'  ||  formula[next] == 'F'  ||  formula[next] == '!')
                return false;
            parenStack.pop();
            break;
        case ' ':
            break;
              
        default:
            return false;
        }
    }
    
    if (curr == ')') {
        if (parenStack.empty()  ||  numOps == 0)
            return false;
        parenStack.pop();
        if (parenStack.empty())
            return true;
        else
            return false;
    }
    
    if (curr == 'T'  ||  curr == 'F')
        return true;
    else
        return false;
}
