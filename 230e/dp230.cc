// Implementation of challenge #230
// https://www.reddit.com/r/dailyprogrammer/comments/3j3pvm/20150831_challenge_230_easy_json_treasure_hunt/

#include <iostream>
#include <list>
#include <boost/algorithm/string/join.hpp>
#include "json.hpp"

using json = nlohmann::json;

template<typename J, typename Path>
bool find_child(J const& j, Path& path, std::string const& target);

template<typename J, typename Path, typename Pred, typename Pather, typename Valuer>
bool for_each_child(J const& j, Path& path, std::string const& target, Pred&& pred, Pather&& pather, Valuer&& valuer)
{
  for (auto it = j.begin(); it != j.end(); ++it)
  {
    if (pred(it) || find_child(valuer(it), path, target))
    {
      path.push_front(pather(it));
      return true;
    }
  }
  return false;
}

template<typename J, typename Path>
bool find_child(J const& j, Path& path, std::string const& target)
{
  switch (j.type())
  {
    case json::value_t::object:
      return for_each_child(j, path, target,
        [&](json::const_iterator it) { return it.key() == target; },
        [](json::const_iterator it) { return it.key(); },
        [](json::const_iterator it) { return it.value(); }
      );

    case json::value_t::array:
      return for_each_child(j, path, target,
        [&](json::const_iterator it) { return *it == target; },
        [&](json::const_iterator it) { return std::to_string(std::distance(j.begin(), it)); },
        [](json::const_iterator it) { return *it; }
      );

    default:
      return false;
  }
}

int main(int argc, char* argv[])
{
  json j; std::cin >> j;

  std::list<std::string> path;
  find_child(j, path, "dailyprogrammer");
  std::cout << boost::algorithm::join(path, " -> ") << std::endl;

  return 0;
}
