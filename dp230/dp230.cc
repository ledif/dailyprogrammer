#include <iostream>
#include <list>
#include <boost/algorithm/string/join.hpp>
#include "json.hpp"

using json = nlohmann::json;

template<typename J, typename Path>
bool recurse(J const& j, Path& path, std::string const& target)
{
  // std::cout << j.dump() << std::endl;
  switch (j.type())
  {
    case json::value_t::object:
      for (auto it = j.begin(); it != j.end(); ++it)
        {
            // std::cout << "obj: " << it.key() << std::endl;
            if (it.key() != target) {
              if (recurse(*it, path, target))
              {
                path.push_front(it.key());
                return true;
              }

            }
            else{
              path.push_front(it.key());

              return true;

            }
        }
        return false;

      break;

      case json::value_t::array:
        for (std::size_t i = 0; i < j.size(); ++i)
        {
          // std::cout << "array: " << *it << std::endl;

            if (j[i] != target) {
              if (recurse(j[i], path, target))
              {
                path.push_front(std::to_string(i));
                return true;
              }
            }
            else {
              path.push_front(std::to_string(i));
              return true;
            }
        }
        return false;


      default:
        return false;

    }
}

int main(int argc, char* argv[])
{
  json j;
  std::cin >> j;

  std::list<std::string> path;

  recurse(j, path, "dailyprogrammer");

  std::cout << boost::algorithm::join(path, " -> ") << std::endl;

  // recurse(j.get<json::object_t>()) << std::endl;

  return 0;
}
