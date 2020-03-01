template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border)
{
    vector<T> vect;
    for(auto it = begin(elements); it != end(elements); ++it)
    {
        if(*it > border)
            vect.push_back(*it);
    }
    return(vect);
}
