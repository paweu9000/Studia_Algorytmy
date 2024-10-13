#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    int value;
    std::vector<Node*> next_values;

    Node(int val) {
        value = val;
        next_values = {};
    }

    void add_node(Node* node) {
        next_values.push_back(node);
    }
};

void find_sequences(Node* node, std::vector<int>& current_sequence, std::vector<std::vector<int>>& all_sequences)
{
    current_sequence.push_back(node->value);

    all_sequences.push_back(current_sequence);

    for (auto next : node->next_values) {
        find_sequences(next, current_sequence, all_sequences);
    }

    current_sequence.pop_back();
}

int main()
{
    std::vector<int> input{1, 4, 3, 5, 9, 10, 10, 11, 8, 7};
    std::vector<Node*> nodes;

    for (auto i: input) {
        nodes.push_back(new Node(i));
    }

    for (int i = 0; i < nodes.size(); ++i) {
        for (int j = i+1; j < nodes.size(); ++j) {
            if (nodes[i]->value <= nodes[j]->value) {
                nodes[i]->add_node(nodes[j]);
            }
        }
    }

    std::vector<std::vector<int>> all_sequences;
    std::vector<int> current_sequence;

    for (auto node : nodes) {
        find_sequences(node, current_sequence, all_sequences);
    }

    std::sort(std::begin(all_sequences), std::end(all_sequences), [](const std::vector<int> v1, const std::vector<int> v2) {
            return !(v1.size() < v2.size());
        }
    );

    int largest = all_sequences[0].size();

    for (auto it = std::begin(all_sequences); it != std::end(all_sequences);) {
        if (it->size() < largest) {
            std::iter_swap(it, std::end(all_sequences)-1);
            all_sequences.pop_back();
        } else {
            ++it;
        }
    }

    for (const auto& seq : all_sequences) {
        for (int num : seq) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    for (auto node : nodes) {
        delete node;
    }

    return 0;
}