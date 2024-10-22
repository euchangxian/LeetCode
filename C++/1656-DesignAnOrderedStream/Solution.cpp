#include <cstddef>
#include <string>
#include <vector>

using namespace std;
/**
 * Question is confusing. Its essentially a TCP buffer.
 * Receive message, if it is out of order, then buffer it.
 */
class OrderedStream {
 private:
  int ptr;
  std::vector<std::string> stream;

 public:
  OrderedStream(int n) : ptr(0), stream(n) {}

  vector<string> insert(int idKey, string value) {
    stream[idKey - 1] = std::move(value);

    vector<std::string> out;
    while (ptr < stream.size() && !stream[ptr].empty()) {
      // There is no need to keep ownership of the string anymore after it has
      // been consumed.
      out.emplace_back(std::move(stream[ptr++]));
    }
    return out;
  }
};

/**
 * Your OrderedStream object will be instantiated and called as such:
 * OrderedStream* obj = new OrderedStream(n);
 * vector<string> param_1 = obj->insert(idKey,value);
 */
