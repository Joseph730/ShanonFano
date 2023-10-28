#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    char data;
    float probability;
    string code;
    Node* left, * right;
};

void shannonFano(std::vector<Node>& nodes, int start, int end) {
    if (start >= end - 1) {
        return;
    }

    float totalProb = 0;
    for (int i = start; i < end; ++i) {
        totalProb += nodes[i].probability;
    }

    float currProb = 0;
    int splitIndex = start;
    float minDiff = std::numeric_limits<float>::max();

    for (int i = start; i < end; ++i) {
        currProb += nodes[i].probability;
        float diff = std::abs(currProb - (totalProb - currProb));
        if (diff < minDiff) {
            minDiff = diff;
            splitIndex = i;
        }
    }

    for (int i = start; i < end; ++i) {
        if (i <= splitIndex) {
            nodes[i].code += "0";
        }
        else {
            nodes[i].code += "1";
        }
    }

    shannonFano(nodes, start, splitIndex + 1);
    shannonFano(nodes, splitIndex + 1, end);
}

int main() {
    setlocale(LC_ALL, "ru");
    vector<Node> nodes;
    // Добавим свои данные о вероятностях и символах вектора nodes
    nodes.push_back({'a', 0.3, "", nullptr, nullptr});
    nodes.push_back({'b', 0.2, "", nullptr, nullptr});
    nodes.push_back({'c', 0.25, "", nullptr, nullptr});
    nodes.push_back({'d', 0.25, "", nullptr, nullptr});
    nodes.push_back({ 'e', 0.35, "", nullptr, nullptr });
    nodes.push_back({ 'f', 0.15, "", nullptr, nullptr });
    nodes.push_back({ 'g', 0.4, "", nullptr, nullptr });

    shannonFano(nodes, 0, nodes.size());

    cout << "Символ\tВероятность\tКод" << std::endl;
    for (const auto& node : nodes) {
        cout << node.data << "\t" << node.probability << "\t\t" << node.code << std::endl;
    }

    return 0;
}