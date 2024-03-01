#pragma once

#include <iostream>
#include <vector>
#include <utility>

#include "inode/inode.hpp"
#include "elems.hpp"

namespace backend
{

using namespace paracl;

class and_t final : public bin_operator_t
{
        public:
                and_t (inode_u_ptr &&lhs_, inode_u_ptr &&rhs_) : bin_operator_t(std::move(lhs_), std::move(rhs_)) {}
                and_t (inode_t *lhs_, inode_t *rhs_) : bin_operator_t(lhs_, rhs_) {}
                and_t (const and_t &rhs_) = default;

                and_t (and_t &&rhs_) = default;

                and_t& operator=(and_t &&rhs_) = default;
                and_t& operator=(const and_t &rhs_) { return *this = and_t {rhs_}; }

                int execute (inode_t& scope_) override 
                { return (lhs->execute(scope_) && rhs->execute(scope_)); }
                
                inode_u_ptr clone () const override 
                { return inode_u_ptr(new and_t {lhs->clone(), rhs->clone()}); }
                
                inline void dump () const override;
};

class or_t final : public bin_operator_t
{
        public:
                or_t (inode_u_ptr &&lhs_, inode_u_ptr &&rhs_) : bin_operator_t(std::move(lhs_), std::move(rhs_)) {}
                or_t (inode_t *lhs_, inode_t *rhs_) : bin_operator_t(lhs_, rhs_) {}
                or_t (const or_t &rhs_) = default;

                or_t (or_t &&rhs_) = default;

                or_t& operator=(or_t &&rhs_) = default;
                or_t& operator=(const or_t &rhs_) { return *this = or_t {rhs_}; }

                int execute (inode_t& scope_) override
                { return (lhs->execute(scope_) || rhs->execute(scope_)); }
                
                inode_u_ptr clone () const override 
                { return inode_u_ptr(new or_t {lhs->clone(), rhs->clone()}); }
                
                inline void dump () const override;
};

//===================================================~~~DECLARATIONS~~~====================================================================

//---------------------------------------------------~~~~~~Public~~~~~~--------------------------------------------------------------------

inline void and_t::dump () const
{
        lhs->dump();
        std::cout << " && ";
        rhs->dump();
}

inline void or_t::dump () const
{
        lhs->dump();
        std::cout << " || ";
        rhs->dump();
}

}