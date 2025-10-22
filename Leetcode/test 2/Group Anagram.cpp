class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>>groups;
        //hashmap to call groups
        //for example: "aet" -> [eat, tea, ate] as those sorted would be aet

        for(string s : strs){ //loop for each string inside input list
            string key = s; //copy original string 
            sort(key.begin(), key.end());//sort character in string so tan -> ant etc

            //intert string 's' into group with key = sorted string
            groups[key].push_back(s); // 
        }
        //so for first 3 itteration "eat","tea","tan
        //eat is copy to s, and then sorted so eat -> aet(this is the key);
        //now afte sort its group so that aet -> [eat]

        //next itteration tea
        //tea is copy, and then sorted so tea -> aet(key);
        //now after sort its group so that aet -> [eat, tea] since its pusing s, the original string

        //so the core implemntation is it copy orignal string to key, sort key and map s to key
        //so key -> [s, s, s] 

        vector<vector<string>> result; //store finalresult
        for (auto& p : groups) { //loops through hasmap
            result.push_back(p.second); //store second , the value so not the key
                                        //for example, p first is key -> sorted string liek aet
                                        // and p second is the value -> like [eat, tea]
        }

        return result;
    }
};