#include <iostream>
#include <Stream.h>

using namespace stream;
using namespace stream::op;

int main(int argc, char* argv[])
{
  auto&& str = MakeStream::from(
      std::istream_iterator<char>(std::cin), std::istream_iterator<char>()
    )
   | drop_while([](char c){ return std::isdigit(c); })
   | filter([](char c){ return std::isalpha(c); })
   | map_([](char c) -> char { return std::tolower(c); })
   | to_vector();

  std::size_t mid = str.size() / 2;

  const bool is_palindrome = std::equal(str.cbegin(), str.cbegin() + mid, str.crbegin());

  std::cout << (is_palindrome ? "Palindrome" : "Not a palindrome") << std::endl;

  return 0;
}
