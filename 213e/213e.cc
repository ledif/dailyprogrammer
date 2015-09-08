#include <iostream>
#include <algorithm>
#include <Stream.h>

using namespace stream;
using namespace stream::op;

template<typename T>
void print(T&& t)
{
  MakeStream::from(t) | map_([](bool x) { return x ? 'x' : ' '; }) | print_to(std::cout, "");
  std::cout << std::endl;
}

int main(int argc, char* argv[])
{
  auto v = MakeStream::from(std::istream_iterator<char>(std::cin), std::istream_iterator<char>())
    | map_([](char x) { return x == '1'; })
    | to_vector();

  print(v);

  for (int i = 0; i < 25 && std::any_of(v.begin(), v.end(), [](bool x){return x; }); ++i)
  {
    MakeStream::singleton(false) | concat(MakeStream::from(v)) | concat(MakeStream::singleton(false))
      | overlap<3>()
      | map_([](auto&& t) -> bool { return std::get<0>(t) ^ std::get<2>(t); })
      | copy_to(v.begin());

    print(v);
  }

  return 0;
}
