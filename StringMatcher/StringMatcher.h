// --------------------------------------------
// AUTHOR: Ashish Shenoy (ashishenoyp@gmail.com)
// --------------------------------------------

#ifndef STRINGMATCHER_H
#define STRINGMATCHER_H

#define ALPHABET_SIZE 52

/// Header for a class that manages the mapping between a
/// string of alphabets and an id.
class StringMatcher
{
public:
    /// Constructor/Destructor
    StringMatcher();
    ~StringMatcher();

    /// Add an exact string match, i.e. “abc” in
    /// the documentation above. Adding an exact match for an
    /// existing `exact_str` will overwrite the previous `id`.
    /// @param exact_str string to match with the id.
    /// @param id (>=0) that is mapped to this string.
    void add_exact_match(const char* exact_str, int id);

    /// Add a prefix string match i.e. “fas” in
    /// the documentation above. Adding a prefix match for an
    /// existing `prefix_str` will overwrite the previous `id`.
    /// @param prefix_str to match with the id.
    /// @param id (>=0) that is mapped to this string.
    void add_prefix_match(const char* prefix_str, int id);

    /// Get the id for the specified string.
    /// @param input to lookup the id for
    /// @returns -1 if there is no match or the id

    int lookup(const char* input) const;

    /// Delete the exact matches for the given string, i.e. if we have
    /// an add_exact_match(“str”, 2), delete_exact_match will remove the
    /// match of “str” to 2.
    /// @param exact_str exact match to delete.
    /// @return true if a match was deleted.

    bool delete_exact_match(const char* exact_str);
    /// Delete the prefix matches for the given string, i.e. if we have
    /// a add_prefix_match(“str”, 2), delete_prefix_match will remove the
    /// match of “str” to 2.

    /// @param prefix_str prefix match to delete.
    /// @return true if a match was deleted.
    bool delete_prefix_match(const char* prefix_str);

private:
    // trie [prefix tree data structure] node
    class trie_node_t
    {
    public:
        trie_node_t();
        ~trie_node_t();
        int prefix_val;
        int exact_val;
        trie_node_t *children[ALPHABET_SIZE];
    };

    class trie_t
    {
    public:
        StringMatcher::trie_node_t *add(const char *prefix_str);
        bool del(const char *prefix_str, bool exact_match);
        int lookup(const char *input) const;
    private:
        StringMatcher::trie_node_t *root_node;
    };

    trie_t trie;
};

#endif // STRINGMATCHER_H
