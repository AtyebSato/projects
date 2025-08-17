#include <iostream>
#include <string>
class TwoToOne
{
public:
    static std::string longest(const std::string &s1, const std::string &s2)
      {
      std::string combined;
      for (char c : s1)
        {
         combined += c;
        }
        for (char h : s2)
          {
          combined += h;
        }
      return combined;
    }
};

int main()
{
    TwoToOne two;
    std::cout << two.longest("abcde", "fghgl");
}