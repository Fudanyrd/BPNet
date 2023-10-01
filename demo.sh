demo(){
    c++ BPNet.cpp train2.cpp -o a
    c++ BPNet.cpp test2.cpp -o b
    ./a
    ./b
    cd ../
    mkdir -p "$1"
}