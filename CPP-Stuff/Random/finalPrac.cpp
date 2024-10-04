//problem 2
Dots(int n = 0)
{
    set(n);
}

string get() const
{
    return s;
}

void set(int n)
{
    s = "";

    if(n <= 0)
    {
        return;
    }

    for(int i = 0; i < n; i++)
    {
        s += '.';
    }
}

Dots& operator++(int dummy)
{
    s += '.';
    return *this;
}

Dots& operator++()
{
    s += '.';
    return *this;
}

Dots& operator*=(int k)
{
    set(k * get());  

    return *this;
}

Dots& operator*(int k) const
{
    Dots temp(get());

    temp.set(k * temp.get());

    return temp;    
}

void print(ostream& out, bool endline = false) const
{
    out << s;

    if(endline) cout << '\n';
}


//problem 3
Person& Person::marry(Person& fiancee)
{
    if(spousePtr == nullptr || fiancee.spousePtr == nullptr || this == fiancee)
    {
        
    }
}