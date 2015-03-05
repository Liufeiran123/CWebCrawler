################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: crawler

# Tool invocations
crawler: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L/home/lfr/ACE_wrappers/lib -L/home/lfr/qfs/build/debug/lib -L/home/lfr/uchardet/debug/root/lib -L/home/lfr/boost_1_57_0/build/lib -L/usr/local/ActiveMQ-CPP/lib -L/home/lfr/berkeleydb/lib -L/home/lfr/oneurl/output/lib/ -L/home/lfr/oneurl/lib4/icu4c/lib -L/home/lfr/workspace3/crawler/htmlParser/lib -L/usr/lib/python2.7 -pg -o "crawler" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) crawler
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
