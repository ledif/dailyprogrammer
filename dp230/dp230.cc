// Implementation of challenge #230
// https://www.reddit.com/r/dailyprogrammer/comments/3j3pvm/20150831_challenge_230_easy_json_treasure_hunt/

#include <iostream>
#include <list>
#include <boost/algorithm/string/join.hpp>
#include "json.hpp"

using json = nlohmann::json;

template<typename J, typename Path>
bool find_child(J const& j, Path& path, std::string const& target);

template<typename J, typename Path, typename Pred, typename Keyer, typename Valuer>
bool for_each_child(J const& j, Path& path, std::string const& target, Pred&& pred, Keyer&& keyer, Valuer&& valuer)
{
  for (auto it = j.begin(); it != j.end(); ++it)
  {
    if (!pred(it)) {
      if (find_child(valuer(it), path, target)) {
        path.push_front(keyer(it));
        return true;
      }
    } else {
      path.push_front(keyer(it));
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
        [&](json::const_iterator it) {return it.key() == target;},
        [](json::const_iterator it) {return it.key();},
        [](json::const_iterator it) {return it.value();}
      );
      break;

    case json::value_t::array:
      for (auto it = j.begin(); it != j.end(); ++it)
      {
        if (*it != target) {
          if (find_child(*it, path, target)) {
            path.push_front(std::to_string(std::distance(j.begin(), it)));
            return true;
          }
        } else {
          path.push_front(std::to_string(std::distance(j.begin(), it)));
          return true;
        }
      }
      return false;
      break;

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
