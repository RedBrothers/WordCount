#include "base_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>


std::string BaseManager::read_file(const std::string &file_name) {
	std::ifstream		in_file;
	std::stringstream	str_stream;
	std::string			file_str;

	in_file.open(file_name);
	str_stream << in_file.rdbuf();
	file_str = str_stream.str();

	return file_str;
}

std::vector<std::string> BaseManager::split_file(const std::string &file, size_t n_chunks) {
	std::vector<std::string>	chunks;
	std::vector<size_t>			indices;
	size_t						estimated_chunk_len;


	estimated_chunk_len = static_cast<size_t>( file.length() / n_chunks );

	for (size_t i = 0; i < n_chunks; ++i) {
		indices.push_back(i * estimated_chunk_len);
	}
	indices.push_back(file.length());

	for (size_t i = 0; i < indices.size() - 1; ++i) {
		while (indices[i] >= 0 && file[indices[i]] != ' ') {
			--indices[i];
		}
	}

	for (size_t i = 0; i < indices.size() - 1; ++i) {
		std::string	chunk = file.substr(indices[i], indices[i + 1]);
		chunks.push_back(chunk);

		std::cout << chunk << std::endl;
	}

	return chunks;
}
