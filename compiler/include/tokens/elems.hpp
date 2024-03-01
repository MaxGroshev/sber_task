#pragma once

#include <iostream>

#include "inode/inode.hpp"

namespace backend
{

using namespace paracl;

template <typename T>
class number_t final : public inode_t
{
        private:
                T data {};
        public:
                number_t (T data_) : data(data_) {}

                int execute (inode_t &scope_) override { return data; }
                inode_u_ptr clone () const override
                { return inode_u_ptr(new number_t {data}); }

                number_t& operator+=(const number_t &rhs_) { data += rhs_.data; return *this; }
                number_t& operator-=(const number_t &rhs_) { data -= rhs_.data; return *this; }

                T get_data () { return data; }

                void dump () const override { std::cout << data; }
};

template <typename T>
number_t<T> operator+(const number_t<T> &rhs_, const number_t<T> &lhs_)
{
        number_t tmp(rhs_);
        tmp += lhs_;
        return tmp;
}

template <typename T>
number_t<T> operator-(const number_t<T> &rhs_, const number_t<T> &lhs_)
{
        number_t tmp(rhs_);
        tmp -= lhs_;
        return tmp;
}

class name_t : public inode_t
{
        protected:
                std::string name {};
        public:
                name_t () = default;
                name_t (std::string name_)   : name(name_) {}
                name_t (const name_t &name_) : name(name_.name) {}
                name_t (name_t &&name_)      : name(std::move(name_.name)) {}

                int execute (inode_t &scope_) override;
                inode_u_ptr clone () const override
                { return inode_u_ptr(new name_t {name}); }

                virtual ~name_t () {}

                std::string get_name () const { return name; }

                void dump () const override { std::cout << name; }
};

template <typename T>
class var_t final : public name_t
{
        private:
                T data {};
        public:
                var_t (T data_, std::string name_) : name_t(name_), data(data_) {}

                int execute (inode_t &scope_) override { return get_data(); }
                inode_u_ptr clone () const override
                { return inode_u_ptr(new var_t {data, name}); }

                var_t (const var_t &rhs_) = default;

                var_t& operator+=(const var_t &rhs_) { data += rhs_.data; return *this; }
                var_t& operator-=(const var_t &rhs_) { data -= rhs_.data; return *this; }

                var_t& operator=(const var_t &rhs_) { data = rhs_.data; return *this; }
                var_t& operator=(const T &data_)    { data = data_;     return *this; }

                T get_data () const { return data; }
                std::string get_name () const { return name; }

                void dump () const override { std::cout << name << "(" << data << ")"; }
};

template <typename T>
inline var_t<T> operator+(const var_t<T> &rhs_, const var_t<T> &lhs_)
{
        var_t tmp(rhs_);
        tmp += lhs_;
        return tmp;
}

template <typename T>
inline var_t<T> operator-(const var_t<T> &rhs_, const var_t<T> &lhs_)
{
        var_t tmp(rhs_);
        tmp -= lhs_;
        return tmp;
}

template <typename T>
inline inode_t* create_number (T data)                 { return new number_t<T> {data}; }
inline inode_t* create_name (std::string &name)        { return new name_t {name}; }
template <typename T>
inline inode_t* create_var (T data, std::string &name) { return new var_t<T> {data, name}; }

}
