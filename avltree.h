#ifndef AVLTREE_H
#define AVLTREE_H

#include "binarytree.h"

namespace avl {
    template <typename TKey, typename TValue>
    int get_height(node<TKey, TValue> *p_node)
    //получить глубину узла дерева
    {
        if (!p_node)
        {
            return -1;
        }
        return (p_node->height);
    }

    template <typename TKey, typename TValue>
    int get_balance(node<TKey, TValue> *p_node)
    //получить баланс между правым и левым потомками узла
    {
        if(!p_node)
        {
            return 0;
        }
        return get_height(p_node->left) - get_height(p_node->right);
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue>* rotate_right(node<TKey, TValue> *p_node)
    //вращение узла вправо
    {
        node<TKey, TValue> *q_node = p_node->left;
        p_node->left = q_node->right;
        q_node->right = p_node;
        p_node->height = std::max(get_height(p_node->left), get_height(p_node->right)) + 1;
        q_node->height = std::max(get_height(q_node->left), q_node->height) + 1;
        return q_node;
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue>* rotate_left(node<TKey, TValue> *p_node)
    //вращение узла влево
    {
        node<TKey, TValue> *q_node = p_node->right;
        p_node->right = q_node->left;
        q_node->left = p_node;
        p_node->height = std::max(get_height(p_node->left), get_height(p_node->right)) + 1;
        q_node->height = std::max(get_height(q_node->right), q_node->height) + 1 ;
        return q_node;
    }
    template <typename TKey, typename TValue>
    node<TKey, TValue> *find_min_node(node<TKey, TValue>* root_node)
    //найти минимальный элемент в дереве
    {
        return bst::find_min_node(root_node);
    }
}

template <typename TKey, typename TValue>
class avl_tree : public binary_tree<TKey, TValue>
{
protected:
    class avl_find_template_method : public binary_tree<TKey, TValue>::find_template_method
    {

    };
    class avl_insert_template_method : public binary_tree<TKey, TValue>::insert_template_method
    {
    protected:
        status_t inner_insert(node<TKey, TValue> *&root_node,
                              TKey key,
                              TValue value,
                              comparator<TKey> *key_comparator,
                              node<TKey, TValue> *&insert_node);
    };
    class avl_remove_template_method : public binary_tree<TKey, TValue>::remove_template_method
    {
    protected:
        status_t inner_remove(node<TKey, TValue> *&root_node,
                              TKey key,
                              comparator<TKey> *key_comparator);
    };
public:
    avl_tree(comparator<TKey> *key_comparator);
    avl_tree(binary_tree<TKey, TValue> &tree);
    ~avl_tree();
};

template <typename TKey, typename TValue>
avl_tree<TKey, TValue>::avl_tree(comparator<TKey> *key_comparator) : binary_tree<TKey, TValue>::binary_tree()
{
    avl_find_template_method *avl_finder = new avl_find_template_method;
    avl_insert_template_method *avl_inserter = new avl_insert_template_method;
    avl_remove_template_method *avl_remover = new avl_remove_template_method;
    avl_tree<TKey, TValue>::init_template_methods(avl_finder, avl_inserter, avl_remover);
    this->key_comparator = key_comparator;
}

template <typename TKey, typename TValue>
avl_tree<TKey, TValue>::avl_tree(binary_tree<TKey, TValue> &tree) : binary_tree<TKey, TValue>::binary_tree(tree)
{
}

template <typename TKey, typename TValue>
avl_tree<TKey, TValue>::~avl_tree()
{
}

template <typename TKey, typename TValue>
status_t avl_tree<TKey, TValue>::avl_insert_template_method::inner_insert(
        node<TKey, TValue> *&root_node,
        TKey key,
        TValue value,
        comparator<TKey> *key_comparator,
        node<TKey, TValue> *&insert_node)
{
    if (!root_node)
    //в пустое место всавляем новый элемент
    {
        root_node = insert_node;
    }
    //рекурсивно ищем пустое место для вставки нового элемента
    else if ((*key_comparator)(key, root_node->key) == LESS)
    //идем по левой стороне
    {
        status_t status = inner_insert(root_node->left, key, value, key_comparator, insert_node);
        if (status == INSERT_ERROR)
        {
            return INSERT_ERROR;
        }
    }
    else if ((*key_comparator)(key, root_node->key) == GREAT)
    //идем по правой стороне
    {
        status_t status = inner_insert(root_node->right, key, value, key_comparator, insert_node);
        if (status == INSERT_ERROR)
        {
            return INSERT_ERROR;
        }
    }
    else if ((*key_comparator)(root_node->key, key) == EQUAL)
    //вставляемый элемент уже существует в дереве
    {
        return INSERT_ERROR;
    }
    //корректируем значение height
    root_node->height = 1 + std::max(avl::get_height(root_node->left), avl::get_height(root_node->right));
    //балансируем дерево
    if (avl::get_balance(root_node) > 1)
    {
        if((*key_comparator)(key, root_node->left->key) == LESS)
        {
            root_node = avl::rotate_right(root_node);
            return INSERT_SUCCESS;
        }
        else
        {
            root_node->left = avl::rotate_left(root_node->left);
            root_node = avl::rotate_right(root_node);
            return INSERT_SUCCESS;
        }
    }
    else if(avl::get_balance(root_node) < -1)
    {
        if((*key_comparator)(key, root_node->right->key) == GREAT)
        {
            root_node = avl::rotate_left(root_node);
            return INSERT_SUCCESS;
        }
        else
        {
            root_node->right = avl::rotate_right(root_node->right);
            root_node = avl::rotate_left(root_node);
            return INSERT_SUCCESS;
        }
    }
    return INSERT_SUCCESS;
}

template <typename TKey, typename TValue>
status_t avl_tree<TKey, TValue>::avl_remove_template_method::inner_remove(
        node<TKey, TValue> *&root_node,
        TKey key,
        comparator<TKey> *key_comparator)
{
    node<TKey, TValue> *remove_node;
    node<TKey, TValue>* replace_node = nullptr;
    if (!root_node)
    {
        return REMOVE_ERROR;
    }
    //рекурсивно ищем элемент, который нужно удалить
    else if ((*key_comparator)(key, root_node->key) == LESS)
    //идем по левой стороне
    {
        status_t status = inner_remove(root_node->left, key, key_comparator);
        if (status == REMOVE_ERROR)
        {
            return REMOVE_ERROR;
        }
    }
    else if ((*key_comparator)(key, root_node->key) == GREAT)
    //идем по правой стороне
    {
        status_t status = inner_remove(root_node->right, key, key_comparator);
        if (status == REMOVE_ERROR)
        {
            return REMOVE_ERROR;
        }
    }
    else if(root_node->left && root_node->right)
    //удаляемый элемент имеет два потомка
    {
        remove_node = root_node;
        //ищем замену удаляемому элементу
        replace_node = avl::find_min_node(root_node->right);
        //копируем значения в удаляемый элемент
        remove_node->key = replace_node->key;
        remove_node->value = replace_node->value;
        remove_node->height = replace_node->height;
        //рекурсивно удаляем элемент
        status_t status = inner_remove(root_node->right, root_node->key, key_comparator);
        if (status == REMOVE_ERROR)
        {
            return REMOVE_ERROR;
        }
    }
    else
    //удаляемый элемент имеет не более одного потомка
    {
        remove_node = root_node;
        if(!remove_node->left)
        //удаляемый элемент не имеет левого потомка
        {
            replace_node = remove_node->right;
            root_node = remove_node->right;
        }
        else if(!remove_node->right)
        //удаляемый элемент имеет только левого потомка
        {
            replace_node = remove_node->left;
            root_node = remove_node->left;
        }
        delete remove_node;
    }
    if (!root_node)
    {
        return REMOVE_SUCCESS;
    }
    //корректируем значение height
    root_node->height = 1 + std::max(avl::get_height(root_node->left), avl::get_height(root_node->right));
    //балансируем дерево
    if(avl::get_balance(root_node) > 1)
    {
        if (avl::get_height(root_node->left) >= avl::get_height(root_node->right))
        {
            root_node = avl::rotate_right(root_node);
        }
        else
        {
            root_node->left = avl::rotate_left(root_node->left);
            root_node = avl::rotate_right(root_node);
        }
    }
    else if (avl::get_balance(root_node) < -1)
    {
        if(avl::get_height(root_node->right) >= avl::get_height(root_node->left))
        {
            root_node = avl::rotate_left(root_node);
        }
        else
        {
            root_node->right = avl::rotate_right(root_node->right);
            root_node = avl::rotate_left(root_node);
        }
    }
    return REMOVE_SUCCESS;
}

#endif // AVLTREE_H
