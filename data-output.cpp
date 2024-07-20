#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;
// ��ȡ�༶�б��洢��������
vector<string> readClassList(const string& classListFileName) {
    vector<string> classList;
    ifstream file(classListFileName);
    if (file.is_open()) {
        string className;
        while (getline(file, className)) {
            classList.push_back(className);
        }
        file.close();
    }
    return classList;

}
//д��data.txt
void writeDataToFile(const string& fileName, int weekNumber, const map<int, vector<string>>& absentData, const map<int, vector<string>>& lateData,const map<int, vector<string>>& leaveData) {
    ofstream file(fileName);
    if (file.is_open()) {
        file << "����:" << weekNumber << endl;

        if (!absentData.empty()) {
            file << "����" << endl;
            for (const auto& entry : absentData) {
                for (const string& info : entry.second) {
                    file << info << endl;
                }
            }
        }

        if (!lateData.empty()) {
            file << "�ٵ�" << endl;
            for (const auto& entry : lateData) {
                for (const string& info : entry.second) {
                    file << info << endl;
                }
            }
        }
        if (!leaveData.empty()) {
            file << "���" << endl;
            for (const auto& entry : leaveData) {
                for (const string& info : entry.second) {
                    file << info << endl;
                }
            }
        }
        file.close();
        cout << "������д���ļ� " << fileName << endl;
    } else {
        cerr << "�޷����ļ� " << fileName << " ��д������." << endl;
    }
}

