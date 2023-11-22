#include <iostream>
#include <string>
#include <fstream>
#include <sstream> //
#include <vector>
#include "model.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

////���캯�������������.obj�ļ�·��
//Model::Model(const char* filename) : verts_(), faces_() {
//    std::ifstream in;
//    in.open(filename, std::ifstream::in);//��.obj�ļ�
//    if (in.fail()) return;
//    std::string line;
//    while (!in.eof()) {//û�е��ļ�ĩβ�Ļ�
//        std::getline(in, line);//����һ��
//        std::istringstream iss(line.c_str());
//        char trash;
//        if (!line.compare(0, 2, "v ")) {//�����һ�е�ǰ�����ַ��ǡ�v ���Ļ��������Ƕ�������
//            iss >> trash;
//            Vec3f v;//���붥������
//            for (int i = 0; i < 3; i++) iss >> v.raw[i];
//            verts_.push_back(v);//���붥�㼯
//        }
//        else if (!line.compare(0, 2, "f ")) {//�����һ�е�ǰ�����ַ��ǡ�f ���Ļ�����������Ƭ����
//            std::vector<int> f;
//            int itrash, idx;//idx�Ƕ���������itrash������������ʱ�ò�������������ͷ�������
//            iss >> trash;
//            while (iss >> idx >> trash >> itrash >> trash >> itrash) {//��ȡx/x/x��ʽ
//                idx--; // in wavefront obj all indices start at 1, not zero
//                f.push_back(idx);//�������Ƭ�Ķ��㼯
//            }
//            faces_.push_back(f);//�Ѹ���Ƭ����ģ�͵���Ƭ��
//        }
//    }
//    std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;//�����������Ƭ����
//}


Model::Model(const char *filename) : verts_(), faces_() {
    std::ifstream in;
    in.open (filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    
    while (!in.eof()) {  //
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v.raw[i];
            verts_.push_back(v); //������ͬͷ�ļ��ĳ�Ա�뺯�����Ե���
        } else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f;
            int itrash, idx;
            iss >> trash;
            while (iss >> idx >> trash >> itrash >> trash >> itrash) {
                idx--; // in wavefront obj all indices start at 1, not zero
                f.push_back(idx);
            }
            faces_.push_back(f);
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << std::endl;
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}

std::vector<int> Model::face(int idx) {
    return faces_[idx];
}

Vec3f Model::vert(int i) {
    return verts_[i];
}

