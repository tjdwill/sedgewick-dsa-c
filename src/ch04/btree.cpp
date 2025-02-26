// btree.cpp
// See implementation result at: https://godbolt.org/z/fP5zcKbPs

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

/// Think: Ownership. There is only one way to access a binary tree node: through its parent. 
/// The parent-child relationship implies ownership (parent owns children).
template<typename T>
class BTreeNode
{
public:
    enum class Direction {left, right};
    
    // CONSTRUCTORS
    explicit BTreeNode(T data)
        : d_data(data) {}   

    BTreeNode(T data, std::shared_ptr<BTreeNode> subtree, Direction dir)
        : d_data(data)
    {
        switch(dir)
        {
            case Direction::lefT:
                d_left_child = subtree;
                break;
            case Direction::right:
                d_right_child = subtree;
                break;
            default:
                throw std::runtime_error("Impossible variant\n");
        }
    }

    BTreeNode(T data, std::shared_ptr<BTreeNode> left_tree, std::shared_ptr<BTreeNode> right_tree)
        : d_data(data), d_left_child(left_tree), d_right_child(right_tree)
    {}

    // ACCESSORS
    auto data() const -> T const& { return d_data; }

    // MANIPULATORS

    /// Traverse the tree, performing the input (non-modifying) operation 
    static void traverse_postorder(
        std::shared_ptr<BTreeNode> tree,
        std::function< void( std::shared_ptr<BTreeNode<T>> )> action
    );

private:
    T d_data;
    std::optional< std::shared_ptr< BTreeNode>> d_left_child {};
    std::optional< std::shared_ptr< BTreeNode>> d_right_child {};

    /// Track which part of the node is being visited.
    enum class TraversalState { root, left, right };

};

int main() 
{
    auto b6 = std::make_shared<BTreeNode<int>>(6);
    auto b5 = std::make_shared<BTreeNode<int>>(5);
    auto b4 = std::make_shared<BTreeNode<int>>(4);
    auto b3 = std::make_shared<BTreeNode<int>>(3);

    auto b2 = std::make_shared<BTreeNode<int>>(2, b5, b6);
    auto b1 = std::make_shared<BTreeNode<int>>(1, b3, b4);

    auto b0 = std::make_shared<BTreeNode<int>>(0, b1, b2);

    std::cout << "Post-order Traversal: ";
    BTreeNode<int>::traverse_postorder(
        b0, 
        [](std::shared_ptr<BTreeNode<int>> node) { 
            std::cout << node->data() << " "; 
            return;
        }
    );
}


//------------------------------------------------------------------------------
template<typename T>
// 
void BTreeNode<T>::traverse_postorder(
    std::shared_ptr<BTreeNode> tree,
    std::function< void( std::shared_ptr<BTreeNode<T>> )> action
)
{
    using State = BTreeNode<T>::TraversalState;
    // Init Tracker variables
    std::vector<State> states { State::left };
    std::vector< std::shared_ptr< BTreeNode<T>>> nodes { tree };

    while (!nodes.empty() && !states.empty())
    {
        auto node = nodes.back();
        // nodes.pop_back();
        auto state = states.back();
        states.pop_back();

        switch(state)
        {
            case State::left:
                states.push_back(State::right);
                if (node->d_left_child)
                {
                    nodes.push_back(node->d_left_child.value());
                    states.push_back(State::left);
                }
                break;
            case State::right:
                states.push_back(State::root);
                if (node->d_right_child)
                {
                    nodes.push_back(node->d_right_child.value());
                    states.push_back(State::left);
                }
                break;
            case State::root:
                action(node);
                // remove the node
                nodes.pop_back();
                break;
            default:
                throw std::runtime_error("Unknown traversal state");
        }
    }
}
