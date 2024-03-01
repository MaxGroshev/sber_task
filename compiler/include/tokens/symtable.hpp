#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <cassert>

#include "operators.hpp"
#include "elems.hpp"

namespace backend
{

struct isymb_obj_t
{
        virtual ~isymb_obj_t () = default;
        virtual std::unique_ptr<isymb_obj_t> clone () const = 0;
        virtual void dump () const = 0;
        virtual std::string get_name () const = 0;
        virtual inode_t* get_data_ptr () = 0;
};

template <typename T>
class symbol_obj_t final : public isymb_obj_t
{
        public:
                T data {};

                symbol_obj_t (T data_) : data(std::move(data_)) {}
                std::unique_ptr<isymb_obj_t> clone () const override { return std::make_unique<symbol_obj_t<T>>(*this); }
                void dump () const override { data.dump(); }
                std::string get_name () const override { return data.get_name(); }
                inode_t* get_data_ptr () override { return &data; }
};

class symbol_t
{
        std::unique_ptr<isymb_obj_t> self;

        public:
                template <typename T>
                symbol_t (T symb) : self(std::make_unique<symbol_obj_t<T>>(std::move(symb))) {}

                symbol_t (const symbol_t &symb) : self(symb.self->clone()) {}
                symbol_t (symbol_t &&symb) noexcept = default;
                symbol_t &operator=(symbol_t symb) noexcept
                {
                        self = std::move(symb.self);
                        return *this;
                }

                void dump () const { self->dump(); }
                std::string get_name () { return self->get_name(); }

                inode_t* get_symbol_ptr () { return self->get_data_ptr(); }
};

class symtable_t
{
        private:
                std::vector<symbol_t> symbs {};
                inline name_t* check_node_type (inode_t *var) const;
        public:
                template <typename It>
                symtable_t (It begin_, It end_) : symbs(begin_, end_) {}
                symtable_t () = default;

                inline inode_t* insert (inode_t *node_, types_t symb_type);
                inline inode_t* find (const name_t &name_);
                inline void dump () const;
};

//===================================================~~~DECLARATIONS~~~====================================================================

//---------------------------------------------------~~~~~~Public~~~~~~--------------------------------------------------------------------

inline inode_t* symtable_t::insert (inode_t *node_, types_t symb_type)
{
        assert(node_);

        auto node = check_node_type(node_);
        if (!node)
                return nullptr;

        if (symb_type == types_t::VAR) {
                if (typeid(*node_) == typeid(var_t<int>))
                        symbs.push_back(*static_cast<var_t<int>*>(node_));
                else
                        symbs.push_back(var_t {0, static_cast<name_t*>(node_)->get_name()});
        }
        // else if (symb_type == types_t::FUNC)

        return symbs.back().get_symbol_ptr();
}

inline inode_t* symtable_t::find (const name_t &name_)
{
        for (auto &symb : symbs) {
                if (name_.get_name() == symb.get_name())
                        return symb.get_symbol_ptr();
        }

        return nullptr;
}

inline void symtable_t::dump () const
{
        std::cout << "Visible symbols:\n";
        for (auto &symb : symbs) {
                std::cout << "\t";
                symb.dump();
                std::cout << "\n";
        }
}

//---------------------------------------------------~~~~~~Private~~~~~~--------------------------------------------------------------------

inline name_t* symtable_t::check_node_type (inode_t *node) const   // how to remove?
{
        if (typeid(*node) == typeid(name_t)) {
                return static_cast<name_t*>(node);
        } else if (typeid(*node) == typeid(var_t<int>)) {
                return static_cast<name_t*>(node);
        } else if (typeid(*node) == typeid(assign_t)) {
                if (typeid(*static_cast<assign_t*>(node)->get_lhs()) == typeid(name_t))
                        return static_cast<name_t*>(static_cast<assign_t*>(node)->get_lhs());
        }

        return nullptr;
}

}
