#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_SIZE 100

int numStack[STACK_SIZE], numTop = -1;
char opStack[STACK_SIZE];
int opTop = -1;

void pushNum(int num) { numStack[++numTop] = num; }
void pushOp(char op) { opStack[++opTop] = op; }
int popNum() { return numStack[numTop--]; }
char popOp() { return opStack[opTop--]; }

int getPrecedence(char op) {
    return (op == '+' || op == '-') ? 1 : (op == '*' || op == '/') ? 2 : 0;
}

int calculate(int x, int y, char op) {
    switch (op) {
        case '+': return x + y;
        case '-': return x - y;
        case '*': return x * y;
        case '/': return x / y;
        default: return 0;
    }
}

void processOp() {
    int right = popNum();
    int left = popNum();
    char op = popOp();
    pushNum(calculate(left, right, op));
}

int computeExpression(const char* expr) {
    for (int i = 0; expr[i] != '\0'; i++) {
        if (isspace(expr[i])) continue;
        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) num = num * 10 + (expr[i++] - '0');
            pushNum(num);
            i--;
        } else if (expr[i] == '(') {
            pushOp(expr[i]);
        } else if (expr[i] == ')') {
            while (opTop >= 0 && opStack[opTop] != '(') processOp();
            popOp();
        } else {
            while (opTop >= 0 && getPrecedence(opStack[opTop]) >= getPrecedence(expr[i])) processOp();
            pushOp(expr[i]);
        }
    }
    while (opTop >= 0) processOp();
    return popNum();
}

int main() {
    char expr[STACK_SIZE];
    fgets(expr, STACK_SIZE, stdin);
    printf("%d\n", computeExpression(expr));
    return 0;
}
