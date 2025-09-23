#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        unordered_set<string> uniqueEmails;
        
        for (const string& email : emails) {
            string processedEmail;
            bool foundPlus = false;
            bool foundAt = false;
            
            for (char c : email) {
                if (c == '@') {
                    foundAt = true;
                    processedEmail += c;
                } else if (foundAt) {
                    processedEmail += c;
                } else if (c == '+') {
                    foundPlus = true;
                } else if (c != '.' && !foundPlus) {
                    processedEmail += c;
                }
            }
            
            uniqueEmails.insert(processedEmail);
        }
        
        return uniqueEmails.size();
    }
};
/*
原来这个就叫流式处理么
*/