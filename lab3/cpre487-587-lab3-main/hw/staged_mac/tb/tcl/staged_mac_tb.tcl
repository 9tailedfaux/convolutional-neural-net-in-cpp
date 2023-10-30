
add_force {staged_mac/ACLK} -radix hex {0 0ns} {1 5000ps} -repeat_every 10000ps
add_force {staged_mac/ARESETN} -radix hex {0 0ns}
run 30ns
add_force {staged_mac/ARESETN} -radix hex {1 0ns}
run 50ns

# No Back Pressure
add_force {/staged_mac/MO_AXIS_TREADY} -radix hex {1 0ns}

# 1. Basic Single Operation
# Expected Multiplication Output: 0x0246 8ACF 0ECA 8642
# Expected Truncated Output: 0x8ACF 0ECA
add_force {/staged_mac/SD_AXIS_TVALID} -radix hex {1 0ns}
add_force {/staged_mac/SD_AXIS_TDATA} -radix hex {1111111122222222 0ns}
add_force {/staged_mac/SD_AXIS_TID} -radix hex {1 0ns}
add_force {/staged_mac/SD_AXIS_TLAST} -radix hex {1 0ns}
add_force {/staged_mac/SD_AXIS_TUSER} -radix hex {0 0ns}
run 20ns

add_force {/staged_mac/SD_AXIS_TVALID} -radix hex {0 0ns}
run 200ns


# 2. Basic Single Operation
add_force {/staged_mac/SD_AXIS_TVALID} -radix hex {1 0ns}
add_force {/staged_mac/SD_AXIS_TDATA}  -radix hex {0000AAAA0000BBBB 0ns}
add_force {/staged_mac/SD_AXIS_TID} -radix hex {2 0ns}
add_force {/staged_mac/SD_AXIS_TLAST} -radix hex {1 0ns}
add_force {/staged_mac/SD_AXIS_TUSER} -radix hex {0 0ns}
run 20ns

add_force {/staged_mac/SD_AXIS_TVALID} -radix hex {0 0ns}
run 200ns


# 3. Inital Load Single Operation
add_force {/staged_mac/SD_AXIS_TVALID} -radix hex {1 0ns}
add_force {/staged_mac/SD_AXIS_TDATA} -radix hex {0000000000001111 0ns}
add_force {/staged_mac/SD_AXIS_TID} -radix hex {2 0ns}
add_force {/staged_mac/SD_AXIS_TLAST} -radix hex {0 0ns}
add_force {/staged_mac/SD_AXIS_TUSER} -radix hex {1 0ns}
run 20ns

add_force {/staged_mac/SD_AXIS_TUSER} -radix hex {0 0ns}
add_force {/staged_mac/SD_AXIS_TLAST} -radix hex {1 0ns}
add_force {/staged_mac/SD_AXIS_TDATA} -radix hex {0000AAAA0000BBBB 0ns}
run 20ns

add_force {/staged_mac/SD_AXIS_TVALID} -radix hex {0 0ns}
run 200ns


# 4. Basic Multi Operation
add_force {/staged_mac/SD_AXIS_TVALID} -radix hex {1 0ns}
add_force {/staged_mac/SD_AXIS_TDATA} -radix hex {0000AAAA0000BBBB 0ns}
add_force {/staged_mac/SD_AXIS_TID} -radix hex {3 0ns}
add_force {/staged_mac/SD_AXIS_TLAST} -radix hex {0 0ns}
add_force {/staged_mac/SD_AXIS_TUSER} -radix hex {0 0ns}
run 20ns
add_force {/staged_mac/SD_AXIS_TVALID} -radix hex {0 0ns}
run 50ns

add_force {/staged_mac/SD_AXIS_TVALID} -radix hex {1 0ns}
add_force {/staged_mac/SD_AXIS_TDATA} -radix hex {0000AAAA0000BBBB 0ns}
run 20ns
add_force {/staged_mac/SD_AXIS_TVALID} -radix hex {0 0ns}
run 50ns

add_force {/staged_mac/SD_AXIS_TVALID} -radix hex {1 0ns}
add_force {/staged_mac/SD_AXIS_TDATA} -radix hex {0000AAAA0000BBBB 0ns}
add_force {/staged_mac/SD_AXIS_TLAST} -radix hex {1 0ns}
run 20ns
add_force {/staged_mac/SD_AXIS_TVALID} -radix hex {0 0ns}
run 100ns


# Apply Back Pressure
add_force {/staged_mac/MO_AXIS_TREADY} -radix hex {0 0ns}
run 20ns

# 5. Basic Single Operation
add_force {/staged_mac/SD_AXIS_TVALID} -radix hex {1 0ns}
add_force {/staged_mac/SD_AXIS_TDATA} -radix hex {1111111122222222 0ns}
add_force {/staged_mac/SD_AXIS_TID} -radix hex {1 0ns}
add_force {/staged_mac/SD_AXIS_TLAST} -radix hex {1 0ns}
add_force {/staged_mac/SD_AXIS_TUSER} -radix hex {0 0ns}
run 20ns

add_force {/staged_mac/SD_AXIS_TVALID} -radix hex {0 0ns}
run 200ns

add_force {/staged_mac/MO_AXIS_TREADY} -radix hex {1 0ns}
run 50ns
