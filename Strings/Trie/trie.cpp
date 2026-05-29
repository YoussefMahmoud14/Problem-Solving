struct Trie{

    struct Node{
        Node*child[26];
        int Prefix , End ;

        Node(){
            memset(child,0,sizeof child);
            Prefix=0;
        }
    };

    Node*root=new Node();

    void insert(string &s){
        Node*cur=root;

        for(auto it:s){
            int idx=it-'a';

            if(cur->child[idx]==0) {
                cur->child[idx]=new Node();
            }

            cur=cur->child[idx];
            cur->Prefix++;
        }

    }

    int query(string &s)
    {
        Node*cur=root;
        for(auto it:s)
        {
            int idx=it-'a';

            if(cur->child[idx]==0) return 0;

            cur=cur->child[idx];
        }

        return cur->Prefix;
    }
};
