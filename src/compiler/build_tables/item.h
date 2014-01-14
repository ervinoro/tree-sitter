#ifndef __TreeSitter__item__
#define __TreeSitter__item__

#include <string>
#include "rule.h"
#include <set>
#include <unordered_set>

namespace tree_sitter {
    class Grammar;
    
    namespace build_tables {
        class Item;

        class Item {
        public:
            Item(const std::string &rule_name, const rules::rule_ptr rule, int consumed_sym_count);
            static Item at_beginning_of_rule(const std::string &rule_name, const Grammar &grammar);
            static Item at_beginning_of_token(const std::string &rule_name, const Grammar &grammar);

            bool operator==(const Item &other) const;
            bool operator<(const Item &other) const;
            bool is_done() const;
            int next_sym_count() const;

            const std::string rule_name;
            const rules::rule_ptr rule;
            const int consumed_sym_count;
        };
        
        typedef std::set<Item> ItemSet;
        
        std::ostream& operator<<(std::ostream &stream, const Item &item);        
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::build_tables::Item> {
        size_t operator()(const tree_sitter::build_tables::Item &item) const {
            return
                hash<std::string>()(item.rule_name) ^
                hash<tree_sitter::rules::Rule>()(*item.rule) ^
                hash<int>()(item.consumed_sym_count);
        }
    };

    template<>
    struct hash<const tree_sitter::build_tables::ItemSet> {
        size_t operator()(const tree_sitter::build_tables::ItemSet &item_set) const {
            size_t result = hash<size_t>()(item_set.size());
            for (auto item : item_set)
                result ^= hash<tree_sitter::build_tables::Item>()(item);
            return result;
        }
    };
}


#endif