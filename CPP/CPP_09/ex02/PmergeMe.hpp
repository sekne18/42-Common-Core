#ifndef MERGEME_HPP
#define MERGEME_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <string>
#include <sstream>

class PmergeMe
{
private:
    std::vector<int> _vec;
    std::list<int> _list;

public:
    PmergeMe(int argc, char **argv);
    PmergeMe(const PmergeMe &src);
    ~PmergeMe();
    PmergeMe &operator=(const PmergeMe &rhs);

    void sortVector();
    void sortList();
    void printVector() const;
    void printList() const;
};

#endif // MERGEME_HPP
