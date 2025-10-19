
// 1 : add 5 functions argo and parser and parse_int and parse_string and parse_map


// 2 . function parser
// get character in file and comparison for " and digits and { if it was not print error and return(-1) 


// 3 . function parse_string
// sureness first character == '"' if it was not return(-1)
// I will fill a buffer for string 
// sureness at while that c != EOF and that was == '\\' take a step forward 
// and hide it node json give her type STRING and string at strdup(buffer) and at the end return(1)


// 4 . function parse_int
// used function fscanf(stream, "%d" , &n)
// and hide it node json give her type INTEGER and intiger at n and at the end return(1)
// if it was function fscanf() not return 1 print error and return(-1)


// 5. function parse_map
// sureness first character == '{' if it was not return(-1)
// create pair *items and size_t size and json key
// i will loop in file until he threw '}'
// i will used realloc to items
// i will fill a key for string if it return -1 i will free(items) and return(-1)
// and after make sure there is ':' if it was not will free(key.string) and free(items) and  return(-1)
// i will fill a key[size].value in function parser if it was not will free(key.string) and free(items) and  return(-1)
// fill a items[size].key to key.string and size++;
// until he threw ',' and '}' if it was not will print error and free(items) and  return(-1)
// and hide it node json give her type MAP and map.size at size and map.data at items at the end return(1)


// ✅  argo: parser
// int argo(json *dst, FILE *stream)
// 	    return (parser(dst, stream));

