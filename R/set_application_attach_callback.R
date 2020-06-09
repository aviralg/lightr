
#' @export
set_application_attach_callback <- function(context, application_attach_callback, ...) { # nolint
    UseMethod("set_application_attach_callback")
}

#' @export
set_application_attach_callback.lightr_context <- function(context, application_attach_callback, ...) {  # nolint

    stopifnot(is_undefined(application_attach_callback) ||
              is_closure(application_attach_callback) &&
              length(formals(application_attach_callback)) >= 2)

    .Call(C_context_set_application_attach_callback, context, application_attach_callback)

    invisible(NULL)
}