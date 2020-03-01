bool cmp(const string& lhs, const string& rhs )
{
    return lhs[0] < rhs[0];
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix)
{
    RandomIt bgit, enit;
    bool flag = false;
    string str;
    str[0] = prefix;
    pair<RandomIt, RandomIt> par;
    par = equal_range(range_begin, range_end, str, cmp);
        return (par);
}
