#include <stdio.h>
// #include <malloc.h>   // code 1 كان مستعمل malloc.h ← تبدلات بــ stdlib.h
#include <ctype.h>
#include <stdlib.h>     // تصحيح

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;

// code 1 كان فيه خطأ: node *n(**s);
// هنا تعوض بالتصريحات الصحيحة:
node *parse_expr(char **s);
node *parse_factor(char **s);
node *parse_term(char **s);

node *new_node(node n) {
    node *ret = calloc(1, sizeof(n)); // calloc جاي من stdlib.h
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void destroy_tree(node *n) {
    if (!n)
        return ;
    if (n->type != VAL) {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void unexpected(char c) {
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpexted end of input\n"); // code 1 كان مكتوب end of file
    exit(1); // جديد: code 1 ماكانش كيخرج
}

int accept(char **s, char c) {
    if (**s == c) { // code 1 كان كاتب if (**s) ← bug
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c) {
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

int eval_tree(node *tree) {
    switch (tree->type) {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
    return (0); // code 1 ماكانش هاد return
}

/* ------------------- parsing functions ------------------- */

// parse_expr = كيتعامل مع + بين terms
node *parse_expr(char **s) {
    node *left = parse_term(s);
    if (!left)
        return (NULL);
    while (accept(s, '+')) {           // خاصو يلقا '+'
        node *right = parse_term(s);   // كيعاود يجيب term آخر
        if (!right) {
            destroy_tree(left);
            return (NULL);
        }
        node n = (node){ADD, 0, left, right};
        left = new_node(n);            // كيدير node جديدة من النوع ADD
        if (!left) {
            destroy_tree(right);
            return (NULL);
        }
    }
    return (left);
}

// parse_factor = كيتعامل مع الأرقام أو (expr)
node *parse_factor(char **s) {
    if (isdigit(**s)) {                            // ملي يلقى digit
        node n = (node){VAL, **s - '0', NULL, NULL}; // VAL node
        (*s)++;
        return new_node(n);
    }
    if (accept(s, '(')) {                          // (expr)
        node *n = parse_expr(s);
        if (!expect(s, ')')) {
            destroy_tree(n);
            return (NULL);
        }
        return (n);
    }
    unexpected(**s); // كيعطي error إلا ماكانش رقم أو (
    return (NULL);
}

// parse_term = كيتعامل مع * بين factors
node *parse_term(char **s) {
    node *left = parse_factor(s);
    if (!left)
        return (NULL);
    while (accept(s, '*')) {           // خاصو يلقا '*'
        node *right = parse_factor(s);
        if (!right) {
            destroy_tree(left);
            return (NULL);
        }
        node n = (node){MULTI, 0, left, right};
        left = new_node(n);            // كيدير node جديدة من النوع MULTI
        if (!left) {
            destroy_tree(right);
            return (NULL);
        }
    }
    return (left);
}

/* ------------------- main ------------------- */

int main(int argc, char **argv) {
    if (argc != 2)
        return (1);
    char *s = argv[1];            // code 1 كان كيدير parse_expr(argv[1]) ← خطأ
    node *tree = parse_expr(&s);  // تصحيح: خاص char**
    if (!tree || *s) {            // إذا بقى شي حروف بلا parsing → error
        if (*s)
            unexpected(*s);
        else
            unexpected(0);
        return (1);
    }
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
}
