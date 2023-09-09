#include<iostream>
#include <fstream>

#include"my_math.hpp"

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/message.h>
#include <google/protobuf/text_format.h>


using namespace std;
int main(){
    cout<<"3+2="<<add(2,3)<<endl;
    cout<<"3-2="<<sub(3,2)<<endl;

    const char * file_path ="file.txt";
    ifstream fs(file_path, std::ifstream::in | std::ifstream::binary);
    if (!fs.is_open())
    {
        return false;
    }
    google::protobuf::io::IstreamInputStream input(&fs);
    google::protobuf::io::CodedInputStream codedstr(&input);
}