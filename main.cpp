#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> input = {5, 2, 1, 3, 6, 7, 4};
    std::vector<std::vector<int>> results;

    int longest = 0;

    for (int j = 0; j < input.size()-1; ++j) {
        int count = 1;
        int temp = input[j];
        std::vector<int> res{};
        res.push_back(input[j]);
        for (int i = j+1; i < input.size(); ++i) {
            if (temp < input[i]) {
                ++count;
                temp = input[i];
                res.push_back(temp);
            }
        }
        results.push_back(res);
        longest = std::max(longest, count);
    }

    for (auto it = results.begin(); it != results.end();) {
        if ((*it).size() != longest) {
            std::iter_swap(it, results.end() - 1);
            results.pop_back();
        } else {
            ++it;
        }
    }

    for (auto i : results) {
        for (auto j : i) {
            std::cout << j << ", ";
        }
        std::cout << "\n";
    }

    return 0;
}