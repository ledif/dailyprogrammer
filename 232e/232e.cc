#include <iostream>
#include <cctype>
#include <Stream.h>

using namespace stream;
using namespace stream::op;

int main(int argc, char* argv[])
{
  auto&& str = MakeStream::from(std::istream_iterator<char>(std::cin), std::istream_iterator<char>())
   | drop_while(isdigit)
   | filter(isalpha)
   | map_(tolower)
   | to_vector();

  const std::size_t mid = str.size() / 2;

  const bool is_palindrome = std::equal(str.cbegin(), str.cbegin() + mid, str.crbegin());

  std::cout << (is_palindrome ? "Palindrome" : "Not a palindrome") << std::endl;

  return 0;
}
