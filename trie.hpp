#include <bits/stdc++.h>
using namespace std;

template<int char_size, int base>
struct Trie {
    struct Node {
        vector<int> next;
        vector<int> accept;
        int c;
        int common;
        Node(int c_) : c(c_), common(0){
            next.assign(char_size, -1);
        }
    };
    vector<Node> nodes;
    int root;
    Trie() : root(0) {
        nodes.push_back(Node(root));
    }
    // 単語を追加
    void insert(const string &word, int word_id) {
        int node_id = 0;
        for (int i = 0;i < word.size();i++) {
            int c = (int)(word[i] - base);
            int next_id = nodes[node_id].next[c];
            if (next_id == -1) {
                next_id = (int)nodes.size();
                nodes[node_id].next[c] = next_id;
                nodes.push_back(Node(c));
            }
            ++nodes[node_id].common;
            node_id = next_id;
        }
        ++nodes[node_id].common;
        nodes[node_id].accept.push_back(word_id);
    }
    // 単語を追加
    void insert(const string &word) {
        insert(word, nodes[0].common);
    }
    // 単語の存在確認
    bool search(const string &word, bool prefix = false) {
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); i++) {
            int c = (int)(word[i] - base);
            int &next_id = nodes[node_id].next[c];
            if (next_id == -1) {  // 次の頂点が存在しなければ終了
                return false;
            }
            node_id = next_id;
        }
        return (prefix) ? true : nodes[node_id].accept.size() > 0;  // 最後の頂点が受理状態か確認
    }
    // prefix を持つ単語が存在するかの検索
    bool start_with(const string &prefix) {
        return search(prefix, true);
    }
    // 単語数
    int count() const {
        return (nodes[0].common);
    }
    // Trie木のノード数
    int size() const {
        return ((int)nodes.size());
    }
    // 最長共通接頭辞
    string lcp() {
        string ans;
        int node_id = root;

        while (true) {
            int next_id = -1;

            for (int c = 0; c < char_size; c++) {
                if (nodes[node_id].next[c] != -1) {
                    int v = nodes[node_id].next[c];

                    if (nodes[v].common == count()) {
                        next_id = v;
                        break;
                    }
                }
            }

            if (next_id == -1) break;

            ans += char(base + nodes[next_id].c);
            node_id = next_id;
        }

        return ans;
    }
    string lcp(const string &s) {
        int node_id = root;
        string ans;

        for (char ch : s) {
            int c = ch - base;
            int next_id = nodes[node_id].next[c];

            if (next_id == -1) break;

            if (nodes[next_id].common - 1 == 0) break;
            ans += ch;
            node_id = next_id;
        }

        return ans;
    }
};
