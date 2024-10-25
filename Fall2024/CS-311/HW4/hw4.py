# interpretation

expression = "17 + 3 * 8"
result = eval(expression) 
print(result)

"""
CRITIQUE:

My favorite part about interpretation is that you can execute random code without
making a full program. Like checking the decimal value of a hex number. You can
also give it code to run, like I did with eval(). This cool feature isn't
possible in C++.

One bad thing though, is that this makes code more vulnerable. People may try to
execute arbitrary code, which is harder in other languages.
"""

# Boolean expressions

print(17 == 38)
print(17 < 38)
print(not 17 == 38)
print(17 == 38 or 17 == 17)
print(17 < 38 and 17 == 38)

"""
CRITIQUE:

Much more intuitive than other languages, like C++ since it uses English.
"""

# short circuit evaluation

i = 0
arr = []
if i == 0 or arr[0]:
    print("all good")

"""
CRITIQUE:

Amazing feature. Stops code from running if previous statements confirm the
status of a bool expression. C/C++ have this too. Here, it stops the program
from crashing (arr is empty; cannot be indexed)
"""

# numeric types

small = 2
big = 54702750987328095894085032859092859408590843095843022584092
real = 17.38
imaginary = 17 + 38j

print(type(small))
print(type(big))
print(type(real))
print(type(imaginary))

"""
CRITIQUE:

Python allows ints of any size without any bounds. C/C++ can't do this even
though it's a great feature, due to types needing fixed-widths. Interpretaion
could contribute to the existence of this.

Imaginary numbers are a rare feature. It's nice seeing them here.
"""

# strings

str = "Hello Worldenheimer"
print(str)
print(str + " fjiewj")

try:
    str[7] = "\n"
except TypeError:
    print("can't change string")

"""
CRITIQUE:

strings function similar to the string class in C++, (append, indexing), but
they are immutable which is understandable. It just means some algorithms take
more space to copy one string, but everything else is fine.
"""

# arrays

import array
arr = array.array('i', [1, 2, 3])

"""
CRITIQUE:

hate them in this language. fixed-size like in c/c++, but out of place (need 
loop to print, need to specify type). Can only hold numbers.
"""

# lists

lis = [1, 'ni hao', 2, 3, [1, 2, 3]]
print(lis)

"""
CRITIQUE:

friggin' awesome! Can hold multiple types at the same time, a bunch of cool methods, like append.
Similar to vectors in C++, but not restricted to single types. A lil slow, but its Python.
"""

# tuples

tup = (1, 2, "wow")
print(tup)

try:
    tup[0] = 2
except TypeError:
    print("can't change tuple")

"""
CRITIQUE:

can hold many different types and uses indexing, like lists, but every part of
it is immutable. Similar functionality on C/C++
"""