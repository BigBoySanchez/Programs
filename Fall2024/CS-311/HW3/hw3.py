import sys
import string
import copy

def main() -> None:
    if(len(sys.argv) < 2):
        print("Error: No file given.")
        return
    
    try:
        in_file = open(sys.argv[1])
    except FileNotFoundError:
        print(f"Error: Could not open \"{sys.argv[1]}\"")
    
    tok_tab = {}
    
    # init sets
    chars = set(list(string.ascii_lowercase) + list(string.ascii_uppercase))
    digits = set(["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"])
    specs = set(["(", ")", "[", "]", "+", "-", "=", ",", ";"])
    whitespaces = set([" ", "\t", "\n", "\r"])
    keywords = set(["if", "then", "else", "begin", "end"])
    tok_classes = set(["keyword", "identifier", "integer", "real", "special"])

    curr_tok = ""
    possible = copy.deepcopy(tok_classes)
    for c in in_file.read() + "\n":
        if c in whitespaces or c in specs:
            if "integer" in possible:
                possible.discard("real")
            if curr_tok not in keywords:
                possible.discard("keyword")
            else:
                possible.discard("identifier")
            
            # get curr_tok into table
            if curr_tok != "":
                if curr_tok in tok_tab:
                    tok_tab[curr_tok][0] += 1
                else:
                    tok_tab[curr_tok] = [1, possible.pop()]
            
            if c in specs:
                if c in tok_tab:
                    tok_tab[c][0] += 1
                else:
                    tok_tab[c] = [1, "special"]

            curr_tok = ""
            possible = copy.deepcopy(tok_classes)

        else:
            curr_tok += c

            possible.discard("special")
            if c not in digits:
                possible.discard("integer")
                if c != '.':
                    possible.discard("real")
            if c not in chars:
                possible.discard("keyword")
                possible.discard("identifier")
    

    for tok in tok_tab:
        print(f"{tok}: [{tok_tab[tok][0]}, {tok_tab[tok][1]}]")

main()