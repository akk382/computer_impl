CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -Iinclude

BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin

COMMON_SRC = \
	src/core/utils.c \
	src/primitives/switch.c \
	src/primitives/nmos.c \
	src/primitives/pmos.c \
	src/primitives/nmos_net.c \
	src/primitives/pmos_net.c \
	src/gates/cmos.c \
	src/gates/nand.c \
	src/gates/nor.c \
	src/gates/not.c \
	src/gates/and.c \
	src/gates/or.c \
	src/gates/xor.c \
	src/combinational/mux.c \
	src/combinational/demux.c \
	src/combinational/half_adder.c \
	src/combinational/full_adder.c \
	src/combinational/two_bit_adder.c \
	src/combinational/four_bit_adder.c \
	src/combinational/four_bit_sub.c \
	src/combinational/four_bit_inc.c \
	src/combinational/four_bit_not.c \
	src/combinational/four_bit_and.c \
	src/combinational/four_bit_xor.c \
	src/combinational/comparator.c \
	src/combinational/four_bit_mux.c \
	src/combinational/four_bit_demux.c \
	src/combinational/one_to_four_demux.c \
	src/combinational/two_to_four_decoder.c \
	src/combinational/four_to_one_mux.c \
	src/combinational/four_to_two_encoder.c \
	src/sequential/sr_latch.c \
	src/sequential/gated_sr_latch.c \
	src/sequential/d_latch.c \
	src/sequential/d_flipflop.c \
	src/sequential/one_bit_reg.c \
	src/sequential/four_bit_reg.c \
	src/bus/one_bit_oe_buffer.c \
	src/bus/four_bit_oe_buffer.c \
	src/bus/bus_conflict_resolver.c \
	src/bus/four_bit_bus_conflict_resolver.c \
	src/bus/two_register_bus.c \
	src/machine/two_register_machine.c

all: two_register_machine_test

two_register_machine_test:
	$(CC) $(CFLAGS) tests/two_register_machine_test.c $(COMMON_SRC) -o $(BIN_DIR)/two_register_machine_test.exe

two_register_bus_test:
	$(CC) $(CFLAGS) tests/two_register_bus_test.c $(COMMON_SRC) -o $(BIN_DIR)/two_register_bus_test.exe

four_bit_bus_conflict_resolver_test:
	$(CC) $(CFLAGS) tests/four_bit_bus_conflict_resolver_test.c $(COMMON_SRC) -o $(BIN_DIR)/four_bit_bus_conflict_resolver_test.exe

four_bit_oe_buffer_test:
	$(CC) $(CFLAGS) tests/four_bit_oe_buffer_test.c $(COMMON_SRC) -o $(BIN_DIR)/four_bit_oe_buffer_test.exe

four_bit_reg_test:
	$(CC) $(CFLAGS) tests/four_bit_reg_test.c $(COMMON_SRC) -o $(BIN_DIR)/four_bit_reg_test.exe

clean:
	del /Q build\bin\*.exe

.PHONY: all clean two_register_machine_test two_register_bus_test four_bit_bus_conflict_resolver_test four_bit_oe_buffer_test four_bit_reg_test