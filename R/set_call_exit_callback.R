
set_call_exit_callback <- function(context, call_exit_callback, ...) {
    UseMethod("set_call_exit_callback")
}

set_call_exit_callback.instrumentr_context <- function(context, call_exit_callback, ...) {  # nolint

    stopifnot(is_undefined(call_exit_callback) ||
              is_closure(call_exit_callback) &&
              has_parameters(call_exit_callback, 5))

    .Call(C_context_set_call_exit_callback,
          context,
          call_exit_callback)

    invisible(NULL)
}
