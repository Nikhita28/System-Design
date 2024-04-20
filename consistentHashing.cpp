#include <bits/stdc++.h>
using namespace std;

class consistentHashing {
    private:
        map<int, string> ring;
        set<int, string> sorted_keys;
        int replicas;
        const int PRIME_CONST = 31;
        
        int hashFunction(const string& key) {
            int hashCode = 0;
            for (int i = 0; i < key.length(); i++) {
                hashCode += key[i] * pow(PRIME_CONST, i);
            }
            return hashCode;
        }
        
        
    public:
        consistentHashing(int replicas = 3) : replicas(replicas) {}
        
        void addNode(const string& node) {
            for(int i = 0; i < replicas; i++) {
                int replica_key = hashFunction(node + "_" + to_string(i));
                ring[replica_key] = node;
                sorted_keys.insert(replica_key);
            }
        }
        
        void removeNode(const string& node) {
            for (int i = 0; i < replicas; i++) {
                int replica_key = hashFunction(node + "_" + to_string(i));
                ring.erase(replica_key);
                sorted_keys.erase(replica_key);
            }
        }
        
        string getNode(const string& key) {
            if(ring.empty())
                return "";
                
            int hashValue = hashFunction(key);
            auto it = sorted_keys.lower_bound(hashValue);
            
            if(it == sorted_keys.end()) {
                it = sorted_keys.begin();
            }
            
            return ring[*it];
        }
        
};

int main() {
    consistentHashing hashRing;
    
    hashRing.addNode("first");
    hashRing.addNode("second");
    hashRing.addNode("third");
    
    string key = "newKey";
    
    string node = hashRing.getNode(key);
    
    cout << "node: " << node;
    
    return 0;
}
