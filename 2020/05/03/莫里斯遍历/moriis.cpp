#define NULL nullptr
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int _val) : val(_val), left(NULL), right(NULL) {}
};

void visit(TreeNode *root);

void inOrderTraversal(TreeNode *root)
{
    TreeNode *cur = root;
    TreeNode *prev = NULL;
    while (cur != NULL)
    {
        if (cur->left == NULL)
        { //最左侧
            visit(cur);
            cur = cur->right;
        }
        else
        {
            prev = cur->left;
            while (prev->right != NULL && prev->right != cur) //find the predecessor
                prev = prev->right;
            if (prev->right == NULL)
            {
                prev->right = cur;
                cur = cur->left;
            }
            else //prev = cur
            {    //recover
                prev->right = NULL;
                visit(cur);
                cur = cur->right;
            }
        }
    }
}

void preOrderTraversal(TreeNode *root)
{
    TreeNode *cur = root;
    TreeNode *prev = NULL;
    while (cur != NULL) {
        if (cur != NULL) {
            visit(cur);
            cur = cur->right;
        }
        else {
            prev = cur->left;
            while (prev->right != NULL && prev->right != cur)
                prev = prev->right;
            if (prev->right == NULL) {
                prev->right = cur;
                visit(cur);
                cur = cur->left;
            }
            else {
                prev->right = NULL;
                cur = cur->right;
            }
        }
    }
}