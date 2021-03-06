#' @export
peek_frame <- function(call_stack, position, ...) {
    UseMethod("peek_frame")
}

#' @export
peek_frame.instrumentr_call_stack <- function(call_stack, position, ...) { # nolint
    .Call(C_call_stack_peek_frame, call_stack, position)
}
