SHELL       := /bin/bash

# custom variables
PLATFORM    := osx
V8_VERSION  := 8.3-lkgr
REPOS_URL   := https://github.com/Vincent0700/learning-v8

# v8 path
V8_URL      := $(REPOS_URL)/releases/download/libv8-$(V8_VERSION)-$(PLATFORM)/$(V8_VERSION).tar.gz
V8_DIR      := ./src/third-party/v8
V8_CUR_DIR  := $(V8_DIR)/$(V8_VERSION)
V8_INCLUDE  := $(V8_CUR_DIR)/include
V8_LIBRARY  := $(V8_CUR_DIR)/lib/$(PLATFORM)

# define standard colors
BLACK       := $(shell tput -Txterm setaf 0)
RED         := $(shell tput -Txterm setaf 1)
GREEN       := $(shell tput -Txterm setaf 2)
YELLOW      := $(shell tput -Txterm setaf 3)
LIGHTPURPLE := $(shell tput -Txterm setaf 4)
PURPLE      := $(shell tput -Txterm setaf 5)
BLUE        := $(shell tput -Txterm setaf 6)
WHITE       := $(shell tput -Txterm setaf 7)
RESET       := $(shell tput -Txterm sgr0)
BEGIN_HL    := \033[44;30m
END_HL      := \033[0m

# install v8 libs
define install_deps
  cd $(V8_DIR)
  wget $(V8_URL)
  tar xzvf $(V8_VERSION).tar.gz
  rm -rf $(V8_VERSION).tar.gz
endef

# build with v8
define build
  clang++ $(1) -o $(2) \
    -I$(V8_INCLUDE) \
    -L$(V8_LIBRARY) -lv8_monolith \
    -std=c++11
endef

# build with v8 & run
define test
  @echo ""
  @echo -e "$(BEGIN_HL) TEST $(END_HL) src/test/hello-world.cc"
  @echo "$(YELLOW)-------------------------------------$(RESET)"
  @$(call build, $(1), $(2))
  @$(2)
endef

.DEFAULT_GOAL := run

clean: # clean ./dist
	@rm -rf dist
	@mkdir -p dist

check: # check & install deps
	@if [ ! -d "$(V8_CUR_DIR)" ]; then \
		mkdir -p $(V8_DIR); \
		echo -e "\n$(BEGIN_HL) INFO $(END_HL) Installing Deps.\n"; \
		cd $(V8_DIR); \
		rm -rf $(V8_VERSION).tar.gz; \
		wget $(V8_URL) -q --show-progress; \
		tar xzvf $(V8_VERSION).tar.gz; \
		rm -rf $(V8_VERSION).tar.gz; \
		echo -e "\n$(GREEN)Done!$(RESET)"; \
	fi

run:
	@make clean
	@echo -e "\n$(BEGIN_HL) INFO $(END_HL) build & run src/main.cc"
	@echo "$(YELLOW)-----------------------------------------$(RESET)"
	@$(call build, src/main.cc, dist/main)
	@./dist/main
