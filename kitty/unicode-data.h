#pragma once
#include "data-types.h"
#include "state.h"
// START_KNOWN_MARKS
static const combining_type VS15 = 1362, VS16 = 1363;
// END_KNOWN_MARKS

bool is_combining_char(char_type ch);
bool is_ignored_char(char_type ch);
bool is_word_char(char_type ch);
bool is_CZ_category(char_type);
bool is_P_category(char_type);
bool is_non_rendered_char(char_type);
char_type codepoint_for_mark(combining_type m);
combining_type mark_for_codepoint(char_type c);

static inline bool
is_excluded_from_url(uint32_t ch) {
    if (OPT(url_excluded_characters)) {
        for (const char_type *p = OPT(url_excluded_characters); *p; p++) {
            if (ch == *p) return true;
        }
    }
    return false;
}

static inline bool
is_url_char(uint32_t ch) {
    return ch && !is_CZ_category(ch) && !is_excluded_from_url(ch);
}

static inline bool
can_strip_from_end_of_url(uint32_t ch) {
    // remove trailing punctuation
    return (is_P_category(ch) && ch != '/' && ch != '&' && ch != '-' && ch != ')' && ch != ']' && ch != '}');
}

static inline bool
is_private_use(char_type ch) {
    return (0xe000 <= ch && ch <= 0xf8ff) || (0xF0000 <= ch && ch <= 0xFFFFF) || (0x100000 <= ch && ch <= 0x10FFFF);
}


static inline bool
is_flag_codepoint(char_type ch) {
    return 0x1F1E6 <= ch && ch <= 0x1F1FF;
}
