#pragma once
#ifndef CONF_PARAM_H_
#define CONF_PARAM_H_

/*****************************************************************************
*  Open Mathmatical Optimization library                                     *
*  Copyright (C) 2019 Dubing.Xiang.                                          *
*                                                                            *
*                                                                            *
*  @file     conf-param.h                                                       *
*  @brief    ��ȡ��س����Ȳ��������ڿ�������                                                    *
*  Details.                                                                  *
*                                                                            *
*  @author   Dubing.Xiang                                                    *
*  @email    1059361402@qq.com                                               *
*  @version  1.0.0.1(�汾��)                                                 *
*  @date     2019-12-18                                                      *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*****************************************************************************/
#include <map>
#include <string>
#include <iostream>
#include <io.h>
#include <direct.h>
#include <windows.h>

namespace util {
	
	class WorkDirConfig;
	class DirectoryManager;

	/**
	 * @class ConfigReader
	 * @brief ��ȡ��������
	 *
	**/
	class ConfigReader {
	public:
		ConfigReader(WorkDirConfig* config);
		~ConfigReader();

		/*void read(const char* filePathSeperator, const char* fileNameSeperator,
			const char* inputDataDir, const char* outputDataDir,
			const char* finalScheduleDirName,
			const char* outputPeriodDirName,
			const char* outputCplexDirName) {
			this->_work_dir_config->setConfig(filePathSeperator, fileNameSeperator,
				inputDataDir, outputDataDir,
				finalScheduleDirName,
				outputPeriodDirName,
				outputCplexDirName);
		}*/


		void readDefault();
		

		/*
		 * @brief TODO
		 * @detail
		 *
		 * @param
		 *
		 * @return
		 *     @retval ����ֵ˵��
		 * @attention
		 * @warning
		 * @exception
		 *
		 **/
		void read(const std::string& configFile);

		

		/*
		 * @brief ����������������ļ���
		 * @detail
		 *
		 * @param
		 *
		 * @return
		 *     @retval ����ֵ˵��
		 * @attention
		 * @warning
		 * @exception
		 *
		 **/
		void prepareWorkDir();


	private:
		WorkDirConfig* _work_dir_config = nullptr;
	};


	class WorkDirConfig {
		/*
			 * data
			 * --input
			 * --output
			 *   --whole_horizion
			 *     --schedule_whole_horizion.txt
			 *     --crew_workload_whole_horizion.txt
			 *   --period
			 *     --period_1
			 *       --schedule_period_1.txt
			 *       --crew_workload_period_1.txt
			 *       --cplex_file
			 *         --model_iter_1.lp
			 *         --soln_iter_1.sln
			 *     --period_2
			 *     --period_n
			 *
			 */
	public:
		
		static WorkDirConfig& getInstance();
		void setConfig(const char* filePathSeperator, const char* fileNameSeperator,
			const char* inputDataDir, const char* outputDataDir,
			const char* finalScheduleDirName,
			const char* outputPeriodDirName,
			const char* outputCplexDirName);
		void setDefaultConfig();

		const std::string& getFilePathSeperator()const;
		const std::string& getFileNameSeperator()const;
		const std::string& getInputDataDir()const;
		const std::string& getOutputDataDir()const;
		const std::string& getFinalScheduleDirName()const;
		const std::string& getPeriodFileDirName()const;
		const std::string& getCplexFileDirName()const;

		std::map<const std::string, const std::string> OutputFileInCalculatingProcess_Map;

	private:
		WorkDirConfig() {}; //˽�й��캯��
		//WorkDirConfig(const WorkDirConfig& other); //�������캯��
		//WorkDirConfig& operator=(const WorkDirConfig &);
		//~WorkDirConfig() ;

		std::string _filePathSeperator = "/"; //< �ļ�·���ָ�����Ĭ��Ϊ"/"
		std::string _fileNameSeperator = "_"; //< �ļ����ָ�����Ĭ��Ϊ"_"
		std::string _inputDataDir = "data/input"; //< ���������ļ��У����·����Ĭ��Ϊ"data/input"
		std::string _outputDataDir = "data/output"; //< ��������ļ��У����·����Ĭ��Ϊ"data/output"

		std::string _outputFinalScheduleDirName = "whole_horizon"; //< ��������ƻ��ļ����ļ�������
		std::string _outputPeriodFileDirName = "period"; //< ÿ���Ż�period����������ļ�������
		std::string _outputCplexFileDirName = "cplex_file"; //< cplex��ص���������ļ�������

	};


	/**
		 * @class DirectoryManager
		 * @brief �ļ�����
		 *
		 * ��������Լ����������ļ���ŵ��ļ���
		 *
		**/
	class DirectoryManager
	{
	public:
		DirectoryManager() {};
		~DirectoryManager() {};
		static const char* kFilePathSeperator_db;

		static bool createDir(const std::string& path = "defaultFolder");

		static bool pathExists(const char* path);

	private:


	};
	


	/**
	 * @class 
	 * @brief �����Ĳ��� TODO
	 *
	 * ��������������������ѡ�񲿷�crew��ĳ������
	 *
	**/
	class ExampleConfig {


	};
}


#endif // !CONF_PARAM_H_
