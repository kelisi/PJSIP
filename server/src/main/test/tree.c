#include <stdlib.h>
struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
typedef struct Element Element;
SearchTree makeEmpty(SearchTree T);
Position find(Element element, SearchTree T);
Position findMin(SearchTree T);
Position findMax(SearchTree T);
SearchTree insert(SearchTree T, Element element);
SearchTree delete (SearchTree T, Element element);
Element retrive(Position P);

struct Element
{
    int value;
};

struct TreeNode
{
    Element element;
    SearchTree left;
    SearchTree right;
};

SearchTree makeEmpty(SearchTree T)
{
    if (T != NULL)
    {
        makeEmpty(T->left);
        makeEmpty(T->right);
    }

    return NULL;
}

Position find(Element element, SearchTree T)
{
    if (T != NULL)
    {
        if (T->element.value == element.value)
        {
            return T;
        }
        else if (T->element.value > element.value)
        {
            return find(element, T->left);
        }
        else
        {
            return find(element, T->right);
        }
    }
    return NULL;
}

Position findMin(SearchTree T)
{
    if (T != NULL)
    {
        if (T->left != NULL)
        {
            return findMin(T->left);
        }
        else
        {
            return T;
        }
    }
    else
    {
        return NULL;
    }
}

Position findMaxUnrecursion(SearchTree T)
{
    if (T == NULL)
    {
        return NULL;
    }

    Position positon = T;

    while (positon->right != NULL)
    {
        positon = positon->right;
    }
    return positon;
}

Position findMax(SearchTree T)
{
    if (T != NULL)
    {
        if (T->right != NULL)
        {
            return findMax(T->right);
        }
        else
        {
            return T;
        }
    }
    else
    {
        return NULL;
    }
}

SearchTree insert(SearchTree T, Element element)
{
    if (T == NULL)
    {
        T = malloc(sizeof(struct TreeNode));
        if (T == NULL)
        {
            // print("exception: NOT ENOUGH MEMORY");
            return NULL;
        }

        makeEmpty(T);
        T->element = element;
    }
    else if (T->element.value > element.value)
    {
        T->left = insert(T->left, element);
    }
    else if (T->element.value < element.value)
    {
        T->right = insert(T->right, element);
    }
    else
    {
        //Already exist Do Nothing
    }
    return T;
}

SearchTree delete (SearchTree T, Element element)
{
    Position TempCell;
    if (T == NULL)
    {
        return NULL;
    }
    else if (T->element.value > element.value)
    {
        delete (T->left, element);
    }
    else if (T->element.value < element.value)
    {
        delete (T->right, element);
    }
    else
    {
        //find
        if (T->left && T->right)
        {
            // find min left child and append it 右子树最小节点不可能有左儿子
            TempCell = findMin(T->right);
            T->element = TempCell->element;
            T->right = delete (T->right, T->element);
        }
        else
        {
            TempCell = T;
            if (T->left)
            {
                T = T->left;
            }
            else if (T->right)
            {
                T = T->right;
            }

            free(TempCell);
        }
    }
}