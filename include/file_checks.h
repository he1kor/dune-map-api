/**
 * \file
 * \brief Contains all checks for files that throw exceptions if it is not passed.
*/

#pragma once
#include <fstream>

/**
 * \brief Throw error and returns false if file is opened.
 * \param file checked file.
 * \return False is file is opened, else True.
*/
bool checkOpenedError(std::fstream& file);

/**
 * \brief Throw error and returns false if file is not opened.
 * \param file checked file.
 * \return False is file is not opened, else True.
*/
bool checkNotOpenedError(std::fstream& file);

/**
 * \brief Throw error, closes file and returns false if fstream got any issues.
 * \param file checked file.
 * \return False is file has issues, else True.
*/
bool checkFileIssues(std::fstream& file);

/**
 * \brief Throw error and returns false if file is opened.
 * \param file checked input file.
 * \return False is file is opened, else True.
*/
bool checkOpenedError(std::ifstream& file);

/**
 * \brief Throw error and returns false if file is not opened.
 * \param file checked input file.
 * \return False is file is not opened, else True.
*/
bool checkNotOpenedError(std::ifstream& file);

/**
 * \brief Throw error, closes file and returns false if fstream got any issues.
 * \param file checked input file.
 * \return False is file has issues, else True.
*/
bool checkFileIssues(std::ifstream& file);

/**
 * \brief Throw error and returns false if provided file path doesn't have provided extension.
 * \param file_path file path to check.
 * \param file_extension expected extension.
 * \return False is file extension is not equal to provided, else True.
*/
bool checkFileExtensionError(const char file_path[], const char file_extension[]);

/**
 * \brief Throw error and returns false if provided file path lead to some file.
 * \param file_path file path to check.
 * \return False if file exists, else True.
*/
bool checkFileExistError(const char file_path[]);

/**
 * \brief Throw error and returns false if provided file path doesn't lead to any file.
 * \param file_path file path to check.
 * \return False if file doesn't exist, else True.
*/
bool checkFileNotExistError(const char file_path[]);