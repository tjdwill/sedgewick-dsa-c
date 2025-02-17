#!/usr/bin/env python3
# btree.py
# A binary tree implementation to refamiliarize with Python
from collections.abc import Callable
from enum import Enum, auto
from typing import Any, Optional, Self, Tuple


class BTreeNode:
    """
    A binary tree node. There's nothing stopping the user from initializing a tree with
    inconsistent types, but don't do it.
    """
    def __init__(self, data: Any=None):
        self.data: Any = data
        self.left_child: Optional[Self] = None
        self.right_child: Optional[Self] = None
    
    def clear(self, which: str="both") -> Tuple[Optional[Self], Optional[Self]]:
        """Removes the specified subtree(s) from this node, returning it as a result"""
        ret = (None, None)
        match which.lower():
            case "left":
                ret = (self.left_child, None)
                self.left_child = None
            case "right":
                ret = (None, self.right_child)
                self.right_child = None
            case "both":
                ret = (self.left_child, self.right_child)
                self.left_child = None
                self.right_child = None
        return ret

    def add(self, node: Self, which: str):
        match which.lower():
            case "left":
                self.left_child = node
            case "right":
                self.right_child = node
            case _:
                raise Exception("Invalid tree child specification")

    def traverse_postorder(self, action: Callable[[Self], None]) -> None:
        class State(Enum):
            LEFT = auto()
            RIGHT = auto()
            ROOT = auto()
        
        state_stack = [State.LEFT]
        node_stack = [self]
        
        while state_stack and node_stack:
            node = node_stack.pop()
            state = state_stack.pop()
            
            match state:
                case State.LEFT:
                    node_stack.append(node)
                    state_stack.append(State.RIGHT)

                    if node.left_child:
                        node_stack.append(node.left_child)
                        state_stack.append(State.LEFT)

                case State.RIGHT:
                    node_stack.append(node)
                    state_stack.append(State.ROOT)

                    if node.right_child:
                        node_stack.append(node.right_child)
                        state_stack.append(State.LEFT)

                case State.ROOT:
                    action(node)

    def __str__(self):
            return str(self.data)

    def init_BTree(vals: list[int] | list[str]) -> Self:
        assert(vals)
        vals.reverse()
        print(vals)
        root_node = BTreeNode(vals.pop())
        
        nodes = [root_node]

        def fill(node: BTreeNode):
            # Fill via level order
            left = vals.pop()
            node.left_child = BTreeNode(left)
            nodes.insert(0, node.left_child)

            right = vals.pop()
            node.right_child = BTreeNode(right)
            nodes.insert(0, node.right_child)
        
        while(vals and nodes):
            curr_node = nodes.pop()
            try:
                fill(curr_node)
            except Exception:
                continue

        return root_node
            



if __name__ == "__main__":

    # Test the function
    def printNode(node: BTreeNode) -> None:
        try:
            print(f"{node.data}", end=" ")
        except Exception:
            print("Could not print the node's data.")


    btree = BTreeNode.init_BTree([x for x in range(5)])
    btree.traverse_postorder(printNode)
    print("")