int main() 
{
    //system("chcp 65001");
    int weekNumber;
    string currentClass;  // ���ڸ��ٵ�ǰ�İ༶
    map<int, vector<string>> absentData;  // ������Ϣ����
    map<int, vector<string>> lateData;    // �ٵ���Ϣ����
    map<int, vector<string>> leaveData;    // �ٵ���Ϣ����
    cout << "������������";
    cin >> weekNumber;
    int cnt = 0;
    string data;
    //int flag=0;
    int cnt_k=0;
    int flag_text=0;
    // ��ȡ�༶�б�
    vector<string> classList = readClassList("class.txt");
    set<string> recordedClasses;
    string str;
    while (true) 
    { //cnt==0�����ǵ�һ��¼��˰������
        if (cnt == 0) {
            cout << "�༶��";
            cin >> currentClass;
            data = currentClass + "��:";
            flag_text=0; 
        }//��ʼ¼��༶�����в���ѡ��
        if(currentClass=="-1")
        {
            data.clear();
            break;
        }
        int choice;
        if(cnt==0)
        {
            cout << "��ѡ����� (1: ����, 2: �ٵ�, 3: ��� ): ";
            cin>>choice;
            cout<<"-----------------------------------------"<<endl;
            if(choice==1)
            {
            	str="����";
            	cout<<currentClass<<"��"<<str<<"¼�룺"<<endl;
            }else if(choice==2)
            {
            	str="�ٵ�";
            	cout<<currentClass<<"��"<<str<<"¼�룺"<<endl;
            }else if(choice==3)
            {
                str="���";
            	cout<<currentClass<<"��"<<str<<"¼�룺"<<endl;
            }
            
        }//���¼���˾��ٽ���ѡ��ѡ����λ�ٵ�
        
        if(choice==1)   str="����";
        if(choice==2)   str="�ٵ�";
        if(choice==3)   str="���";
        
        if (choice == 0) {
        	cout<<">>"<<"��ѡ�����˳�ϵͳ"<<endl; 
            break;
        }
        string studentName, dayTime;
        cout << "������";
        cin >> studentName;
        if(choice==2)	flag_text=1; 
        if(choice==3)   flag_text=-1;
        if(studentName=="-1")
        {
        	// ��¼��¼��İ༶
            recordedClasses.insert(currentClass);
            cnt=0;
            data.erase(data.end() - 1);
            cout<<">>"<<currentClass<<"��������ȫ��¼����ϣ�"<<endl;
            cout<<"-----------------------------------------"<<endl;
            cnt_k++;
            cout<<"----�������"<<cnt_k<<"���༶��¼�룬�ܰ���Ŷ~-----"<<endl<<endl; 
            if(data.size()<=6)
			{
				data.clear();
				continue;
			} 
            if(flag_text==1)	 lateData[weekNumber].push_back(data);//�˳����гٵ����ݾͰ����ݷŽ��ٵ�����������
            else if(flag_text==0) absentData[weekNumber].push_back(data);
            else if(flag_text==-1) leaveData[weekNumber].push_back(data);
            data.clear();
            continue;
        }
         if(studentName=="1")
        {
            choice=1;
            data.erase(data.end() - 1);
            cout<<">>"<<currentClass<<"��"<<str<<"������ȫ��¼����ϣ�"<<endl;
            cout<<"-----------------------------------------"<<endl;
            if(data.size()<=6)
			{
				data.clear();
				continue;
			}
            cout<<currentClass<<"�����¼�룺"<<endl;
            if(flag_text==1)	 lateData[weekNumber].push_back(data);//�˳����гٵ����ݾͰ����ݷŽ��ٵ�����������
            else if(flag_text==0) absentData[weekNumber].push_back(data);
            else if(flag_text==-1) leaveData[weekNumber].push_back(data);
            data.clear();
            flag_text=0;
            data = currentClass + "��:";
            continue;
        }
     
        if(studentName=="2")
        {
            choice=2;//�Ǻ���������Ϊ�ٵ�
            data.erase(data.end() - 1);
            //data.erase(data.end() - 2);
            cout<<">>"<<currentClass<<"��"<<str<<"������ȫ��¼����ϣ�"<<endl;
            cout<<"-----------------------------------------"<<endl;
            cout<<currentClass<<"��ٵ�¼�룺"<<endl;
            if(data.size()<=6)
			{
				data.clear();
				continue;
			}
            if(flag_text==1)	 lateData[weekNumber].push_back(data);//�˳����гٵ����ݾͰ����ݷŽ��ٵ�����������
            else if(flag_text==0) absentData[weekNumber].push_back(data);
            else if(flag_text==-1) leaveData[weekNumber].push_back(data);
            data.clear();
            flag_text=1;
            data = currentClass + "��:";
            continue;
        }
        if(studentName=="3")
        {
            choice=3;
            data.erase(data.end() - 1);
            cout<<">>"<<currentClass<<"��"<<str<<"������ȫ��¼����ϣ�"<<endl;
            cout<<"-----------------------------------------"<<endl;
            if(data.size()<=6)
			{
				data.clear();
				continue;
			}
            cout<<currentClass<<"�����¼�룺"<<endl;
            if(flag_text==1)	 lateData[weekNumber].push_back(data);//�˳����гٵ����ݾͰ����ݷŽ��ٵ�����������
            else if(flag_text==0) absentData[weekNumber].push_back(data);
            else if(flag_text==-1) leaveData[weekNumber].push_back(data);
            data.clear();
            flag_text=-1;
            data = currentClass + "��:";
            continue;
        }
        if(choice==1||choice==2)
        {
            cout << "���ںͽڴΣ�";
            cin.ignore();
            getline(cin,dayTime);
            data += studentName + ":" + dayTime;
            int len=data.size()-1;
            if(data[len]==' ')		data.erase(data.end() - 1); 
        }else
        {
        	data += studentName;
        }
        data += ",";
        cnt = 1;  // ��־λ�����ú����Ϊ1
        //} 
    }


    // д�����ݵ��ı��ļ�
    writeDataToFile("data.txt", weekNumber, absentData, lateData,leaveData);
	// ���û�б�¼��İ༶
    cout << "-----------------------------------------" << endl;
    cout << "���°༶δ��¼�룺" << endl;
    int cnt_p=0;
    for (const string& className : classList) {
        if (recordedClasses.find(className) == recordedClasses.end()) {
        	++cnt_p;
            cout << className << "\t";
            if(cnt_p%5==0)	cout<<endl;
        }
    }
    cout<<endl;
    system("pause");
    return 0;
}
    
