#include <iostream>
#include <cctype>
#include <Stream.h>

using namespace stream;
using namespace stream::op;

int main(int argc, char* argv[])
{
  auto&& v = MakeStream::uniform_random_ints(65,122) | filter(isalpha) | limit(1e6) | to_vector();

  std::cout << 1 << std::endl;
  std::copy(v.begin(), v.end(), std::ostream_iterator<char>(std::cout, ""));
  std::copy(v.rbegin(), v.rend(), std::ostream_iterator<char>(std::cout, ""));
  std::cout << std::endl;

  return 0;
}
