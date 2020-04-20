PARSER_SRC_PATH     = src

PARSER_INCLUDE_PATH = include

COMMON_PATH  = ../../common/cpp

CCX = g++

PARSER_SRC  =   ${PARSER_SRC_PATH}/parser.cpp \
                ${PARSER_SRC_PATH}/network/udp_client_server.cpp \
                ${PARSER_SRC_PATH}/gci/gci.cpp \
                ${PARSER_SRC_PATH}/gci/response/response.cpp \
                ${PARSER_SRC_PATH}/gci/response/response_snapshotv2.cpp \
                ${PARSER_SRC_PATH}/gci/response/data_vectorizer.cpp \
                ${PARSER_SRC_PATH}/gci/query/query.cpp \
                ${PARSER_SRC_PATH}/gci/query/query_snapshotv2.cpp

COMMON_SRC   =  ${COMMON_PATH}/timer/src/timer.cpp \
                ${COMMON_PATH}/log/src/logs.cpp \
                $(COMMON_PATH)/configloader/src/conf_loader.cpp

NAME   = sensor

PARSER_OBJ  = $(PARSER_SRC:.cpp=.o)
COMMON_OBJ  = $(COMMON_SRC:.cpp=.o)

CPPFLAGS += -std=c++17 -Wall -Wextra -Iincludes -O3

CPPFLAGS += -I${PARSER_INCLUDE_PATH} -I${PARSER_INCLUDE_PATH}/gci -I${PARSER_INCLUDE_PATH}/gci/query
CPPFLAGS += -I${PARSER_INCLUDE_PATH}/gci/response -I${PARSER_INCLUDE_PATH}/network

CPPFLAGS += -I${COMMON_PATH}/timer/include -I${COMMON_PATH}/log/include -I${COMMON_PATH}/configloader/include -I${COMMON_PATH}/exception/include

all: $(NAME)

$(NAME): $(PARSER_OBJ) $(COMMON_OBJ)
	$(CCX) $(PARSER_OBJ) $(COMMON_OBJ) $(CPPFLAGS) -lpthread -lyaml-cpp -lrt -lzmq -lavrocpp -o $(NAME)

clean:
	rm -rf $(PARSER_OBJ) $(COMMON_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
