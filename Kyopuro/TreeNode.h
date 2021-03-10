
#pragma once

#include <string>
#include<vector>

template<typename T>
class TreeNode {
public:
    TreeNode() {}
    TreeNode(T value_) :value(value_) {}
    TreeNode(T value_, T left, T right) :value(value_) {
        children.push_back(TreeNode(left));
        children.push_back(TreeNode(right));
    }
    TreeNode(T value_, TreeNode<T>& left, TreeNode<T>& right) :value(value_) {
        children.push_back(left);
        children.push_back(right);
    }
    TreeNode(T value_, TreeNode<T>& left) :value(value_) {
        children.push_back(left);
    }
    TreeNode(T value_, std::vector<TreeNode<T>>& children_) :value(value_) {
        for (auto& i : children_)
            children.push_back(i);
    }
    void Push(T value_) { children.push_back(TreeNode<T>(value_)); }
    void Push(std::vector<T> value_) {
        for (auto& i : value_)
            children.push_back(TreeNode<T>(i));
    }
    void Push(TreeNode<T> value_) { children.push_back(value_); }
    void Push(std::vector<TreeNode<T>> value_) {
        for (auto& i : value_)
            children.push_back(i);
    }
    T value;
    std::vector<TreeNode<T>> children;
    static std::string order_string(const TreeNode<T>& node) {
        std::string res;
        res += indent;
        res += node.value;
        indent += " ";
        for (auto& i : node.children) {
            res += "\n";
            res += order_string(i);
        }
        indent.pop_back();
        return res;
    }
private:
    static std::string indent;
};

template<typename T>
std::string TreeNode<T>::indent = "";