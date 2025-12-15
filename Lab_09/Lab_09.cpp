#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <queue>

int priority(std::string elem) {
    if (elem == "+" || elem == "-")
        return 0;
    else if(elem == "*" || elem == "/")
        return 1;
    return 2;
}

int main()
{
    std::stack <std::string> st;
    std::vector <std::string> elements;
    std::string expr;
    std::string last;
    std::queue <std::string> q;

    std::getline(std::cin, expr);
    bool un_minus = true;
    for (auto ch : expr) {  
        if (un_minus && ch == '-')
        {
            elements.push_back("0");
        }
        if (ch == ' ')
        {
            if (last.size() > 0) {
                elements.push_back(last);
                last = "";
            }
        }
        else if (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '(' || ch == ')') {
            if (last.size() > 0){
                elements.push_back(last);
                last = "";
            }
            last += ch;
            elements.push_back(last);
            last = "";
        }
        else {
            last += ch;
        }
        if (ch == '(')
            un_minus = true;
        else
            un_minus = false;

    }
    if (last.size() > 0) {
        elements.push_back(last);
        last = "";
    }
    
   for (auto elem : elements) {
        if (elem == "+" || elem == "-" || elem == "/" || elem == "*") {
            if (st.empty() || st.top() == "(" || priority(st.top()) < priority(elem)) {
                st.push(elem);
            }
            else {
                while (!st.empty() && st.top() != "(" && priority(st.top()) >= priority(elem)) {
                    q.push(st.top());
                    st.pop();
                }
                st.push(elem);
            }
        }
        else if (elem == "(") {
            st.push(elem);
        }
        else if (elem == ")") {
            while (st.top() != "(") {
                q.push(st.top());
                st.pop();
            }
            st.pop();
        }
        else {
            st.push(elem);
        }
    }
    while (!st.empty()) {
       q.push(st.top());
       st.pop();
   }

    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
}

