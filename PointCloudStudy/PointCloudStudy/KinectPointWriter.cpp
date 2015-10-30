#include "KinectPointIO.h"
template<typename T_n>
void KinectPointIO::saveBinary(std::vector<T_n>& pointsList){
	//**************************************************
	//�t�@�C��������
	//**************************************************
	namespace pt = boost::posix_time;
	namespace gg = boost::gregorian;

	// �t�H�[�}�b�g�̎w��
	// facet �̓X�g���[�����Ŏ����I�� delete �����
	auto facet = new pt::time_facet("%Y%m%d_%H%M%S");
	std::stringstream ss;
	ss.imbue(std::locale(std::cout.getloc(), facet));

	// ���݂̎������擾
	auto now_time = pt::second_clock::local_time();
	ss << computerName << "_";
	ss << "pointcloud_";
	ss << now_time;
	ss << ".k3d";

	saveBinary(ss.str(), pointsList);
}
template<typename T_n>
void KinectPointIO::saveBinary(std::string filepath, std::vector<T_n>& pointsList){
	//**************************************************
	//�����o���t�@�C���ݒ�
	//**************************************************
	std::ofstream ofs(filepath, std::ios_base::out | std::ios_base::binary);
	if(ofs.fail()) {
		std::cout << "�t�@�C���I�[�v�����s" << std::endl;
		return;
	}

	//**************************************************
	//�e���̏o��
	//**************************************************
	for(auto p : pointsList) {
		ofs.write((const char*)&p, sizeof(p));
	}

	ofs.close();

	std::cout << filepath << "��ۑ����܂���" << std::endl;
}


void KinectPointIO::savePoints(Kinect2Sensor &kinect){
	auto p = convCamera2Points(kinect);
	saveBinary(p);
}

void KinectPointIO::savePoints(std::string filepath, Kinect2Sensor &kinect){
	auto p = convCamera2Points(kinect);
	saveBinary(filepath, p);
}