#include <string>
#include <stack>
#include <map>
#include <functional>

class Caculator
{
public:
    typedef double DataType;
    DataType run(const std::string &exp);
private:
    typedef std::map<char,int>  ttype_t;
    typedef std::map<char,char> mtype_t;
    typedef std::function<DataType(DataType, DataType)> func_t;

    void advance(std::stack<char> &ops, std::stack<DataType> &nums);
    bool is_priorier(char left, char right) const;
    bool is_equal(char left, char right) const;
    func_t func_factory(char op) const;

    const ttype_t PRIORITY = {{'+', 0}, {'-', 0}, {'*', 1}, {'/', 1},
                              {'(', -1}, {')', 2}, {'=', -1}, {'#', -1}};
    const mtype_t MATCH = {{')', '('}, {'=', '#'}};
    const std::string MATCHL = "(#";
    const std::string MATCHR = ")=";
    const std::string DIGITS = "01234567890.";
    const std::string OPS = "+-*/";
    bool status;
};

