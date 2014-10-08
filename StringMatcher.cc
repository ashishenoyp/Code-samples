#include "StringMatcher.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

// ------------------------------------------------------------------
// Private function definitions:
// ------------------------------------------------------------------
namespace {
    int
    get_index_for_char(const char c)
    {
        if (c >= 'A' && c <= 'Z') 
            return c - 'A';
        else if (c >= 'a' && c <= 'z') 
            return c - 'a' + 26;
        else 
            assert(!"Invalid character !!!");
    }
}

// ------------------------------------------------------------------
// Operations on the trie
// ------------------------------------------------------------------

StringMatcher::trie_node_t *
StringMatcher::trie_t::add(const char *prefix_str)
{
    if (*prefix_str == '\0') 
        return NULL;

    int str_length = strlen(prefix_str);
    int i = 0;

    StringMatcher::trie_node_t *curr_node = root_node;
    for (i = 0; i < str_length; i++) {
        int index = get_index_for_char(prefix_str[i]);
        if (!curr_node->children[index]) {
            trie_node_t *new_node = (trie_node_t *)malloc(sizeof(trie_node_t));
            assert(new_node); 
            new_node->prefix_val = -1;
            new_node->exact_val = -1;
            int j;
            for(j = 0; j < ALPHABET_SIZE; j++)
            {
                new_node->children[j] = NULL;
            }
            curr_node->children[index] = new_node;
        }
        curr_node = curr_node->children[index];
    }

    return curr_node;
}

bool
StringMatcher::trie_t::del(const char *prefix_str, bool exact_match)
{
    if (*prefix_str == '\0') 
        return false;

    int str_length = strlen(prefix_str);
    int i = 0;

    StringMatcher::trie_node_t *curr_node = root_node;
    for (i = 0; i < str_length; i++) {
        int index = get_index_for_char(prefix_str[i]);
        if (curr_node->children[index]) {
            if (!prefix_str[i]) {
                // Last character of input string prefix_str
                if (exact_match) {
                   if (curr_node->children[index]->exact_val != -1) {
                       curr_node->children[index]->exact_val = -1;
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    if (curr_node->children[index]->prefix_val != -1) {
                        curr_node->children[index]->prefix_val = -1;
                        return true;
                    } else {
                        return false;
                    }
                }
            }
            curr_node = curr_node->children[index];
        } else {
            return false;
        }
    }
    return false;
}

int 
StringMatcher::trie_t::lookup(const char *input) const
{
    if (*input == '\0') 
        return -1;

    int str_length = strlen(input);
    int i = 0;

    StringMatcher::trie_node_t *curr_node = root_node;
    for (i = 0; i < str_length; i++) {
        int index = get_index_for_char(input[i]);
        if (!curr_node->children[index])
            return -1;
        curr_node = curr_node->children[index];
    }

    if (curr_node->exact_val != -1)
        return curr_node->exact_val;
    else
        return curr_node->prefix_val;
}

// Public function definitions:
// ------------------------------------------------------------------
StringMatcher::StringMatcher()
{
}

StringMatcher::~StringMatcher()
{
}

void
StringMatcher::add_exact_match(const char *exact_str, int id)
{
    assert(id > 0);
    assert(exact_str[0]);
    StringMatcher::trie_node_t *node = trie.add(exact_str);
    node->exact_val = id;
}

void
StringMatcher::add_prefix_match(const char *prefix_str, int id)
{
    assert(id > 0);
    assert(prefix_str[0]);
    StringMatcher::trie_node_t *node = trie.add(prefix_str);
    node->prefix_val = id;
}

int
StringMatcher::lookup(const char *input) const
{
    return trie.lookup(input);
}

bool
StringMatcher::delete_exact_match(const char *exact_str)
{
    return trie.del(exact_str, true);
}

bool
StringMatcher::delete_prefix_match(const char *prefix_str)
{
    return trie.del(prefix_str, false);
}
