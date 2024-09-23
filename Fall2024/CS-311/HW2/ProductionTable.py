import string
import random

class Production:
    def __init__(self, lhs) -> None:
        self.__lhs = lhs
        self.__rhs = []
        self.__weights = []

    def add_rhs(self, weights, strs) -> None:
        if len(weights) != len(strs):
            print(f"{self.__lhs}: weights and strs not the same length.\n")
            return
        
        self.__rhs += strs
        self.__weights += weights

    def expand(self) -> str:
        return random.choices(self.__rhs, self.__weights)[0]
    
    def rhs_to_string(self) -> str:
        ret = ""
        first_guy = True
        
        for guy in self.__rhs:
            if not first_guy:
                ret += ", "

            ret += guy
            first_guy = False

        return ret

def make_table() -> dict:
    ret = {}

    curr = Production("prog")

    curr.add_rhs([1], [f"int main \n{{\n<stat_list> \nreturn 0;\n}}"])
    ret["prog"] = curr

    curr = Production("stat_list")

    curr.add_rhs([1, 0.1], ["<stat>", "<stat_list>\n<stat>"])
    ret["stat_list"] = curr
    
    curr = Production("stat")
    
    curr.add_rhs([5, 10, 10, 17, 38], ["<cmpd_stat>", "<if_stat>", "<iter_stat>", "<assgn_stat>", "<decl_stat>"])
    ret["stat"] = curr

    curr = Production("cmpd_stat")

    curr.add_rhs([1], ["{\n<stat_list>\n}"])
    ret["cmpd_stat"] = curr

    curr = Production("if_stat")

    curr.add_rhs([1, 1, 1, 1, 1, 1], [
               "if(<exp>)\n<stat>"
             , "if(<exp>)\n<cmpd_stat>"
             , "if(<exp>)\n<stat>\nelse\n<stat>"
             , "if(<exp>)\n<cmpd_stat>\nelse\n<stat>"
             , "if(<exp>)\n<stat>\nelse\n<cmpd_stat>"
             , "if(<exp>)\n<cmpd_stat>\nelse\n<cmpd_stat>"])
    ret["if_stat"] = curr

    curr = Production("iter_stat")

    curr.add_rhs([1, 1], [
                  "while(<exp>)\n<stat>"
                , "while(<exp>)\n<cmpd_stat>"])
    ret["iter_stat"] = curr

    curr = Production("assgn_stat")

    curr.add_rhs([1], ["<id> = <exp>;"])
    ret["assgn_stat"] = curr

    curr = Production("decl_stat")
    
    curr.add_rhs([1, 1], ["<type> <id>;", "<type> <assgn_stat>"])
    ret["decl_stat"] = curr

    curr = Production("exp")
    
    curr.add_rhs([0.5, 1, 1], ["<exp> <op> <exp>", "<id>", "<const>"])
    ret["exp"] = curr

    curr = Production("op")

    curr.add_rhs([1, 1, 1, 1], ["+", "-", "*", "/"])
    ret["op"] = curr

    curr = Production("type")
    
    curr.add_rhs([1, 1], ["int", "double"])
    ret["type"] = curr

    curr = Production("id")
    
    curr.add_rhs([1], ["<char><char_digit_seq>"])
    ret["id"] = curr

    curr = Production("const")

    curr.add_rhs([1], ["<digit><digit_seq>"])
    ret["const"] = curr

    curr = Production("char")
    
    temp = list(string.ascii_uppercase) + list(string.ascii_lowercase)
    temp.append('_')
    curr.add_rhs([1] * len(temp), temp)
    ret["char"] = curr

    curr = Production("char_digit_seq")
    curr.add_rhs([3, 1, 1], ["", "<char><char_digit_seq>", "<digit><char_digit_seq>"])
    ret["char_digit_seq"] = curr

    curr = Production("digit_seq")
    
    curr.add_rhs([1.2, 1], ["", "<digit><digit_seq>"])
    ret["digit_seq"] = curr

    curr = Production("digit")
    curr.add_rhs([1] * 10, ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"])
    ret["digit"] = curr

    return ret

