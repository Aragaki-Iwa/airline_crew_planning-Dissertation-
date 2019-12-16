#ifndef CSV_READER_H
#define CSV_READER_H
#include <string>
#include <memory>
#include <vector>
#include <map>

using namespace std;

#define TableSeparator "------"

	//csvParser�ӿ���
	class csvParser {
	public:
		virtual string toCsv(vector<string>& headers, void* obj) = 0;
		//virtual void fromCsv(vector<string>& headers, std::string line, void* obj) = 0;
		virtual void fromCsv(vector<string>& headers, int index, char* value, void* obj) = 0;
		virtual vector<string>& getDefaultHeaders() = 0;
		virtual void* createInstance() = 0;
		virtual void deleteInstance(void* obj) = 0;
		bool isAvailable() { return true; }
		virtual void init(vector<string>& headers) = 0;//derived by parsers
	};

extern long long dbgTestTimer;

#define SPLITER_BUF_SIZE 16 * 1024
#define SPLITER_WORD_SIZE 1024
	class csvSpliter {
	public:
		csvSpliter(char delim = '^');
		char * getNextWord(); //EOL: return null, Other: return word
		char * getBuf();      //for istream.getline()
		int count();
		void reset();         //clear buf/word
	private:
		char buf[SPLITER_BUF_SIZE];
		char word[SPLITER_WORD_SIZE];
		int index = 0;
		char delim;           //word separator
	};

	//--------------------------------
	//��дcsv��
	//1 tableParserMap��tableName -> parser
	//2 getParser������tableName��ȡparser
	//3 createInstance������tableName����parser��������ʵ��
	//4 readMutiTableCsv����ȡ���csv�ļ��������䰴 -----����
	//5 datas������������ݴ��룬��tableName����
	//6 ��ȡ��ʽ
	//  ------ TableName1: ...
	//  tableHeader1, tableHeader2, ...
	//  ...
	//  ...
	//  ------ TableName2: ...
	//  tableHeaderA, tableHeaderB, ...
	//7 ʹ�÷���
	//  ʵ�� csvParser�࣬������Ӧ������ 
	//--------------------------------
	class csvReader {
	public:
		void readCsvAttribute(string filepath);
		void readMutiTableCsv(string filepath);
		void readMutiTableCsvByMemMap(string filepath);
		void write(ofstream& outfile, string tableName, vector<void*>& list, shared_ptr<csvParser> parser);
		virtual shared_ptr<csvParser> getParser(string tableName) = 0;
		virtual string getParserName(string tableName) = 0;
		map<string, shared_ptr<csvParser>> tableParserMap;
		map<string, vector<void*>> datas;
		void clear();
	private:
		string readLine(ifstream& in);
		void parseTableName(string& line);
		void parserLine(string& line);
		void parserLine(const char* line);
		string table;
		vector<string> headers;
		shared_ptr<csvParser> parser;
		csvSpliter spliter; //delim: ^
	};

#endif//CSV_READER_H