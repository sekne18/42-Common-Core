#include "MutantStack.hpp"

void testBasicStackOperations() {
    std::cout << "Test 1: Basic stack operations\n";

    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);

    // Check top element
    std::cout << "Top element: " << mstack.top() << std::endl;  // Expected: 17

    mstack.pop();
    std::cout << "Size after pop: " << mstack.size() << std::endl;  // Expected: 1

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    // Check size
    std::cout << "Size after pushing 4 elements: " << mstack.size() << std::endl;  // Expected: 5
}

void testIterator() {
    std::cout << "Test 2: Iterator functionality\n";

    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    // Iterator to traverse and print all elements
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    std::cout << "Iterating forward over the stack: \n";
    while (it != ite) {
        std::cout << *it << std::endl;
        ++it;
    }
}

void testReverseIterator() {
    std::cout << "Test 3: Reverse iterator functionality\n";

    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    // Reverse iterator to traverse and print all elements
    MutantStack<int>::reverse_iterator rit = mstack.rbegin();
    MutantStack<int>::reverse_iterator rite = mstack.rend();

    std::cout << "Iterating backward over the stack: \n";
    while (rit != rite) {
        std::cout << *rit << std::endl;
        ++rit;
    }
}

void testCopyToStdStack() {
    std::cout << "Test 4: Copy MutantStack to std::stack\n";

    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    std::stack<int> s(mstack);  // Copying MutantStack to std::stack

    // Print the std::stack (only top element is accessible)
    std::cout << "Top element of std::stack: " << s.top() << std::endl;  // Expected: 0
    s.pop();
    std::cout << "Top element of std::stack after pop: " << s.top() << std::endl;  // Expected: 737
}

void testFullFunctionality() {
    std::cout << "Test 5: Full functionality\n";

    MutantStack<int> mstack;

    mstack.push(10);
    mstack.push(20);
    mstack.push(30);
    mstack.push(40);
    mstack.push(50);

    // Check top element
    std::cout << "Top element: " << mstack.top() << std::endl;  // Expected: 50

    // Iterate over stack (forward)
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    std::cout << "Forward iteration:\n";
    while (it != ite) {
        std::cout << *it << std::endl;
        ++it;
    }

    // Iterate over stack (reverse)
    MutantStack<int>::reverse_iterator rit = mstack.rbegin();
    MutantStack<int>::reverse_iterator rite = mstack.rend();
    std::cout << "Reverse iteration:\n";
    while (rit != rite) {
        std::cout << *rit << std::endl;
        ++rit;
    }

    // Pop and check top again
    mstack.pop();
    std::cout << "Top element after pop: " << mstack.top() << std::endl;  // Expected: 40
}

int main()
{
  testBasicStackOperations();
  testIterator();
  testReverseIterator();
  testCopyToStdStack();
  testFullFunctionality();
  return (0);
}
