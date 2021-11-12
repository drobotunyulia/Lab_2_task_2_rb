#ifndef AVLTREE_H
#define AVLTREE_H

#include "binarytree.h"

enum color_t {
    RED,
    BLACK
};

namespace rb {

    template <typename TKey, typename TValue>
    node<TKey, TValue> *get_left(node<TKey, TValue> *p_node);
    template <typename TKey, typename TValue>
    node<TKey, TValue> *get_right(node<TKey, TValue> *p_node);
    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_insert_case_1(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator);
    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_insert_case_2(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator);
    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_insert_case_3(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator);
    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_insert_case_4(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator);
    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_insert_case_5(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator);
    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_remove_case_1(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator);
    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_remove_case_2(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator);
    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_remove_case_3(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator);
    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_remove_case_4(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator);

    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_remove_case_5(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator);
    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_remove_case_6(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator);
    template <typename TKey, typename TValue>
    node<TKey, TValue> *get_parent(node<TKey, TValue> *root_node,
                                   node<TKey, TValue> *p_node,
                                   comparator<TKey> *key_comparator)
    //получить указатель на предка
    {
        return bst::get_parent(root_node, p_node, key_comparator);
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *get_grandparent(node<TKey, TValue> *root_node,
                                      node<TKey, TValue> *p_node,
                                      comparator<TKey> *key_comparator)
    //получить указатель на предка предка ("дедушку")
    {
        if ((p_node) && (get_parent(root_node, p_node, key_comparator)))
        {
            return get_parent(root_node, get_parent(root_node, p_node, key_comparator), key_comparator);
        }
        else
        {
            return nullptr;
        }
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *get_uncle(node<TKey, TValue> *root_node,
                                  node<TKey, TValue> *p_node,
                                  comparator<TKey> *key_comparator)
    //получить указатель на другого потомка от предка предка ("дядя")
    {
        node<TKey, TValue> *grandparent = get_grandparent(root_node, p_node, key_comparator);
        if (!grandparent)
        {
            return nullptr;
        }
        if (get_parent(root_node, p_node, key_comparator) == get_left(grandparent))
        {
            return get_right(grandparent);
        }
        else
        {
            return get_left(grandparent);
        }
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *get_sibling(node<TKey, TValue> *root_node,
                                    node<TKey, TValue> *p_node,
                                    comparator<TKey> *key_comparator)
    //получить указатель на другого потомка своего предка ("брат")
    {
        if (p_node == get_left(get_parent(root_node, p_node, key_comparator)))
        {
            return get_right(get_parent(root_node, p_node, key_comparator));
        }
        else
        {
            return get_left(get_parent(root_node, p_node, key_comparator));
        }
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *get_left(node<TKey, TValue> *p_node)
    //получить указатель на левого потомка
    {
        return bst::get_left(p_node);
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *get_right(node<TKey, TValue> *p_node)
    //получить указатель на правого потомка
    {
        return bst::get_right(p_node);
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> * rotate_right(node<TKey, TValue> *root_node,
                                      node<TKey, TValue> *p_node,
                                      comparator<TKey> *key_comparator)
    //правый поворот
    {
        node<TKey, TValue> *q_node = p_node->left;
        p_node->left = q_node->right;
        if (!get_parent(root_node, p_node, key_comparator))
        {
            root_node = q_node;
        }
        else if (p_node == get_parent(root_node, p_node, key_comparator)->left)
        {
            get_parent(root_node, p_node, key_comparator)->left = q_node;
        }
        else
        {
            get_parent(root_node, p_node, key_comparator)->right = q_node;
        }
        q_node->right = p_node;
        return root_node;
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> * rotate_left(node<TKey, TValue> *root_node,
                                     node<TKey, TValue> *p_node,
                                     comparator<TKey> *key_comparator)
    //левый поворот
    {
        node<TKey, TValue> *q_node = p_node->right;
        p_node->right = q_node->left;
        if (!get_parent(root_node, p_node, key_comparator))
        {
            root_node = q_node;
        }
        else if (p_node == get_parent(root_node, p_node, key_comparator)->left)
        {
            get_parent(root_node, p_node, key_comparator)->left = q_node;
        }
        else
        {
            get_parent(root_node, p_node, key_comparator)->right = q_node;
        }
        q_node->left = p_node;
        return root_node;
    }

    template <typename TKey, typename TValue>
    int get_color(node<TKey, TValue> *p_node)
    //получить значение цвета
    {
        if (!p_node)
        {
            return BLACK;
        }
        return p_node->color;
    }

    template <typename TKey, typename TValue>
    void set_color(node<TKey, TValue> *p_node, int color)
    //установить значение цвета
    {
        if (!p_node)
        {
            return;
        }
        p_node->color = color;
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_insert_case_1(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator)
    //если текущий узел в корне дерева (case 1)
    {
        if (!get_parent(root_node, p_node, key_comparator))
        {
            set_color(p_node, BLACK);
        }
        else
        {
            root_node = fix_insert_case_2(root_node, p_node, key_comparator);
        }
        return root_node;
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_insert_case_2(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator)
    //если предок текущего узла "черный" (case 2)
    {
        if (get_color(get_parent(root_node, p_node, key_comparator)) == BLACK)
        {
            return root_node;
        }
        else
        {
            root_node = fix_insert_case_3(root_node, p_node, key_comparator);
        }
        return root_node;
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_insert_case_3(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator)
    //если предок и "дядя" "красные" (case 3)
    {
        node<TKey, TValue> *uncle = get_uncle(root_node, p_node, key_comparator);
        node<TKey, TValue> *grandparent = get_grandparent(root_node, p_node, key_comparator);
        if ((uncle) && (get_color(uncle) == RED))
        {
            set_color(get_parent(root_node, p_node, key_comparator), BLACK);
            set_color(uncle, BLACK);
            set_color(grandparent, RED);
            root_node = fix_insert_case_1(root_node, grandparent, key_comparator);
        }
        else
        {
            root_node = fix_insert_case_4(root_node, p_node, key_comparator);
        }
        return root_node;
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_insert_case_4(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator)
    //если предок текущего узла "красный", а "дядя" "черный" (case 4)
    {
        node<TKey, TValue> *grandparent = get_grandparent(root_node, p_node, key_comparator);
        //текущий узел — правый потомок своего предка, а предок текущего узла в свою очередь — левый потомок своего предка ("дедушки")
        if ((p_node == get_right(get_parent(root_node, p_node, key_comparator))) && (get_parent(root_node, p_node, key_comparator) == get_left(grandparent)))
        {
            root_node = rotate_left(root_node, get_parent(root_node, p_node, key_comparator), key_comparator);
            p_node = get_left(p_node);
        }
        //текущий узел — левый потомок своего предка, а предок текущего узла в свою очередь — правый потомок своего предка ("дедушки")
        else if ((p_node == get_left(get_parent(root_node, p_node, key_comparator))) && (get_parent(root_node, p_node, key_comparator) == get_right(grandparent)))
        {
            root_node = rotate_right(root_node, get_parent(root_node, p_node, key_comparator), key_comparator);
            p_node = get_right(p_node);
        }
        root_node = fix_insert_case_5(root_node, p_node, key_comparator);
        return root_node;
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_insert_case_5(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator)
    //предок текущего узла "красный", "дядя" "чёрный", текущий узел - левый потомок своего предка и предок текущего узла - левый потомок своего предка ("дедушки")
    {
        node<TKey, TValue> *grandparent = get_grandparent(root_node, p_node, key_comparator);
        set_color(get_parent(root_node, p_node, key_comparator), BLACK);
        set_color(grandparent, RED);
        if ((p_node == get_left(get_parent(root_node, p_node, key_comparator))) && (get_parent(root_node, p_node, key_comparator) == get_left(grandparent)))
        {
            root_node = rotate_right(root_node, grandparent, key_comparator);
        }
        else
        {
            root_node = rotate_left(root_node, grandparent, key_comparator);
        }
        return root_node;
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_remove_case_1(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator)
    //если текущий (удаленный) узел является корнем (case 1)
    {
        if (get_parent(root_node, p_node, key_comparator))
        {
            root_node = fix_remove_case_2(root_node, p_node, key_comparator);
        }
        return root_node;
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_remove_case_2(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator)
    //если "брат" текущего (удаленного) узла "красный" (case 2)
    {
        node<TKey, TValue> *sibling = get_sibling(root_node, p_node, key_comparator);
        if (get_color(sibling) == RED)
        {
            set_color(get_parent(root_node, p_node, key_comparator), RED);
            set_color(sibling, BLACK);
            if (p_node == get_left(get_parent(root_node, p_node, key_comparator)))
            {
                root_node = rotate_left(root_node, get_parent(root_node, p_node, key_comparator), key_comparator);
            }
            else
            {
                root_node = rotate_right(root_node, get_parent(root_node, p_node, key_comparator), key_comparator);
            }
        }
        root_node = fix_remove_case_3(root_node, p_node, key_comparator);
        return root_node;
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_remove_case_3(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator)

    //если предок, "брат" и потомки "брата" текущего (удаленного) узла "черные" (case 3)
    {
        node<TKey, TValue> *sibling = get_sibling(root_node, p_node, key_comparator);
        node<TKey, TValue> *parent = get_parent(root_node, p_node, key_comparator);
        if ((get_color(parent) == BLACK) && (get_color(sibling) == BLACK) && (get_color(get_left(sibling)) == BLACK) && (get_color(get_right(sibling)) == BLACK))
        {
            set_color(sibling, RED);
            root_node = fix_remove_case_1(root_node, parent, key_comparator);
        }
        else
        {
            root_node = fix_remove_case_4(root_node, p_node, key_comparator);
        }
        return root_node;
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_remove_case_4(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator)
    //если предок текущего (удаленного) узла "красный", а "брат" и потомки "брата" текущего (удаленного) узла "черные" (case 4)
    {
        node<TKey, TValue> *sibling = get_sibling(root_node, p_node, key_comparator);
        node<TKey, TValue> *parent = get_parent(root_node, p_node, key_comparator);
        if ((get_color(parent) == RED) && (get_color(sibling) == BLACK) && (get_color(get_left(sibling)) == BLACK) && (get_color(get_right(sibling)) == BLACK))
        {
            set_color(sibling,  RED);
            set_color(parent, BLACK);
        }
        else
        {
            root_node = fix_remove_case_5(root_node, p_node, key_comparator);
        }
        return root_node;
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_remove_case_5(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator)
    //если "брат" текущего (удаленного) узла "черный" (case 5)
    {
        node<TKey, TValue> *sibling = get_sibling(root_node, p_node, key_comparator);
        node<TKey, TValue> *parent = get_parent(root_node, p_node, key_comparator);
        if  (get_color(sibling) == BLACK)
        {
            //текущий (удаленный) узел является левым потомком своего предка, левый потомок "брата" - "красный", а правый - "черный"
            if ((p_node == get_left(parent)) && (get_color(get_left(sibling)) == RED) && (get_color(get_right(sibling)) == BLACK))
            {
                set_color(sibling, RED);
                set_color(get_left(sibling), BLACK);
                root_node = rotate_right(root_node, sibling, key_comparator);
            }
            //текущий (удаленный) узел является правым потомком своего предка, левый потомок "брата" - "черный", а правый - "красный"
            else if ((p_node == get_right(parent)) && (get_color(get_left(sibling)) == BLACK) && (get_color(get_right(sibling)) == RED))
            {
                set_color(sibling, RED);
                set_color(get_right(sibling), BLACK);
                root_node = rotate_left(root_node, sibling, key_comparator);
            }
        }
        root_node = fix_remove_case_6(root_node, p_node, key_comparator);
        return root_node;
    }

    template <typename TKey, typename TValue>
    node<TKey, TValue> *fix_remove_case_6(node<TKey, TValue> *root_node,
                                          node<TKey, TValue> *p_node,
                                          comparator<TKey> *key_comparator)
    //"брат" текущего (удаленного) узла - "черный", а правый птомок "брата" - "черный" (case 6)
    {
        node<TKey, TValue> *sibling = get_sibling(root_node, p_node, key_comparator);
        node<TKey, TValue> *parent = get_parent(root_node, p_node, key_comparator);
        set_color(sibling, get_color(parent));
        set_color(parent, BLACK);
        //текущий (удаленный) узел - левый потомок своего предка
        if (p_node == get_left(parent))
        {
            set_color(get_right(sibling), BLACK);
            root_node = rotate_left(root_node, parent, key_comparator);
        }
        //текущий (удаленный) узел - правый потомок своего предка
        else
        {
            set_color(get_left(sibling), BLACK);
            root_node = rotate_right(root_node, parent, key_comparator);
        }
        return root_node;
    }
}

template <typename TKey, typename TValue>
class rb_tree : public binary_tree<TKey, TValue>
{
protected:
    class rb_find_template_method : public binary_tree<TKey, TValue>::find_template_method
    {

    };
    class rb_insert_template_method : public binary_tree<TKey, TValue>::insert_template_method
    {
    protected:
        void post_insert_hook(node<TKey, TValue> *&root_node,
                              node<TKey, TValue> *&insert_node,
                              comparator<TKey> *key_comparator);

    };
    class rb_remove_template_method : public binary_tree<TKey, TValue>::remove_template_method
    {
    protected:
        status_t inner_remove(node<TKey, TValue> *&root_node,
                              TKey key,
                              comparator<TKey> *key_comparator);

    };
public:
    rb_tree(comparator<TKey> *key_comparator);
    rb_tree(binary_tree<TKey, TValue> &tree);
    ~rb_tree();
};

template <typename TKey, typename TValue>
rb_tree<TKey, TValue>::rb_tree(comparator<TKey> *key_comparator) : binary_tree<TKey, TValue>::binary_tree()
{
    rb_find_template_method *rb_finder = new rb_find_template_method;
    rb_insert_template_method *rb_inserter = new rb_insert_template_method;
    rb_remove_template_method *rb_remover = new rb_remove_template_method;
    rb_tree<TKey, TValue>::init_template_methods(rb_finder, rb_inserter, rb_remover);
    this->key_comparator = key_comparator;
}

template <typename TKey, typename TValue>
rb_tree<TKey, TValue>::rb_tree(binary_tree<TKey, TValue> &tree) : binary_tree<TKey, TValue>::binary_tree(tree)
{

}

template <typename TKey, typename TValue>
rb_tree<TKey, TValue>::~rb_tree()
{
}

template <typename TKey, typename TValue>
void rb_tree<TKey, TValue>::rb_insert_template_method::post_insert_hook(node<TKey, TValue> *&root_node,
                                                                        node<TKey, TValue> *&insert_node,
                                                                        comparator<TKey> *key_comparator)
{
    //балансируем дерево
    root_node = rb::fix_insert_case_1(root_node, insert_node, key_comparator);
}

template <typename TKey, typename TValue>
status_t rb_tree<TKey, TValue>::rb_remove_template_method::inner_remove(
        node<TKey, TValue> *&root_node,
        TKey key,
        comparator<TKey> *key_comparator)
{
    node<TKey, TValue> *replace_node = nullptr;
    node<TKey, TValue> *replace_parent_node = nullptr;
    node<TKey, TValue> *current_node = root_node;
    node<TKey, TValue> *remove_node = nullptr;
    while(current_node)
    //ищем удаляемый элемент
    {
        compare_t compare_result = (*key_comparator)(key, current_node->key);
        if (compare_result == LESS)
        //идем по левой стороне
        {
            current_node = current_node->left;
        }
        else if (compare_result == GREAT)
        //идем по правой стороне
        {
            current_node = current_node->right;
        }
        else if (compare_result == EQUAL)
        //элемент найден
        {
            remove_node = current_node;
            break;
        }
    }
    if (!remove_node)
    //удаляемый элемент отсутствует
    {
        return REMOVE_ERROR;
    }
    if (remove_node->left && remove_node->right)
    //удаляемый элемент имеет двоих потомков
    {
        replace_node = bst::find_min_node(remove_node->right);
        replace_parent_node = bst::get_parent(root_node, replace_node, key_comparator);
        //переносим значения из заменяющего элемента в удаляемый элемент
        remove_node->key = replace_node->key;
        remove_node->value = replace_node->value;
        remove_node->color = replace_node->color;
        //теперь заменяющий элемент становится удаляемым
        remove_node = replace_node;
        //и его нужно удалить
        if (remove_node->right)
        //заменяющий (удаляемый) элемент имеет правого потомка
        {
            replace_node = remove_node->right;
            if (remove_node == replace_parent_node->right)
            {
                replace_parent_node->right = replace_node;
            }
            else
            {
                replace_parent_node->left = replace_node;
            }
        }
        else
        //заменяющий (удаляемый) элемент не имеет потомков
        {
            replace_node = nullptr;
            if (remove_node == replace_parent_node->left)
            {                replace_parent_node->left = replace_node;
            }
            else
            {
                replace_parent_node->right = replace_node;
            }
        }
    }
    else if (remove_node->left)
    //удаляемый элемент имеет только левого потомка
    {
        replace_node = remove_node->left;
        if (rb::get_parent(root_node, remove_node, key_comparator))
        //удаляемый элемент не корневой (имеет предка)
        {
            if (remove_node == rb::get_left(rb::get_parent(root_node, remove_node, key_comparator)))
            {
                rb::get_parent(root_node, remove_node, key_comparator)->left = replace_node;
            }
            else
            {
                rb::get_parent(root_node, remove_node, key_comparator)->right = replace_node;
            }
        }
        else
        //удаляемый элемент корневой
        {
            root_node = replace_node;
        }
    }
    else if (remove_node->right)
    //удаляемый элемент имеет только правого потомка
    {
        replace_node = remove_node->right;
        if (rb::get_parent(root_node, remove_node, key_comparator))
        //удаляемый элемент не корневой (имеет предка)
        {
            if (remove_node == rb::get_right(rb::get_parent(root_node, remove_node, key_comparator)))
            {
                rb::get_parent(root_node, remove_node, key_comparator)->right = replace_node;
            }
            else
            {
                rb::get_parent(root_node, remove_node, key_comparator)->left = replace_node;
            }
        }
        else
        //удаляемый элемент корневой
        {
            root_node = replace_node;
        }
    }
    else
    //удаляемый элемент не имеет потомков
    {
        if (rb::get_parent(root_node, remove_node, key_comparator))
        //удаляемый элемент не корневой (имеет предка)
        {
            if (remove_node == rb::get_left(rb::get_parent(root_node, remove_node, key_comparator)))
            {
                rb::get_parent(root_node, remove_node, key_comparator)->left = replace_node;
            }
            else
            {
                rb::get_parent(root_node, remove_node, key_comparator)->right = replace_node;
            }
        }
        else
        //удаляемый элемент корневой
        {
            root_node = replace_node;
        }
    }
    //балансируем дерево
    if (rb::get_color(remove_node) == BLACK)
    {
        if (rb::get_color(replace_node) == RED)
        {
            rb::set_color(replace_node, BLACK);
        }
        else
        {
            root_node = rb::fix_remove_case_1(root_node, replace_node, key_comparator);
        }
    }
    delete remove_node;
    return REMOVE_SUCCESS;
}

#endif // AVLTREE_H
