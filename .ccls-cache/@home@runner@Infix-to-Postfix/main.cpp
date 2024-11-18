#include <iostream>
#include <stack>
#include <string>
#include <fstream>


class InfixToPostfixConverter {
private:
    std::string postfix;

    int getOperatorPrecedence(char op) {
        if (op == '+' || op == '-')
            return 1;
        else if (op == '*' || op == '/')
            return 2;
        return 0; 
    }

public:
    InfixToPostfixConverter() {
        postfix = "";
    }

    void convert(const std::string& infix) {
        std::stack<char> operators;
        postfix = "";

        for (char c : infix) {
            if (isalpha(c)) {
                postfix += c;
            } else if (c == '(') {
                operators.push(c);
            } else if (c == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.pop(); // Pop '('
            } else if (c == ' ') {
                continue;
            } else {
                while (!operators.empty() && getOperatorPrecedence(c) <= getOperatorPrecedence(operators.top())) {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(c);
            }
        }

        while (!operators.empty()) {
            postfix += operators.top();
            operators.pop();
        }
    }

    std::string getPostfix() {
        return postfix;
    }
};

int main() {
    InfixToPostfixConverter converter;

    std::ifstream inputFile("InfixData.txt"); 

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::string infix;

    while (std::getline(inputFile, infix)) {
        converter.convert(infix);

        std::cout << "Infix Expression: " << infix << std::endl;
        std::cout << "Postfix Expression: " << converter.getPostfix() << "\n\n";
    }

    inputFile.close();

    return 0;
}