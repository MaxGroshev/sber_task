#pragma once

#include <iostream>
#include <vector>
#include <utility>

#include "inode/inode.hpp"
#include "elems.hpp"

namespace backend
{

using namespace paracl;

class bin_operator_t : public inode_t 
{
        protected:
                inode_u_ptr lhs = nullptr;
                inode_u_ptr rhs = nullptr;

                bin_operator_t (inode_u_ptr lhs_, inode_u_ptr rhs_) : lhs(std::move(lhs_)), rhs(std::move(rhs_)) {}
                bin_operator_t (inode_t *lhs_, inode_t *rhs_) : lhs(lhs_), rhs(rhs_) {}

                bin_operator_t (bin_operator_t &&rhs_) = default;

                bin_operator_t (const bin_operator_t &rhs_) : lhs(rhs_.lhs->clone()), rhs(rhs_.rhs->clone()) {}

                bin_operator_t& operator=(bin_operator_t &rhs_) 
                { 
                        delete lhs.release(); lhs.reset(rhs_.lhs->clone().release()); 
                        delete rhs.release(); rhs.reset(rhs_.rhs->clone().release()); 
                        return *this; 
                }
                bin_operator_t& operator=(bin_operator_t &&rhs_) = default;

                virtual ~bin_operator_t () {}
        public:
                inode_t* get_lhs () { return lhs.get(); }
                inode_t* get_rhs () { return rhs.get(); }

        protected:
                virtual bool check_node_type (const inode_t *node);
};

class uno_operator_t : public inode_t 
{
        protected:
                inode_u_ptr child = nullptr;

                uno_operator_t (inode_u_ptr child_) : child(std::move(child_)) {}
                uno_operator_t (inode_t *child_)    : child(std::move(child_)) {}

                uno_operator_t (uno_operator_t &&rhs_) = default;
                uno_operator_t (const uno_operator_t &rhs_) : child(rhs_.child->clone()) {}

                uno_operator_t& operator=(uno_operator_t &rhs_)
                {
                        delete child.release(); child.reset(rhs_.child->clone().release());
                        return *this;
                }
                uno_operator_t& operator=(uno_operator_t &&rhs_) = default;

                virtual ~uno_operator_t () {}
        public:
                inode_t* get_child () { return child.get(); }

        // protected:
        //         virtual bool check_node_type (const inode_t *node);
};

class assign_t final : public bin_operator_t
{
        public:
                assign_t (inode_u_ptr &&lhs_, inode_u_ptr &&rhs_) : bin_operator_t(std::move(lhs_), std::move(rhs_)) {}
                assign_t (inode_t *lhs_, inode_t *rhs_) : bin_operator_t(lhs_, rhs_) {}
                
                assign_t (const assign_t &rhs_) = default;
                assign_t (assign_t &&rhs_)      = default;

                assign_t& operator=(assign_t &rhs_)  = default;
                assign_t& operator=(assign_t &&rhs_) = default;

                int execute (inode_t& scope_) override;
                inode_u_ptr clone () const override 
                { return inode_u_ptr(new assign_t {lhs->clone(), rhs->clone()}); }
                
                inline void dump () const override;
};

class plus_t final : public bin_operator_t
{
        public:
                plus_t (inode_u_ptr &&lhs_, inode_u_ptr &&rhs_) : bin_operator_t(std::move(lhs_), std::move(rhs_)) {}
                plus_t (inode_t *lhs_, inode_t *rhs_) : bin_operator_t(lhs_, rhs_) {}
                
                plus_t (const plus_t &rhs_) = default;
                plus_t (plus_t &&rhs_)      = default;

                plus_t& operator=(plus_t &rhs_)  = default;
                plus_t& operator=(plus_t &&rhs_) = default;
                plus_t& operator=(const plus_t &rhs_) { return *this = plus_t {rhs_}; }

                int execute (inode_t& scope_) override 
                { 
                        if (rhs == lhs) 
                                throw std::runtime_error("Children are broken."); 
                        return lhs->execute(scope_) + rhs->execute(scope_); 
                }
                inode_u_ptr clone () const override 
                { return inode_u_ptr(new plus_t {lhs->clone(), rhs->clone()}); }
                
                inline void dump () const override;
};

class minus_t final : public bin_operator_t
{
        public:
                minus_t (inode_u_ptr &&lhs_, inode_u_ptr &&rhs_) : bin_operator_t(std::move(lhs_), std::move(rhs_)) {}
                minus_t (inode_t *lhs_, inode_t *rhs_) : bin_operator_t(lhs_, rhs_) {}

                minus_t (const minus_t &rhs_) = default;
                minus_t (minus_t &&rhs_)      = default;

                minus_t& operator=(minus_t &rhs_)  = default;
                minus_t& operator=(minus_t &&rhs_) = default;
                minus_t& operator=(const minus_t &rhs_) { return *this = minus_t {rhs_}; }

