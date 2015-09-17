#include <iostream>
#include <unordered_map>
#include <cctype>
#include <Stream.h>

using namespace stream;
using namespace stream::op;

class line : public std::string {};

std::istream& operator>>(std::istream& is, line& l)
{
    std::getline(is, l);
    return is;
}

struct point : std::pair<double, double>
{
  point(std::pair<double, double> const& p) : std::pair<double, double>(p) { }
  point() {}

  bool operator==(point const& other)
  {
    return this->first == other.first && this->second == other.second;
  }

  double distance(point const& other) const
  {
    return other == *this ?
      std::numeric_limits<double>::max() :
      std::sqrt(std::pow(this->first - other.first, 2) + std::pow(this->second - other.second, 2));
  }
};

struct point_hash
{
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const
  {
    return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
  }
};

struct point_equal
{
  template <typename T, typename U>
  bool operator()(const std::pair<T, U> &x, const std::pair<T, U> &y) const
  {
    return x.first == y.first && x.second == y.second;
  }
};

using set_type = std::unordered_set<point, point_hash>;
using mesh_type = std::unordered_map<std::pair<long, long>, set_type, point_hash, point_equal>;

// compute a mesh whose cells are bxb in size
template<typename Set>
mesh_type mesh(Set const& set, double b)
{
  mesh_type m;

  for (auto&& p : set)
    m[std::make_pair(std::lround(p.first/b), std::lround(p.second/b))].insert(p);

  return m;
}

// all points in the 3x3 neighborhood of a cell in a given mesh
set_type neighborhood(mesh_type::key_type const& cell, mesh_type const& mesh)
{
  set_type n;

  for (int i = -1; i <= 1; ++i)
    for (int j = -1; j <= 1; ++j)
    {
      auto neighbors_it = mesh.find(std::make_pair(cell.first+i, cell.second+j));

      if (neighbors_it != mesh.end())
        n.insert(neighbors_it->second.begin(), neighbors_it->second.end());
    }

  return n;
}

int main(int argc, char* argv[])
{
  auto&& pairs = MakeStream::from(std::istream_iterator<line>(std::cin), std::istream_iterator<line>())
   | skip(1)
   | map_([](std::string str) {
     str.erase(std::remove_if(std::begin(str), std::end(str), [](char c){
       return c == '(' || c == ')' || c == ',';
     }), str.end());

     const std::size_t space = str.find(" ");
     auto x_str = str.substr(0, space-1);
     auto y_str = str.substr(space+1, str.size());
     double x = atof(x_str.c_str());
     double y = atof(y_str.c_str());

     return std::make_pair(x, y);
   })
   | to_vector();

  set_type S(pairs.begin(), pairs.end());

  std::vector<double> bs;

  while (!S.empty())
  {
    auto x = *S.begin();
    double b = MakeStream::from(S) | map_([&](auto&& p){ return p.distance(x); }) | min();
    b /= 3;
    bs.push_back(b);

    auto&& sieve = mesh(S, b);

    set_type X1;

    for (auto&& cell : sieve)
    {
      auto&& neighbors = neighborhood(cell.first, sieve);

      if (neighbors.size() == 1)
        X1.insert(neighbors.begin(), neighbors.end());
    }

    for (auto x1 : X1)
      S.erase(x1);

  }

  auto&& final_mesh = mesh(pairs, bs[bs.size()-2]);

  std::array<point, 2> closest_points;
  double closest_distance = std::numeric_limits<double>::max();

  for (auto&& cell : final_mesh)
  {
    auto&& neighbors = neighborhood(cell.first, final_mesh);

    for (auto&& p0 : neighbors)
      for (auto&& p1 : neighbors)
        if (p0.distance(p1) < closest_distance)
        {
          closest_distance = p0.distance(p1);
          closest_points[0] = p0;
          closest_points[1] = p1;
        }
  }

  std::cout << "(" << closest_points[0].first << ", " << closest_points[0].second << ") "
            << "(" << closest_points[1].first << ", " << closest_points[1].second << ")" << std::endl;

  return 0;
}
