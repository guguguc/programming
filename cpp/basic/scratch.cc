#include <set>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <fmt/core.h>

using namespace std;


int main()
{
    vector<int> v1{1, 2, 3};
    vector<int> v2({1, 2, 3});
    set<vector<int>> st;
    st.insert(v2);
    fmt::print("{}\n", st.size());
    fmt::print("{}", v1.back());
    return 0;
}
