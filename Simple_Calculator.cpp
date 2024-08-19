#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip> // For std::setprecision

using namespace std;

// Function to evaluate a simple expression
double evaluateExpression(const string& expression) {
    stack<double> values;
    stack<char> operators;

    auto applyOperator = [&]() {
        double right = values.top(); values.pop();
        double left = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        switch (op) {
            case '+': values.push(left + right); break;
            case '-': values.push(left - right); break;
            case '*': values.push(left * right); break;
            case '/': values.push(left / right); break;
        }
    };

    istringstream iss(expression);
    string token;
    while (iss >> token) {
        if (isdigit(token[0])) {
            values.push(stod(token));
        } else if (token == "+" || token == "-" || token == "*" || token == "/") {
            while (!operators.empty() && 
                   ((operators.top() == '*' || operators.top() == '/') || 
                    (token == "+" || token == "-"))) {
                applyOperator();
            }
            operators.push(token[0]);
        }
    }

    while (!operators.empty()) {
        applyOperator();
    }

    return values.top();
}

class Calculator {
private:
    vector<string> history;

public:
    // Function to add a new entry to history
    void addHistory(const string& entry) {
        history.push_back(entry);
    }

    // Function to display the history
    void displayHistory() const {
        cout << "Calculation History:" << endl;
        for (size_t i = 0; i < history.size(); ++i) {
            cout << (i + 1) << ": " << history[i] << endl;
        }
    }

    // Function to perform a calculation
    void calculate(const string& expression) {
        double result = evaluateExpression(expression);
        cout << fixed << setprecision(2) << "Result: " << result << endl;
        addHistory(expression + " = " + to_string(result));
    }

    // Function to run the calculator application
    void run() {
        string command;
        while (true) {
            cout << "\nCommands:\n"
                 << "1. Calculate Expression (format: '<expression>')\n"
                 << "2. Show History (format: 'history')\n"
                 << "3. Exit (format: 'exit')\n"
                 << "Enter command: ";

            getline(cin, command);

            if (command == "history") {
                displayHistory();
            } else if (command == "exit") {
                break;
            } else {
                calculate(command);
            }
        }
    }
};

int main() {
    Calculator calc;
    calc.run();
    return 0;
}
