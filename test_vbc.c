// 1. debbug include
// 2. removed prototype  *n and add new 3 prototype 
// 3. debbug string in printf and add exit(1)
// 4. debbug condition if(**s == c)
// 5. add return(0) in funtion eval_tree

// 6. function node *p_e(char **s)
// 6.1. left = funtion p_t(s)
// 6.2. !left -> NULL
// 6.3. while(accept( s ,'+'))
// 6.3.1. right = funtion p_t(s)
// 6.3.2. !right -> destroy_tree(left) and return NULL
// 6.3.3. node n  = (node){ADD, 0, left, right};
// 6.3.4. left = new_node(n); 
// 6.3.5. !left -> destroy_tree(right) and return NULL
// 6.4. return (left)

// 7. node *p_f(char **s)
// 7.1. isdigit(**s)
// 7.1.1. node n = (node){VAL, **s - '0', NULL, NULL} -> (*s)++ -> return new_node(n)
// 7.2. if(accept(s, '('))
// 7.2.1. node *n = parse_expr(s);
// 7.2.2. if (!expect(s, ')')) -> destroy_tree(n) and return (NULL)
// 7.2.3. return (n);
// 7.3. funtion error
// 7.4. return NULL

// 8. function node *p_t(char **s) /////////
// 8.1. left = funtion p_f(s) ///////////
// 8.2. !left -> NULL
// 8.3. while(accept( s ,'*')) ///////////
// 8.3.1. right = funtion p_f(s) //////////
// 8.3.2. !right -> destroy_tree(left) and return NULL
// 8.3.3. node n  = (node){MULTI, 0, left, right}; /////////////
// 8.3.4. left = new_node(n); 
// 8.3.5. !left -> destroy_tree(right) and return NULL
// 8.4. return (left)

// 9. create pointer *s depandece to argv[1]
// 9.1. craete node *tree = p_e(&s)
// 9.2.  if (!tree || *s) 
// 9.2.1. if (*s) -> error (*s)
// 9.2.2. else -> error (0)
// 9.2.3. return (1)