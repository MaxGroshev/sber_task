#pragma once

#include <iostream>
#include <vector>
#include <utility>

#include "inode/inode.hpp"
#include "elems.hpp"

namespace backend
{

using namespace paracl;

class negative_t final : public uno_operator_t
{
        public:
                negative_t (inode_u_ptr &&rhs_) : uno_operator_t(std::move(rhs_)) {}
                negative_t (inode_t *child_)  : uno_operator_t(child_) {}

                negative_t (const negative_t &rhs_) = default;
                negative_t (negative_t &&rhs_)      = default;

                negative_t& operator=(negative_t &&rhs_) = default;
                negative_t& operator=(const negative_t &rhs_) { return *this = negative_t {rhs_}; }

                int execute (inode_t& scope_) override 
                { return !static_cast<bool>(child->execute(scope_)); }
                inode_u_ptr clone () const override 
                { return inode_u_ptr(new negative_t {child->clone()}); }

                inline void dump () const override;
};

class equal_t final : public bin_operator_t
{                                           
        public:
                equal_t (inode_u_ptr &&lhs_, 
                         inode_u_ptr &&rhs_) : bin_operator_t(std::move(lhs_), std::move(rhs_)) {}
                equal_t (inode_t *lhs_, inode_t *rhs_)  : bin_operator_t(lhs_, rhs_) {}

                equal_t (const equal_t &rhs_) = default;
                equal_t (equal_t &&rhs_)      = default;

                equal_t& operator=(equal_t &&rhs_) = default;
                equal_t& operator=(const equal_t &rhs_) { return *this = equal_t {rhs_}; }

                int execute (inode_t& scope_) override 
                { return (lhs->execute(scope_) == rhs->execute(scope_)); }
                inode_u_ptr clone () const override 
                { return inode_u_ptr(new equal_t {lhs->clone(), rhs->clone()}); }

                inline void dump () const override;

        private:
                // std::pair<bool, operator_t> check_lhs_type ();
                inline bool check_lhs_type ();
};

class not_equal_t final : public bin_operator_t
{
        public:
                not_equal_t (inode_u_ptr &&lhs_, 
                             inode_u_ptr &&rhs_) : bin_operator_t(std::move(lhs_), std::move(rhs_)) {}
                not_equal_t (inode_t *lhs_, inode_t *rhs_)  : bin_operator_t(lhs_, rhs_) {}
                
                not_equal_t (const not_equal_t &rhs_) = default;
                not_equal_t (not_equal_t &&rhs_)      = default;

                not_equal_t& operator=(not_equal_t &&rhs_) = default;
                not_equal_t& operator=(const not_equal_t &rhs_) { return *this = not_equal_t {rhs_}; }

                int execute (inode_t& scope_) override
                { return (lhs->execute(scope_) != rhs->execute(scope_)); }

                inline void dump () const override;
                inode_u_ptr clone () const override
                { return inode_u_ptr(new not_equal_t {lhs->clone(), rhs->clone()}); }
};

class greater_t final : public bin_operator_t
{
        public:
                greater_t (inode_u_ptr &&lhs_, 
                           inode_u_ptr &&rhs_) : bin_operator_t(std::move(lhs_), std::move(rhs_)) {}
                greater_t (inode_t *lhs_, inode_t *rhs_)  : bin_operator_t(lhs_, rhs_) {}

                greater_t (const greater_t &rhs_)      = default;
                greater_t (greater_t &&rhs_)           = default;

                greater_t& operator=(greater_t &&rhs_) = default;
                greater_t& operator=(const greater_t &rhs_) { return *this = greater_t {rhs_}; }

                int execute (inode_t& scope_) override 
                { return (lhs->execute(scope_) > rhs->execute(scope_)); }
                inode_u_ptr clone () const override
                { return inode_u_ptr(new greater_t {lhs->clone(), rhs->clone()}); }
                
