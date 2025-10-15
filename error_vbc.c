// this code is already given you just need to code the following functions found in vbc.c
// parse_factor - parse_term - parse_expr
// and you have to modify the following functions unexpected - accept - eval_tree - main
// read vbc.c and you will understand

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node
{
    enum
    {
        ADD,
        MULTI,
        VAL
    } type;
    int val;
    struct node *l;
    struct node *r;
} node;

node *p_e(char **s);
node *p_f(char **s);
node *p_t(char **s);

node *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void destroy_tree(node *n)
{
    if (!n)
        return;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpexted end of input\n");
    exit(1);
}

int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

node *p_e(char **s)
{
    node *left = p_t(s);
    if (!left)
        return NULL;
    while (accept(s, '+'))
    {
        node *right = p_t(s);
        if (!right)
        {
            destroy_tree(left);
            return NULL;
        }
        node n = (node){ADD,0,left,right};
        left = new_node(n);
        if (!left)
        {
            destroy_tree(right);
            return NULL;
        }
    }
    return left;
}

node *p_f(char **s)
{
    if(isdigit(**s))
    {
        node n = (node){VAL,**s - '0',NULL,NULL};
        (*s)++;
        return new_node(n);
    }
    if(accept(s,'('))
    {
        node *node = p_e(s);
        if(!expect(s,')'))
        {
            destroy_tree(node);
            return NULL;
        }
        return node;
    }
    unexpected(**s);
    return NULL;
}

node *p_t(char **s)
{
        node *left = p_f(s);
    if (!left)
        return NULL;
    while (accept(s, '*'))
    {
        node *right = p_f(s);
        if (!right)
        {
            destroy_tree(left);
            return NULL;
        }
        node n = (node){MULTI,0,left,right};
        left = new_node(n);
        if (!left)
        {
            destroy_tree(right);
            return NULL;
        }
    }
    return left;
}

int eval_tree(node *tree)
{
    switch (tree->type)
    {
    case ADD:
        return (eval_tree(tree->l) + eval_tree(tree->r));
    case MULTI:
        return (eval_tree(tree->l) * eval_tree(tree->r));
    case VAL:
        return (tree->val);
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    char *s = argv[1];
    node *tree = p_e(&s);
    if (!tree || *s)
    {
        if(*s)
            unexpected(*s);
        else
            unexpected(0);

        return (1);
    }
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
}