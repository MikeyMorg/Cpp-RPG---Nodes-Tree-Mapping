cmake_minimum_required(VERSION 3.24)
project(TextBasedRPG)

set(CMAKE_CXX_STANDARD 23)

add_executable(Morgan_MichaelRPG main.cpp Story.h Node.h GameDecisionTree.h SanQuest.txt makefile)
