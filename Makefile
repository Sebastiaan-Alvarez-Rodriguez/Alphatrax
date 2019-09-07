CXX      ?= g++
SRC      = src
OBJ      = obj

WARNINGS = -Wall -Wextra -pedantic -O3
IDIRS    = -I$(SRC)
LDIRS    = 
CXXFLAGS   = $(IDIRS) -std=c++11 $(WARNINGS) $(LDIRS)

find = $(shell find $1 -type f -name $2 -print 2>/dev/null)

SRCS := $(call find, $(SRC)/, "*.cpp")
OBJECTS := $(SRCS:%.cpp=$(OBJ)/%.o)
EXEC = exec


CLEAR  = [0m
CYAN   = [1;36m
GREEN  = [1;32m
YELLOW = [1;33m
WHITE  = [1;37m

HAVE := $(call find, $(OBJ)/, "*.o")
TOTAL := $(words $(SRCS) . )
xoutofy = $(or $(eval PROCESSED := $(PROCESSED) . $(HAVE)),$(info $(WHITE)[$(YELLOW)$(words $(PROCESSED))$(WHITE)/$(YELLOW)$(TOTAL)$(WHITE)] $1$(CLEAR)))

MAKEFLAGS = -j

.PHONY: all git c clean

$(EXEC): $(OBJECTS)
	@$(call xoutofy,$(GREEN)Linking $@)
	$(CXX) $(OBJECTS) -o $@ $(CXXFLAGS)

$(OBJ)/%.o: %.cpp
	@$(call xoutofy,$(CYAN)Compiling $<)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@echo Cleaning...
	@rm -rf $(OBJ) $(EXEC)
	@echo Done!

git: clean
	git add *
	git commit
	git push

c: clean