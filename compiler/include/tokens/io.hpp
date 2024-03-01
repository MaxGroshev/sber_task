#pragma once

#include <iostream>
#include <vector>
#include <utility>

#include "inode/inode.hpp"
#include "elems.hpp"

namespace backend
{

using namespace paracl;

class output_t final : public uno_operator_t
{
        public:
                output_t (inode_u_ptr &&child_) : uno_operator_t(std::move(child_)) {}
                output_t (inode_t *child_) : uno_operator_t(child_) {}
                output_t (const output_t &rhs_) = default;

                output_t (output_t &&rhs_) = default;
                output_t& operator=(output_t &&rhs_) = default;
                output_t& operator=(const output_t &rhs_) { return *this = output_t {rhs_}; }

                int execute (inode_t& scope_) override { std::cout << child->execute(scope_) << '\n'; return 1; }
                inline void dump () const override;
                inode_u_ptr clone () const override
                { return inode_u_ptr(new output_t {child->clone()}); }
};

class input_t final : public uno_operator_t
{
        public:
                input_t (inode_u_ptr &&child_) : uno_operator_t(std::move(child_)) {}
                input_t (inode_t *child_)      : uno_operator_t(child_) {}

                input_t (const input_t &rhs_) = default;
                input_t (input_t &&rhs_)      = default;

                input_t& operator=(input_t &&rhs_) = default;
                input_t& operator=(const input_t &rhs_) { return *this = input_t {rhs_}; }

                int execute (inode_t& scope_) override;
                inode_u_ptr clone () const override
                { return inode_u_ptr(new input_t {child->clone()}); }

                inline void dump () const override;
};

//===================================================~~~DECLARATIONS~~~====================================================================

//---------------------------------------------------~~~~~~Public~~~~~~--------------------------------------------------------------------

inline void output_t::dump () const
{
        std::cout << " print ";
        child->dump();
}

inline int input_t::execute (inode_t& scope_) // as long as input redirected to file keyboard input does not work
{
        int val = 0; //make polymorf later
        std::cin >> val;
        return val;
}

inline void input_t::dump () const
{
        std::cout << " ? ";
        child->dump();
}

}
