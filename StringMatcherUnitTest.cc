// --------------------------------------------
// AUTHOR: Ashish Shenoy (ashishenoyp@gmail.com)
// --------------------------------------------

#include "StringMatcher.h"
#include <stdio.h>
#include <assert.h>

int
main(int argc, char **argv)
{
    // Basic exact match
    {
        StringMatcher matcher;
        matcher.add_exact_match("contactus", 1);
        assert(matcher.lookup("contactus") == 1);
    }

    // Basic prefix test
    {
        StringMatcher matcher;
        matcher.add_prefix_match("img", 1);
        assert(matcher.lookup("imgcutepuppy") == 1);
        assert(matcher.lookup("htmlcutepuppy") == -1);
    }

    // Basic longest match test
    {
        StringMatcher matcher;
        matcher.add_prefix_match("img", 1);
        matcher.add_prefix_match("imghd", 2);
        assert(matcher.lookup("imgcutepuppy") == 1);
        assert(matcher.lookup("imghdcutepuppy") == 2);
    }

    return 0;
}
