#include <iostream>
#include <vector>
#include <algorithm>

class line : public std::string {};

std::istream& operator>>(std::istream& is, line& l)
{
    std::getline(is, l);
    return is;
}

int main(int argc, char* argv[])
{
  std::for_each(
    std::istream_iterator<line>(std::cin),
    std::istream_iterator<line>(),
    [](auto&& str) {
      bool forward = std::is_sorted(str.begin(), str.end(), std::less<char>());
      bool backward = std::is_sorted(str.begin(), str.end(), std::greater<char>());

      const std::string result = forward ? "IN ORDER" : backward ? "REVERSE ORDER" : "NOT IN ORDER";

      std::cout << str << " " << result << std::endl;
  });

  return 0;
}