                int execute (inode_t& scope_) override 
                {
                        if (rhs == lhs) 
                                throw std::runtime_error("Children are broken."); 

                        return lhs->execute(scope_) - rhs->execute(scope_); 
                }
                inode_u_ptr clone () const override 
                { return inode_u_ptr(new minus_t {lhs->clone(), rhs->clone()}); }
                
                inline void dump () const override;
};

class mul_t final : public bin_operator_t
{
        public:
                mul_t (inode_u_ptr &&lhs_, inode_u_ptr &&rhs_) : bin_operator_t(std::move(lhs_), std::move(rhs_)) {}
                mul_t (inode_t *lhs_, inode_t *rhs_) : bin_operator_t(lhs_, rhs_) {}
                
                mul_t (const mul_t &rhs_) = default;
                mul_t (mul_t &&rhs_)      = default;

                mul_t& operator=(mul_t &rhs_)  = default;
                mul_t& operator=(mul_t &&rhs_) = default;
                mul_t& operator=(const mul_t &rhs_) { return *this = mul_t {rhs_}; }

                int execute (inode_t& scope_) override 
                { 
                        if (rhs == lhs) 
                                throw std::runtime_error("Children are broken."); 
                        return lhs->execute(scope_) * rhs->execute(scope_); 
                }
                inode_u_ptr clone () const override 
                { return inode_u_ptr(new mul_t {lhs->clone(), rhs->clone()}); }
                
                inline void dump () const override;
};

class div_t final : public bin_operator_t
{
        public:
                div_t (inode_u_ptr &&lhs_, inode_u_ptr &&rhs_) : bin_operator_t(std::move(lhs_), std::move(rhs_)) {}
                div_t (inode_t *lhs_, inode_t *rhs_) : bin_operator_t(lhs_, rhs_) {}
                
                div_t (const div_t &rhs_) = default;
                div_t (div_t &&rhs_)      = default;

                div_t& operator=(div_t &rhs_)  = default;
                div_t& operator=(div_t &&rhs_) = default;
                div_t& operator=(const div_t &rhs_) { return *this = div_t {rhs_}; }

                int execute (inode_t& scope_) override
                { 
                        if (rhs == lhs) 
                                throw std::runtime_error("Children are broken."); 
                        return lhs->execute(scope_) / rhs->execute(scope_);
                }
                inode_u_ptr clone () const override 
                { return inode_u_ptr(new div_t {lhs->clone(), rhs->clone()}); }
                
                inline void dump () const override;
};

class modulo_t final : public bin_operator_t
{
        public:
                modulo_t (inode_u_ptr &&lhs_, inode_u_ptr &&rhs_) : bin_operator_t(std::move(lhs_), std::move(rhs_)) {}
                modulo_t (inode_t *lhs_, inode_t *rhs_) : bin_operator_t(lhs_, rhs_) {}
                
                modulo_t (const modulo_t &rhs_) = default;
                modulo_t (modulo_t &&rhs_) = default;

                modulo_t& operator=(modulo_t &rhs_)  = default;
                modulo_t& operator=(modulo_t &&rhs_) = default;
                modulo_t& operator=(const modulo_t &rhs_) { return *this = modulo_t {rhs_}; }

                int execute (inode_t& scope_) override
                { 
                        if (rhs == lhs) 
                                throw std::runtime_error("Children are broken."); 
                        return lhs->execute(scope_) % rhs->execute(scope_); 
                }
                inode_u_ptr clone () const override
                { return inode_u_ptr(new modulo_t {lhs->clone(), rhs->clone()}); }
                
                inline void dump () const override;
};

//===================================================~~~DECLARATIONS~~~====================================================================

//---------------------------------------------------~~~~~~Public~~~~~~--------------------------------------------------------------------

inline void assign_t::dump () const
{
        lhs->dump();
        std::cout << " = ";
        rhs->dump();
}

inline void plus_t::dump () const
{
        lhs->dump();
        std::cout << " + ";
        rhs->dump();
}

inline void minus_t::dump () const
{
        lhs->dump();
        std::cout << " - ";
        rhs->dump();
}

inline void mul_t::dump () const
{
        lhs->dump();
        std::cout << " * ";
        rhs->dump();
}

inline void div_t::dump () const
{
        lhs->dump();
        std::cout << " / ";
        rhs->dump();
}

inline void modulo_t::dump () const
{
        lhs->dump();
        std::cout << " % ";
        rhs->dump();
}

//---------------------------------------------------~~~~~~Private~~~~~~--------------------------------------------------------------------

inline bool bin_operator_t::check_node_type (const inode_t *node)
{
        if (!node)
                return false;
        if (typeid(*lhs) == typeid(name_t)) {
                return true;
        } else if (typeid(*lhs) == typeid(var_t<int>)) {
                return true;
        }
        return false;
}

}
