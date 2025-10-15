
// 1 : add 5 functions
// int		argo(json *dst, FILE *stream);
// int		parser(json *dst, FILE *stream);
// int		parse_int(json *dst, FILE *stream);
// int		parse_string(json *dst, FILE *stream);
// int 	    parse_map(json *dst, FILE *stream);


// 2 . function parser
// 2.1 : int c = peek(stream);
// 2.2 : if(c == '"') return (parse_string(dst, stream))
// 2.3 : else if (isdigit(c) || c == '-') return (parse_int(dst, stream))
// 2.4 : else if (c == '{') return (parse_map(dst, stream))
// 2.5 : else { unexpected(stream); return (-1);}

// 3 . function parse_string
// 3.1 : create 3 variable => char buffer[4096] ; char c ;  int i ;
// 3.2 : if not first character == ' " ' => return (-1) ;
// 3.3 : i = 0 => loop unlimited
// 3.3.1          : c = getc(stream)
// 3.3.2          : if (c == EOF) =>  unexpected(stream) => return (-1);
// 3.3.3          : if (c == '"') =>	break 
// 3.3.4          : if (c == '\\') => 3.3.1 => if (c == EOF) { unexpected(stream) ; return (-1) }
// 3.3.5          : buffer[i++] = c
// 3.4 :  buffer[i] = '\0'
// 3.5 : dst->type = STRING;
// 3.6 : dst->string = strdup(buffer)
// 3.7 : return (1)

// 4 . function parse_int
// 4.1 : add var int n
// 4.2 : if(fscanf(stream, "%d", &n) == 1)
// 4.2.1 : dst->type = INTEGER ; dst->integer = n ; return (1);
// 4.3 : unexpected(stream);
// 4.4 : return(-1);

// 5. function parse_map
// 5.1 : if(!expect(stream, '{')) => return(-1)
// 5.2 : pair *items = NULL ; size_t size = 0 ; json key ;
// 5.3 : while(!accept(stream, '}'))
// 5.3.1        :  items = realloc(items, sizeof(pair) * (size + 1));
// 5.3.2        :  if (parse_string(&key, stream) == -1) { free(items) ; return (-1) }
// 5.3.3        :  if (!expect(stream, ':')){ free(key.string);	free(items); return (-1);}
// 5.3.4        :  if (parser(&items[size].value, stream) == -1) {free(key.string); free(items); return (-1); }
// 5.3.5        :  items[size].key = key.string;
// 5.3.6        :  size++;
// 5.3.7        :  if (!accept(stream, ',') && peek(stream) != '}'){ unexpected(stream); free(items); return (-1) }
// 5.4 : dst->type = MAP;  
// 5.5 : dst->map.size = size;
// 5.6 : dst->map.data = items;
// 5.7 : return (1);

// ✅  argo: parser
// int argo(json *dst, FILE *stream)
// 	    return (parser(dst, stream));