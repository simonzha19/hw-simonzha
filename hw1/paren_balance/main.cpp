#include <iostream>
#include <string>

using namespace std;

// Implement below
bool are_paren_balanced(const string& expression);

// We have suggested a helper method, but feel free to write whatever you see fit
bool are_paren_balanced(const string& expression, size_t& i, char expected_closing);

// Do not change this method
int main(int argc, char* argv[]) {

    // Check if an expression has been passed to the program
    if (argc != 2) {
        cerr << "error: expected expression to check!" << endl;
        return -1;
    }

    // The second argument is the expression string in the format specified and
    // promised in the assignment page. You do not need to do any error checking
    // except for checking the parentheses.
    string expression(argv[1]);
    if (are_paren_balanced(expression)) {
        cout << "correct" << endl;
    } else {
        cout << "incorrect" << endl;
    }

    return 0;
}

// Some notes:
// - This method must be implemented recursively.
// - When debugging, make sure to output to cerr rather than cout. This will
//   prevent any leftover debug statements from confusing the automated
//   grading and will make sure output is guaranteed to be written to the
//   terminal in case your program crashes.
bool are_paren_balanced(const string& expression) {
    // TODO: your code here
    size_t index = 0;
    bool result = true;
    char expected_closing = expression.at(index);
    if(expression.at(index) == '('){
        expected_closing = ')';
    }
    if(expression.at(index) == '['){
        expected_closing = ']';
    }
    
    result = are_paren_balanced(expression, index, expected_closing);
    
    return result;
}

// Add any additional function implementations here.
//
// If you want to use the suggested helper method, you'll have to write its
// definition here.
bool are_paren_balanced(const string& expression, size_t& i, char expected_closing){
    if(i+1 >= expression.length()){
        cout << "expression length reached" << endl;
        if(expected_closing != ')' && expected_closing != ']'){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        
        i++;
        cout << expression.at(i) << endl;
        if(expression.at(i) == '('){
            return are_paren_balanced(expression, i, ')') && are_paren_balanced(expression, i, expected_closing);
            
        }
        else if(expression.at(i) == '['){
            if(are_paren_balanced(expression, i, ']')){
                return are_paren_balanced(expression, i, expected_closing);
            }
            else{
                return false;
            }
        }
        else if(expression.at(i) == ')' && expected_closing == ')'){
            return true;
        }
        else if(expression.at(i) == ']' && expected_closing == ']'){
            return true;
        }
        else if(expression.at(i) == ']' && expected_closing != ']'){
            return false;
        }
        else if(expression.at(i) == ')' && expected_closing != ')'){
            return false;
        }
        else{

            
            return are_paren_balanced(expression, i, expected_closing);
        }
            
            
        
    }
        
    
    
}