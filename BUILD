cc_library(
    name = "lib_i_comm",
    srcs = [
        "i_comm_client.cc",
        "i_comm_master.cc",
    ],
    hdrs = [
        "i_comm_client.h",
        "i_comm_master.h",
        "i_comm_receiver.hpp",
        "i_comm_sender.hpp"
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "simple_example",
    srcs = [
        "example/simple_example.cc",
    ],
    deps = [
        "lib_i_comm",
    ],
)