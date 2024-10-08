/**
 * (c) 2024 Houssem Guissouma.
 * Licensed under the BSD-3-Clause License.
 *
 * @file utils/src/data_node.cpp
 * @brief Implementation of the class DataNode.
 */
#include "icarus/utils/data_node.h"

#include <fstream>
#include <iostream>

#include "icarus/utils/system_ops.h"

namespace icarus {

// ================================
// NodeIterator class
// ================================

DataNode::NodeIterator::NodeIterator(std::shared_ptr<ryml::Tree> tree, size_t node_id)
        : tree_(tree), node_id_(node_id) {}

DataNode::NodeIterator& DataNode::NodeIterator::operator++() {
    node_id_ = tree_->next_sibling(node_id_);
    return *this;
}

DataNode DataNode::NodeIterator::operator*() const {
    return DataNode(tree_, node_id_);
}

bool DataNode::NodeIterator::operator!=(const NodeIterator& other) const {
    return (node_id_ != other.node_id_) || (tree_ != other.tree_);
}

// End NodeIterator class =========

DataNode::DataNode(Type type)
        : tree_(std::make_shared<ryml::Tree>()),
          node_id_(tree_->root_id()) {
    if (type == Type::kMap) {
		tree_->rootref() |= ryml::MAP;
    } else {
        tree_->rootref() |= ryml::SEQ;
    }
}

DataNode::DataNode(const std::string& file_path)
        : tree_(std::make_shared<ryml::Tree>()) {
    parseFromFile(file_path);
}

DataNode::DataNode(const DataNode& other)
        : tree_(other.tree_), node_id_(other.node_id_) {}

DataNode::DataNode(DataNode&& other) noexcept
        : tree_(std::move(other.tree_)), node_id_(other.node_id_) {}

void DataNode::parseFromStr(const std::string& content) {
    try {
        ryml::parse_in_arena(ryml::to_csubstr(content), *tree_);
        node_id_ = tree_->root_id();
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Parsing error: " + std::string(e.what()));
    }
}

void DataNode::parseFromFile(const std::string& file_path) {
	std::string content = utils::getFileContent(file_path);
	parseFromStr(content);
}

DataNode::NodeIterator DataNode::begin() const {
    return NodeIterator(tree_, tree_->first_child(node_id_));
}

DataNode::NodeIterator DataNode::end() const {
    return NodeIterator(tree_, ryml::NONE);
}

DataNode& DataNode::operator=(const char* value) {
    tree_->ref(node_id_) = value;
    return *this;
}

DataNode DataNode::operator=(const DataNode& other) {
    if (this != &other) {
        tree_ = other.tree_;
        node_id_ = other.node_id_;
    }
    return *this;
}

DataNode DataNode::operator[](const std::string& key) const {
    if (!isMap()) {
        throw std::runtime_error("Node is not a map.");
    }

    ryml::csubstr ryml_key = ryml::to_csubstr(key);
    if (!tree_->has_child(node_id_, ryml_key)) {
        // Return a None node if the key does not exist
        return DataNode(nullptr, ryml::NONE);
    }
    return DataNode(tree_, tree_->find_child(node_id_, ryml_key));
}

DataNode DataNode::operator[](const std::string& key) {
    if (!isMap()) {
        throw std::runtime_error("Node is not a map.");
	}

    ryml::csubstr ryml_key = ryml::to_csubstr(key);
    if (!tree_->has_child(node_id_, ryml_key)) {
        tree_->ref(node_id_).append_child() << ryml::key(key);
	}

    return DataNode(tree_, tree_->find_child(node_id_, ryml_key));
}

DataNode DataNode::operator[](size_t index) const {
    if (!isSeq()) {
        throw std::runtime_error("Node is not a sequence.");
    }
    if (index >= tree_->num_children(node_id_)) {
        throw std::runtime_error("Index out of bounds.");
    } else
    return DataNode(tree_, tree_->child(node_id_, index));
}

DataNode DataNode::operator[](size_t index) {
    if (!isSeq()) {
        throw std::runtime_error("Node is not a sequence.");
    }

    // Extend the sequence if the index is out of bounds
    if (index >= tree_->num_children(node_id_)) {
        tree_->ref(node_id_).append_child();
    }

    return DataNode(tree_, tree_->child(node_id_, index));
}

bool DataNode::isValid() const {
    return (tree_ != nullptr) && (node_id_ != ryml::NONE);
}

bool DataNode::isMap() const {
    return tree_->is_map(node_id_);
}

bool DataNode::isSeq() const {
    return tree_->is_seq(node_id_);
}

bool DataNode::isVal() const {
	return tree_->is_val(node_id_);
}

bool DataNode::isKeyVal() const {
    return tree_->is_keyval(node_id_);
}

std::string DataNode::getKey() const {
    if (tree_->has_key(node_id_)) {
        return toStr(tree_->key(node_id_));
    } else {
        std::cerr << "Warning: node has no key!" << std::endl;
        return "";
    }
}

DataNode DataNode::first() const {
    return DataNode(tree_, tree_->first_child(node_id_));
}

bool DataNode::hasChild(const char* key) const {
	return isMap() && tree_->has_child(node_id_, key);
}

size_t DataNode::getNumChildren() const {
	return tree_->num_children(node_id_);
}

void DataNode::print(Format format) const {
    std::cout << "============================\n";

    if (format == Format::kYaml) {
        std::cout << " Node content (YAML): \n"
                  << "============================\n"
                  << emitYaml() << std::endl;
    } else {
        std::cout << " Node content (JSON): \n"
                  << "============================\n"
                  << emitJson() << std::endl;
    }

    std::cout << "============================\n" << std::endl;
}

void DataNode::writeToFile(const std::string& output_file_path, Format format) const {
    std::ofstream file(output_file_path);
    if (file) {
        if (format == Format::kYaml) {
            file << emitYaml();
        } else {
            file << emitJson();
        }
        file.close();
    } else {
        throw std::runtime_error("Cannot open file for writing: " + output_file_path);
    }
}

DataNode DataNode::getMapFromSeq(const std::string& key) const {
    if (!isSeq()) {
        throw std::runtime_error("Node is not a sequence.");
    }

    // Iterate over the sequence elements and search for map with the given key
    for (size_t id = tree_->first_child(node_id_); id != ryml::NONE; 
         id = tree_->next_sibling(id)) {
        if (tree_->is_map(id)) {
            size_t child_id = tree_->find_child(id, key.c_str());

            if (child_id != ryml::NONE) {
                return DataNode(tree_, child_id);
            }
        }
    }

    throw std::runtime_error("Key not found in the sequence.");
}

std::vector<std::string> DataNode::getSeqStrings() {
    std::vector<std::string> seq_strings;

    // Check if the node is a sequence
    if (isSeq()) {
        for (size_t child_id = tree_->first_child(node_id_); child_id != ryml::NONE;
             child_id = tree_->next_sibling(child_id)) {
			auto& child_str = tree_->val(child_id);
			std::string element_str(child_str.begin(), child_str.end());
            seq_strings.push_back(element_str);
        }
    }
    else {
        throw std::runtime_error("The provided YAML node is not a sequence.");
    }

    return seq_strings;
}

DataNode::DataNode(std::shared_ptr<ryml::Tree> tree, size_t node_id)
        : tree_(tree),
	      node_id_(node_id) {}


std::string DataNode::emitYaml() const {
	if (!isValid()) {
		throw std::runtime_error("Invalid YAML tree");
	}
	return ryml::emitrs_yaml<std::string>(*tree_, node_id_);
}

std::string DataNode::emitJson() const {
    if (!isValid()) {
		throw std::runtime_error("Invalid YAML tree");
	}
	return ryml::emitrs_json<std::string>(*tree_, node_id_);
}

std::string DataNode::toStr(const c4::csubstr& buffer) const {
    std::string key;
    ryml::from_chars(buffer, &key);
    return key;
}

} // namespace icarus
