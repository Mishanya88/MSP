APP_NAME = comp
LIB_NAME = lib

BIN_DIR = bin
SRC_DIR = src
OBJ_DIR = obj


CFLAGS =   -Wall -Werror  -I$(SRC_DIR)/$(LIB_NAME)
APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)

all:$(OBJ_DIR) $(BIN_DIR) $(APP_PATH) $(BIN_DIR)/term $(BIN_DIR)/msp $(BIN_DIR)/mbc $(BIN_DIR)/mbr $(BIN_DIR)/signal

$(OBJ_DIR):
	mkdir $(OBJ_DIR)
$(BIN_DIR):
	mkdir $(BIN_DIR)

$(APP_PATH): $(OBJ_DIR)/main.o $(LIB_PATH)/libmySimpleComputer.a $(LIB_PATH)/libmyTerm.a $(LIB_PATH)/libmyBigChars.a $(LIB_PATH)/libmyReadkey.a
	gcc $(CFLAGS) $^ -o $@ -l mySimpleComputer -l myTerm -l myBigChars -l myReadkey -L $(OBJ_DIR)

$(BIN_DIR)/term: $(OBJ_DIR)/main_terminal.o $(LIB_PATH)/libmyTerm.a
	gcc $(CFLAGS) $^ -o $@ -lmyTerm -L $(OBJ_DIR)

$(BIN_DIR)/msp: $(OBJ_DIR)/main_msp.o $(LIB_PATH)/libmySimpleComputer.a
	gcc $(CFLAGS) $^ -o $@ -l mySimpleComputer -L $(OBJ_DIR)

$(BIN_DIR)/mbc: $(OBJ_DIR)/main_mbc.o $(LIB_PATH)/libmySimpleComputer.a $(LIB_PATH)/libmyTerm.a $(LIB_PATH)/libmyBigChars.a
	gcc $(CFLAGS) $^ -o $@ -l mySimpleComputer -l myTerm -l myBigChars -L $(OBJ_DIR)

$(BIN_DIR)/mbr: $(OBJ_DIR)/main_redkey.o $(LIB_PATH)/libmySimpleComputer.a $(LIB_PATH)/libmyTerm.a $(LIB_PATH)/libmyBigChars.a $(LIB_PATH)/libmyReadkey.a
	gcc $(CFLAGS) $^ -o $@ -l mySimpleComputer -l myTerm -l myBigChars -l myReadkey -L $(OBJ_DIR)

$(BIN_DIR)/signal: $(OBJ_DIR)/main_redkey.o $(LIB_PATH)/libmySimpleComputer.a $(LIB_PATH)/libmyTerm.a $(LIB_PATH)/libmyBigChars.a $(LIB_PATH)/libmyReadkey.a
	gcc $(CFLAGS) $^ -o $@ -l mySimpleComputer -l myTerm -l myBigChars -l myReadkey -L $(OBJ_DIR)
	
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	gcc -c $(CFLAGS) $< -o $@ 

$(OBJ_DIR)/main_terminal.o: $(SRC_DIR)/main_terminal.c
	gcc -c $(CFLAGS) $< -o $@ 
	
$(OBJ_DIR)/main_msp.o: $(SRC_DIR)/main_msp.c
	gcc -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/main_mbc.o: $(SRC_DIR)/main_bgchr.c
	gcc -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/main_redkey.o: $(SRC_DIR)/main_redkey.c
	gcc -c $(CFLAGS) $< -o $@ 		

$(LIB_PATH)/libmySimpleComputer.a: $(OBJ_DIR)/mySimpleComputer.o
	ar rcs  $@ $< 

$(OBJ_DIR)/mySimpleComputer.o: $(SRC_DIR)/$(LIB_NAME)/mySimpleComputer.c
	gcc -c $(CFLAGS) $< -o $@ 

$(LIB_PATH)/libmyTerm.a: $(OBJ_DIR)/myTerm.o
	ar rcs  $@ $< 

$(OBJ_DIR)/myTerm.o: $(SRC_DIR)/$(LIB_NAME)/myTerm.c
	gcc -c $(CFLAGS) $< -o $@ 

$(LIB_PATH)/libmyBigChars.a: $(OBJ_DIR)/myBigChars.o
	ar rcs  $@ $< 

$(OBJ_DIR)/myBigChars.o: $(SRC_DIR)/$(LIB_NAME)/myBigChars.c
	gcc -c $(CFLAGS) $< -o $@

$(LIB_PATH)/libmyReadkey.a: $(OBJ_DIR)/myReadkey.o
	ar rcs  $@ $< 

$(OBJ_DIR)/myReadkey.o: $(SRC_DIR)/$(LIB_NAME)/myReadkey.c
	gcc -c $(CFLAGS) $< -o $@ 

.PHONY: clean all

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) BigChar.txt
