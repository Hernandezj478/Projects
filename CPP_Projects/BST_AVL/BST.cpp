
#include "BST.hpp"

BST::BST(){
    root=nullptr;
}

void BST::insert(int val){
    if(root==nullptr)
        root = insertNode(root,val);
    else{
        insertNode(root,val);
    }
}

void BST::deleteNode(int val){
    deleteNode(root,val);
}

void BST::printLevel(int lvl){
    printLevel(root,lvl);
}

void BST::print(){
    print(root);
}

void BST::preOrder(){
    preOrder(root);
}

void BST::postOrder(){
    postOrder(root);
}

BSTNode* BST::searchVal(BSTNode* root,int val){
    if(root==nullptr || root->val==val)
        return root;
    if(val > root->val)
        return searchVal(root->right,val);
    return searchVal(root->left,val);
}

BSTNode* BST::newNode(int val){
    BSTNode *temp = new BSTNode;
    temp->val=val;
    temp->left=nullptr;
    temp->right=nullptr;
    return temp;
}

BSTNode* BST::insertNode(BSTNode *parent,int val){
    if(parent==nullptr){
        return newNode(val);
    }
    
    if(val>parent->val){
        parent->right=insertNode(parent->right,val);
    }
    else if(val<parent->val){
        parent->left=insertNode(parent->left,val);
    }
    return parent;
}

BSTNode* BST::deleteNode(BSTNode *root,int val){
    if(root==nullptr) return root;
    if(val < root->val){
        root->left=deleteNode(root->left,val);
    }
    else if(val > root->val){
        root->right=deleteNode(root->right,val);
    }
    else{
        if(root->left==nullptr){
            BSTNode *temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right==nullptr){
            BSTNode *temp=root->left;
            delete root;
            return temp;
        }
        BSTNode *temp = minVal(root->right);
        root->val = temp->val;
        root->right = deleteNode(root->right,temp->val);
    }
    return root;
}

BSTNode* BST::minVal(BSTNode *node){
    BSTNode *current = node;
    while(current!=nullptr && current->left!=nullptr)
        current = current->left;
    return current;
}

int BST::height(BSTNode* root){
    if(root==nullptr){
        return 0;
    }
    else{
        int l_depth = height(root->left);
        int r_depth = height(root->right);
        
        if(l_depth > r_depth){
            return (l_depth + 1);
        }
        else 
            return (r_depth + 1);   
    }
}

void BST::printLevel(BSTNode* root,int level){
    if(root==nullptr) return;
    if(level == 1) cout<<root->val<<" ";
    else if(level > 1){
        printLevel(root->left,level - 1);
        printLevel(root->right,level - 1);
    }
}

void BST::print(BSTNode *root){
    int h = height(root);
    int i;
    for(i=1;i<=h;i++){
        printLevel(root,i);
        cout<<endl;
    }
}

void BST::printLeaf(BSTNode *root){
    if(!root) return;
    if(!root->right && !root->left){
        cout<<root->val<<" ";
        return;
    }
    if(root->left)
        printLeaf(root->left);
    if(root->right)
        printLeaf(root->right);
}

void BST::printParent(BSTNode *root){
    if(root==nullptr || (root->left==nullptr && root->right==nullptr))
        return;
    if(root->left!=nullptr || root->right!=nullptr){
        cout<<root->val<<" ";
    }
    printParent(root->left);
    printParent(root->right);
}

void BST::inOrder(){
    inOrder(root);
}

void BST::inOrder(BSTNode *root){
    if(root!=nullptr){
        inOrder(root->left);
        cout<<root->val<<" ";
        inOrder(root->right);
    }
}

void BST::preOrder(BSTNode *root){
    if(root!=nullptr){
        cout<<root->val<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void BST::postOrder(BSTNode *root){
    if(root!=nullptr){
        postOrder(root->left);
        postOrder(root->right);
        cout<<root->val<<" ";
    }
}

bool BST::search(int val){
    return searchVal(root,val);
}


