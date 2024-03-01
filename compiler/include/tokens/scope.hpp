#pragma once

#include <vector>
#include <memory>
#include <cassert>

#include "inode/inode.hpp"
#include "symtable.hpp"

namespace backend
{

class scope_t final : public inode_t
{
        public:
                symtable_t symtable {};
                scope_t *upper_scope = nullptr;
                std::vector<std::shared_ptr<inode_t>> nodes {};

        public:
                scope_t (scope_t *upper_scope_) : upper_scope(upper_scope_) {}
                scope_t (scope_t *upper_scope_, const symtable_t &symtable_,
                         const std::vector<std::shared_ptr<inode_t>> &nodes_)
                        : symtable(symtable_), upper_scope(upper_scope_)
                {
                        for (auto it = nodes_.begin(); it != nodes_.end(); it++)
                                nodes.push_back(std::shared_ptr<inode_t>{(*it)->clone()});
                }
                scope_t (const scope_t &rhs_) : symtable(rhs_.symtable), upper_scope(rhs_.upper_scope)
                {
                        for (auto it = rhs_.nodes.begin(); it != rhs_.nodes.end(); it++)
                                nodes.push_back(std::shared_ptr<inode_t>{(*it)->clone()});
                }
                scope_t () = default;

                inline int execute (inode_t &scope_) override { execute_block(); return 0; }
                inline void execute_block ();

                inline inode_u_ptr clone () const override;
                inline scope_t*    clone_raw () const;
                inline scope_t     copy () const;

                inline void dump () const override;
                inline void dump_uppers() const;

                void set_upper_scope (scope_t *upper_scope_) { upper_scope = upper_scope_; }
                const scope_t* get_upper_scope () const { return upper_scope; }

                inline void insert (inode_t *node_);
                inline inode_t* insert_symbs (inode_t *node_, types_t symb_type);
                inline inode_t* find (const name_t &name_);
};

//===================================================~~~DECLARATIONS~~~====================================================================

//---------------------------------------------------~~~~~~Public~~~~~~--------------------------------------------------------------------

inline void scope_t::execute_block ()
{
        for (auto it = nodes.begin(); it != nodes.end(); it++) {
                if (it->get())
                        (*it)->execute(*this);
        }
}

inline inode_u_ptr scope_t::clone () const
{
        return inode_u_ptr(new scope_t {upper_scope, symtable, nodes});
}

inline scope_t* scope_t::clone_raw () const
{
        return new scope_t {upper_scope, symtable, nodes};
}


inline scope_t scope_t::copy () const
{
        return scope_t {upper_scope, symtable, nodes};
}

inline void scope_t::dump() const
{
        std::cout << "{\n";
        std::cout << "\t$Symtable:\n";
        symtable.dump();
        std::cout << "\t$\n";
        for (auto it = nodes.begin(); it != nodes.end(); it++) {
                (*it)->dump();
                std::cout << ";\n";
        }
        std::cout << "}\n";
}

inline void scope_t::dump_uppers() const
{
        if (upper_scope) {
                std::cout << "Upper Scope:\n";
                upper_scope->dump();
                std::cout << "Exit Upper Scope\n";
        }
}

inline inode_t* scope_t::insert_symbs (inode_t *node_, types_t symb_type)
{
        assert(node_);

        if (typeid(*node_) != typeid(name_t) && typeid(*node_) != typeid(var_t<int>))
                return nullptr;
                // throw std::runtime_error("Not a symbol.");
        auto name = find(*static_cast<const name_t*>(node_));
        if (name)
                return name;

        if (symb_type == types_t::UNKOWN)       // all unknown names will be zero initialized variables
                symb_type = types_t::VAR;

        return symtable.insert(node_, symb_type);
}

inline inode_t* scope_t::find (const name_t &name_)
{
        auto var = symtable.find(name_);
        if (!var && upper_scope)
                var = upper_scope->find(name_);

        return var;
}

inline void scope_t::insert (inode_t *node_)
{
        nodes.push_back(std::shared_ptr<inode_t>{node_});
        if ((typeid(*node_) == typeid(name_t) || typeid(*node_) == typeid(var_t<int>)) &&
            !find(*static_cast<const name_t*>(node_))) {
                try { insert_symbs(node_, types_t::VAR); }
                catch (std::runtime_error &re) { std::cerr << re.what(); }
        }
}

inline scope_t* create_scope (scope_t* upper_scope)  // TODO: Do we need this? (create operator in inode.cpp)
{
        return new scope_t(upper_scope);
}

}
