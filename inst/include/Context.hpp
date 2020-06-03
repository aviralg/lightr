#ifndef LIGHTR_CONTEXT_HPP
#define LIGHTR_CONTEXT_HPP

#include "Object.hpp"
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace lightr {

class Context: public Object {
  public:
    Context()
        : Object()
        , r_initializer_(nullptr)
        , r_finalizer_(nullptr)
        , r_package_entry_callback_(nullptr)
        , r_package_exit_callback_(nullptr)
        , r_call_entry_callback_(nullptr)
        , r_call_exit_callback_(nullptr)
        , r_environment_(R_GlobalEnv) {
    }

    void set_initializer(SEXP r_initializer) {
        r_initializer_ = r_initializer;
    }

    SEXP get_initializer() {
        return r_initializer_;
    }

    bool has_initializer() const {
        return r_initializer_ != nullptr;
    }

    void set_finalizer(SEXP r_finalizer) {
        r_finalizer_ = r_finalizer;
    }

    SEXP get_finalizer() {
        return r_finalizer_;
    }

    bool has_finalizer() const {
        return r_finalizer_ != nullptr;
    }

    void set_package_entry_callback(SEXP r_package_entry_callback) {
        r_package_entry_callback_ = r_package_entry_callback;
    }

    SEXP get_package_entry_callback() {
        return r_package_entry_callback_;
    }

    bool has_package_entry_callback() const {
        return r_package_entry_callback_ != nullptr;
    }

    void set_package_exit_callback(SEXP r_package_exit_callback) {
        r_package_exit_callback_ = r_package_exit_callback;
    }

    SEXP get_package_exit_callback() {
        return r_package_exit_callback_;
    }

    bool has_package_exit_callback() const {
        return r_package_exit_callback_ != nullptr;
    }

    void set_call_entry_callback(SEXP r_call_entry_callback) {
        r_call_entry_callback_ = r_call_entry_callback;
    }

    SEXP get_call_entry_callback() {
        return r_call_entry_callback_;
    }

    bool has_call_entry_callback() const {
        return r_call_entry_callback_ != nullptr;
    }

    void set_call_exit_callback(SEXP r_call_exit_callback) {
        r_call_exit_callback_ = r_call_exit_callback;
    }

    SEXP get_call_exit_callback() {
        return r_call_exit_callback_;
    }

    bool has_call_exit_callback() const {
        return r_call_exit_callback_ != nullptr;
    }

    void set_environment(SEXP r_environment) {
        r_environment_ = r_environment;
    }

    SEXP get_environment() {
        return r_environment_;
    }

    void trace_package(const std::string& package_name) {
        /* empty function list implies trace all functions of that package  */
        packages_[package_name] = std::unordered_set<std::string>();
    }

    void trace_function(const std::string& package_name,
                        const std::string& function_name) {
        auto iter = packages_.find(package_name);

        /* package has not been added before */
        if (iter == packages_.end()) {
            std::unordered_set<std::string> names;
            names.insert(function_name);
            packages_[package_name] = names;
        }
        /* package has been added with specific function names  */
        else if (iter->second.size() != 0) {
            iter->second.insert(function_name);
        }
    }

    std::vector<std::string> get_traced_packages() const {
        std::vector<std::string> keys;

        for (const auto& node: packages_) {
            keys.push_back(node.first);
        }

        return keys;
    }

    const std::unordered_set<std::string>&
    get_traced_functions(const std::string& package_name) const {
        return packages_.find(package_name)->second;
    }

    bool is_package_traced(const std::string& package_name) const {
        return packages_.find(package_name) != packages_.end();
    }

    bool is_function_traced(const std::string& package_name,
                            const std::string& function_name) const {
        auto iter = packages_.find(package_name);

        if (iter == packages_.end()) {
            return false;
        }

        const std::unordered_set<std::string>& function_names(iter->second);

        return function_names.find(function_name) != function_names.end();
    }

    static void initialize();

    static SEXP get_class();

    static std::shared_ptr<Context> from_sexp(SEXP r_context);

    static SEXP to_sexp(std::shared_ptr<Context> context);

    static void destroy_sexp(SEXP r_context);

  private:
    SEXP r_initializer_;
    SEXP r_finalizer_;
    SEXP r_package_entry_callback_;
    SEXP r_package_exit_callback_;
    SEXP r_call_entry_callback_;
    SEXP r_call_exit_callback_;
    SEXP r_environment_;
    std::unordered_map<std::string, std::unordered_set<std::string>> packages_;

    static SEXP class_;
};

using ContextSPtr = std::shared_ptr<Context>;

} // namespace lightr

#endif /* LIGHTR_CONTEXT_HPP */
