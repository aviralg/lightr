#include "../inst/include/Application.hpp"
#include "../inst/include/Package.hpp"
#include "../inst/include/Function.hpp"
#include "r_api.hpp"

SEXP r_package_get_application(SEXP r_package) {
    PackageSPtr package = Package::from_sexp(r_package);
    ApplicationSPtr application = package->get_application();
    return Application::to_sexp(application);
}

SEXP r_package_get_name(SEXP r_package) {
    PackageSPtr package = Package::from_sexp(r_package);
    const std::string& name = package->get_name();
    return mkString(name.c_str());
}

SEXP r_package_get_functions(SEXP r_package) {
    PackageSPtr package = Package::from_sexp(r_package);
    const std::vector<FunctionSPtr>& functions = package->get_functions();

    int length = functions.size();
    SEXP result = PROTECT(allocVector(VECSXP, length));
    for (int index = 0; index < length; ++index) {
        SET_VECTOR_ELT(result, index, Function::to_sexp(functions.at(index)));
    }
    UNPROTECT(1);

    return result;
}

SEXP r_package_add_function(SEXP r_package, SEXP r_function) {
    PackageSPtr package = Package::from_sexp(r_package);
    FunctionSPtr function = Function::from_sexp(r_function);
    package->add_function(function);
    return r_package;
}