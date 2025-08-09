#!/bin/bash

# Format all C files in the project using c_formatter_42
echo "Formatting C files..."

# Format all .c and .h files
find . -name "*.c" -o -name "*.h" | while read file; do
    echo "Formatting $file"
    c_formatter_42 "$file"
done

echo "Formatting complete!"
