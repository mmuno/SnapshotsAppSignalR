COMPRESSOR_SRC_PATH     = src

COMPRESSOR_INCLUDE_PATH = include

COMMON_PATH  = ../../common/cpp

CCX = g++

COMPRESSOR_SRC  =   $(COMPRESSOR_SRC_PATH)/core.cpp \
                    $(COMPRESSOR_SRC_PATH)/compression.cpp

COMMON_SRC   =  ${COMMON_PATH}/timer/src/timer.cpp \
                ${COMMON_PATH}/log/src/logs.cpp \
                $(COMMON_PATH)/configloader/src/conf_loader.cpp

NAME   = compress

COMPRESSOR_OBJ  = $(COMPRESSOR_SRC:.cpp=.o)
COMMON_OBJ   = $(COMMON_SRC:.cpp=.o)

CPPFLAGS += -std=c++17 -Wall -Wextra -Iincludes -O3

CPPFLAGS += -I${COMPRESSOR_INCLUDE_PATH} -I${COMPRESSOR_INCLUDE_PATH}/gci -I${COMPRESSOR_INCLUDE_PATH}/gci/query
CPPFLAGS += -I${COMPRESSOR_INCLUDE_PATH}/gci/response -I${COMPRESSOR_INCLUDE_PATH}/network

CPPFLAGS += -I${COMMON_PATH}/timer/include -I${COMMON_PATH}/log/include -I${COMMON_PATH}/configloader/include -I${COMMON_PATH}/exception/include

all: $(NAME)

$(NAME): $(COMPRESSOR_OBJ) $(COMMON_OBJ)
	$(CCX) $(COMPRESSOR_OBJ) $(COMMON_OBJ) $(CPPFLAGS) -lpthread -lyaml-cpp -lrt -lzmq -lzstd -o $(NAME)

clean:
	rm -rf $(COMPRESSOR_OBJ) $(COMMON_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
