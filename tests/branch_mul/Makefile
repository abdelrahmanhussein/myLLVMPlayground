PASS_NAME ?= instructionModifier
PASS_DIR ?= $(HOME)/myllvmspace/$(PASS_NAME)/build
PASS_LIB = $(PASS_DIR)/lib$(PASS_NAME).so

CXX = clang++
OPT = opt

.PHONY: all default build_pass generate_unmodified_ir generate_modified_ir generate_executable test test_only clean

default: all
all: runTest

# Only re-run cmake if the build directory or cache doesn't exist
$(PASS_DIR)/CMakeCache.txt:
	mkdir -p $(PASS_DIR)
	cd $(PASS_DIR) && cmake .. -G Ninja

build_pass: $(PASS_DIR)/CMakeCache.txt
	ninja -C $(PASS_DIR)

unmodified.ll: *.cpp
	$(CXX) -S -emit-llvm $< -o $@

generate_unmodified_ir: unmodified.ll

modified.ll: unmodified.ll build_pass
	$(OPT) -load-pass-plugin=$(PASS_LIB) -passes=$(PASS_NAME) $< -S -o $@

generate_modified_ir: modified.ll

test: modified.ll
	$(CXX) $< -o $@

generate_executable: test

runTest: generate_executable
	./test 10
	./test 20

runTestOnly:
	./test 10
	./test 20

clean:
	rm -f unmodified.ll modified.ll cfgWorkload