##=============================================================================
## [Filename]       gauss.cp
## [Project]        gauss
## [Author]         Ciro Bermudez - cirofabian.bermudezmarquez@ba.infn.it
## [Language]       Makefile
## [Created]        March 2025
## [Modified]       -
## [Description]    Main Makefile to automate the project
## [Notes]          -
## [Status]         devel
## [Revisions]      -
##=============================================================================

# ===============================  VARIABLES  =================================

# Miscellaneous variables
CUR_DATE := $(shell date +%Y-%m-%d_%H-%M-%S)

# Directories
CPP_DIR := cpp
GNU_DIR := gnuplot

# Colors
C_RED := \033[31m
C_GRE := \033[32m
C_BLU := \033[34m
C_YEL := \033[33m
C_ORA := \033[38;5;214m
NC    := \033[0m 

# ================================  TARGETS  ==================================

.DEFAULT_GOAL := all

.PHONY: all
all: help
#______________________________________________________________________________

.PHONY: cpp-gauss
cpp-gauss: ## Compile and run C++ code Gauss
	@echo -e "$(C_ORA)Compiling and Running C++ Gauss$(NC)"
	cd $(CPP_DIR)/gauss && $(MAKE) compile run
#______________________________________________________________________________

.PHONY: cpp-matt
cpp-matt: ## Compile and run C++ code Mattonella
	@echo -e "$(C_ORA)Compiling and Running C++ Mattonella$(NC)"
	cd $(CPP_DIR)/mattonella && $(MAKE) compile run
#______________________________________________________________________________

.PHONY: gnu-gauss
gnu-gauss: ## Run gnuplot Gauss code
	@echo -e "$(C_ORA)Running gnuplot gauss$(NC)"
	cd $(GNU_DIR) && gnuplot gauss.gp
#______________________________________________________________________________

.PHONY: gnu-matt
gnu-matt: ## Run gnuplot Mattonella code
	@echo -e "$(C_ORA)Running gnuplot mattonella$(NC)"
	cd $(GNU_DIR) && gnuplot mattonella.gp
#______________________________________________________________________________

.PHONY: help
help: ## Display help message
	@echo ""
	@echo "====================================================================="
	@echo "Usage: make <target> "
	@echo ""
	@echo "Available targets:"
	@echo ""
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "- make \033[36m%-15s\033[0m %s\n", $$1, $$2}'
	@echo ""
	@echo "====================================================================="
	@echo ""
