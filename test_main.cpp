#include <iostream>
#include <fstream>
#include <string>
#include "libxl.h"

using namespace std;
using namespace libxl;

int main(int agrc, char *argc[])
{

	//cout << "helloworld" << endl;
	fstream f;
	ifstream ifile(argc[1]);
	string temp;
	int i = 0, j=1, k = 0;

	Book* book = xlCreateBook();//����һ�������Ƹ�ʽ��XLS��Execl97-03����ʵ��,��ʹ��ǰ�����ȵ������������������excel�Ķ���
	//book->setKey(......);//��������˸ÿ⣬��������Ӧ��key����û�й�����������
	if (book)//�Ƿ񴴽�ʵ���ɹ�
	{

		Sheet* sheet = book->addSheet("Sheet1");//���һ��������
		
		for(i=0;i<30;i++)
		{
			for(j=0;j<10;j++){
				sheet->setCol(i, j, 20);//�����п���ʽ��
			}
		}
		i=0;
		j=1;
		
		if (sheet)
		{
			sheet->writeStr(j, 0, "API");
			sheet->writeStr(j, 1, "Concurrency Level");
			sheet->writeStr(j, 2, "Time taken for tests");
			sheet->writeStr(j, 3, "Complete requests");
			sheet->writeStr(j, 4, "Failed requests");
			sheet->writeStr(j, 5, "Total transferred");
			sheet->writeStr(j, 6, "Requests per second");
			sheet->writeStr(j, 7, "Time per reques(user)");
			sheet->writeStr(j, 8, "Time per reques(server)");
			j++;
			while (getline(ifile, temp))
			{
				if (temp[0] == '/'){
					f << temp << " ";
					sheet->writeStr(j, i, temp.c_str());
				}
				else if (temp.find('[') != string::npos){
	
					f << temp.substr(0, temp.find('[') - 1) << " ";
					sheet->writeStr(j, i, temp.substr(0, temp.find('[') - 1).c_str());
				}
				else if (temp.find('b') != string::npos){
	
					f << temp.substr(0, temp.find('b') - 1) << " ";
					sheet->writeStr(j, i, temp.substr(0, temp.find('b') - 1).c_str());
				}
				else if (temp.find('s') != string::npos){
					sheet->writeStr(j, i, temp.substr(0, temp.find('s') - 1).c_str());
					f << temp.substr(0, temp.find('s') - 1) << " ";
				}
				else{
					sheet->writeStr(j, i, temp.c_str());
					f << temp << " ";
				}
				i++;
				if (i == 9){
					f << " " << endl;
					i = 0;
					j++;
				}
			}
			ifile.close();
		}
		if (book->save(argc[2]))//���浽example.xls
		{
			//.....
		}
		else
		{
			std::cout << book->errorMessage() << std::endl;
		}
		book->release();//�ͷŶ��󣡣�������
	}
	
	return 0;
}

