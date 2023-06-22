cmake_minimum_required(VERSION 3.24)
project(library)

set(CMAKE_CXX_STANDARD 17)

add_executable(library main.cpp library.h library.cpp client.h searchFields.h clientBase.h book.h bookCollection.h borrowData.h borrowRecords.h book.cpp bookCollection.cpp client.cpp borrowData.cpp clientBase.cpp borrowRecords.cpp errors.h)
