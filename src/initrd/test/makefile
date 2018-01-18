CC=i686-elf-gcc 
LIN=i686-elf-ld 
LDFLAGS=--oformat=binary -Ttext=0x80000000
TEST_SOURCE=test.s 
TEST_OBJF=test.o
TEST_DEST=test.bin

.PHONY: clean

$(TEST_DEST):  $(TEST_SOURCE) 
	@printf "Building test binary...." 
	@$(CC) -c $(TEST_SOURCE) -o $(TEST_OBJF) ||:
	@$(LIN) $(TEST_OBJF) -o $(TEST_DEST) $(LDFLAGS) ||:
	@printf "Done.\n" 

clean:
	@printf "Cleaning build files for the test binary...."
	@rm -rf $(TEST_OBJF) $(TEST_DEST) 
	@printf "Done.\n"
	
