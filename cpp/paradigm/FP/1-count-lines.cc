#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <optional>
#include <range/v3/view.hpp>

using namespace ranges;

std::optional<int>
count_lines(const std::string &filename)
{
    std::ifstream in(filename);
    if (in.fail())
    {
        return std::nullopt;
    }
    return std::count(
            std::istreambuf_iterator<char>(in),
            std::istreambuf_iterator<char>(),
            '\n');
}


std::vector<std::optional<int>>
batch_cnt_lines(const std::vector<std::string> &files)
{
    std::vector<std::optional<int>> lines(files.size());
    std::transform(files.cbegin(), files.cend(), lines.begin(),
            count_lines);
    return lines;
}

auto
batch_cnt_lines_2(const std::vector<std::string> &files)
{
    return files | views::transform(count_lines);
}

int
main()
{
    std::vector<std::string> files{"test1.txt", "test2.txt", "test3.txt"};
    auto lines = batch_cnt_lines(files);
    for (std::optional<int> line : lines)
    {
        std::cout << line.value_or(-1) << "\n";
    }
    return 0;
}
