################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CharsetConverter.cpp \
../src/CrawlerEntity.cpp \
../src/CrawlerThread.cpp \
../src/DBManager.cpp \
../src/DocQueue.cpp \
../src/Document.cpp \
../src/EncodingDetector.cpp \
../src/Fetcher.cpp \
../src/HTTPURL.cpp \
../src/HtmlParser.cpp \
../src/ImageURLFIlter.cpp \
../src/MemPool.cpp \
../src/MessageBus.cpp \
../src/MessageComponent.cpp \
../src/RingBuffer.cpp \
../src/TP_Task.cpp \
../src/TimeoutControl.cpp \
../src/URLFilter.cpp \
../src/URLQueue.cpp \
../src/URLTest.cpp \
../src/htmlwriter.cpp \
../src/mainfile.cpp \
../src/urlstring.cpp 

OBJS += \
./src/CharsetConverter.o \
./src/CrawlerEntity.o \
./src/CrawlerThread.o \
./src/DBManager.o \
./src/DocQueue.o \
./src/Document.o \
./src/EncodingDetector.o \
./src/Fetcher.o \
./src/HTTPURL.o \
./src/HtmlParser.o \
./src/ImageURLFIlter.o \
./src/MemPool.o \
./src/MessageBus.o \
./src/MessageComponent.o \
./src/RingBuffer.o \
./src/TP_Task.o \
./src/TimeoutControl.o \
./src/URLFilter.o \
./src/URLQueue.o \
./src/URLTest.o \
./src/htmlwriter.o \
./src/mainfile.o \
./src/urlstring.o 

CPP_DEPS += \
./src/CharsetConverter.d \
./src/CrawlerEntity.d \
./src/CrawlerThread.d \
./src/DBManager.d \
./src/DocQueue.d \
./src/Document.d \
./src/EncodingDetector.d \
./src/Fetcher.d \
./src/HTTPURL.d \
./src/HtmlParser.d \
./src/ImageURLFIlter.d \
./src/MemPool.d \
./src/MessageBus.d \
./src/MessageComponent.d \
./src/RingBuffer.d \
./src/TP_Task.d \
./src/TimeoutControl.d \
./src/URLFilter.d \
./src/URLQueue.d \
./src/URLTest.d \
./src/htmlwriter.d \
./src/mainfile.d \
./src/urlstring.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/lfr/ACE_wrappers -I/home/lfr/qfs/build/debug/include/kfs -I/home/lfr/uchardet/debug/root/include/uchardet -I/usr/local/apr/include/apr-1 -I/usr/local/ActiveMQ-CPP/include/activemq-cpp-3.8.3 -I/home/lfr/berkeleydb/include -I/home/lfr/oneurl/output/include -I/home/lfr/boost_1_57_0/build/include -I/home/lfr/workspace3/crawler/htmlParser/include/htmlcxx/html -O0 -g3 -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