                inline void dump () const override;
};

class less_t final : public bin_operator_t
{
        public:
                less_t (inode_u_ptr &&lhs_, 
                        inode_u_ptr &&rhs_) : bin_operator_t(std::move(lhs_), std::move(rhs_)) {}
                less_t (inode_t *lhs_, inode_t *rhs_)  : bin_operator_t(lhs_, rhs_) {}

                less_t (const less_t &rhs_) = default;
                less_t (less_t &&rhs_)      = default;

                less_t& operator=(less_t &&rhs_) = default;
                less_t& operator=(const less_t &rhs_) { return *this = less_t {rhs_}; }

                int execute (inode_t& scope_) override
                { return (lhs->execute(scope_) < rhs->execute(scope_)); }

                inode_u_ptr clone () const override
                { return inode_u_ptr(new less_t {lhs->clone(), rhs->clone()}); }
                
                inline void dump () const override;
};

class ls_equal_t final : public bin_operator_t
{
        public:
                ls_equal_t (inode_u_ptr &&lhs_, 
                            inode_u_ptr &&rhs_) : bin_operator_t(std::move(lhs_), std::move(rhs_)) {}
                ls_equal_t (inode_t *lhs_, inode_t *rhs_)  : bin_operator_t(lhs_, rhs_) {}

                ls_equal_t (const ls_equal_t &rhs_) = default;
                ls_equal_t (ls_equal_t &&rhs_)      = default;

                ls_equal_t& operator=(ls_equal_t &&rhs_) = default;
                ls_equal_t& operator=(const ls_equal_t &rhs_) { return *this = ls_equal_t {rhs_}; }

                int execute (inode_t& scope_) override 
                { return (lhs->execute(scope_) <= rhs->execute(scope_)); }
                
                inode_u_ptr clone () const override 
                { return inode_u_ptr(new ls_equal_t {lhs->clone(), rhs->clone()}); }
                
                inline void dump () const override;
};

class gr_equal_t final : public bin_operator_t
{
        public:
                gr_equal_t (inode_u_ptr &&lhs_, 
                            inode_u_ptr &&rhs_) : bin_operator_t(std::move(lhs_), std::move(rhs_)) {}
                gr_equal_t (inode_t *lhs_, inode_t *rhs_)  : bin_operator_t(lhs_, rhs_) {}

                gr_equal_t (const gr_equal_t &rhs_) = default;
                gr_equal_t (gr_equal_t &&rhs_) = default;
                
                gr_equal_t& operator=(gr_equal_t &&rhs_) = default;
                gr_equal_t& operator=(const gr_equal_t &rhs_) { return *this = gr_equal_t {rhs_}; }

                int execute (inode_t& scope_) override
                { return (lhs->execute(scope_) >= rhs->execute(scope_)); }
                inode_u_ptr clone () const override 
                { return inode_u_ptr(new gr_equal_t {lhs->clone(), rhs->clone()}); }
                
                inline void dump () const override;
};

//===================================================~~~DECLARATIONS~~~====================================================================

//---------------------------------------------------~~~~~~Public~~~~~~--------------------------------------------------------------------

inline void negative_t::dump () const
{
        std::cout << "!("; 
        child->dump();
        std::cout << ")"; 
}

inline void equal_t::dump () const
{
        lhs->dump();
        std::cout << " == ";
        rhs->dump();
}

inline void not_equal_t::dump () const
{
        lhs->dump();
        std::cout << " != ";
        rhs->dump();
}

inline void greater_t::dump () const
{
        lhs->dump();
        std::cout << " > ";
        rhs->dump();
}

inline void less_t::dump () const
{
        lhs->dump();
        std::cout << " < ";
        rhs->dump();
}

inline void ls_equal_t::dump () const
{
        lhs->dump();
        std::cout << " <= ";
        rhs->dump();
}

inline void gr_equal_t::dump () const
{
        lhs->dump();
        std::cout << " >= ";
        rhs->dump();
}

}
