#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

ostream& operator<<(ostream& os, const vector<string>& v)
{
    for(auto& x: v)
        os << x << " ";
    return os;
}

bool IsSubdomain(string_view domain, string_view subdomain) {
    int i = 0;
    int j = 0;
    while (i < subdomain.size() && j < domain.size()) {
        if (subdomain[i++] != domain[j++]) {
            return false;
        }
    }
    return (i >= subdomain.size() && domain[j] == '.')
           || (subdomain.size() == domain.size());
}


vector<string> ReadDomains() {
    size_t count;
    cin >> count;
    string word;
    getline(cin, word);
    vector<string> domains;
    for (size_t i = 0; i < count; ++i) {
        string domain;
        getline(cin, domain);
        domains.push_back(domain);
    }
    return domains;
}


int main() {
    vector<string> banned_domains = ReadDomains();
    vector<string> domains_to_check = ReadDomains();
    for (string& domain : banned_domains) {
        reverse(begin(domain), end(domain));
    }
    sort(begin(banned_domains), end(banned_domains));
    size_t insert_pos = 0;
    for (string& domain : banned_domains) {
        if (insert_pos == 0 || !IsSubdomain(domain, banned_domains[insert_pos - 1])) {
            swap(banned_domains[insert_pos++], domain);
        }
    }
    banned_domains.resize(insert_pos);
    for (string& domain : domains_to_check) {
        reverse(domain.begin(), domain.end());
        if (const auto it = upper_bound(begin(banned_domains), end(banned_domains), domain);
                it != begin(banned_domains) && IsSubdomain(domain, *prev(it))) {
            cout << "Bad"  << endl;
        } else {
            cout << "Good" << endl;
        }
    }
    return 0;
}