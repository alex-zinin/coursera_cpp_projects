template<typename T> T Sqr(const T &con);

template<typename First, typename Second> pair<First, Second> operator*(const pair<First,Second> &lhs, const pair<First,Second> &rhs);
template<typename T> vector<T> operator*(const vector<T> &lhs, const vector<T> &rhs);
template<typename K,class T> map<K,T> operator*(const map<K,T> &lhs, const map<K,T> &rhs);







template<typename First, typename Second>
pair<First, Second> operator*(const pair<First,Second> &lhs, const pair<First,Second> &rhs)
{

First f = lhs.first*rhs.first;
Second s = lhs.second*rhs.second;
    return(make_pair(f,s));
}

template<typename K, class T>
map<K,T> operator*(const map<K,T> &lhs, const map<K,T> &rhs)
{
    map<K,T> m;
    for(const auto &[key,value]: lhs)
    {
        m[key] = value*value;
    }
    return(m);
}

template<typename T>
vector<T> operator*(const vector<T> &lhs, const vector<T> &rhs)
{
    vector<T> v;
    for(int i = 0; i < lhs.size(); i++)
    {
        v.push_back((lhs[i])*(rhs[i]));
    }
    return(v);
}




template<typename T>
T Sqr(const T &con)
{
    return(con*con);
}
