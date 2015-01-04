################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CrawlerEntity.cpp \
../src/CrawlerThread.cpp \
../src/DocQueue.cpp \
../src/Document.cpp \
../src/Fetcher.cpp \
../src/HTTPURL.cpp \
../src/HtmlParser.cpp \
../src/MemPool.cpp \
../src/MessageBus.cpp \
../src/MessageComponent.cpp \
../src/RingBuffer.cpp \
../src/TP_Task.cpp \
../src/URLQueue.cpp \
../src/URLTest.cpp \
../src/mainfile.cpp \
../src/urlstring.cpp 

OBJS += \
./src/CrawlerEntity.o \
./src/CrawlerThread.o \
./src/DocQueue.o \
./src/Document.o \
./src/Fetcher.o \
./src/HTTPURL.o \
./src/HtmlParser.o \
./src/MemPool.o \
./src/MessageBus.o \
./src/MessageComponent.o \
./src/RingBuffer.o \
./src/TP_Task.o \
./src/URLQueue.o \
./src/URLTest.o \
./src/mainfile.o \
./src/urlstring.o 

CPP_DEPS += \
./src/CrawlerEntity.d \
./src/CrawlerThread.d \
./src/DocQueue.d \
./src/Document.d \
./src/Fetcher.d \
./src/HTTPURL.d \
./src/HtmlParser.d \
./src/MemPool.d \
./src/MessageBus.d \
./src/MessageComponent.d \
./src/RingBuffer.d \
./src/TP_Task.d \
./src/URLQueue.d \
./src/URLTest.d \
./src/mainfile.d \
./src/urlstring.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/lfr/ACE_wrappers -I/home/lfr/boost_1_57_0/build/include -I/home/lfr/workspace3/crawler/htmlParser/include/htmlcxx/html -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


