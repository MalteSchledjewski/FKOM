#!/bin/sh
g++ -std=c++11 -O3 -flto -march=native -o wartesystem wartesystem.cpp distributedsimulation.cpp erlangc.cpp event.cpp eventqueue.cpp packet.cpp packetgenerator.cpp packetqueue.cpp service.cpp simulation.cpp statisticsagent.cpp statisticsaggregate.cpp worker.cpp
g++ -std=c++11 -O3 -flto -march=native -o verlustsystem verlustsystem.cpp distributedsimulation.cpp erlangb.cpp event.cpp eventqueue.cpp packet.cpp packetgenerator.cpp packetqueue.cpp service.cpp simulation.cpp statisticsagent.cpp statisticsaggregate.cpp worker.cpp
g++ -std=c++11 -O3 -flto -march=native -o hybridsystem hybridsystem.cpp distributedsimulation.cpp event.cpp eventqueue.cpp packet.cpp packetgenerator.cpp packetqueue.cpp service.cpp simulation.cpp statisticsagent.cpp statisticsaggregate.cpp worker.cpp
g++ -std=c++11 -O3 -flto -march=native -o callcenter callcenter.cpp distributedsimulation.cpp erlangc.cpp event.cpp eventqueue.cpp packet.cpp packetgenerator.cpp packetqueue.cpp service.cpp simulation.cpp statisticsagent.cpp statisticsaggregate.cpp worker.cpp

