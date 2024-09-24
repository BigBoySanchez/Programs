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
            
            curr_str = curr_str.replace("<" + prod_name + ">", dfs(table[prod_name].expand()), 1)

        return curr_str

    program = dfs(program)
    program = clean(program)
    
    # print(program)

    out_file = open("output.txt", "w")
    out_file.write(program)
    out_file.close()




main()

# int main 
# {
#     while(00)
#     if(J9)
#     if(_L357)
#     if(g)
#     {
#         u = 6;
#     }
#     else
#     int dD = Z14;
#     return 0;
# }