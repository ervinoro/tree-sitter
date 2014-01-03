#include "rules.h"
#include "transition_map.h"

using std::string;
using std::hash;

namespace tree_sitter  {
    namespace rules {
        Token::Token(const std::string &name) : name(name) {};
        
        bool Token::operator==(const Rule &rule) const {
            const Token *other = dynamic_cast<const Token *>(&rule);
            return other && (other->name == name);
        }
        
        size_t Token::hash_code() const {
            return typeid(this).hash_code() ^ hash<string>()(name);
        }
        
        rule_ptr Token::copy() const {
            return std::make_shared<Token>(*this);
        }
        
        string Token::to_string() const {
            return string("#<token '") + name + "'>";
        }
        
        void Token::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}