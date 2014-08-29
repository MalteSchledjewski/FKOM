#!/bin/sh
echo waiting system 1
time taskset -c 0 ./wartesystem1
echo waiting system 2
time taskset -c 0-1 ./wartesystem2
echo waiting system 4
time taskset -c 0-3 ./wartesystem4
echo waiting system 8
time taskset -c 0-7 ./wartesystem8
echo waiting system 16
time taskset -c 0-15 ./wartesystem16
echo waiting system 32
time taskset -c 0-31 ./wartesystem32
echo waiting system 64
time taskset -c 0-63 ./wartesystem64
echo hybrid system 1
time taskset -c 0 ./hybridsystem1
echo hybrid system 2
time taskset -c 0-1 ./hybridsystem2
echo hybrid system 4
time taskset -c 0-3 ./hybridsystem4
echo hybrid system 8
time taskset -c 0-7 ./hybridsystem8
echo hybrid system 16
time taskset -c 0-15 ./hybridsystem16
echo hybrid system 32
time taskset -c 0-31 ./hybridsystem32
echo hybrid system 64
time taskset -c 0-63 ./hybridsystem64
echo blocking system 1
time taskset -c 0 ./verlustsystem1
echo blocking system 2
time taskset -c 0-1 ./verlustsystem2
echo blocking system 4
time taskset -c 0-3 ./verlustsystem4
echo blocking system 8
time taskset -c 0-7 ./verlustsystem8
echo blocking system 16
time taskset -c 0-15 ./verlustsystem16
echo blocking system 32
time taskset -c 0-31 ./verlustsystem32
echo blocking system 64
time taskset -c 0-63 ./verlustsystem64
echo call centre 1
time taskset -c 0 ./callcenter1
echo call centre 2
time taskset -c 0-1 ./callcenter2
echo call centre 4
time taskset -c 0-3 ./callcenter4
echo call centre 8
time taskset -c 0-7 ./callcenter8
echo call centre 16
time taskset -c 0-15 ./callcenter16
echo call centre 32
time taskset -c 0-31 ./callcenter32
echo call centre 64
time taskset -c 0-63 ./callcenter64
