class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

def preorder_traversal(root):
    print(root.val)
    if root.left is not None:
        preorder_traversal(root.left)
    if root.right is not None:
        preorder_traversal(root.right)

root = TreeNode(5)
root.left = TreeNode(1)
root.right = TreeNode(4)
root.right.left = TreeNode(3)
root.right.right = TreeNode(6)

preorder_traversal(root)         # 5 1 4 3 6
