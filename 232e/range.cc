#include <cstdio>
#include <iostream>
#include <cctype>
#include "range/v3/all.hpp"

using namespace ranges;

int main()
{
    std::string str =
        make_range(std::istream_iterator<char>(std::cin), std::istream_iterator<char>())
        | view::drop_while(isdigit)
        | view::remove_if([](char c){return !isalpha(c);})
        | view::transform(tolower);

    const size_t mid = str.size() / 2;

    const bool is_palindrome = std::equal(str.cbegin(), str.cbegin() + mid, str.crbegin());

    printf(is_palindrome ? "Palindrome\n" : "Not a palindrome\n");

}
