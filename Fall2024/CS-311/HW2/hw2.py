# Problem 1

from ProductionTable import *
import random

def clean(program) -> str:
    tab_size = 4
    indent = 0

    lines = program.split('\n')
    n_lines = len(lines)
    
    for i in range(0, n_lines - 1):
        if lines[i].strip() == '}':
            indent -= tab_size
        
        lines[i] = ''.join([' '] * indent) + lines[i]

        if lines[i].strip() == '{':
            indent += tab_size
        
    program = '\n'.join(lines)
    
    return program



def main() -> None:
    random.seed(None)

    table = make_table()
    program = table["prog"].expand()

    def dfs(curr_str) -> str:
        prod_start = 0
        prod_name = ""

        # resolve all non-terminals
        while prod_start != -1:    
            prod_start = curr_str.find('<')
            if prod_start == -1: 
                break
            prod_name = curr_str[prod_start + 1 : curr_str.find('>')]
            
            curr_str = curr_str.replace("<" + prod_name + ">", 
					dfs(table[prod_name].expand()), 1)

        return curr_str

    program = dfs(program)
    program = clean(program)
    
    print(program)

    # out_file = open("output.txt", "w")
    # out_file.write(program)
    # out_file.close()




main()

"""
Problem 2

The largest error with these outputs that I've noticed is that they often use 
or assign values to variables that haven't been declared. To fix this, I
would use a hash set with the key = the variable name and value = the address of
the variable. If the returned value is 0, then the variable hasn't been declared.
I'd then go line by line in the program looking for <id>'s and add them to the
table when they're declared

Another error could be type mismatches. For example, an int being assigned 17/38.
To solve this, values in the variable table will also contain the type of the
variable, as a string or an enum. Then the values can be adjusted to match the
type of the variable they're being assigned to.

"""
