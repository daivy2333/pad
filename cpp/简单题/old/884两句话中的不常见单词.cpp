class Solution {
private:
	vector<string> list_words(string s)
    {
        vector<string> res;
        string road="";
        for (auto ch : s)
        {
            if (ch == ' ')
            {
                res.push_back(road);
                road = "";
                continue;
            }
            else
            {
                road += ch;
            }
        }
        res.push_back(road);
        return res;
    }
	
public:
    vector<string> uncommonFromSentences(string s1, string s2) {
        unordered_map<string,int> hash;
        vector<string> res;
        vector<string> com1 = list_words(s1);
        vector<string> com2 = list_words(s2);

        for (auto it : com1)
        {
            hash[it]++;
        }
        for (auto it : com2)
        {
            hash[it]++;
        }
        for (auto pair : hash)
        {
            if (pair.second == 1)
            {
				res.push_back(pair.first);
            }
        }
        return res;
    }
};